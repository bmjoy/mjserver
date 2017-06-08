#include "MemoryServerStdafx.h"


#include <vector>
#include <signal.h>
#include <string>

using namespace std;


#ifndef WIN32
#include <sys/resource.h>
#endif

initialiseSingleton(CGameDataBaseServer);

//Database* sLandSQL;
Database* sGameinfoSQL;
Database* sGetdataSQL;

#define BANNER "BjdGame %s %s/%s-%s (%s) :: AccoutMemory"

#ifndef WIN32
#include <sched.h>
#endif

bool StartConsoleListener();
void CloseConsoleListener();
ThreadBase* GetConsoleListener();

Arcemu::Threading::AtomicBoolean mrunning(true);

/*** Signal Handler ***/
void _OnSignal(int s)
{
	switch(s)
	{
#ifndef WIN32
		case SIGHUP:
			{
				LOG_DETAIL("Received SIGHUP signal, reloading accounts.");
				//AccountMgr::getSingleton().ReloadAccounts(true);
			}
			break;
#endif
		case SIGINT:
		case SIGTERM:
		case SIGABRT:
#ifdef _WIN32
		case SIGBREAK:
#endif
			mrunning.SetVal(false);
			break;
	}

	signal(s, _OnSignal);
}


bool startdb()
{
	string lhostname, lusername, lpassword, ldatabase;
	int lport = 0;
	// Configure Main Database

	bool result;

	// Set up reusable parameter checks for each parameter
	// Note that the Config.MainConfig.Get[$type] methods returns boolean value and not $type

	bool existsUsername = Config.MainConfig.GetString("AccountDatabase", "Username", &lusername);
	bool existsPassword = Config.MainConfig.GetString("AccountDatabase", "Password", &lpassword);
	bool existsHostname = Config.MainConfig.GetString("AccountDatabase", "Hostname", &lhostname);
	bool existsName     = Config.MainConfig.GetString("AccountDatabase", "Name",     &ldatabase);
	bool existsPort     = Config.MainConfig.GetInt("AccountDatabase", "Port",     &lport);

	// Configure Logon Database...

	// logical AND every parameter to ensure we catch any error
	result = existsUsername && existsPassword && existsHostname && existsName && existsPort;

	if(!result)
	{
		string errorMessage = "sql: Certain <AccountDatabase> parameters not found in configs\\accountmem.conf \r\n";
		if(!(existsHostname || existsUsername || existsPassword  ||
			existsName     || existsPort))
		{
			errorMessage += "  Double check that you have remembered the entire <AccountDatabase> tag.\r\n";
			errorMessage += "  All parameters missing. It is possible you forgot the first '<' character.\r\n";
		}
		else
		{
			errorMessage +=                        "  Missing paramer(s):\r\n";
			if(!existsHostname) { errorMessage += "    Hostname\r\n" ; }
			if(!existsUsername) { errorMessage += "    Username\r\n" ; }
			if(!existsPassword) { errorMessage += "    Password\r\n" ; }
			if(!existsName) { errorMessage += "    Name\r\n"; }
			if(!existsPort) { errorMessage += "    Port\r\n"; }
		}

		LOG_ERROR(errorMessage.c_str());
		return false;
	}

	//sLandSQL = Database::CreateDatabaseInterface();
	sGameinfoSQL = Database::CreateDatabaseInterface();
	sGetdataSQL = Database::CreateDatabaseInterface();

	// Initialize it
	//if(!sLandSQL->Initialize(lhostname.c_str(), (unsigned int)lport, lusername.c_str(),
	//	lpassword.c_str(), ldatabase.c_str(), Config.MainConfig.GetIntDefault("AccountDatabase", "LandConnectionCount", 1),
	//	16384))
	//{
	//	LOG_ERROR("sql: Logon database initialization failed. Exiting.");
	//	//return false;
	//}

	if(!sGameinfoSQL->Initialize(lhostname.c_str(), (unsigned int)lport, lusername.c_str(),
		lpassword.c_str(), "Bjd_pdk", 5,
		16384))
	{
		LOG_ERROR("sql: Logon database initialization failed. Exiting.");
		return false;
	}

	if(!sGetdataSQL->Initialize(lhostname.c_str(), (unsigned int)lport, lusername.c_str(),
		lpassword.c_str(), "Bjd_account", Config.MainConfig.GetIntDefault("AccountDatabase", "GetdataConnectionCount", 5),
		16384))
	{
		LOG_ERROR("sql: Logon database initialization failed. Exiting.");
		return false;
	}

	return true;
}

int main()
{
	new CGameDataBaseServer;

	// Run!
	CGameDataBaseServer::getSingleton().Run();
	delete CGameDataBaseServer::getSingletonPtr();
}


#define DEF_VALUE_NOT_SET 0xDEADBEEF

Mutex m_allowedIpLock;
std::vector<AllowedIP> m_allowedIps;


bool Rehash()
{
	char* config_file = (char*)"configs/accountmem.conf";
	if(!Config.MainConfig.SetSource(config_file))
	{
		LOG_ERROR("Config file could not be rehashed.");
		return false;
	}

	return true;
}

void CGameDataBaseServer::Run()
{
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);
	char* config_file = (char*)"configs/accountmem.conf";
	
	sLog.Init(2, ACCOUNTMEM_LOG);
	
	sLog.outBasic(BANNER, BUILD_TAG, BUILD_HASH_STR, CONFIG, PLATFORM_TEXT, ARCH);
	sLog.outErrorSilent(BANNER, BUILD_TAG, BUILD_HASH_STR, CONFIG, PLATFORM_TEXT, ARCH); // Echo off.

	InitRandomNumberGenerators();
	
	if(!Rehash())
	{
		sLog.Close();
		return;
	}
	
	sLog.SetFileLoggingLevel(Config.MainConfig.GetIntDefault("LogLevel", "File", 0));

	// 线程池开启
	ThreadPool.Startup();

	// 连接数据库
	if(!startdb())
	{
		sLog.Close();
		return;
	}
	
	////创建事件类
	//	new EventMgr;

	////创建脚本管理
	//	new ScriptMgr;

	// 创建协议处理管理类
	new CProcessManager; 

	// 创建会话管理类
	new CSessionsManager;

	// 创建自定义单例类
	new CAccountMgr;

	// 开启游戏主控制循环线程
	CGameRunnable* gr = new CGameRunnable();
	ThreadPool.ExecuteTask(gr);

	// 开启控制台线程
	//ConsoleThread* console = new ConsoleThread();
	//ThreadPool.ExecuteTask(console);
	
	// 注册协议类
	RegisterProtocols();

	// 创建socket管理
	new SocketMgr;
	new SocketGarbageCollector;
	
	sSocketMgr.SpawnWorkerThreads();

	////载入脚本
	//	sScriptMgr.LoadScripts();

	// 开启控制台监听		
	if(StartConsoleListener())
	{
#ifdef WIN32
		ThreadPool.ExecuteTask(GetConsoleListener());
#endif
		Log.Notice("RemoteConsole", "Now open.");
	}
	else
	{
		Log.Warning("RemoteConsole", "Not enabled or failed listen.");
	}
	


	// 连接其他服务器管理
	//new ServerConnect();
	//sServerConnect.Startup();

	// 接收客户端连接管理
	string shost = Config.MainConfig.GetStringDefault("Listen", "ISHost", "0.0.0.0");
	uint32 sport = Config.MainConfig.GetIntDefault("Listen", "ServerPort", 8097);
	ListenSocket<CServerSocket> * sl = new ListenSocket<CServerSocket>(shost.c_str(), sport);

	bool intersockcreated = sl->IsOpen();
	
	if(intersockcreated)
	{
#ifdef WIN32
		ThreadPool.ExecuteTask(sl);
#endif
		// hook signals
		sLog.outString("Hooking signals...");
		signal(SIGINT, _OnSignal);
		signal(SIGTERM, _OnSignal);
		signal(SIGABRT, _OnSignal);
#ifdef _WIN32
		signal(SIGBREAK, _OnSignal);
#else
		signal(SIGHUP, _OnSignal);
#endif

		uint32 loop_counter = 0;

		sLog.outString("Success! Ready for connections");
		while(mrunning.GetVal())
		{
			loop_counter++;
			//if (!(loop_counter % 5))	// 20s
			//{
			//	sAccountMgr.CheckPrimarySaveData();
			//}

			//if (!(loop_counter % 200))	// 200s
			//{
			//	sAccountMgr.CheckSecondaryData();
			//}
			
			if(!(loop_counter % 300))	// 5mins
			{
				ThreadPool.IntegrityCheck();
			}
				

			if(!(loop_counter % 5))
			{
				UNIXTIME = time(NULL);
				g_localTime = *localtime(&UNIXTIME);
			}

			Arcemu::Sleep(1000);
		}

		sLog.outString("Shutting down...");
		signal(SIGINT, 0);
		signal(SIGTERM, 0);
		signal(SIGABRT, 0);
#ifdef _WIN32
		signal(SIGBREAK, 0);
#else
		signal(SIGHUP, 0);
#endif
	}
	else
	{
		LOG_ERROR("Error creating sockets. Shutting down...");
	}

	gr->SetThreadState(THREADSTATE_TERMINATE);

	//console->terminate();
	//delete console;

	// 结束数据库线程
	//sLandSQL->EndThreads();
	sGameinfoSQL->EndThreads();
	sGetdataSQL->EndThreads();

	sl->Close();

	CloseConsoleListener();

	
#ifdef WIN32
	sSocketMgr.ShutdownThreads();
#endif
	sSocketMgr.CloseAll();

	ThreadPool.Shutdown();

	// 解除注册协议类
	UnregisterProtocols();

	delete sl;

	//delete ScriptMgr::getSingletonPtr();
	//delete EventMgr::getSingletonPtr();

	//删除数据库连接类
	////if(sLandSQL != NULL)
	////	delete sLandSQL;
	if(sGameinfoSQL != NULL)
		delete sGameinfoSQL;
	if(sGetdataSQL != NULL)
		delete sGetdataSQL;

	Database::CleanupLibs();

	// 删除协议处理管理类
	delete CProcessManager::getSingletonPtr();

	//删除socket管理类		
	delete CSessionsManager::getSingletonPtr();
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();

	//删除日志类
	Log.Close();

	// 删除自定义单例类
	delete CAccountMgr::getSingletonPtr();

	//关闭与其他服务器的连接
	//delete ServerConnect::getSingletonPtr();
	
	delete gr;
	
	delete CGameDataBaseServer::getSingletonPtr();
}

void OnCrash(bool Terminate)
{

}
