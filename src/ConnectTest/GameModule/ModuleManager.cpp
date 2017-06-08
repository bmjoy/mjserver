#include "ConnectTestStdafx.h"

initialiseSingleton(CModuleManager);


CModuleManager::CModuleManager()
{
	m_ModuleList.clear();

	m_pLoginModule = new CLoginModule();
}

CModuleManager::~CModuleManager()
{
	for (list<CModuleBase*>::iterator it = m_ModuleList.begin();it!=m_ModuleList.end();++it)
	{
		delete (*it);
	}
	m_ModuleList.clear();
}

void CModuleManager::ProcessProtocols(uint16 Opcode, ProtoProtocol* ptrPacket, CSession * pSession)
{
	for (list<CModuleBase*>::iterator it = m_ModuleList.begin();it!=m_ModuleList.end();++it)
	{
		if ((*it)->IsRegisterOpcode(Opcode))
		{
			(*it)->ProcessProtocol(Opcode,ptrPacket,pSession);
		}
	}
}

void CModuleManager::RegisterModule(CModuleBase * module)
{
	m_ModuleList.push_back(module);
}


void CModuleManager::SetPrimary(CModuleBase* module)
{
	for (list<CModuleBase*>::iterator it = m_ModuleList.begin();it!=m_ModuleList.end();++it)
	{
		if ((*it) == module)
		{
			m_ModuleList.erase(it);
			break;
		}
	}
	m_ModuleList.push_front(module);
}

void CModuleManager::SetLast(CModuleBase* module)
{
	for (list<CModuleBase*>::iterator it = m_ModuleList.begin();it!=m_ModuleList.end();++it)
	{
		if ((*it) == module)
		{
			m_ModuleList.erase(it);
			break;
		}
	}
	m_ModuleList.push_back(module);
}
