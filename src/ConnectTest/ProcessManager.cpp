#include "ConnectTestStdafx.h"
#include "CAccount_ATOS_Info.h"
#include "CError_ErrorInfo.h"
#include "ErrorCode.h"
#include "ProtocolStruct.h"
#include "CAccount_STOA_Find.h"
#include "CAccount_STOA_Register.h"
#include "CAccount_HToA_AccountInfo.h"
#include "CGame_STOC_Over.h"
#include "CGameGoldsChanged_WTOH_Info.h"
#include "CReport_CTOS_LBSRelated.h"
#include "CAccount_HttpTOA_Info.h"
#include "CAccount_Mem_GameInfo.h"
#include "CGame_CTOS_PlayerInfo.h"
//#include "FriendModule.h"

#include "CGame_STOA_MatchHis.h"
#include "CGame_STOA_GameOver.h"
#include "CGame_STOA_ItemChange.h"
#include "CAccount_STOA_Login.h"

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
	//sFriendModule.Update(diff);
}

void CProcessManager::ProcessProtocols(uint16 Opcode, Protocol* ptrPacket,CSession * pSession)
{
	switch (Opcode)
	{
	case MSG_ERROR:																// 注册失败及账号验证失败
		ProcessErrorInfo(ptrPacket,pSession);
		break;
	default:
		break;
	}
	//消息传给好友模块处理
	//sFriendModule.ProcessProtocols(Opcode, ptrPacket,pSession);
}

void CProcessManager::ProcessErrorInfo( Protocol* ptrPacket,CSession * pSession)
{
	//CError_ErrorInfo *pError = dynamic_cast<CError_ErrorInfo*>(ptrPacket);
	//if (pError == NULL||pSession == NULL)
	//{
	//	return;
	//}


	//if (pError->ErrorTypeID == ErrorCode_AccountRegisterFail)
	//{
	//	CSession* pSessionGS = sAccountManager.GetRegisterSession(pError->Param1);

	//	CError_ErrorInfo ErrorInfo;
	//	ErrorInfo.ErrorTypeID = ErrorCode_AccountRegisterFail;
	//	ErrorInfo.Param1 = pError->Param1;
	//	ErrorInfo.ErrorSubtypes = pError->ErrorSubtypes;
	//	ErrorInfo.ErrorCode = pError->ErrorCode;
	//	pSessionGS->SendPacket(&ErrorInfo);
	//}else if (pError->ErrorTypeID == ErrorCode_AccountVerifyFail)
	//{
	//	for (std::list<RequestInfo>::iterator it = sAccountManager.request_info_list.begin();it!=sAccountManager.request_info_list.end();++it)
	//	{
	//		if (strcmp(it->account_name.c_str(),pError->ErrorString.c_str()) == 0)
	//		{
	//			CError_ErrorInfo info;
	//			info.ErrorTypeID = pError->ErrorTypeID;
	//			info.ErrorString = pError->ErrorString;
	//			sSessionsManager.SendErrorInfo(it->server_id,&info);
	//		}
	//	}
	//}
}

void CProcessManager::ProcessAccountLogin( Protocol* ptrPacket,CSession * pSession)
{
	//CAccount_STOA_Login *pLogin = dynamic_cast<CAccount_STOA_Login*>(ptrPacket);
	//if (pLogin == NULL)
	//{
	//	sLog.outDebug("Error,CAccount_STOA_Find -- Empty Protocol");
	//	return;
	//}
	//
	//if (pLogin->LoginType == LoginType_UnLogin)
	//{
	//	sAccountManager.AccountUnLogin(pLogin->AccountID);
	//}
}

void CProcessManager::ProcessAccountFind( Protocol* ptrPacket,CSession * pSession)
{
	//CAccount_STOA_Find *pFind = dynamic_cast<CAccount_STOA_Find*>(ptrPacket);
	//if (pFind == NULL)
	//{
	//	sLog.outDebug("Error,CAccount_STOA_Find -- Empty Protocol");
	//	return;
	//}

	//// 查找内存数据
	//Account* pAccount = sAccountManager.FindAccountInfoByName(pFind->strAccount);
	//if (pAccount)
	//{
	//	if (pAccount->GetAccountState() == AccountState_ONLINE)
	//	{
	//		// 账号已经在其他游戏服务器登陆
	//		CError_ErrorInfo ErrorInfo;
	//		ErrorInfo.ErrorTypeID = ErrorCode_AccountOtherGameLogin;
	//		ErrorInfo.ErrorString = pAccount->account_name;
	//		//ErrorInfo.ErrorSubtypes = pAccount->account_serverID;
	//		pSession->SendPacket(&ErrorInfo);

	//		return;
	//	}

	//	// 记录账号登陆的服务器
	//	pAccount->account_serverID = pSession->server_id;
	//	
	//	sAccountManager.AccountLogin(pAccount);

	//	// 通过account_serverID确定具体游戏ID
	//	uint32 GameID = 1;
	//	GameStatData& gsd = pAccount->GetGameStatData(GameID);

	//	// 返回游戏服务器账号信息
	//	CAccount_ATOS_Info	info;
	//	info.account_id = pAccount->account_id;
	//	info.account_gold = pAccount->account_gold;
	//	info.account_present = pAccount->account_present;
	//	info.account_exp = gsd.account_exp;
	//	info.account_lost = gsd.account_lost;
	//	info.account_win = gsd.account_win;

	//	info.account_bindip = pAccount->account_bindip;
	//	info.account_bindpsw = pAccount->account_bindpsw;
	//	info.account_bindpswparam = pAccount->account_bindpswparam;

	//	info.account_name = pAccount->account_name;
	//	info.account_password = pAccount->account_password;

	//	info.account_PlayerName = pAccount->account_PlayerName;
	//	info.account_sex = pAccount->account_sex;
	//	info.account_HeadVersion = pAccount->account_HeadVersion;
	//	info.account_province = pAccount->account_province;
	//	info.account_city = pAccount->account_city;
	//	pSession->SendPacket(&info);

	//}else
	//{
	//	// 记录哪个游戏服务器需要此数据
	//	for (std::list<RequestInfo>::iterator it = sAccountManager.request_info_list.begin();it!=sAccountManager.request_info_list.end();++it)
	//	{
	//		if (strcmp(it->account_name.c_str(),pFind->strAccount.c_str()) == 0 &&
	//			it->server_id == pSession->server_id)
	//		{
	//			sAccountManager.request_info_list.erase(it);
	//			break;
	//		}
	//	}

	//	RequestInfo request;
	//	request.server_id = pSession->server_id;
	//	request.account_name = pFind->strAccount;
	//	sAccountManager.request_info_list.push_back(request);
	//	
	//	// 发送到账号数据库服务器查询
	//	CAccount_STOA_Find aFind;
	//	aFind.strAccount = pFind->strAccount;
	//	aFind.strPassword = pFind->strPassword;
	//	SendToAccountMemServer(&aFind);
	//}
}

void CProcessManager::ProcessAccountInfo( Protocol* ptrPacket,CSession * pSession)
{
	//CAccount_ATOS_Info *pFind = dynamic_cast<CAccount_ATOS_Info*>(ptrPacket);
	//if (pFind == NULL)
	//{
	//	sLog.outDebug("Error,CAccount_STOA_Find -- Empty Protocol");
	//	return;
	//}

	//// 加入内存数据
	//Account* pAccount = sAccountManager.FindAccountInfoByName(pFind->account_name);
	//if (pAccount)
	//{
	//	//pAccount->account_activetime = time(NULL);
	//	//pAccount->account_PlayerName = pFind->account_PlayerName;
	//	//if (pFind->account_update_type == AMUPDATETYPE_USERINFO)
	//	//{
	//	//	pAccount->account_sex = pFind->account_sex;
	//	//	pAccount->account_HeadVersion = pFind->account_HeadVersion;
	//	//	pAccount->account_province = pFind->account_province;
	//	//	pAccount->account_city = pFind->account_city;			
	//	//	sSessionsManager.SendAccountInfo(pAccount->account_serverID,pFind);
	//	//	return;
	//	//}

	//	//pAccount->account_id = pFind->account_id;
	//	//pAccount->account_name = pFind->account_name;
	//	//pAccount->account_password = pFind->account_password;
	//	//pAccount->account_gold = pFind->account_gold;
	//	//pAccount->account_present = pFind->account_present;
	//	//pAccount->account_exp = pFind->account_exp;
	//	//pAccount->account_lost = pFind->account_lost;
	//	//pAccount->account_win = pFind->account_win;
	//	//sSessionsManager.SendAccountInfo(pAccount->account_serverID,pFind);
	//}else
	//{
	//	Account* pAcc = new Account;
	//	// 通过account_serverID确定具体游戏ID
	//	uint32 GameID = 1;
	//	GameStatData& gsd = pAccount->GetGameStatData(GameID);
	//	gsd.account_exp = pFind->account_exp;
	//	gsd.account_lost = pFind->account_lost;
	//	gsd.account_win = pFind->account_win;

	//	pAcc->account_id = pFind->account_id;
	//	pAcc->account_name = pFind->account_name;
	//	pAcc->account_password = pFind->account_password;
	//	pAcc->account_gold = pFind->account_gold;
	//	pAcc->account_present = pFind->account_present;
	//	pAcc->account_activetime = time(NULL);
	//	pAcc->account_PlayerName = pFind->account_PlayerName;
	//	pAcc->account_sex = pFind->account_sex;
	//	pAcc->account_HeadVersion = pFind->account_HeadVersion;
	//	pAcc->account_province = pFind->account_province;
	//	pAcc->account_city = pFind->account_city;

	//	pAcc->SetAccountState(AccountState_ONLINE);
	//	pAcc->account_activetime = 0;

	//	sAccountManager.AddAccountInfo(pAcc);

	//	// 发送到游戏服务器
	//	for (std::list<RequestInfo>::iterator it = sAccountManager.request_info_list.begin();it!=sAccountManager.request_info_list.end();++it)
	//	{
	//		if (strcmp(it->account_name.c_str(),pAcc->account_name.c_str()) == 0 )
	//		{
	//			sSessionsManager.SendAccountInfo(it->server_id,pFind);
	//		}
	//	}
	//}

}

void CProcessManager::ProcessGoldSchanged( Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CGameGoldsChanged_WTOH_Info *pInfo = dynamic_cast<CGameGoldsChanged_WTOH_Info*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	return;
	//}

	////sAccountManager.pSessionGate = pSession;

	//SendToAccountMemServer(pInfo);
}

void CProcessManager::ProcessMatchHis( Protocol* ptrPacket,CSession * pSession)
{
	//CGame_STOA_MatchHis *pMatchHis = dynamic_cast<CGame_STOA_MatchHis*>(ptrPacket);
	//if (pMatchHis == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//SendToAccountMemServer(pMatchHis);
}

void CProcessManager::ProcessGameOver( Protocol* ptrPacket,CSession * pSession)
{
	//CGame_STOA_GameOver *pGameOver = dynamic_cast<CGame_STOA_GameOver*>(ptrPacket);
	//if (pGameOver == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//Account* pAccount = NULL;
	//for (int i = 0 ;i< pGameOver->PlayerNum;i++)
	//{
	//	pAccount = sAccountManager.FindAccountInfoByID(pGameOver->VecGameOverInfo[i].PlayerID);
	//	if (pAccount)
	//	{
	//		pAccount->account_gold += pGameOver->VecGameOverInfo[i].MoneyChange;

	//		GameStatData& gsd = pAccount->GetGameStatData(pGameOver->GameID);

	//		gsd.account_exp += pGameOver->VecGameOverInfo[i].ExpAdd;
	//		if (pGameOver->VecGameOverInfo[i].GameResult == GResultT_Win)
	//			gsd.account_win += 1;
	//		else
	//			gsd.account_lost += 1;
	//	}
	//}

	//SendToAccountMemServer(pGameOver);
}

void CProcessManager::ProcessItemChange( Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CGame_STOA_ItemChange *pItemChange = dynamic_cast<CGame_STOA_ItemChange*>(ptrPacket);
	//if (pItemChange == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//Account* pAccount = NULL;
	//for (int i = 0 ;i< pItemChange->VecSize;i++)
	//{
	//	pAccount = sAccountManager.FindAccountInfoByID(pItemChange->VecItemChange[i].playerID);
	//	if (pAccount)
	//	{
	//		if (pItemChange->VecItemChange[i].itemType == GAMEOBJTYPE_GOLD)
	//		{
	//			pAccount->account_gold += pItemChange->VecItemChange[i].itemNum;
	//		}
	//	}
	//}

	//SendToAccountMemServer(pItemChange);
}

void CProcessManager::ProcessPlayerInfo( Protocol* ptrPacket,CSession * pSession)
{
	//CGame_CTOS_PlayerInfo *pInfo = dynamic_cast<CGame_CTOS_PlayerInfo*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	sLog.outError("Error,ProcessPlayerInfo Empty Point!\n");
	//	return;
	//}
	////更新缓存，因为非第一次登陆都是从缓存取数据
	//Account* pAccount = sAccountManager.FindAccountInfoByID(pInfo->playerId);

	//if (!pAccount)
	//{
	//	return;
	//}
	//switch (pInfo->Key)
	//{
	//case PLAYERPARAM_NULL:
	//	return;
	//case PLAYERINFO_GOLDADD:
	//	pAccount->account_gold += pInfo->Value;
	//	break;
	//case PLAYERINFO_GOLDSUB:
	//	pAccount->account_gold -= pInfo->Value;
	//	break;
	//case PLAYERINFO_EXP:
	//	{
	//		GameStatData& gsd = pAccount->GetGameStatData(pInfo->Param);
	//		gsd.account_exp += pInfo->Value;
	//	}

	//	break;
	//default:
	//	return;
	//}

	//SendToAccountMemServer(pInfo);
}

void CProcessManager::ProcessAccountRegister( Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CAccount_STOA_Register *pRegister = dynamic_cast<CAccount_STOA_Register*>(ptrPacket);
	//if (pRegister == NULL)
	//{
	//	return;
	//}

	//sAccountManager.CacheRegister(pRegister->m_iRegisterID,pSession);

	//CSession * pSessionHttp = sSessionsManager.GetHttpSession();
	//// 发送信息到HTTP网关
	//CAccount_STOA_Register aFind;

	//aFind.m_strPhone = pRegister->m_strPhone;
	//aFind.m_strAccount = pRegister->m_strAccount;
	//aFind.m_strPassword = pRegister->m_strPassword;
	//aFind.m_strDeviceNum = pRegister->m_strDeviceNum;
	//aFind.m_iRegisterType = pRegister->m_iRegisterType;
	//aFind.m_strIP = pRegister->m_strIP;
	//aFind.m_iRegisterID = pRegister->m_iRegisterID;

	//if (pSessionHttp)
	//{
	//	pSessionHttp->SendPacket(&aFind);
	//}


	//SendToAccountServer(&aFind);
}

void CProcessManager::ProcessHttpAccountData(Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CAccount_HTOA_AccountInfo *pInfo = dynamic_cast<CAccount_HTOA_AccountInfo*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//CSession* pSessionGS = sAccountManager.GetRegisterSession(pInfo->m_iRegisterID);

	//CAccount_HTOA_AccountInfo info;
	//info.m_strAccount = pInfo->m_strAccount;
	//info.m_strPassword = pInfo->m_strPassword;
	//info.m_iUserID = pInfo->m_iUserID;
	//info.m_iRegisterID = pInfo->m_iRegisterID;
	//if (pSessionGS)
	//{
	//	pSessionGS->SendPacket(&info);
	//}
	
}

void CProcessManager::ProcessLBSInfo(Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CReport_CTOS_LBSRelated *pInfo = dynamic_cast<CReport_CTOS_LBSRelated*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//CSession * pSessionHttp = sSessionsManager.GetHttpSession();

	//CReport_CTOS_LBSRelated info;
	//info.m_strAccount = pInfo->m_strAccount;
	//info.m_strLatitude = pInfo->m_strLatitude;
	//info.m_strLongitude = pInfo->m_strLongitude;
	//info.m_page = pInfo->m_page;
	//info.m_iRegisterType = pInfo->m_iRegisterType;
	//if (pSessionHttp)
	//{
	//	pSessionHttp->SendPacket(&info);
	//}

}

void CProcessManager::ProcessHttpInfo( Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CAccount_HttpTOA_Info *pInfo = dynamic_cast<CAccount_HttpTOA_Info*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//sLog.outString("Info: HttpProcess:  ProcessHttpInfo");

	//if (pInfo->optType == REQUESTTYPE_RELOADUSERINFO)
	//{
	//	sLog.outString("Info: HttpProcess:  REQUESTTYPE_RELOADUSERINFO");

	//	// 从数据库重新载入userinfo数据

	//	// 如缓存内有此数据   通知到内存服务器取数据
	//	// 加入内存数据
	//	Account* pAccount = sAccountManager.FindAccountInfoByID(pInfo->optParam1);
	//	if (!pAccount)
	//	{
	//		// 发送到账号数据库服务器查询
	//		sLog.outString("Info: HttpProcess:  REQUESTTYPE_RELOADUSERINFO----SendToAccountMemServer");
	//		SendToAccountMemServer(pInfo);
	//	}

	//	// 缓存服务器无此数据
	//	  // 不用处理
	//}else if (pInfo->optType == REQUESTTYPE_REQUESTGAMEINFO)
	//{
	//	sLog.outString("Info: HttpProcess:  REQUESTTYPE_REQUESTGAMEINFO");
	//	Account* pAccount = sAccountManager.FindAccountInfoByID(pInfo->optParam1);
	//	if (pAccount)
	//	{
	//		CAccount_Mem_GameInfo	info;

	//		info.account_id = pAccount->account_id;
	//		info.account_gold = pAccount->account_gold;
	//		info.account_present = pAccount->account_present;

	//		uint32 GameID = 1;
	//		GameStatData& gsd = pAccount->GetGameStatData(GameID);

	//		info.account_exp = gsd.account_exp;
	//		info.account_lost = gsd.account_lost;
	//		info.account_win = gsd.account_win;

	//		CSession* pSession = sSessionsManager.GetHttpSession();
	//		if (pSession)
	//		{
	//			sLog.outString("Info: HttpProcess:  REQUESTTYPE_REQUESTGAMEINFO---FindAccount---sendtohttp");

	//			pSession->SendPacket(&info);
	//		}
	//	}else
	//	{
	//		sLog.outString("Info: HttpProcess:  REQUESTTYPE_REQUESTGAMEINFO---SendToAccountMemServer");
	//		// 发送到账号数据库服务器查询
	//		SendToAccountMemServer(pInfo);
	//	}
	//}
	
}

void CProcessManager::ProcessGameInfoToHttp( Protocol* ptrPacket,CSession * pSession)
{
	//return;
	//CAccount_Mem_GameInfo *pInfo = dynamic_cast<CAccount_Mem_GameInfo*>(ptrPacket);
	//if (pInfo == NULL||pSession == NULL)
	//{
	//	return;
	//}

	//sLog.outString("Info: HttpProcess:  ProcessGameInfoToHttp");

	//CSession* pSessionHttp = sSessionsManager.GetHttpSession();
	//if (pSessionHttp)
	//{
	//	sLog.outString("Info: HttpProcess:  ProcessGameInfoSendToHttp");
	//	pSessionHttp->SendPacket(pInfo);
	//}
}


void CProcessManager::ProcessModifyAccountData( Protocol* ptrPacket,CSession * pSession)
{

}

void CProcessManager::SendToAccountMemServer(Protocol* sendinfo)
{
	//sendinfo->clear();
	//sendinfo->WriteProtocol(*sendinfo);

	//sServerConnect.SendToAccountMemServer(sendinfo);
}