#include "ConnectTestStdafx.h"

initialiseSingleton(CSessionsManager);

void CSessionsManager::Update(time_t diff)
{

}

void CSessionsManager::UpdateSessions(uint32 diff)
{
	SessionSet::iterator itr, it2;
	CSession* session;
	int result;

	std::list< CSession* > ErasableSessions;

	SessionsMutex.Acquire();

	for(itr = Sessions.begin(); itr != Sessions.end();)
	{
		session = (*itr);
		it2 = itr;
		++itr;
		if(!session /*|| session->instanceId != 0*/)
		{
			Sessions.erase(it2);
			continue;
		}

		if((result = session->Update(0)) != 0)
		{
			if(result == 1)
			{
				ErasableSessions.push_back(session);
			}
			Sessions.erase(it2);
		}
	}

	SessionsMutex.Release();

	DeleteSessions(ErasableSessions);
	ErasableSessions.clear();
}

void CSessionsManager::DeleteSessions(std::list< CSession* > &slist)
{
	m_sessionlock.AcquireWriteLock();

	for(std::list< CSession* >::iterator itr = slist.begin(); itr != slist.end(); ++itr)
	{
		CSession* s = *itr;
		m_sessions.erase(s->instanceId);
	}

	m_sessionlock.ReleaseWriteLock();

	for(std::list< CSession* >::iterator itr = slist.begin(); itr != slist.end(); ++itr)
	{
		CSession* s = *itr;
		delete s;
	}
}

void CSessionsManager::AddGlobalSession(CSession* session)
{
	assert(session != NULL);

	SessionsMutex.Acquire();
	Sessions.insert(session);
	SessionsMutex.Release();
}

void CSessionsManager::SendAccountInfo(uint32 serverid,Protocol* pInfo)
{
	CSession* pSession = NULL;
	SessionsMutex.Acquire();
	for (SessionSet::iterator it = Sessions.begin();it!=Sessions.end();++it)
	{
		pSession = (*it);
		if (pSession->server_id == serverid)
		{
			break;
		}
		pSession = NULL;
	}
	SessionsMutex.Release();
	if (pSession)
	{
		pSession->SendPacket(pInfo);
	}
	
}


void CSessionsManager::SendErrorInfo(uint32 serverid,CError_ErrorInfo* pInfo)
{
	CSession* pSession = NULL;
	SessionsMutex.Acquire();
	for (SessionSet::iterator it = Sessions.begin();it!=Sessions.end();++it)
	{
		pSession = (*it);
		if (pSession->server_id == serverid)
		{
			break;
		}
		pSession = NULL;
	}
	SessionsMutex.Release();
	if (pSession)
	{
		pSession->SendPacket(pInfo);
	}
}

CSession* CSessionsManager::GetHttpSession()
{
	CSession* pSession = NULL;

	uint32 port = ntohs((u_short)8196);

	SessionsMutex.Acquire();
	for (SessionSet::iterator it = Sessions.begin();it!=Sessions.end();++it)
	{
		pSession = (*it);
		if (pSession && pSession->GetSocket() &&  pSession->GetSocket()->serverPort == port )
		{
			SessionsMutex.Release();
			return pSession;
		}
		
	}
	SessionsMutex.Release();

	return NULL;
}
