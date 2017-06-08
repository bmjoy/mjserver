#ifndef _CACCOUNTHTOAACCOUNTINFO_H
#define _CACCOUNTHTOAACCOUNTINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"



class CAccount_HTOA_AccountInfo : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SA_HTTPACCOUNTINFO};

	// ����Ҫ�õ����ַ����� ""

	std::string m_strAccount;			// �˺�
	std::string m_strPassword;			// ����
	uint64		m_iUserID;				// �û������˺�
	uint32		m_iRegisterID;			// ע������ID  Ψһ���к�   ����ʱ�뽫��IDԭ������

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