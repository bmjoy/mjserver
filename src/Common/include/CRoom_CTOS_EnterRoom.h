#ifndef _CROOMCTOSENTERROOM_H
#define _CROOMCTOSENTERROOM_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CRoom_CTOS_EnterRoom : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_ENTERROOM};

	uint32	RoomID;

	CRoom_CTOS_EnterRoom()
	{
		m_opcode = PROTOCOL_TYPE;
	}
	
	void ReadProtocol(Protocol & data)
	{
		data>>RoomID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RoomID;
	}
};

#endif	//_CROOMCTOSENTERROOM_H