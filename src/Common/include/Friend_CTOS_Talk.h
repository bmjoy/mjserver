#ifndef _CFRIDENCTOSTALK_H
#define _CFRIDENCTOSTALK_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_Talk : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDTALK};
	
	uint32 playID;	    //���췢��
	uint32 friendID;	//������շ�
	std::string strTalk;	//��������
	bool	isOpen;			//����˱�־���ͻ��˲���Ҫ��

	CFriend_CTOS_Talk()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{		
		data>>playID;
		data>>friendID;
		data>>strTalk;
		data>>isOpen;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<strTalk;
		data<<isOpen;
	}

};
#endif	//_CFRIDENCTOSTALK_H