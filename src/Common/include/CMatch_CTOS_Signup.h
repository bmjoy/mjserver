#ifndef _CMATCHCTOSSIGNUP_H
#define _CMATCHCTOSSIGNUP_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CMatch_CTOS_Signup : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_Match_Signup};

	uint8	type;		// 1 ±¨Ãû  0 ÍËÈü
	uint16	MatchID;

	CMatch_CTOS_Signup()
	{
		m_opcode = PROTOCOL_TYPE;
	}
	
	void ReadProtocol(Protocol & data)
	{
		data>>type;
		data>>MatchID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<type;
		data<<MatchID;
	}
};

#endif	//_CMATCHCTOSSIGNUP_H