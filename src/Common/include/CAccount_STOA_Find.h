#ifndef _CACCOUNTSTOAFIND_H
#define _CACCOUNTSTOAFIND_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_STOA_Find : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SA_ACCOUNTFIND};

	std::string strAccount;
	std::string strPassword;
	uint8		iLoginType;
	
	CAccount_STOA_Find()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>strAccount;
		data>>strPassword;
		data>>iLoginType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<strAccount;
		data<<strPassword;
		data<<iLoginType;
	}
};

#endif	//_CACCOUNTSTOAFIND_H