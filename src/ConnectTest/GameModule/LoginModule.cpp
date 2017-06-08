#include "ConnectTestStdafx.h"

#include <string>
#include <iostream>
#include <fstream>




CLoginModule::CLoginModule()
{
	sModuleManager.RegisterModule(this);
	RegisterProtocolIDs();
}

CLoginModule::~CLoginModule()
{
	
}

void CLoginModule::RegisterProtocolIDs()
{
	RegisterProtocolID(MSG_CS_LOGINLOGIN);
	RegisterProtocolID(MSG_AS_ACCOUNTINFO);
	RegisterProtocolID(MSG_ERROR);
	RegisterProtocolID(MSG_PROTOTEST);
}

void CLoginModule::ProcessProtocol(uint16 Opcode, ProtoProtocol* ptrPacket, CSession * pSession)
{
	switch (Opcode)
	{
	//case MSG_CS_LOGINLOGIN:
	//	ProcessLogin(ptrPacket,pSession);
	//	break;

	default:
		break;
	}
}
//
//void CLoginModule::DoLogin(CPlayerData* pdata,CSession * pSession)
//{
//	if ((!pdata) || (!pSession) )
//		return;
//
//	if (pdata->GetPlayerSession() != NULL)
//	{
//		m_proto_error.Clear();
//		m_proto_error.set_ierrorid(ErrorCode_AccountRepeatLogin);
//		m_proto_error.SerializeToString(&m_inputStr);
//		pSession->SendPacket(m_inputStr,MSG_ERROR);
//		return;
//	}
//
//	pdata->SetIsLogin(true);
//	
//	// �������session
//	pSession->BindPlayer(pdata);
//	pdata->SetPlayerSession(pSession);
//	if (!pSession->GetSocket())
//		return;
//
//	// �ҵ���ʵ����  ��֤�˺�����  ���ص�½�ɹ�����һ�������
//	pdata->SendAccountInfo();
//
//	// ���ط�����Ϣ
//	sRoomManager.SendRoomList(pSession);
//	sRoomManager.SendMatchList(pSession);
//	
//	if (pdata->GetInfo()->PlayerState == PLAYERSTATE_PLAYING)
//	{
//		DealReconnect(pdata);
//
//		if (pdata->GetMatchID())
//			SendMatchReconnect(pdata);
//	}else
//	{
//		if (pdata->GetMatchID())
//		{
//			// ���ͱ���������Ϣ
//			SendMatchReconnect(pdata);
//		}
//	}
//}

//void CLoginModule::DealReconnect(CPlayerData* pdata)
//{
//	uint32 roomID = pdata->GetRoomID();
//
//	// ������������
//	CError_ErrorInfo ErrorInfo;
//	ErrorInfo.ErrorTypeID = ErrorCode_EnterRoomSuccess;
//	ErrorInfo.Param1 = roomID;
//	pdata->GetPlayerSession()->SendPacket(&ErrorInfo);
//
//	CGameNotifyBase* pNotify = sGameLogic.GetGameNotify();
//	if (pNotify)
//	{
//		pNotify->DealReconnect(pdata);
//	}
//}
