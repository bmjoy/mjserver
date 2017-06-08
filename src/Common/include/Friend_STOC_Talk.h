#ifndef _CFRIDENSTOCTALK_H
#define _CFRIDENSTOCTALK_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_STOC_Talk : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDTALK};

	uint32 playID;	    //���췢��
	uint32 friendID;	//������շ�
	time_t recvTime;	//����ʱ��
	std::string strTalk;	//��������

	CFriend_STOC_Talk()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{		
		data>>playID;
		data>>friendID;
		data>>recvTime;
		data>>strTalk;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<recvTime;
		data<<strTalk;
	}

};
#endif	//_CFRIDENSTOCTALK_H