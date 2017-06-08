#ifndef __PROCESSMANAGER_H
#define __PROCESSMANAGER_H

#include "Common.h"
#include <list>

using namespace std;


class Protocol;
class CSession;
//class CGameFrameSession;
//class CHallManager;

struct HttpRequestInfo
{
	uint8 RequestType;
	uint32 RequestParam1;
};

class CProcessManager : public Singleton<CProcessManager>
{

public:
	CProcessManager();
	~CProcessManager();

	void ProcessProtocols(uint16 Opcode, Protocol* ptrPacket,CSession * pSession);
	
	void Update(uint32 diff);	
private:
	void ProcessAccountFind( Protocol* ptrPacket,CSession * pSession);
	void ProcessGoldSchanged( Protocol* ptrPacket,CSession * pSession);
	void ProcessGameOver( Protocol* ptrPacket,CSession * pSession);
	
	void ProcessHttpInfo( Protocol* ptrPacket,CSession * pSession);

	void ProcessMatchHis( Protocol* ptrPacket,CSession * pSession);
	void ProcessItemChange( Protocol* ptrPacket,CSession * pSession);


	void ProcessPlayerInfo( Protocol* ptrPacket,CSession * pSession);	
	

//public:
//	HttpRequestInfo* GetHttpRequest();

private:
	std::list<HttpRequestInfo*> m_HttpRequestList;

};

#define sProcessManager CProcessManager::getSingleton()

#endif	//__PROCESSMANAGER_H