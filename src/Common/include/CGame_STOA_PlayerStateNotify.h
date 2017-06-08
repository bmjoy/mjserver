#ifndef _CGAMESTOA_PLAYERSTATENOTIFY_H
#define _CGAMESTOA_PLAYERSTATENOTIFY_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOA_PlayerStateNotify : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SERVER_STATENOTIFY};

	uint32				m_RoomID;		// ����ID  Ϊ0 �����˳�����
	uint32				m_PlayerID;		// ��ɫID  
	CGame_STOA_PlayerStateNotify()
	{
		m_opcode = PROTOCOL_TYPE;
		m_RoomID = 0;
		m_PlayerID = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_RoomID;
		data>>m_PlayerID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_RoomID;
		data<<m_PlayerID;
	}

};



#endif	//_CGAMESTOA_PLAYERSTATENOTIFY_H