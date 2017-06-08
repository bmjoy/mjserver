#ifndef _LOGINMODULE_H_
#define _LOGINMODULE_H_

#include "Common.h"
#include "ModuleBase.h"
//#include "login_c2s_login.pb.h"
//#include "com_s2c_errorinfo.pb.h"

class ProtoProtocol;


class CLoginModule : public CModuleBase 
{
public:
	CLoginModule();
	~CLoginModule();
	virtual void ProcessProtocol(uint16 Opcode, ProtoProtocol* ptrPacket, CSession * pSession);

	void RegisterProtocolIDs();
private:
	void ProcessLogin(ProtoProtocol* ptrPacket, CSession * pSession);


private:
	//stringstream m_input;
	//std::string m_inputStr;
	//protocol::Login_C2S_Login m_proto_login;
	//protocol::ErrorInfo m_proto_error;
};


#endif	//_LOGINMODULE_H_