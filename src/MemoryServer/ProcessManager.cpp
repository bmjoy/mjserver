#include "MemoryServerStdafx.h"

#include "CAccount_STOA_Find.h"
#include "CAccount_ATOS_Info.h"
#include "CGame_STOC_Over.h"
#include "CGameGoldsChanged_WTOH_Info.h"
#include "CError_ErrorInfo.h"
#include "ErrorCode.h"
#include "CAccount_HttpTOA_Info.h"

#include "CAccount_Mem_GameInfo.h"

#include "CGame_CTOS_PlayerInfo.h"
//#include "FriendModule.h"


#include "CGame_STOA_MatchHis.h"
#include "CGame_STOA_GameOver.h"
#include "CGame_STOA_ItemChange.h"
#include "ProtocolStruct.h"

initialiseSingleton(CProcessManager);

CProcessManager::CProcessManager()
{
	//new CFriendModule;
}

CProcessManager::~CProcessManager()
{
	//delete sFriendModule.getSingletonPtr();
}

void CProcessManager::Update(uint32 diff)
{

}

void CProcessManager::ProcessProtocols(uint16 Opcode, Protocol* ptrPacket,CSession * pSession)
{
	switch (Opcode)
	{
	case MSG_SA_ACCOUNTFIND:
		ProcessAccountFind(ptrPacket,pSession);
		break;
	case MSG_SERVER_GAMEOVER:
		ProcessGameOver(ptrPacket,pSession);
		break;
	case MSG_CS_PLAYERINFO:
		ProcessPlayerInfo(ptrPacket,pSession);
		break;


	case MSG_SERVER_MATCHHIS:
		ProcessMatchHis(ptrPacket,pSession);
		break;
	case MSG_WH_GOLDSCHANGED:
		ProcessGoldSchanged(ptrPacket,pSession);
		break;
	case MSG_HTTPTOA_INFO:
		ProcessHttpInfo(ptrPacket,pSession);
		break;
	case MSG_SERVER_ITEMCHANGE:
		ProcessItemChange(ptrPacket,pSession);
		break;
	default:
		break;
	}
}

void CProcessManager::ProcessAccountFind( Protocol* ptrPacket,CSession * pSession)
{
	CAccount_STOA_Find *pFind = dynamic_cast<CAccount_STOA_Find*>(ptrPacket);
	if (pFind == NULL)
	{
		return;
	}

	// 查找内存数据
	Account* pAccount = sAccountMgr.GetAccount(pFind->strAccount);
	if (pAccount)
	{
		// 发送账号信息给账号管理服务器
		CAccount_ATOS_Info	info;
		info.account_id = pAccount->account_id;
		info.account_name = pAccount->account_name;
		info.account_password = pAccount->account_password;
		info.account_gold = pAccount->account_gold;

		info.account_PlayerName = pAccount->account_PlayerName;
		info.account_sex = pAccount->account_sex;
		info.account_HeadVersion = pAccount->account_HeadVersion;
		info.account_province = pAccount->account_province;
		info.account_city = pAccount->account_city;

		info.account_present = pAccount->account_present;

		GameStatData& gsd = pAccount->GetGameStatData(GAMETYPE_PDK);
		info.account_exp = gsd.account_exp;
		info.account_lost = gsd.account_lost;
		info.account_win = gsd.account_win;

		info.account_bindip = pAccount->account_bindip;
		info.account_bindpsw = pAccount->account_bindpsw;
		info.account_bindpswparam = pAccount->account_bindpswparam;

		pAccount->dirtytime_primary = 0;
		pAccount->account_activetime = time(NULL);

		pSession->SendPacket(&info);		
	}else
	{
		// 没找到  添加到查询列表
		AccountQueue* paq = new AccountQueue;
		paq->queueType = ACCOUNTQUEUETYPE_LOGIN;
		paq->account_name = pFind->strAccount;
		paq->queue_state_id = ACCOUNTQUEUESTATE_NULL;
		sAccountMgr.AddGainAccountInfo(paq);
	}
}

void CProcessManager::ProcessGameOver( Protocol* ptrPacket,CSession * pSession)
{
	CGame_STOA_GameOver *pCardoverInfo = dynamic_cast<CGame_STOA_GameOver*>(ptrPacket);
	if (pCardoverInfo == NULL||pSession == NULL)
	{
		return;
	}

	Account* pAccount = NULL;

	for (int i=0;i<pCardoverInfo->PlayerNum;++i)
	{
		pAccount = sAccountMgr.GetAccountByID(pCardoverInfo->VecGameOverInfo[i].PlayerID);

		if (pAccount)
		{
			if (pCardoverInfo->VecGameOverInfo[i].MoneyChange < 0 && pAccount->account_gold < 0 - pCardoverInfo->VecGameOverInfo[i].MoneyChange)
			{
				pAccount->account_gold = 0;
			}else
			{
				pAccount->account_gold += pCardoverInfo->VecGameOverInfo[i].MoneyChange;
			}

			GameStatData& gsd = pAccount->GetGameStatData(GAMETYPE_PDK);

			gsd.account_exp += pCardoverInfo->VecGameOverInfo[i].ExpAdd;

			if (pCardoverInfo->VecGameOverInfo[i].GameResult == GResultT_Win)
			{
				gsd.account_win++;
			}else
			{
				gsd.account_lost++;
			}

			pAccount->DirtyData();
		}
	}
}

//更新玩家信息
void CProcessManager::ProcessPlayerInfo( Protocol* ptrPacket,CSession * pSession)
{
	CGame_CTOS_PlayerInfo *pInfo = dynamic_cast<CGame_CTOS_PlayerInfo*>(ptrPacket);
	if (pInfo == NULL||pSession == NULL)
	{
		sLog.outError("Error,ProcessPlayerInfo Empty Point!\n");
		return;
	}
	Account* pAccount = sAccountMgr.GetAccountByID(pInfo->playerId);

	if (!pAccount)
	{
		return;
	}

	switch (pInfo->Key)
	{
	case PLAYERPARAM_NULL:
		return;
	case PLAYERINFO_GOLDADD:
		pAccount->account_gold += pInfo->Value;
		break;
	case PLAYERINFO_GOLDSUB:
		pAccount->account_gold -= pInfo->Value;
		break;
	case PLAYERINFO_EXP:
		{
			GameStatData& gsd = pAccount->GetGameStatData(pInfo->Param);
			gsd.account_exp += pInfo->Value;
		}

		break;
	default:
		return;
	}
}

//void CProcessManager::ProcessPlayerInfo( Protocol* ptrPacket,CSession * pSession)
//{
//	CGame_CTOS_PlayerInfo *pInfo = dynamic_cast<CGame_CTOS_PlayerInfo*>(ptrPacket);
//	if (pInfo == NULL||pSession == NULL)
//	{
//		sLog.outError("Error,ProcessPlayerInfo Empty Point!\n");
//		return;
//	}
//	Account* pAccount = sAccountMgr.GetAccountByID(pInfo->playerId);
//	if (pAccount)
//	{
//		switch (pInfo->u8Key)
//		{	
//		case PLAYERINFO_GOLDADD:
//			pAccount->account_gold += pInfo->u64Value;
//			//sLog.outError("Info,PLAYERINFO_GOLDADD changed gold=%u,playid=%u",pAccount->account_gold,pInfo->playerId);
//			break;
//		case PLAYERINFO_GOLDSUB:
//			if (pAccount->account_gold>pInfo->u64Value)
//			{
//				pAccount->account_gold -= pInfo->u64Value;
//			}else
//			{
//				pAccount->account_gold = 0;
//			}
//
//			//sLog.outError("Info,PLAYERINFO_GOLDSUB changed gold=%u,playid=%u",pAccount->account_gold,pInfo->playerId);
//			break;
//		case PLAYERINFO_REWARD:
//		case PLAYERINFO_LV:
//		case PLAYERINFO_VIPLV:
//			break;
//		case PLAYERINFO_HEADVERSION:
//			pAccount->account_HeadVersion = pInfo->u64Value;
//			break;
//		case PLAYERINFO_SEX:
//			pAccount->account_sex = pInfo->u64Value;
//			break;
//		case PLAYERINFO_PRESENT:
//			pAccount->account_present = pInfo->u64Value;
//			break;
//		case PLAYERINFO_EXP:
//			pAccount->account_exp = pInfo->u64Value;
//			break;
//		case PLAYERINFO_LOST:
//			pAccount->account_lost = pInfo->u64Value;
//			break;
//		case PLAYERINFO_WIN:
//			pAccount->account_win = pInfo->u64Value;
//			break;
//		case PLAYERINFO_INTEGRAL:
//			break;
//		case PLAYERINFO_BINDIP:
//			pAccount->account_bindip = pInfo->u64Value;
//			break;	
//		default:
//			break;
//		}
//		//如果这个字段有值则会保存到数据库
//		pAccount->DirtyData();
//	}else
//	{
//		char buf[20] = {0};
//
//		switch (pInfo->u8Key)
//		{
//		case PLAYERINFO_GOLDADD:
//			sGameinfoSQL->Execute("UPDATE gameinfo%u SET  gold = (gold+%u) WHERE uid = %u",
//				pInfo->playerId%10,pInfo->u64Value,pInfo->playerId);
//			//sLog.outError("Info,PLAYERINFO_GOLDADD changed gold+=%u,playid=%u",pInfo->u64Value,pInfo->playerId);
//			return;
//		case PLAYERINFO_GOLDSUB:
//			sGameinfoSQL->Execute("UPDATE gameinfo%u SET  gold = 0 WHERE uid = %u AND gold < %u",
//				pInfo->playerId%10,pInfo->playerId,pInfo->u64Value);
//
//			sGameinfoSQL->Execute("UPDATE gameinfo%u SET  gold = (gold-%u) WHERE uid = %u AND gold > %u",
//				pInfo->playerId%10,pInfo->u64Value,pInfo->playerId,pInfo->u64Value);
//
//			//sLog.outError("Info,PLAYERINFO_GOLDSUB changed gold-=%u,playid=%u",pInfo->u64Value,pInfo->playerId);
//			return;
//		case PLAYERINFO_PRESENT:
//			strcat(buf,"present");
//			break;
//		case PLAYERINFO_EXP:
//			strcat(buf,"exp");
//			break;
//		case PLAYERINFO_LOST:
//			strcat(buf,"lost");
//			break;
//		case PLAYERINFO_WIN:
//			strcat(buf,"win");
//			break;
//		default:
//			break;
//		}
//
//		if (strlen(buf)>0)
//		{
//			sGameinfoSQL->Execute("UPDATE gameinfo%u SET  %s = %u WHERE uid = %u",
//				pInfo->playerId%10,buf,pInfo->u64Value,pInfo->playerId);
//		}		
//	}
//}


void CProcessManager::ProcessMatchHis( Protocol* ptrPacket,CSession * pSession)
{
	return;
	CGame_STOA_MatchHis *pCardoverInfo = dynamic_cast<CGame_STOA_MatchHis*>(ptrPacket);
	if (pCardoverInfo == NULL||pSession == NULL)
	{
		return;
	}

	char buf[300];
	//查询是否有比赛记录
	sprintf(buf,"SELECT rank FROM match WHERE match_id = %u AND uid = %u",pCardoverInfo->matchID,pCardoverInfo->playerID);
	QueryResult* matchInfo = sGameinfoSQL->Query(buf);
	if (matchInfo)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"UPDATE match SET rank=%u WHERE match_id = %u AND uid = %u AND rank>%u",pCardoverInfo->matchRank,pCardoverInfo->matchID,pCardoverInfo->playerID,pCardoverInfo->matchRank);
		sGameinfoSQL->Execute(buf);
		matchInfo->Delete();
	}else
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"INSERT INTO match(match_id,uid,rank) VALUES(%u,%u,%u)",pCardoverInfo->matchID,pCardoverInfo->playerID,pCardoverInfo->matchRank);
		sGameinfoSQL->Execute(buf);
	}
	//保存比赛历史记录
	std::list<TMatchPlayerReward>::iterator it = pCardoverInfo->m_RewardList.begin();
	for (; it!=pCardoverInfo->m_RewardList.end(); it++)
	{
		TMatchPlayerReward mathHis = *it;
		memset(buf,0,sizeof(buf));
		sprintf(buf,"INSERT INTO match_his(match_id,uid,item_id,item_num,match_time) VALUES(%u,%u,%u,%u,NOW())",pCardoverInfo->matchID,pCardoverInfo->playerID,mathHis.ItmeID,mathHis.ItmeNum);
		sGameinfoSQL->Execute(buf);
	}
}

void CProcessManager::ProcessGoldSchanged( Protocol* ptrPacket,CSession * pSession)
{
	return;
	CGameGoldsChanged_WTOH_Info *pInfo = dynamic_cast<CGameGoldsChanged_WTOH_Info*>(ptrPacket);
	if (pInfo == NULL||pSession == NULL)
	{
		return;
	}


	if (pInfo->account_id > 100000000)
	{
		CError_ErrorInfo ErrorInfo;
		ErrorInfo.ErrorTypeID = ErrorCode_Http_NoAccoutID;
		ErrorInfo.Param1 =	pInfo->account_id;
		pSession->SendPacket(&ErrorInfo);
		return;
	}


	// 查找内存数据
	Account* pAccount = sAccountMgr.GetAccountByID(pInfo->account_id);
	if (pAccount)
	{
		if (pInfo->golds_plusvornot)
		{
			pAccount->account_gold += pInfo->account_gold;
			pAccount->DirtyData();

			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_ChangeGoldSuc;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);
		}else 
		{
			if (pInfo->account_gold>pAccount->account_gold)
			{
				CError_ErrorInfo ErrorInfo;
				ErrorInfo.ErrorTypeID = ErrorCode_Game_NoMoney;
				ErrorInfo.Param1 =	pInfo->account_id;
				pSession->SendPacket(&ErrorInfo);
				return;
			}

			pAccount->account_gold -= pInfo->account_gold;
			pAccount->DirtyData();
			
			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_ChangeGoldSuc;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);

			return;
		}

		return;
	}else
	{
		char buf[200];
		sprintf(buf,"SELECT uid, gold FROM gameinfo%u WHERE uid = %u",pInfo->account_id%10,pInfo->account_id);
		QueryResult* gameinfo = sGameinfoSQL->Query(buf);
		if (!gameinfo)
		{
			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_NoAccoutID;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);
			return;
		}

		Field* field_gameinfo = gameinfo->Fetch();
		if (!field_gameinfo)
		{
			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_NoAccoutID;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);
			return;
		}

		Account tAccount ;

		field_gameinfo = gameinfo->Fetch();

		tAccount.account_id			= field_gameinfo[0].GetUInt32();
		tAccount.account_gold			= field_gameinfo[1].GetUInt64();

		delete gameinfo;
		if (pInfo->golds_plusvornot)
		{
			sprintf(buf,"gameinfo%u",tAccount.account_id%10);

			bool _suc = sGameinfoSQL->Execute("UPDATE %s SET  gold = %u WHERE uid = %u",
				buf,tAccount.account_gold + pInfo->account_gold,tAccount.account_id);

			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_ChangeGoldSuc;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);

			return;
		}else 
		{
			if (pInfo->account_gold>tAccount.account_gold)
			{
				CError_ErrorInfo ErrorInfo;
				ErrorInfo.ErrorTypeID = ErrorCode_Game_NoMoney;
				ErrorInfo.Param1 =	pInfo->account_id;
				pSession->SendPacket(&ErrorInfo);
				return;
			}

			sGameinfoSQL->Execute("UPDATE %s SET  gold = %u WHERE uid = %u",
				buf,tAccount.account_gold - pInfo->account_gold,tAccount.account_id);

			CError_ErrorInfo ErrorInfo;
			ErrorInfo.ErrorTypeID = ErrorCode_Http_ChangeGoldSuc;
			ErrorInfo.Param1 =	pInfo->account_id;
			pSession->SendPacket(&ErrorInfo);

			return;
		}

	}
}

void CProcessManager::ProcessHttpInfo( Protocol* ptrPacket,CSession * pSession)
{
	return;
	CAccount_HttpTOA_Info *pInfo = dynamic_cast<CAccount_HttpTOA_Info*>(ptrPacket);
	if (pInfo == NULL||pSession == NULL)
	{
		return;
	}

	if (pInfo->optType == REQUESTTYPE_RELOADUSERINFO)
	{
		AccountQueue* paq = new AccountQueue;
		paq->queueType = ACCOUNTQUEUETYPE_RELOADUSERINFO;
		paq->account_id = pInfo->optParam1;
		paq->queue_state_id = ACCOUNTQUEUESTATE_NULL;
		sAccountMgr.AddGainAccountInfo(paq);
	}else if(pInfo->optType == REQUESTTYPE_REQUESTGAMEINFO)
	{
		Account* pAccount = sAccountMgr.GetAccountByID(pInfo->optParam1);

		if(pAccount)
		{
			CAccount_Mem_GameInfo	info;

			info.account_id = pAccount->account_id;
			info.account_gold = pAccount->account_gold;
			info.account_present = pAccount->account_present;

			GameStatData& gsd = pAccount->GetGameStatData(GAMETYPE_PDK);
			info.account_exp = gsd.account_exp;
			info.account_lost = gsd.account_lost;
			info.account_win = gsd.account_win;

			CSession* pSession = sSessionsManager.GetOnlySession();
			if (pSession)
			{
				sLog.outString("Info: HttpProcess:  REQUESTTYPE_REQUESTGAMEINFO  ---  SendPacketToAccountManager ");

				pSession->SendPacket(&info);
			}
		}else
		{
			AccountQueue* paq = new AccountQueue;
			paq->queueType = ACCOUNTQUEUETYPE_GETGAMEINFO;
			paq->account_id = pInfo->optParam1;
			paq->queue_state_id = ACCOUNTQUEUESTATE_NULL;
			sAccountMgr.AddGainAccountInfo(paq);
		}
	}
}

void CProcessManager::ProcessItemChange( Protocol* ptrPacket,CSession * pSession)
{
	return ;
	CGame_STOA_ItemChange *pItemChange = dynamic_cast<CGame_STOA_ItemChange*>(ptrPacket);
	if (pItemChange == NULL||pSession == NULL)
	{
		return;
	}

	Account* pAccount = NULL;

	for (int i=0;i<pItemChange->VecSize;++i)
	{
		pAccount = sAccountMgr.GetAccountByID(pItemChange->VecItemChange[i].playerID);

		if (pAccount)
		{
			if (pItemChange->VecItemChange[i].itemType == GAMEOBJTYPE_GOLD)
			{
				if (pItemChange->VecItemChange[i].itemNum < 0 && pAccount->account_gold < 0 - pItemChange->VecItemChange[i].itemNum)
				{
					pAccount->account_gold = 0;
				}else
				{
					pAccount->account_gold += pItemChange->VecItemChange[i].itemNum;
				}
			}

			pAccount->DirtyData();
		}
	}

}


//
//HttpRequestInfo* CProcessManager::GetHttpRequest()
//{
//	if (m_HttpRequestList.empty())
//	{
//		return NULL;
//	}
//
//	HttpRequestInfo* pInfo = *(m_HttpRequestList.begin());
//	m_HttpRequestList.pop_front();
//	return pInfo;
//}
