#ifndef _CFRIDENCTOSRECORDLIST_H
#define _CFRIDENCTOSRECORDLIST_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_RecordList : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDRECORDLIST};

	uint32 playID;	    //Íæ¼Ò	

	CFriend_CTOS_RecordList()
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
#endif	//_CFRIDENCTOSRECORDLIST_H