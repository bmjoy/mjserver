#ifndef _CFRIDENCTOSTALK_H
#define _CFRIDENCTOSTALK_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_Talk : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDTALK};
	
	uint32 playID;	    //聊天发起方
	uint32 friendID;	//聊天接收方
	std::string strTalk;	//聊天内容
	bool	isOpen;			//服务端标志，客户端不需要改

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