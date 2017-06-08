#ifndef _GAMESTOCOUTCARD_H
#define _GAMESTOCOUTCARD_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_OutCard : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMEOUTCARD};

	uint32				PlayerID;		// �ĸ���ҵ���  ��������
	std::vector<uint8>	OutCards;		// ������

	CGame_STOC_OutCard()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>PlayerID;
		data>>OutCards;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<PlayerID;
		data<<OutCards;
	}

};



#endif	//_GAMESTOCOUTCARD_H