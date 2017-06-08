#ifndef _MODULEMANAGER_H
#define _MODULEMANAGER_H

#include "Common.h"
#include <list>


using namespace std;

class CModuleBase;
class CSession;

class CLoginModule;
class CMatchModule;


class CModuleManager : public Singleton<CModuleManager>
{

public:
	CModuleManager();
	~CModuleManager();

	void ProcessProtocols(uint16 Opcode, ProtoProtocol* ptrPacket, CSession * pSession);

	void RegisterModule(CModuleBase * module);

	void SetPrimary(CModuleBase* module);

	void SetLast(CModuleBase* module);
	
protected:
private:
	list<CModuleBase*> m_ModuleList;

	CLoginModule* m_pLoginModule;

};

#define sModuleManager CModuleManager::getSingleton()


#endif	//_MODULEMANAGER_H