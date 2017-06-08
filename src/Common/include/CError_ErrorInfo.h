#ifndef _CError_ErrorInfo_H
#define _CError_ErrorInfo_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CError_ErrorInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_ERROR};

	uint32		ErrorTypeID;
	uint32		Param1;
	uint32		ErrorSubtypes ;				//´íÎó×ÓÀàÐÍ
	uint32		ErrorCode;					//

	std::string ErrorString;
	
	CError_ErrorInfo()
	{
		ErrorString = "";
		m_opcode = PROTOCOL_TYPE;
		ErrorSubtypes =0;
		ErrorCode = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>ErrorTypeID;
		data>>Param1;
		data>>ErrorSubtypes;
		data>>ErrorCode;
		data>>ErrorString;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<ErrorTypeID;
		data<<Param1;
		data<<ErrorSubtypes;
		data<<ErrorCode;
		data<<ErrorString;
	}
};

#endif	//_CError_ErrorInfo_H