#ifndef _CGAMECTOSREADY_H
#define _CGAMECTOSREADY_H

#include "Opcodes.h"
#include "Protocol.h"


class CGame_CTOS_Ready : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_GAMEREADY};

	uint32	Reserve;			// 

	CGame_CTOS_Ready()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>Reserve;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<Reserve;
	}

};



#endif	//_CGAMECTOSREADY_H