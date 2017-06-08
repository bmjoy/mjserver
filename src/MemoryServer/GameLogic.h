#ifndef _GAMEDATABASESERVER_GAMELOGIC_H_
#define _GAMEDATABASESERVER_GAMELOGIC_H_

#include "Common.h"


class SERVER_DECL CGameLogic : public Singleton<CGameLogic>
{
public:
	// 
	CGameLogic();

	~CGameLogic();

	void Update(uint32 diff);

	//typedef HM_NAMESPACE::hash_map<string, Account*> AccountHashMap;

	std::list<CDataOptThread*> data_write_thread_list;
	std::list<CDataOptThread*> data_read_thread_list;
	//std::list<CDataOptThread*> data_friend_thread_list;
	//std::list<CDataOptThread*> data_secondary_thread_list;

	//CDataOptThread* m_HttpOpt;
};

#define sGameLogic CGameLogic::getSingleton()


#endif	//_GAMEDATABASESERVER_GAMELOGIC_H_