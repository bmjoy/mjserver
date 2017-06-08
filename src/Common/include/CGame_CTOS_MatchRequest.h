#ifndef _CGAMECTOSMATCHREQUEST_H
#define _CGAMECTOSMATCHREQUEST_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_CTOS_MatchRequest : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_MATCHREQUEST};

	uint8				eRequestType;	// MATCHREQUEST_HISTORY = 1 请求比赛历史


	CGame_CTOS_MatchRequest()
	{
		m_opcode = PROTOCOL_TYPE;
		eRequestType = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>eRequestType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<eRequestType;
	}


};



#endif	//_CGAMECTOSMATCHREQUEST_H