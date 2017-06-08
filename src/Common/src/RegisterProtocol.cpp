#include "RegisterProtocol.h"
#include "Protocol.h"


#include "CGame_STOA_ItemChange.h"
#include "CGame_STOA_MatchHis.h"
#include "CGame_STOA_GameOver.h"

#include "CLogin_CTOS_Register.h"
#include "CLogin_CTOS_Login.h"
#include "CPDKGame_STOC_Start.h"
#include "CRoom_CTOS_MatchList.h"
#include "CRoom_STOC_RoomList.h"
#include "CGame_CTOS_OutCard.h"
#include "CGame_STOC_OutCard.h"
#include "CGame_STOC_Over.h"
#include "CGame_STOC_TurnRound.h"
#include "CGame_CTOS_Ready.h"
#include "CAccount_STOA_Find.h"
#include "CAccount_ATOS_Info.h"
#include "CAccount_STOA_Register.h"
#include "CError_ErrorInfo.h"
#include "CAccount_HToA_AccountInfo.h"

#include "CGame_STOC_ChangeGold.h"

//web发给网关的金币增减信息;
#include "CGameGoldsChanged_WTOH_Info.h"
#include "CReport_CTOS_LBSRelated.h"

#include "CRoom_CTOS_EnterRoom.h"
//比赛相关;
#include "CApply_CTOS_EnterCompetition.h"
#include "CMatch_CTOS_Signup.h"
#include "CGame_CTOS_MatchRequest.h"
#include "CGame_STOC_MatchRank.h"
#include "CGame_STOC_MatchHistory.h"
#include "CGame_STOC_MatchReconnect.h"


#include "CClient_Ping.h"
//好友相关
#include "CAccount_HttpTOA_Info.h"
#include "CAccount_Mem_GameInfo.h"
#include "Friend_CTOS_Request.h"
#include "Friend_CTOS_List.h"
#include "Friend_CTOS_Talk.h"
#include "Friend_CTOS_Record.h"
#include "Friend_CTOS_RecordList.h"
#include "Friend_STOC_Request.h"
#include "Friend_STOC_List.h"
#include "Friend_STOC_Talk.h"
#include "Friend_STOC_Record.h"
#include "Friend_STOC_RecordList.h"
#include "Friend_CTOS_TalkWindow.h"
#include "CGame_STOC_MatchMessage.h"
#include "CGame_STOA_PlayerStateNotify.h"
#include "CLogin_STOC_Succeed.h"
#include "CGame_STOC_ONTCANOUT.h"
#include "CGame_CTOS_PlayerInfo.h"


//托管
#include "CGame_CTOS_Trusteeship.h"

#include "CClient_Ping.h"
#include "CServer_Pong.h"

void InnerProtocolsStubs( bool add)
{
	static Protocol::TStub<CError_ErrorInfo>				stub_CError_ErrorInfo;
	static Protocol::TStub<CClient_Ping>					stub_CClient_Ping;	
	static Protocol::TStub<CServer_Pong>					stub_CServer_Pong;

	static Protocol::TStub<CGame_STOA_ItemChange>			stub_CGame_STOA_ItemChange;
	static Protocol::TStub<CGame_STOA_MatchHis>				stub_CGame_STOA_MatchHis;
	static Protocol::TStub<CGame_STOA_GameOver>				stub_CGame_STOA_GameOver;


	static Protocol::TStub<CGame_STOC_ChangeGold>			stub_CGame_STOC_ChangeGold;
	static Protocol::TStub<CLogin_CTOS_Login>				stub_CLogin_CTOS_Login;
	static Protocol::TStub<CLogin_CTOS_Register>			stub_CLogin_CTOS_Register;
	static Protocol::TStub<CPDKGame_STOC_Start>				stub_CPDKGame_STOC_Start;
	static Protocol::TStub<CRoom_CTOS_MatchList>			stub_CRoom_CTOS_MatchList;
	static Protocol::TStub<CRoom_STOC_RoomList>				stub_CRoom_CTOS_RoomList;
	static Protocol::TStub<CGame_CTOS_OutCard>				stub_CGame_CTOS_OutCard;
	static Protocol::TStub<CGame_STOC_OutCard>				stub_CGame_STOC_OutCard;
	static Protocol::TStub<CGame_STOC_Over>					stub_CGame_STOC_Over;
	static Protocol::TStub<CGame_STOC_TurnRound>			stub_CGame_STOC_TurnRound;

	static Protocol::TStub<CGame_CTOS_Ready>				stub_CGame_CTOS_Ready;
	static Protocol::TStub<CAccount_STOA_Find>				stub_CAccount_STOA_Find;
	static Protocol::TStub<CAccount_STOA_Register>			stub_CAccount_STOA_Register;

	static Protocol::TStub<CAccount_ATOS_Info>				stub_CAccount_ATOS_Info;
	static Protocol::TStub<CRoom_CTOS_EnterRoom>			stub_CRoom_CTOS_EnterRoom;

	static Protocol::TStub<CApply_CTOS_EnterCompetition>	stub_CApply_CTOS_EnterCompetition;
	static Protocol::TStub<CAccount_HTOA_AccountInfo>		stub_CAccount_HTOA_AccountInfo;
	static Protocol::TStub<CGameGoldsChanged_WTOH_Info>		stub_CGameGoldsChangedInfo;	
	static Protocol::TStub<CReport_CTOS_LBSRelated>			stub_CReport_CTOS_LBSRelatedInfo;

	static Protocol::TStub<CGame_STOC_MatchRank>			stub_CGame_STOC_MatchRank;	
	static Protocol::TStub<CGame_STOC_MatchHistory>			stub_CGame_STOC_MatchHistory;	
	static Protocol::TStub<CGame_STOC_MatchReconnect>		stub_CGame_STOC_MatchReconnect;	
	
	static Protocol::TStub<CMatch_CTOS_Signup>				stub_CMatch_CTOS_Signup;	
	static Protocol::TStub<CGame_CTOS_MatchRequest>			stub_CGame_CTOS_MatchRequest;
	static Protocol::TStub<CAccount_HttpTOA_Info>			stub_CAccount_HttpTOA_UpdataPlayerInfo;	
	static Protocol::TStub<CAccount_Mem_GameInfo>			stub_CAccount_Mem_UpdataPlayerInfo;

	static Protocol::TStub<CFriend_CTOS_Request>			stub_CFriend_CTOS_Request;	
	static Protocol::TStub<CFriend_CTOS_List>				stub_CFriend_CTOS_List;
	static Protocol::TStub<CFriend_CTOS_Talk>				stub_CFriend_CTOS_Talk;
	static Protocol::TStub<CFriend_CTOS_Record>				stub_CFriend_CTOS_Record;
	static Protocol::TStub<CFriend_STOC_Request>			stub_CFriend_STOC_Request;	
	static Protocol::TStub<CFriend_STOC_List>				stub_CFriend_STOC_List;	
	static Protocol::TStub<CFriend_STOC_Talk>				stub_CFriend_STOC_Talk;
	static Protocol::TStub<CFriend_STOC_Record>				stub_CFriend_STOC_Record;
	static Protocol::TStub<CFriend_CTOS_RecordList>			stub_CFriend_CTOS_RecordList;
	static Protocol::TStub<CFriend_STOC_RecordList>			stub_CFriend_STOC_RecordList;
	static Protocol::TStub<CFriend_CTOS_TalkWindow>			stub_CFriend_CTOS_TalkWindow;

	static Protocol::TStub<CGame_STOC_MatchMessage>			stub_CGame_STOC_MatchMessage;	
	static Protocol::TStub<CGame_CTOS_Trusteeship>			stub_CGame_CTOS_Trusteeship;
	static Protocol::TStub<CGame_STOA_PlayerStateNotify>	stub_CGame_STOA_PlayerStateNotify;	
	static Protocol::TStub<CLogin_STOC_Succeed>				stub_CLogin_STOC_Succeed;	
	static Protocol::TStub<CGame_STOC_NotCanOut>			stub_CGame_STOC_NotCanOut;	
	static Protocol::TStub<CGame_CTOS_PlayerInfo>			stub_CGame_CTOS_PlayerInfo;

	if(add)
	{
		Protocol::AddStub( &stub_CError_ErrorInfo);
		Protocol::AddStub( &stub_CClient_Ping);
		Protocol::AddStub( &stub_CServer_Pong);

		Protocol::AddStub( &stub_CGame_STOA_ItemChange);
		Protocol::AddStub( &stub_CGame_STOA_MatchHis);
		Protocol::AddStub( &stub_CGame_STOA_GameOver);

		
		Protocol::AddStub( &stub_CGame_STOC_ChangeGold);
		Protocol::AddStub( &stub_CLogin_CTOS_Login);
		Protocol::AddStub( &stub_CLogin_CTOS_Register);
		Protocol::AddStub( &stub_CPDKGame_STOC_Start);
		Protocol::AddStub( &stub_CRoom_CTOS_MatchList);
		Protocol::AddStub( &stub_CRoom_CTOS_RoomList);
		Protocol::AddStub( &stub_CGame_CTOS_OutCard);
		Protocol::AddStub( &stub_CGame_STOC_OutCard);
		Protocol::AddStub( &stub_CGame_STOC_Over);
		Protocol::AddStub( &stub_CGame_STOC_TurnRound);
		Protocol::AddStub( &stub_CGame_CTOS_Ready);	

		Protocol::AddStub( &stub_CAccount_STOA_Find);	

		Protocol::AddStub( &stub_CAccount_ATOS_Info);	
		Protocol::AddStub( &stub_CAccount_STOA_Register);	
		Protocol::AddStub( &stub_CRoom_CTOS_EnterRoom);	

		Protocol::AddStub( &stub_CApply_CTOS_EnterCompetition);	
		Protocol::AddStub( &stub_CAccount_HTOA_AccountInfo);	

		Protocol::AddStub( &stub_CGameGoldsChangedInfo);
		Protocol::AddStub( &stub_CReport_CTOS_LBSRelatedInfo);	
		
		Protocol::AddStub( &stub_CGame_STOC_MatchRank);
		Protocol::AddStub( &stub_CGame_STOC_MatchHistory);
		Protocol::AddStub( &stub_CGame_STOC_MatchReconnect);
		
		
		Protocol::AddStub( &stub_CMatch_CTOS_Signup);
		Protocol::AddStub( &stub_CGame_CTOS_MatchRequest);
		Protocol::AddStub( &stub_CAccount_HttpTOA_UpdataPlayerInfo);
		Protocol::AddStub( &stub_CAccount_Mem_UpdataPlayerInfo);

		Protocol::AddStub( &stub_CFriend_CTOS_Request);
		Protocol::AddStub( &stub_CFriend_CTOS_List);
		Protocol::AddStub( &stub_CFriend_CTOS_Talk);
		Protocol::AddStub( &stub_CFriend_CTOS_Record);
		Protocol::AddStub( &stub_CFriend_STOC_Request);		
		Protocol::AddStub( &stub_CFriend_STOC_List);
		Protocol::AddStub( &stub_CFriend_STOC_Talk);		
		Protocol::AddStub( &stub_CFriend_STOC_Record);
		Protocol::AddStub( &stub_CFriend_CTOS_RecordList);
		Protocol::AddStub( &stub_CFriend_STOC_RecordList);
		Protocol::AddStub( &stub_CFriend_CTOS_TalkWindow);

		Protocol::AddStub( &stub_CGame_STOC_MatchMessage);
		Protocol::AddStub( &stub_CGame_CTOS_Trusteeship);
		Protocol::AddStub( &stub_CGame_STOA_PlayerStateNotify);
		Protocol::AddStub( &stub_CLogin_STOC_Succeed);
		Protocol::AddStub( &stub_CGame_STOC_NotCanOut);
		Protocol::AddStub( &stub_CGame_CTOS_PlayerInfo);
	}else
	{
		Protocol::DelStub( &stub_CError_ErrorInfo);
		Protocol::DelStub( &stub_CClient_Ping);
		Protocol::DelStub( &stub_CServer_Pong);

		Protocol::DelStub( &stub_CGame_STOA_ItemChange);
		Protocol::DelStub( &stub_CGame_STOA_MatchHis);
		Protocol::DelStub( &stub_CGame_STOA_GameOver);

		Protocol::DelStub( &stub_CGame_STOC_ChangeGold);
		Protocol::DelStub( &stub_CLogin_CTOS_Login);
		Protocol::DelStub( &stub_CLogin_CTOS_Register);
		Protocol::DelStub( &stub_CPDKGame_STOC_Start);
		Protocol::DelStub( &stub_CRoom_CTOS_MatchList);
		Protocol::DelStub( &stub_CRoom_CTOS_RoomList);
		Protocol::DelStub( &stub_CGame_CTOS_OutCard);
		Protocol::DelStub( &stub_CGame_STOC_OutCard);
		Protocol::DelStub( &stub_CGame_STOC_Over);
		Protocol::DelStub( &stub_CGame_STOC_TurnRound);
		Protocol::DelStub( &stub_CGame_CTOS_Ready);
		Protocol::DelStub( &stub_CAccount_STOA_Find);	
		Protocol::DelStub( &stub_CAccount_ATOS_Info);	
		Protocol::DelStub( &stub_CAccount_STOA_Register);	
		Protocol::DelStub( &stub_CRoom_CTOS_EnterRoom);	
		Protocol::DelStub( &stub_CApply_CTOS_EnterCompetition);	
		Protocol::DelStub( &stub_CAccount_HTOA_AccountInfo);	
		Protocol::DelStub( &stub_CGameGoldsChangedInfo);
		Protocol::DelStub( &stub_CReport_CTOS_LBSRelatedInfo);	
		Protocol::DelStub( &stub_CGame_STOC_MatchRank);
		Protocol::DelStub( &stub_CGame_STOC_MatchHistory);
		Protocol::DelStub( &stub_CGame_STOC_MatchReconnect);
		Protocol::DelStub( &stub_CMatch_CTOS_Signup);
		Protocol::DelStub( &stub_CGame_CTOS_MatchRequest);
		Protocol::DelStub( &stub_CAccount_HttpTOA_UpdataPlayerInfo);
		Protocol::DelStub( &stub_CAccount_Mem_UpdataPlayerInfo);
		Protocol::DelStub( &stub_CFriend_CTOS_Request);
		Protocol::DelStub( &stub_CFriend_CTOS_List);
		Protocol::DelStub( &stub_CFriend_CTOS_Talk);		
		Protocol::DelStub( &stub_CFriend_CTOS_Record);
		Protocol::DelStub( &stub_CFriend_STOC_Request);
		Protocol::DelStub( &stub_CFriend_STOC_List);
		Protocol::DelStub( &stub_CFriend_STOC_Talk);
		Protocol::DelStub( &stub_CFriend_STOC_Record);
		Protocol::DelStub( &stub_CFriend_CTOS_RecordList);
		Protocol::DelStub( &stub_CFriend_STOC_RecordList);
		Protocol::DelStub( &stub_CFriend_CTOS_TalkWindow);
		Protocol::DelStub( &stub_CGame_STOC_MatchMessage);
		Protocol::DelStub( &stub_CGame_CTOS_Trusteeship);
		Protocol::DelStub( &stub_CGame_STOA_PlayerStateNotify);
		Protocol::DelStub( &stub_CLogin_STOC_Succeed);
		Protocol::DelStub( &stub_CGame_STOC_NotCanOut);
		Protocol::DelStub( &stub_CGame_CTOS_PlayerInfo);
	}
}

void RegisterProtocols()
{
	InnerProtocolsStubs( true);
}

void UnregisterProtocols()
{
	InnerProtocolsStubs( false);
}