#ifndef _CACCOUNTMEMGAMEINFO_H
#define _CACCOUNTMEMGAMEINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_Mem_GameInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_MEM_GAMEINFO};

	uint32			account_id;				// �˺�ID		= 0 ����յ�ַλ
	uint64			account_gold;			// ����ֵ
	uint64			account_present;		// ��Ʒȯ
	uint64			account_exp;			// ����
	uint64			account_lost;			// �����
	uint64			account_win;			// Ӯ����

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