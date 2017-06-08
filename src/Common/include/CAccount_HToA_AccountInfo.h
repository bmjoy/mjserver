#ifndef _CACCOUNTHTOAACCOUNTINFO_H
#define _CACCOUNTHTOAACCOUNTINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"



class CAccount_HTOA_AccountInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SA_HTTPACCOUNTINFO};

	// 不需要用到的字符串填 ""

	std::string m_strAccount;			// 账号
	std::string m_strPassword;			// 密码
	uint64		m_iUserID;				// 用户数字账号
	uint32		m_iRegisterID;			// 注册序列ID  唯一序列号   返回时请将此ID原样返回

	CAccount_HTOA_AccountInfo()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strAccount;		
		data>>m_strPassword;	
		data>>m_iUserID;		
		data>>m_iRegisterID;		
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strAccount;		
		data<<m_strPassword;	
		data<<m_iUserID;		
		data<<m_iRegisterID;		
	}
};

#endif	//_CACCOUNTHTOAACCOUNTINFO_H