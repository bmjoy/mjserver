#ifndef _CFRIDENCTOSTALKWINDOW_H
#define _CFRIDENCTOSTALKWINDOW_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_TalkWindow : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDTALKWINDOW};
	uint32 playID;  //打开窗口的玩家
	uint32 friendID; //朋友ID
	bool   openStatus; //1为打开窗口,0为关闭窗口

	CFriend_CTOS_TalkWindow()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>friendID;
		data>>openStatus;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<openStatus;
	}

};
#endif	//_CFRIDENCTOSTALKWINDOW_H