#ifndef _CGAMESTOCTURNROUND_H
#define _CGAMESTOCTURNROUND_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_TurnRound : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_TURNROUND};

	uint32	PlayerID;

	CGame_STOC_TurnRound()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>PlayerID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<PlayerID;
	}


};



#endif	//_CGAMESTOCTURNROUND_H