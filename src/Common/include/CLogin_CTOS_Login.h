#ifndef _CLOGINCTOSLOGIN_H
#define _CLOGINCTOSLOGIN_H

#include "Opcodes.h"
#include "Protocol.h"

class CLogin_CTOS_Login : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_LOGINLOGIN};

	std::string m_strAccount;	// 测试期间只需要保证m_strAccount为不重复的数值
	std::string m_strPassword;
	uint8 m_LoginType;			// 100 退出登录   0 为账号密码登陆 1 为手机登陆

	CLogin_CTOS_Login()
	{
		m_LoginType = 0;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strAccount;
		data>>m_strPassword;
		data>>m_LoginType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strAccount;
		data<<m_strPassword;
		data<<m_LoginType;
	}
};



#endif	//_CLOGINCTOSLOGIN_H