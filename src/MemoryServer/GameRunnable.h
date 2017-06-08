#ifndef _GAMEDATABASESERVER_GAMERUNNABLE_H_
#define _GAMEDATABASESERVER_GAMERUNNABLE_H_

#include "Common.h"
#include "../sharelib/CThreads.h"

class CGameRunnable : public CThread
{
public:
	CGameRunnable();
	~CGameRunnable();
	bool run();
};

#endif	// _GAMEDATABASESERVER_GAMERUNNABLE_H_