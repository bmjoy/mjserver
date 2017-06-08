#ifndef _CACCOUNTHTTPTOAINFO_H
#define _CACCOUNTHTTPTOAINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_HttpTOA_Info : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_HTTPTOA_INFO};

	uint8			optType;				// 	
	uint32			optParam1;				// 	

	CAccount_HttpTOA_Info()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>optType;
		data>>optParam1;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<optType;
		data<<optParam1;
	}
};

#endif	//_CACCOUNTHTTPTOAINFO_H