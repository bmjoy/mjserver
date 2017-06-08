#ifndef _CFRIDENCTOSREQUEST_H
#define _CFRIDENCTOSREQUEST_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_Request : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDREQUEST};

	uint8  msgType;     //子消息类型
	uint32 playID;	    //玩家
	uint32 friendID;	//准备添加的好友
	CFriend_CTOS_Request()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>msgType;
		data>>playID;
		data>>friendID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<msgType;
		data<<playID;
		data<<friendID;
	}

};
#endif	//_CFRIDENCTOSREQUEST_H