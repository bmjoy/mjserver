#ifndef _CGAMESTOCNOTCANOUT_H
#define _CGAMESTOCNOTCANOUT_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_NotCanOut : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMENOTCANOUT};

	uint32	PlayerID;

	CGame_STOC_NotCanOut()
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