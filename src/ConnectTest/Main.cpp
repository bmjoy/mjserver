#include "ConnectTestStdafx.h"
#include "person.pb.h"

#include <vector>
#include <signal.h>
#include <string>
#include <iostream>

using namespace std;


#ifndef WIN32
#include <sys/resource.h>
#endif

initialiseSingleton(CConnectTestServer);


#define BANNER "BjdGame %s %s/%s-%s (%s) :: CConnectTestServer"

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


int main()
{
	//string serialStr;
	//Person  ps;
	//ps.set_id(10);
	//ps.set_name("zhou");
	//ps.set_email("ffff");
	//bool _b = ps.SerializePartialToString(&serialStr);


	//std::cout << serialStr;
	//Person  ps2;
	//ps2.ParseFromString(serialStr);


	new CConnectTestServer;

	CConnectTestServer::getSingleton().Run();
	delete CConnectTestServer::getSingletonPtr();
}


#define DEF_VALUE_NOT_SET 0xDEADBEEF

Mutex m_allowedIpLock;
std::vector<AllowedIP> m_allowedIps;


bool Rehash()
{
										
	char* config_file = (char*)"configs/connecttest.conf";
	if(!Config.MainConfig.SetSource(config_file))
	{
		LOG_ERROR("Config file could not be rehashed.");
		return false;
	}

	return true;
}

void CConnectTestServer::Run()
{
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);
	char* config_file = (char*)"configs/connecttest.conf";
	
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

	// 创建会话管理类
	new CSessionsManager;

	// 创建协议处理管理类
	new CProcessManager;

	// 创建协议处理管理类
	new CModuleManager;

	new CRoleManager;

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

//	// 开启控制台监听		
//	if(StartConsoleListener())
//	{
//#ifdef WIN32
//		ThreadPool.ExecuteTask(GetConsoleListener());
//#endif
//		Log.Notice("RemoteConsole", "Now open.");
//	}
//	else
//	{
//		Log.Warning("RemoteConsole", "Not enabled or failed listen.");
//	}

	// 连接其他服务器管理
	//new ServerConnect();
	//sServerConnect.Startup();

	// 接收客户端连接管理
	string shost = Config.MainConfig.GetStringDefault("Listen", "ISHost", "0.0.0.0");
	uint32 sport = Config.MainConfig.GetIntDefault("Listen", "ServerPort", 8096);
	ListenSocket<CServerSocket> * sl = new ListenSocket<CServerSocket>(shost.c_str(), sport);			// 供GameFrame连接
	//ListenSocket<CServerSocket> * sl2 = new ListenSocket<CServerSocket>(shost.c_str(), sport+100);		// 供HttpServer连接

	bool intersockcreated = sl->IsOpen();
	//bool intersockcreated2 = sl2->IsOpen();
	
	if(intersockcreated /*&& intersockcreated2*/)
	{
#ifdef WIN32
		ThreadPool.ExecuteTask(sl);
		//ThreadPool.ExecuteTask(sl2);
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

	sl->Close();
	//sl2->Close();

	//CloseConsoleListener();

	
#ifdef WIN32
	sSocketMgr.ShutdownThreads();
#endif
	sSocketMgr.CloseAll();

	ThreadPool.Shutdown();

	// 解除注册协议类
	UnregisterProtocols();

	delete sl;
	//delete sl2;

	// 删除协议处理管理类
	delete CProcessManager::getSingletonPtr();
	delete CModuleManager::getSingletonPtr();
	delete CRoleManager::getSingletonPtr();


	//删除socket管理类		
	delete CSessionsManager::getSingletonPtr();
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();

	//删除日志类
	Log.Close();

	// 删除自定义单例类
	//delete CAccountManager::getSingletonPtr();
	
	//关闭与其他服务器的连接

	delete gr;
	
	delete CConnectTestServer::getSingletonPtr();
}

void OnCrash(bool Terminate)
{

}
