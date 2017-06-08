#ifndef _GAME_STOC_CHANGEGOLD_H_
#define _GAME_STOC_CHANGEGOLD_H_

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CGame_STOC_ChangeGold : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_CHANGEGOLD};

	uint8				ChangeType;	
	uint8				ChangeItemType;	
	uint32				playerID;
	int32				ChangeNum;
	int32				NowNum;
	
	CGame_STOC_ChangeGold()
	{
		m_opcode = PROTOCOL_TYPE;

		ChangeType = 0;	
		ChangeItemType = 0;	
		playerID = 0;
		ChangeNum = 0;	
		NowNum = 0;	
	}

	void ReadProtocol(Protocol & data)
	{
		data>>ChangeType;
		data>>ChangeItemType;
		data>>playerID;
		data>>ChangeNum;
		data>>NowNum;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<ChangeType;
		data<<ChangeItemType;
		data<<playerID;
		data<<ChangeNum;
		data<<NowNum;
	}

};



#endif	//_GAME_STOC_CHANGEGOLD_H_