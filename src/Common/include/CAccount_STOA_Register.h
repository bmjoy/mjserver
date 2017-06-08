#ifndef _CACCOUNTSTOAREGISTER_H
#define _CACCOUNTSTOAREGISTER_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"



class CAccount_STOA_Register : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SA_ACCOUNTREGISTER};

	// 不需要用到的字符串填 ""
	std::string m_strPhone;				// 电话号码  
	std::string m_strAccount;			// 账号  或 验证码
	std::string m_strPassword;			// 密码
	std::string m_strIP;				// IP
	std::string m_strDeviceNum;			// 设备号
	uint8		m_iRegisterType;		// 注册类型  Opcodes.h   enumRegisterType
	uint32		m_iRegisterID;			// 注册序列ID  唯一序列号   返回时请将此ID原样返回

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