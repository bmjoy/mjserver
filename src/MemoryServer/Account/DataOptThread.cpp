#include "MemoryServerStdafx.h"
#include "CAccount_ATOS_Info.h"

#include "crc32.h"

#define DATAOPT_UPDATE_DELAY 50

CDataOptThread::CDataOptThread()
{
	opt_Result = 0;
	
	SetThreadState(THREADSTATE_PAUSED);
	m_pAccount = new Account;
	m_bHasFriendMsg = false;
}

CDataOptThread::~CDataOptThread()
{
	delete m_pAccount;
}

bool CDataOptThread::run()
{
	SetThreadName("CDataOptThread");

	uint32 LastDataDeal = getMSTime();
	
	while(GetThreadState() != THREADSTATE_TERMINATE)
	{
		if(GetThreadState() == THREADSTATE_PAUSED)
		{
			while(GetThreadState() == THREADSTATE_PAUSED)
			{
/*				if (opt_type==3)
				{
					sFriendModule.Update(0);
				}	*/			
				Arcemu::Sleep(200);
			}
		}

		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_BUSY);

		uint32 diff;
		//calc time passed
		uint32 now, execution_start;
		now = getMSTime();
		execution_start = now;

		if(now < LastDataDeal) //overrun
			diff = DATAOPT_UPDATE_DELAY;
		else
			diff = now - LastDataDeal;

		LastDataDeal = now;

		if (opt_type == 1)
		{
			DoGetAccountData();
		}
		else if (opt_type == 2)
		{
			DoSavePrimaryAccountData();
		}
		else if (opt_type == 3)
		{
			//DoProcessFriendData();
		}
		

		now = getMSTime();
		//we have to wait now

		if(execution_start > now)//overrun
			diff = DATAOPT_UPDATE_DELAY - now;

		else
			diff = now - execution_start; //time used for updating

		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_PAUSED);

		/*This is execution time compensating system
			if execution took more than default delay
			no need to make this sleep*/
		if(diff < DATAOPT_UPDATE_DELAY)
			Arcemu::Sleep(DATAOPT_UPDATE_DELAY - diff);
	}

	return true;
}

void CDataOptThread::DoGetAccountData()
{
	char bufname[200];
	sprintf(bufname,"%s",preget_account_name.c_str());

	if ( (unsigned int)strlen(preget_account_name.c_str()) > 16 )
	{
		return;
	}
	
	
	//LOG_ERROR("DoGetAccountData_start '%s'",preget_account_name.c_str());
	unsigned long account_hash = crc32(preget_account_name.c_str(), (unsigned int)strlen(preget_account_name.c_str()));
	
	uint8 SqlIndex = account_hash%10;

	char buf[200];

	unsigned long phoneNum = atol(preget_account_name.c_str());

	if (bufname[0] != 33)
	{
		sprintf(buf,"Select uid,account,psw From landinfo%u where account = '%s' ",SqlIndex,preget_account_name.c_str());
	}else
	{
		sprintf(buf,"Select uid,account,psw From phone_account%u where phone = '%u' ",phoneNum%10,phoneNum);
	}

	m_pAccount->account_id = 0;

	QueryResult* land = sGetdataSQL->Query(buf);
	
	if (!land)
	{
		return;
	}

	Field* field_land = land->Fetch();
	if (!field_land)
	{
		return;
	}
	uint32 accID =  field_land[0].GetUInt32();
	if (accID == 0)
	{
		return;
	}
	std::string accname =  field_land[1].GetString();
	std::string password =  field_land[2].GetString();

	// 获取userinfo信息
	memset(buf,0,sizeof(buf));
	sprintf(buf,"SELECT nick,sex, icon_version, province,city FROM userinfo%u WHERE uid = %u",accID%10,accID);
	QueryResult* userinfo = sGetdataSQL->Query(buf);
	if (!userinfo)
	{
		return;
	}

	Field* field_userinfo = userinfo->Fetch();
	if (!field_userinfo)
	{
		return;
	}

	std::string nick =  field_userinfo[0].GetString();
	uint8 sex =  field_userinfo[1].GetUInt8();
	uint32 icon_version =  field_userinfo[2].GetUInt32();
	uint8 province =  field_userinfo[3].GetUInt8();
	uint8 city =  field_userinfo[4].GetUInt8();

	memset(buf,0,sizeof(buf));
	sprintf(buf,"SELECT uid, gold, present,exp,lost,win FROM gameinfo%u WHERE uid = %u",accID%10,accID);
	QueryResult* gameinfo = sGameinfoSQL->Query(buf);
	if (!gameinfo)
	{
		return;
	}

	Field* field_gameinfo = gameinfo->Fetch();
	if (!field_gameinfo)
	{
		return;
	}
	
	field_gameinfo = gameinfo->Fetch();

	m_pAccount->account_id			= field_gameinfo[0].GetUInt32();
	m_pAccount->account_gold		= field_gameinfo[1].GetUInt64();
	m_pAccount->account_present		= field_gameinfo[2].GetUInt64();
	GameStatData& gsd = m_pAccount->GetGameStatData(GAMETYPE_PDK);
	gsd.account_exp			= field_gameinfo[3].GetUInt64();
	gsd.account_lost		= field_gameinfo[4].GetUInt64();
	gsd.account_win			= field_gameinfo[5].GetUInt64();
	//pAccount->account_bankgold		= field_gameinfo[5].GetUInt64();
	//pAccount->account_bankbCard		= field_gameinfo[6].GetUInt64();
	m_pAccount->account_name			= accname;
	m_pAccount->account_password		= password;

	m_pAccount->account_PlayerName		= nick;
	if (sex)
		m_pAccount->account_sex = true;
	else
		m_pAccount->account_sex = false;
	m_pAccount->account_HeadVersion		= icon_version;
	m_pAccount->account_province			= province;
	m_pAccount->account_city				= city;


	delete gameinfo;
	delete land;

	// 发送账号信息给账号管理服务器
	//LOG_ERROR("DoGetAccountData_end '%s'",preget_account_name.c_str());

}

void CDataOptThread::DoSavePrimaryAccountData()
{
	Account* pAccount = sAccountMgr.GetAccount(preget_account_name);
	if (pAccount == NULL)
	{
		return;
	}

	GameStatData& gsd = pAccount->GetGameStatData(GAMETYPE_PDK);

	char buf[20];
	sprintf(buf,"gameinfo%u",pAccount->account_id%10);

	sGameinfoSQL->Execute("UPDATE %s SET  gold = %u,present = %u,exp = %u,lost = %u,win = %u WHERE uid = %u",
		buf,pAccount->account_gold,pAccount->account_present,gsd.account_exp,gsd.account_lost,gsd.account_win,pAccount->account_id);

	preget_account_name = "";
}

//void CDataOptThread::DoSaveSecondaryAccountData()
//{
//	Account* pAccount = sAccountMgr.GetAccount(preget_account_name);
//
//}
//
//void CDataOptThread::DoHttpRequest()
//{
//	char buf[200];
//	memset(buf,0,sizeof(buf));
//	sLog.outString("Info: HttpProcess: CDataOptThread::DoHttpRequest()");
//	if (http_opt_type == REQUESTTYPE_RELOADUSERINFO)
//	{
//		sprintf(buf,"SELECT nick,sex, icon_version, province,city FROM userinfo%u WHERE uid = %u",http_opt_value1%10,http_opt_value1);
//		QueryResult* userinfo = sGetdataSQL->Query(buf);
//		if (!userinfo)
//		{
//			opt_Result = 2;
//			return;
//		}
//
//		Field* field_userinfo = userinfo->Fetch();
//		if (!field_userinfo)
//		{
//			opt_Result = 2;
//			return;
//		}
//
//		std::string nick =  field_userinfo[0].GetString();
//		uint8 sex =  field_userinfo[1].GetUInt8();
//		uint32 icon_version =  field_userinfo[2].GetUInt32();
//		uint8 province =  field_userinfo[3].GetUInt8();
//		uint8 city =  field_userinfo[4].GetUInt8();
//
//		m_pAccount->account_PlayerName		= nick;
//		if (sex)
//			m_pAccount->account_sex = true;
//		else
//			m_pAccount->account_sex = false;
//		m_pAccount->account_HeadVersion		= icon_version;
//		m_pAccount->account_province			= province;
//		m_pAccount->account_city				= city;
//
//		opt_Result = 1;
//	}
//	else if (http_opt_type == REQUESTTYPE_REQUESTGAMEINFO)
//	{
//		sprintf(buf,"SELECT uid, gold, present,exp,lost,win FROM gameinfo%u WHERE uid = %u",http_opt_value1%10,http_opt_value1);
//		QueryResult* gameinfo = sGameinfoSQL->Query(buf);
//		if (!gameinfo)
//		{
//			opt_Result = 2;
//			return;
//		}
//
//		Field* field_gameinfo = gameinfo->Fetch();
//		if (!field_gameinfo)
//		{
//			opt_Result = 2;
//			return;
//		}
//
//		//pAccount = new Account;
//
//
//		field_gameinfo = gameinfo->Fetch();
//
//		m_pAccount->account_id			= field_gameinfo[0].GetUInt32();
//		m_pAccount->account_gold		= field_gameinfo[1].GetUInt64();
//		m_pAccount->account_present		= field_gameinfo[2].GetUInt64();
//		m_pAccount->account_exp			= field_gameinfo[3].GetUInt64();
//		m_pAccount->account_lost		= field_gameinfo[4].GetUInt64();
//		m_pAccount->account_win			= field_gameinfo[5].GetUInt64();
//
//		opt_Result = 1;
//	}
//}

//
//void CDataOptThread::DoProcessFriendData()
//{
//	FriendQueueMutex.Acquire();
//	if (m_bHasFriendMsg)
//	{
//		m_bHasFriendMsg = false;
//		uint32 nProcessNum = sFriendModule.GetFriendQueueSize();
//		//sLog.outError("info,nProcessNum=%u",nProcessNum);
//		for (int i = 0; i < nProcessNum; i++)
//		{
//			if (i>600)
//			{
//				break;
//			}
//			FriendModuleQueue* pFriendQueue = sFriendModule.PopFriendQueue();
//			if (pFriendQueue)
//			{
//				sFriendModule.ProcessProtocols(pFriendQueue->Opcode,pFriendQueue->m_pPacket,pFriendQueue->pSession);
//				delete pFriendQueue;
//				pFriendQueue = NULL;
//			}			
//		}
//	}
//	FriendQueueMutex.Release();
//}