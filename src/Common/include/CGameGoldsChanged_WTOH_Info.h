#ifndef _CGAMEGOLDSCJANDEDWTOHINFO_H
#define _CGAMEGOLDSCJANDEDWTOHINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CGameGoldsChanged_WTOH_Info : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_WH_GOLDSCHANGED};


	uint8			golds_plusvornot;		// ��� 1��ʾ����
	uint32			golds_type;				//�������ԭ���ʾ��;
	uint32			account_id;				// �˺�ID	
	uint32			account_gold;			// �����Ľ��ֵ��û�и�����
	
	

	CGameGoldsChanged_WTOH_Info()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>golds_plusvornot;			
		data>>golds_type;			
		data>>account_id;		
		data>>account_gold;				
	}

	void WriteProtocol(Protocol & data)
	{
		data<<golds_plusvornot;			
		data<<golds_type;			
		data<<account_id;		
		data<<account_gold;				
	}
};

#endif	//_CGAMEGOLDSCJANDEDWTOHINFO_H