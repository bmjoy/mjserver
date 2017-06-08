#ifndef _CGAMESTOCOVER_H
#define _CGAMESTOCOVER_H

#include "Opcodes.h"
#include "Protocol.h"


class CGame_STOC_Over : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMEOVER};

	uint32	WinnerID;			// 胜利玩家
	uint32	BaopeiCharID;		// 包赔玩家
	uint32	BaseRate;			// 基础赔率
	TGameSettlement	SettlePlayer[3];

	CGame_STOC_Over()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>WinnerID;
		data>>BaopeiCharID;
		data>>BaseRate;
		for (int i = 0;i<3;i++)
		{
			data>>SettlePlayer[i].isEscape;
			data>>SettlePlayer[i].RemainCardNum;
			data>>SettlePlayer[i].ChrID;
			data>>SettlePlayer[i].AddExp;
			data>>SettlePlayer[i].AddMoney;
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<WinnerID;
		data<<BaopeiCharID;
		data<<BaseRate;
		for (int i = 0;i<3;i++)
		{
			data<<SettlePlayer[i].isEscape;
			data<<SettlePlayer[i].RemainCardNum;
			data<<SettlePlayer[i].ChrID;
			data<<SettlePlayer[i].AddExp;
			data<<SettlePlayer[i].AddMoney;
		}
	}

};



#endif	//_CGAMESTOCOVER_H