#include "MemoryServerStdafx.h"

initialiseSingleton(CAccountMgr);


#define  DirtyaPrimarySaveTime		5*60		// 5分钟
#define  DirtySecondarySaveTime		1800		// 30分钟
#define  DataDeleteTime				7200		// 2小时
#define  OneTimeSavePrimaryMax		1000		// 一次最多保存的重要数据用户数量
#define  OneTimeSaveSecondaryMax	2000		// 一次最多保存的次要数据用户数量


Account::Account()
	:account_sex(false),
	account_bindip(false),
	account_bindpsw(0),
	account_bindpswparam(0),
	account_province(0),
	account_city(0),
	account_HeadVersion(0),
	account_id(0),
	account_gold(0),
	account_present(0),
	account_name(""),
	account_password(""),
	account_PlayerName(""),
	dirtytime_primary(0),
	account_activetime(0)
{
	account_gameStatMap.clear();
}

void Account::DirtyData()
{
	if (dirtytime_primary == 0)
	{
		dirtytime_primary = time(NULL);
	}
	account_activetime = time(NULL);
}

GameStatData& Account::GetGameStatData(uint32 gameID)
{
	GameStatMap::iterator it = account_gameStatMap.find(gameID);
	if (it != account_gameStatMap.end())
	{
		return it->second;
	}

	GameStatData gsd;
	gsd.gameID = gameID;
	account_gameStatMap[gameID] = gsd;
	return account_gameStatMap[gameID];
}

//Account* CAccountMgr::_LoadAccount(string AccountName)
//{
	//sLog.outString("[AccountMgr] Load Account...");

	//QueryResult* result = sAccountSQL->Query("SELECT account_id, account_account, account_password,account_money WHERE account_account = '%s'",AccountName );

	//Field* field;
	//Account* pacct = NULL;

	//if(result)
	//{
	//	pacct = new Account;

	//	field = result->Fetch();

	//	pacct->AccountId			= field[0].GetUInt32();
	//	pacct->AccountName			= field[1].GetString();
	//	//pacct->AccountAuthority		= field[2].GetUInt16();
	//	pacct->Password				= field[2].GetString();
	//	pacct->LuckMoney			= field[3].GetUInt64();
	//	//pacct->LoveMoney			= field[8].GetUInt32();
	//	//pacct->DirtyTime			= field[11].GetUInt32();

	//	delete result;


	//}
	//else
	//{
	//	sLog.outString("[AccountMgr] NOT Found %s account.", AccountName);
	//}

	//return pacct;

//	return NULL;
//}

void CAccountMgr::update()
{
	time_t nowTick = Arcemu::SysInfo::GetTickCount();
	
	if (nowTick - m_primarySaveTick > 1000)
	{
		sAccountMgr.CheckPrimarySaveData();
		m_primarySaveTick = nowTick;
	}
	
	
}


void CAccountMgr::AddGainAccountInfo(AccountQueue* pAccQueue)
{
	//GetAccountMutex.Acquire();
	for(std::list<AccountQueue*>::iterator it = pre_take_list.begin();it!=pre_take_list.end();)
	{
		if (strcmp((*it)->account_name.c_str(),pAccQueue->account_name.c_str()) == 0 &&
			(*it)->account_id == pAccQueue->account_id &&
			(*it)->queueType == pAccQueue->queueType)
		{
			delete (*it);
			it = pre_take_list.erase(it);
		}else
		{
			++it;
		}
	}
	pre_take_list.push_back(pAccQueue);
	//GetAccountMutex.Release();
}

AccountQueue* CAccountMgr::GetGainAccountInfo()
{
	AccountQueue* aq = NULL;
	//GetAccountMutex.Acquire();

	for(std::list<AccountQueue*>::iterator it = pre_take_list.begin();it!=pre_take_list.end();++it)
	{
		//if ((*it) != NULL)
		//{
			//take_data_list.push_back(*it);

			aq = (*it);
			pre_take_list.erase(it);
			break;
		//}
	}
	
	//GetAccountMutex.Release();
	return aq;
}

void CAccountMgr::AddAccountInfo(Account * pAcc)
{
	if (pAcc == NULL)
	{
		return;
	}


	AccountNameMutex.Acquire();

	Account* pAccount = new Account;
	
	pAccount->account_id = pAcc->account_id;
	pAccount->account_name = pAcc->account_name;
	pAccount->account_password = pAcc->account_password;
	pAccount->account_gold = pAcc->account_gold;
	pAccount->account_PlayerName = pAcc->account_PlayerName;
	pAccount->account_sex = pAcc->account_sex;
	pAccount->account_HeadVersion = pAcc->account_HeadVersion;
	pAccount->account_province = pAcc->account_province;
	pAccount->account_city = pAcc->account_city;

	pAccount->account_present = pAcc->account_present;

	GameStatData& gsd = pAcc->GetGameStatData(GAMETYPE_PDK);
	GameStatData& gsd2 = pAccount->GetGameStatData(GAMETYPE_PDK);
	gsd2.account_exp = gsd.account_exp;
	gsd2.account_lost = gsd.account_lost;
	gsd2.account_win = gsd.account_win;

	pAccount->account_bindip = pAcc->account_bindip;
	pAccount->account_bindpsw = pAcc->account_bindpsw;
	pAccount->account_bindpswparam = pAcc->account_bindpswparam;

	pAccount->dirtytime_primary = 0;
	//pAccount->dirtytime_secondary = pAcc->dirtytime_secondary;
	pAccount->account_activetime = time(NULL);
	
	name_map[pAccount->account_name] = pAccount;
	id_map[pAccount->account_id] = pAccount;

	AccountNameMutex.Release();

	//// 清除待取列表中相同的账号请求
	////GetAccountMutex.Acquire();
	for(std::list<AccountQueue*>::iterator it = pre_take_list.begin();it!=pre_take_list.end();)
	{
		if ((*it) != NULL && 
			((*it)->queueType == ACCOUNTQUEUETYPE_LOGIN && strcmp(pAccount->account_name.c_str(),(*it)->account_name.c_str()) == 0 ) ||
			((*it)->queueType == ACCOUNTQUEUETYPE_RELOADUSERINFO && pAccount->account_id == (*it)->account_id ) ||
			((*it)->queueType == ACCOUNTQUEUETYPE_GETGAMEINFO && pAccount->account_id == (*it)->account_id ))
		{
			it = pre_take_list.erase(it);
		}else
		{
			++it;
		}
	}
}

void CAccountMgr::CheckPrimarySaveData()
{
	int SaveNumPri = 0;
	time_t curTime = time(NULL);

	AccountNameMutex.Acquire();
	
	for (AccountNameHashMap::iterator itr = name_map.begin();itr!=name_map.end();++itr)
	{
		if (itr->second->dirtytime_primary > 0 && 
			curTime - itr->second->dirtytime_primary >  DirtyaPrimarySaveTime)
		{
			// 保存脏数据
			if (SaveNumPri > OneTimeSavePrimaryMax)
			{
				break;
			}
			save_primary_mutex.Acquire();
			save_primary_list.push(itr->second->account_name);
			save_primary_mutex.Release();

			itr->second->dirtytime_primary = 0;
			//SavePrimaryData(itr->second);
			SaveNumPri++;
		}
	}
	
	AccountNameMutex.Release();
}

void CAccountMgr::CheckSecondaryData()
{
	//int SaveNumSec = 0;
	//time_t curTime = time(NULL);
	//AccountNameMutex.Acquire();

	//for (AccountNameHashMap::iterator itr = name_map.begin();itr!=name_map.end();++itr)
	//{
	//	if (itr->second->dirtytime_secondary > 0 && 
	//		curTime - itr->second->dirtytime_secondary >  DirtySecondarySaveTime)
	//	{
	//		// 保存脏数据
	//		if (SaveNumSec > OneTimeSaveSecondaryMax)
	//		{
	//			break;
	//		}

	//		save_secondary_mutex.Acquire();
	//		save_secondary_list.push(itr->second->account_name);
	//		save_secondary_mutex.Release();

	//		itr->second->dirtytime_secondary = 0;
	//		//SaveSecondaryData(itr->second);
	//		SaveNumSec++;
	//	}
	//}

	//AccountNameMutex.Release();
}


void CAccountMgr::CheckDelete()
{
	time_t curTime = time(NULL);

	for (std::list<Account*>::iterator it = delete_list.begin();it!= delete_list.end();++it)
	{
		delete (*it);
	}
	delete_list.clear();

	AccountNameMutex.Acquire();

	for (AccountNameHashMap::iterator itr = name_map.begin();itr!=name_map.end();)
	{
		if (itr->second->account_activetime  >  DataDeleteTime)
		{
			delete_list.push_back(itr->second);
			AccountIDHashMap::iterator itID = id_map.find(itr->second->account_id);
			if (itID!=id_map.end())
			{
				id_map.erase(itID);
			}
			name_map.erase(itr++);
		}else
		{
			++itr;
		}
	}

	AccountNameMutex.Release();
}
