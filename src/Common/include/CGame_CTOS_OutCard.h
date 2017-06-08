#ifndef _CGAMECTOSOUTCARD_H
#define _CGAMECTOSOUTCARD_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_CTOS_OutCard : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_GAMEOUTCARD};
	uint32 size;
	std::vector<uint8>	OutCards;
	CGame_CTOS_OutCard()
	{
		size = 0;
		OutCards.clear();
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>size;
		data>>OutCards;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<size;
		data<<OutCards;
	}

};



#endif	//_CGAMECTOSOUTCARD_H