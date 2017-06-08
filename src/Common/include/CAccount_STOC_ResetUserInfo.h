#ifndef _CACCOUNTSTOCRESETUSERINFO_H
#define _CACCOUNTSTOCRESETUSERINFO_H

#include "Opcodes.h"
#include "Protocol.h"

class CAccount_STOC_ResetUserInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_RESETUSERINFO};

	bool			account_sex;			// 性别 0 男 1女
	std::string		account_PlayerName;		// 昵称
	uint32			account_HeadVersion; 	// 头像版本号
	uint8			account_province; 		// 省代码
	uint8			account_city; 			// 市代码

	CAccount_STOC_ResetUserInfo()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>account_sex;			
		data>>account_PlayerName;	
		data>>account_HeadVersion; 	
		data>>account_province; 	
		data>>account_city; 		
	}

	void WriteProtocol(Protocol & data)
	{
		data<<account_sex;			
		data<<account_PlayerName;	
		data<<account_HeadVersion; 	
		data<<account_province; 	
		data<<account_city; 		
	}

};


#endif	//_CACCOUNTSTOCRESETUSERINFO_H