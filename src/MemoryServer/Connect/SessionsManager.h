#ifndef __SESSIONSMANAGER_H
#define __SESSIONSMANAGER_H

#include "Common.h"

typedef set<CSession*> SessionSet;

class SERVER_DECL CSessionsManager : public Singleton<CSessionsManager>
{
public:
	void Update(time_t diff);

	void UpdateSessions(uint32 diff);

	void DeleteSessions(std::list< CSession* > &slist);

	void AddGlobalSession(CSession* session);

	// 账号数据库服务器特有  获取唯一的session
	CSession* GetOnlySession();

private:
	typedef HM_NAMESPACE::hash_map<uint32, CSession*> SessionMap;
	SessionMap m_sessions;

	RWLock m_sessionlock;

protected:
	Mutex SessionsMutex;//FOR GLOBAL !
	SessionSet Sessions;
};

#define sSessionsManager CSessionsManager::getSingleton()

#endif //__SESSIONSMANAGER_H