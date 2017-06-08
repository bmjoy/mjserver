#include "MemoryServerStdafx.h"

#include <CrashHandler.h>

#define WORLD_UPDATE_DELAY 50


CGameRunnable::CGameRunnable() : CThread()
{
	new CGameLogic();
	//new QueueMechanismManager();
}

CGameRunnable::~CGameRunnable()
{
	delete CGameLogic::getSingletonPtr();
	//delete QueueMechanismManager::getSingletonPtr();
}

bool CGameRunnable::run()
{
	SetThreadName("WorldRunnable (non-instance/logon)");
	uint32 LastWorldUpdate = getMSTime();
	uint32 LastSessionsUpdate = getMSTime();

	THREAD_TRY_EXECUTION
	
	while(GetThreadState() != THREADSTATE_TERMINATE)
	{
		// Provision for pausing this thread.
		if(GetThreadState() == THREADSTATE_PAUSED)
		{
			while(GetThreadState() == THREADSTATE_PAUSED)
			{
				Arcemu::Sleep(200);
			}
		}
		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_BUSY);

		uint32 diff;
		//calc time passed
		uint32 now, execution_start;
		now = getMSTime();
		execution_start = now;

		if(now < LastWorldUpdate) //overrun
			diff = WORLD_UPDATE_DELAY;
		else
			diff = now - LastWorldUpdate;

		LastWorldUpdate = now;
		//sLog.outError("CGameRunnable::Update111");

		// 
		sGameLogic.Update(diff);

		now = getMSTime();

		if(now < LastSessionsUpdate) //overrun
			diff = WORLD_UPDATE_DELAY;
		else
			diff = now - LastSessionsUpdate;

		LastSessionsUpdate = now;

		sSessionsManager.UpdateSessions(diff);

		now = getMSTime();
		//we have to wait now

		if(execution_start > now)//overrun
			diff = WORLD_UPDATE_DELAY - now;

		else
			diff = now - execution_start; //time used for updating

		if(GetThreadState() == THREADSTATE_TERMINATE)
			break;

		ThreadState.SetVal(THREADSTATE_SLEEPING);

		/*This is execution time compensating system
			if execution took more than default delay
			no need to make this sleep*/
		if(diff < WORLD_UPDATE_DELAY)
			Arcemu::Sleep(WORLD_UPDATE_DELAY - diff);

		//sLog.outError("CGameRunnable::Update222");

	}

	THREAD_HANDLE_CRASH
	return true;
}