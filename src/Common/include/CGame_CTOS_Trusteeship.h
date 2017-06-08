#ifndef _CTOS_TRUSTEESHIP_H
#define _CTOS_TRUSTEESHIP_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_CTOS_Trusteeship :public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_WH_CLIENTTRUSTEESHIP};

	bool			ClientTrusteeship;		//玩家是否设置托管;

	CGame_CTOS_Trusteeship()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>ClientTrusteeship;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<ClientTrusteeship;
	}

};



#endif	//_CTOS_TRUSTEESHIP_H