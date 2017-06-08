#ifndef _CLOGINSTOCREGISTER_H
#define _CLOGINSTOCREGISTER_H

#include "Opcodes.h"
#include "Protocol.h"

class CLogin_STOC_Register : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_REGISTER};

	std::string m_strAccount;			// �˺�  �� ��֤��
	std::string m_strPassword;			// ����
	uint64		m_iUserID;				// �û�ID


	CLogin_STOC_Register()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strAccount;		
		data>>m_strPassword;	
		data>>m_iUserID;		
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strAccount;		
		data<<m_strPassword;	
		data<<m_iUserID;		
	}

};



#endif	//_CLOGINCTOSREGISTER_H