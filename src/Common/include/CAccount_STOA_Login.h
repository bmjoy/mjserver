#ifndef _CACCOUNTSTOALOGIN_H
#define _CACCOUNTSTOALOGIN_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_STOA_Login : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SERVER_LOGIN};

	uint8		LoginType;
	uint32		AccountID;
	
	CAccount_STOA_Login()
	{
		m_opcode = PROTOCOL_TYPE;
		LoginType = LoginType_Login;
		AccountID = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>LoginType;
		data>>AccountID;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<LoginType;
		data<<AccountID;
	}
};

#endif	//_CACCOUNTSTOALOGIN_H