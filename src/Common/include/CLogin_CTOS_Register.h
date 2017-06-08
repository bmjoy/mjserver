#ifndef _CLOGINCTOSREGISTER_H
#define _CLOGINCTOSREGISTER_H

#include "Opcodes.h"
#include "Protocol.h"

class CLogin_CTOS_Register : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_REGISTER};

	// ����Ҫ�õ����ַ����� ""
	std::string m_strPhone;				// �绰����  
	std::string m_strAccount;			// �˺�  �� ��֤��
	std::string m_strPassword;			// ����
	std::string m_strDeviceNum;			// �豸��
	uint8		m_iRegisterType;		// ע������  Opcodes.h   enumRegisterType
	

	CLogin_CTOS_Register()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strPhone;	
		data>>m_strAccount;
		data>>m_strPassword;
		data>>m_strDeviceNum;
		data>>m_iRegisterType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strPhone;	
		data<<m_strAccount;
		data<<m_strPassword;
		data<<m_strDeviceNum;
		data<<m_iRegisterType;
	}

};



#endif	//_CLOGINCTOSREGISTER_H