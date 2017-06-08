#ifndef _CGAMECTOSPLALYERINFO_H
#define _CGAMECTOSPLALYERINFO_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_CTOS_PlayerInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_PLAYERINFO};
	uint32  playerId;
	uint8   Key;
	uint32	Param;
	uint64	Value;
	CGame_CTOS_PlayerInfo()
	{
		playerId = 0;
		Key = 0;
		Param = 0;
		Value = 0;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playerId;
		data>>Key;
		data>>Param;
		data>>Value;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playerId;
		data<<Key;
		data<<Param;
		data<<Value;
	}

};
#endif	//_CGAMECTOSPLALYERINFO_H