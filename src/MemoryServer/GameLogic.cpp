#include "MemoryServerStdafx.h"
#include "CAccount_ATOS_Info.h"
#include "CError_ErrorInfo.h"
#include "ErrorCode.h"
#include "CAccount_Mem_GameInfo.h"


initialiseSingleton(CGameLogic);

#define  WriteOptThreadNum 5
#define  ReadPrimaryThreadNum 5
#define  FriendOptThreadNum 1
#define  ReadSecondaryThreadNum 2

CGameLogic::CGameLogic()
{
	for (int i = 0 ;i < WriteOptThreadNum;++i)
	{
		CDataOptThread* pdataOpt = new CDataOptThread();
		pdataOpt->opt_type = 1;
		ThreadPool.ExecuteTask(pdataOpt);
		data_write_thread_list.push_back(pdataOpt);
	}
	
	for (int i = 0 ;i < ReadPrimaryThreadNum;++i)
	{
		CDataOptThread* pdataOpt = new CDataOptThread();
		pdataOpt->opt_type = 2;
		ThreadPool.ExecuteTask(pdataOpt);
		data_read_thread_list.push_back(pdataOpt);
	}

	//for (int i = 0 ;i < FriendOptThreadNum;++i)
	//{
	//	CDataOptThread* pdataOpt = new CDataOptThread();
	//	pdataOpt->opt_type = 3;
	//	ThreadPool.ExecuteTask(pdataOpt);
	//	data_friend_thread_list.push_back(pdataOpt);
	//}

	//m_HttpOpt = new CDataOptThread();
	//m_HttpOpt->opt_type = 4;
	//ThreadPool.ExecuteTask(m_HttpOpt);

	//for (int i = 0 ;i < ReadSecondaryThreadNum;++i)
	//{
	//	CDataOptThread* pdataOpt = new CDataOptThread();
	//	pdataOpt->opt_type = 3;
	//	ThreadPool.ExecuteTask(pdataOpt);
	//	data_secondary_thread_list.push_back(pdataOpt);
	//}


	//new CRoomManager;
}

CGameLogic::~CGameLogic()
{
	for (std::list<CDataOptThread*>::iterator it = data_read_thread_list.begin();it!=data_read_thread_list.end();++it)
	{
		CDataOptThread* pdataOpt = *it;
		delete pdataOpt;
	}
	data_read_thread_list.clear();

	for (std::list<CDataOptThread*>::iterator it = data_write_thread_list.begin();it!=data_write_thread_list.end();++it)
	{
		CDataOptThread* pdataOpt = *it;
		delete pdataOpt;
	}
	data_write_thread_list.clear();

	//for (std::list<CDataOptThread*>::iterator it = data_friend_thread_list.begin();it!=data_friend_thread_list.end();++it)
	//{
	//	CDataOptThread* pdataOpt = *it;
	//	delete pdataOpt;
	//}
	//data_friend_thread_list.clear();

	//for (std::list<CDataOptThread*>::iterator it = data_secondary_thread_list.begin();it!=data_secondary_thread_list.end();++it)
	//{
	//	CDataOptThread* pdataOpt = *it;
	//	delete pdataOpt;
	//}
	//data_secondary_thread_list.clear();
	//delete CRoomManager::getSingletonPtr();
}

void CGameLogic::Update(uint32 diff)
{
	AccountQueue* paccount = NULL;

	// 取数据
	for (std::list<CDataOptThread*>::iterator it = data_read_thread_list.begin();it!=data_read_thread_list.end();++it)
	{
		CDataOptThread* pdataOpt = *it;
		
		if (pdataOpt && pdataOpt->GetThreadState() == THREADSTATE_PAUSED)
		{
			//// 已经取出数据
			if (pdataOpt->m_pAccount->account_id)
			{
				sAccountMgr.AddAccountInfo(pdataOpt->m_pAccount);

				CSession* pSession = sSessionsManager.GetOnlySession();
				if (!pSession)
					return;

				if (pdataOpt->preget_queueType == ACCOUNTQUEUETYPE_GETGAMEINFO)
				{
					CAccount_Mem_GameInfo	info;

					info.account_id = pdataOpt->m_pAccount->account_id;
					info.account_gold = pdataOpt->m_pAccount->account_gold;
					info.account_present = pdataOpt->m_pAccount->account_present;

					GameStatData& gsd = pdataOpt->m_pAccount->GetGameStatData(GAMETYPE_PDK);

					info.account_exp = gsd.account_exp;
					info.account_lost = gsd.account_lost;
					info.account_win = gsd.account_win;

					pSession->SendPacket(&info);
				}else
				{
					CAccount_ATOS_Info	info;

					if (pdataOpt->preget_queueType == ACCOUNTQUEUETYPE_RELOADUSERINFO)
						info.account_update_type = AMUPDATETYPE_USERINFO;

					info.account_id = pdataOpt->m_pAccount->account_id;
					info.account_name = pdataOpt->m_pAccount->account_name;
					info.account_password = pdataOpt->m_pAccount->account_password;
					info.account_PlayerName = pdataOpt->m_pAccount->account_PlayerName;

					info.account_gold = pdataOpt->m_pAccount->account_gold;
					info.account_present = pdataOpt->m_pAccount->account_present;

					GameStatData& gsd = pdataOpt->m_pAccount->GetGameStatData(GAMETYPE_PDK);
					info.account_exp = gsd.account_exp;
					info.account_lost = gsd.account_lost;
					info.account_win = gsd.account_win;

					info.account_sex = pdataOpt->m_pAccount->account_sex;

					info.account_HeadVersion = pdataOpt->m_pAccount->account_HeadVersion;
					info.account_province = pdataOpt->m_pAccount->account_province;
					info.account_city = pdataOpt->m_pAccount->account_city;
					
					pSession->SendPacket(&info);					
				}

				pdataOpt->m_pAccount->account_id = 0;
				pdataOpt->preget_account_name = "";
			}else if (!pdataOpt->preget_account_name.empty())
			{
				CSession* pSession = sSessionsManager.GetOnlySession();
				if (!pSession)
					return;
				
				if (pdataOpt->preget_queueType == ACCOUNTQUEUETYPE_LOGIN)
				{
					CError_ErrorInfo ErrorInfo;
					ErrorInfo.ErrorTypeID = ErrorCode_AccountVerifyFail;
					ErrorInfo.ErrorString =	pdataOpt->preget_account_name;
					pSession->SendPacket(&ErrorInfo);
				}else if (pdataOpt->preget_queueType == ACCOUNTQUEUETYPE_RELOADUSERINFO)
				{
					CError_ErrorInfo ErrorInfo;
					ErrorInfo.ErrorTypeID = ErrorCode_Http_NoAccoutID;
					ErrorInfo.ErrorSubtypes = REQUESTTYPE_RELOADUSERINFO;
					pSession->SendPacket(&ErrorInfo);
				}else if (pdataOpt->preget_queueType == ACCOUNTQUEUETYPE_GETGAMEINFO)
				{
					CError_ErrorInfo ErrorInfo;
					ErrorInfo.ErrorTypeID = ErrorCode_Http_NoAccoutID;
					ErrorInfo.ErrorSubtypes = REQUESTTYPE_REQUESTGAMEINFO;
					pSession->SendPacket(&ErrorInfo);
				}
				
				pdataOpt->preget_account_name = "";
				pdataOpt->m_pAccount->account_id = 0;
			}
			
			paccount = sAccountMgr.GetGainAccountInfo();
			if (paccount)
			{
				pdataOpt->opt_type = 1;
				pdataOpt->preget_account_name = paccount->account_name;
				pdataOpt->preget_account_id = paccount->account_id;
				pdataOpt->preget_queueType = paccount->queueType;

				pdataOpt->SetThreadState(THREADSTATE_AWAITING);
			}
			delete paccount;
		}
	}

	// 写首要数据
	for (std::list<CDataOptThread*>::iterator it = data_write_thread_list.begin();it!=data_write_thread_list.end();++it)
	{
		CDataOptThread* pdataOpt = *it;

		if (pdataOpt && pdataOpt->GetThreadState() == THREADSTATE_PAUSED)
		{
			std::string saveAccName = sAccountMgr.GetPrimarySaveAccount();
			if (!saveAccName.empty())
			{
				pdataOpt->opt_type = 2;
				pdataOpt->preget_account_name = saveAccName;
				pdataOpt->SetThreadState(THREADSTATE_AWAITING);
			}
		}
	}

	////好友处理线程
	//for (std::list<CDataOptThread*>::iterator it = data_friend_thread_list.begin();it!=data_friend_thread_list.end();++it)
	//{
	//	CDataOptThread* pdataOpt = *it;

	//	if (pdataOpt && pdataOpt->GetThreadState() == THREADSTATE_PAUSED)
	//	{
	//		uint32 nFriendSize = sFriendModule.GetFriendQueueSize();
	//		if (nFriendSize>0)
	//		{
	//			pdataOpt->opt_type = 3;
	//			pdataOpt->m_bHasFriendMsg = true;
	//			pdataOpt->SetThreadState(THREADSTATE_AWAITING);
	//		}
	//		break;
	//	}
	//}
}
