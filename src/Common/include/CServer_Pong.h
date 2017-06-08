#ifndef _CSERVERPONG_H
#define _CSERVERPONG_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CServer_Pong : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_PONG};

	uint8		ID;
	
	CServer_Pong()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>ID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<ID;
	}
};

#endif	//_CSERVERPONG_H