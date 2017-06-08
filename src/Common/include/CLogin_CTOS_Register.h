#ifndef _CLOGINCTOSREGISTER_H
#define _CLOGINCTOSREGISTER_H

#include "Opcodes.h"
#include "Protocol.h"

class CLogin_CTOS_Register : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_REGISTER};

	// 不需要用到的字符串填 ""
	std::string m_strPhone;				// 电话号码  
	std::string m_strAccount;			// 账号  或 验证码
	std::string m_strPassword;			// 密码
	std::string m_strDeviceNum;			// 设备号
	uint8		m_iRegisterType;		// 注册类型  Opcodes.h   enumRegisterType
	

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