#ifndef _CACCOUNTSTOCRESETUSERINFO_H
#define _CACCOUNTSTOCRESETUSERINFO_H

#include "Opcodes.h"
#include "Protocol.h"

class CAccount_STOC_ResetUserInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_RESETUSERINFO};

	bool			account_sex;			// �Ա� 0 �� 1Ů
	std::string		account_PlayerName;		// �ǳ�
	uint32			account_HeadVersion; 	// ͷ��汾��
	uint8			account_province; 		// ʡ����
	uint8			account_city; 			// �д���

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