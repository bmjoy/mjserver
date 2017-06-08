#ifndef _CFRIDENCTOSLIST_H
#define _CFRIDENCTOSLIST_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_List : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDLIST};
	uint32 playID;
	
	CFriend_CTOS_List()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
	}

};
#endif	//_CFRIDENCTOSLIST_H