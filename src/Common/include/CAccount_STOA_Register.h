#ifndef _CACCOUNTSTOAREGISTER_H
#define _CACCOUNTSTOAREGISTER_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"



class CAccount_STOA_Register : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SA_ACCOUNTREGISTER};

	// ����Ҫ�õ����ַ����� ""
	std::string m_strPhone;				// �绰����  
	std::string m_strAccount;			// �˺�  �� ��֤��
	std::string m_strPassword;			// ����
	std::string m_strIP;				// IP
	std::string m_strDeviceNum;			// �豸��
	uint8		m_iRegisterType;		// ע������  Opcodes.h   enumRegisterType
	uint32		m_iRegisterID;			// ע������ID  Ψһ���к�   ����ʱ�뽫��IDԭ������

	CAccount_STOA_Register()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strPhone;			
		data>>m_strAccount;			
		data>>m_strPassword;		
		data>>m_strIP;				
		data>>m_strDeviceNum;		
		data>>m_iRegisterType;		
		data>>m_iRegisterID;		
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strPhone;			
		data<<m_strAccount;			
		data<<m_strPassword;		
		data<<m_strIP;				
		data<<m_strDeviceNum;		
		data<<m_iRegisterType;		
		data<<m_iRegisterID;		
	}
};

#endif	//_CACCOUNTSTOAREGISTER_H