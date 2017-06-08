#ifndef _CFRIDENCTOSRECORD_H
#define _CFRIDENCTOSRECORD_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_Record : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDRECORD};
		
	uint32 playID;	    //玩家
	uint32 friendID;	//想查看谁的记录
	uint64 timeBase;	//时间基准值，为0就是取最近的记录
	uint16 pageSize;	//一页显示多少条记录
	uint8  msgType;		//0为查看留言，1为查看聊天记录

	CFriend_CTOS_Record()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>friendID;
		data>>timeBase;
		data>>pageSize;
		data>>msgType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<timeBase;
		data<<pageSize;
		data<<msgType;
	}

};
#endif	//_CFRIDENCTOSRECORD_H