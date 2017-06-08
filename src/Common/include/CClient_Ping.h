#ifndef _CCLIENTPING_H
#define _CCLIENTPING_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CClient_Ping : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_PING};

	uint8		ID;
	
	CClient_Ping()
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

#endif	//_CCLIENTPING_H