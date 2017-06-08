#ifndef _CACCOUNTMEMGAMEINFO_H
#define _CACCOUNTMEMGAMEINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_Mem_GameInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_MEM_GAMEINFO};

	uint32			account_id;				// 账号ID		= 0 代表空地址位
	uint64			account_gold;			// 手气值
	uint64			account_present;		// 礼品券
	uint64			account_exp;			// 经验
	uint64			account_lost;			// 输局数
	uint64			account_win;			// 赢局数

	CAccount_Mem_GameInfo()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>account_id;			
		data>>account_gold;			
		data>>account_present;		
		data>>account_exp;			
		data>>account_lost;			
		data>>account_win;			
	}

	void WriteProtocol(Protocol & data)
	{
		data<<account_id;			
		data<<account_gold;			
		data<<account_present;		
		data<<account_exp;			
		data<<account_lost;			
		data<<account_win;			
	}
};

#endif	//_CACCOUNTMEMGAMEINFO_H