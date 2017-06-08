#ifndef __PROCESSMANAGER_H
#define __PROCESSMANAGER_H

#include "Common.h"
#include <list>

using namespace std;


class Protocol;
class CSession;
//class CGameFrameSession;
//class CHallManager;

class CProcessManager : public Singleton<CProcessManager>
{

public:
	CProcessManager();
	~CProcessManager();

	void ProcessProtocols(uint16 Opcode, Protocol* ptrPacket,CSession * pSession);
	void Update(uint32 diff);
private:
	void ProcessErrorInfo( Protocol* ptrPacket,CSession * pSession);
	void ProcessAccountLogin( Protocol* ptrPacket,CSession * pSession);

	void ProcessMatchHis( Protocol* ptrPacket,CSession * pSession);
	void ProcessGameOver( Protocol* ptrPacket,CSession * pSession);
	void ProcessItemChange( Protocol* ptrPacket,CSession * pSession);
	
	void ProcessAccountFind( Protocol* ptrPacket,CSession * pSession);	
	void ProcessAccountRegister( Protocol* ptrPacket,CSession * pSession);
	void ProcessAccountInfo( Protocol* ptrPacket,CSession * pSession);
	void ProcessModifyAccountData( Protocol* ptrPacket,CSession * pSession);
	void ProcessHttpAccountData( Protocol* ptrPacket,CSession * pSession);
	void ProcessGoldSchanged( Protocol* ptrPacket,CSession * pSession);
	void ProcessLBSInfo( Protocol* ptrPacket,CSession * pSession);
	void ProcessHttpInfo( Protocol* ptrPacket,CSession * pSession);
	void ProcessGameInfoToHttp( Protocol* ptrPacket,CSession * pSession);
	void ProcessPlayerInfo( Protocol* ptrPacket,CSession * pSession);
		
	void SendToAccountMemServer(Protocol* sendinfo);
};

#define sProcessManager CProcessManager::getSingleton()

#endif	//__PROCESSMANAGER_H