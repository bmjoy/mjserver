/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008-2012 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _ACCOUNTMEMORY_ACCOUNTCACHE_H_
#define _ACCOUNTMEMORY_ACCOUNTCACHE_H_

#include "Common.h"


// 查询类型
enum EAccountQueueType
{
	ACCOUNTQUEUETYPE_NULL,
	ACCOUNTQUEUETYPE_LOGIN,
	ACCOUNTQUEUETYPE_RELOADUSERINFO,
	ACCOUNTQUEUETYPE_GETGAMEINFO,
};

// 账号查询状态
enum EAccountQueueState
{
	ACCOUNTQUEUESTATE_NULL,
	ACCOUNTQUEUESTATE_BUSY,
	ACCOUNTQUEUESTATE_END,
	ACCOUNTQUEUESTATE_NUM,
};


#pragma pack(push, 1)

// 游戏统计数据
struct GameStatData
{
	uint32			gameID;					// 游戏ID
	uint32			account_escape;			// 逃跑
	uint32			account_exp;			// 经验
	uint32			account_lost;			// 输局数
	uint32			account_win;			// 赢局数

	GameStatData()
		: gameID(0),
		account_escape(0),
		account_exp(0),
		account_lost(0),
		account_win(0)
	{

	}
};

typedef HM_NAMESPACE::hash_map<uint16, GameStatData> GameStatMap;


class Account
{
public:
	bool			account_sex;
	bool			account_bindip;			// 绑定ID 1表示绑定

	uint8			account_bindpsw;		// 1表示登陆时需要手机验证码，2表示需要矩阵码 0 表示不需要
	uint8			account_bindpswparam;	// 手机验证码、或者矩阵码的列号;网上当切换为矩阵码时这个值变为0
	uint8			account_province;
	uint8			account_city;

	uint32			account_HeadVersion;
	uint32			account_id;				// 账号ID		= 0 代表空地址位

	uint64			account_gold;			// 手气值
	uint64			account_present;		// 礼品券

	std::string		account_name;			// 账号名
	std::string		account_password;		// 密码
	std::string		account_PlayerName;
	
	//uint64			account_exp;			// 经验
	//uint64			account_lost;			// 输局数
	//uint64			account_win;			// 赢局数
		
	time_t			dirtytime_primary;		// 脏数据时间 
	//time_t			dirtytime_secondary;	// 脏数据时间   非紧要数据
	time_t			account_activetime;		// 最后激活时间		长时间不激活的从内存池删掉
	
	GameStatMap account_gameStatMap;

	Account();

	void DirtyData();

	GameStatData& GetGameStatData(uint32 gameID);
};

#pragma pack(pop)

typedef HM_NAMESPACE::hash_map<std::string, Account*> AccountNameHashMap;		// 以名字排列
typedef HM_NAMESPACE::hash_map<uint32, Account*> AccountIDHashMap;					// 以ID排列



class AccountQueue
{
public:
	uint8					queueType;				// 查找类型
	EAccountQueueState		queue_state_id;			// 查询状态
	std::string				account_name;			// 账号名
	uint32					account_id;				// 账号id
	//unsigned long			account_hash;			// 账号hash值

};



class CAccountMgr : public Singleton < CAccountMgr >
{
public:
	CAccountMgr()
		: m_primarySaveTick(0),
		m_secondarySaveTick(0)
	{
		lunchTime = time(NULL);

		// 建立缓冲池
		// int BaseCacheNum = Config.MainConfig.GetIntDefault("AccountCache", "BaseCacheNum", 1000);
	}
	~CAccountMgr()
	{
		for(AccountIDHashMap::iterator itr = id_map.begin(); itr != id_map.end(); ++itr)
		{
			delete itr->second;
		}
	}

	void update();

	time_t GetLunchTime(){}

	//// 从数据库中加载出玩家账号信息
	//void AddAccount(Field* field){}

	// 从内存中获取账号信息
	Account* GetAccount(string Name)
	{
		Account* pAccount = NULL;

		AccountNameMutex.Acquire();
		AccountNameHashMap::iterator itr = name_map.find(Name);

		if(itr == name_map.end())
		{
			AccountNameMutex.Release();
			return NULL;
		}
		else
		{
			pAccount = itr->second;
			if (pAccount)
			{
				pAccount->account_activetime = time(NULL);
			}
			AccountNameMutex.Release();
			return pAccount;
		}
	}

	// 从内存中获取账号信息
	Account* GetAccountByID(uint32 accountID)
	{
		Account* pAccount = NULL;

		AccountIDHashMap::iterator itr = id_map.find(accountID);

		if(itr == id_map.end())
		{
			return NULL;
		}
		else
		{
			pAccount = itr->second;
			if (pAccount)
			{
				pAccount->account_activetime = time(NULL);
			}
			return pAccount;
		}
	}

	// 查找脏数据保存 一次只遍历N个
	void CheckPrimarySaveData();
	void CheckSecondaryData();

	// 获取一个待获取的账号信息
	AccountQueue* GetGainAccountInfo();

	void AddAccountInfo(Account * pAcc);

	// 添加获取账号信息列表
	void AddGainAccountInfo(AccountQueue * pAccQueue);

	std::string GetPrimarySaveAccount()
	{
		std::string restr;
		save_primary_mutex.Acquire();
		if (!save_primary_list.empty())
		{
			restr = save_primary_list.front();
			save_primary_list.pop();
		}		
		save_primary_mutex.Release();
		return restr;
	}

	std::string GetSecondarySaveAccount()
	{
		std::string restr;
		save_secondary_mutex.Acquire();
		if (!save_secondary_list.empty())
		{
			restr = save_secondary_list.front();
		}
		save_secondary_mutex.Release();
		return restr;
	}

private:
	//void SavePrimaryData(Account* pAccount);
	//void SaveSecondaryData(Account* pAccount);


	//// 只从内存中查找账号数据
	//Account* GetAccountMem(string Name)
	//{
	//	Account* pAccount = NULL;

	//	setBusy.Acquire();

	//	AccountHashMap::iterator itr = AccountDatabase.find(Name);

	//	if(itr == AccountDatabase.end())
	//	{
	//		pAccount = NULL;
	//	}
	//	else
	//	{
	//		pAccount = itr->second;
	//	}

	//	setBusy.Release();

	//	return pAccount;
	//}

	

	void CheckDelete();


	//ARCEMU_INLINE size_t GetCount() { return AccountDatabase.size(); }
	




private:
	AccountNameHashMap	name_map;		
	AccountIDHashMap	id_map;		

	// 待取数据列表
	std::list<AccountQueue*>	pre_take_list;

	// 在取数据列表
	//std::list<AccountQueue*>	take_data_list;

	// 待存首要数据表
	std::queue<std::string>		save_primary_list;

	// 待存次要数据表
	std::queue<std::string>		save_secondary_list;

	std::list<Account*>			delete_list;

		

	//Account* _LoadAccount(std::string AccountName);


	time_t			lunchTime;

	time_t			m_primarySaveTick;
	time_t			m_secondarySaveTick;

protected:
	Mutex AccountNameMutex;
	Mutex GetAccountMutex;
	Mutex save_primary_mutex;
	Mutex save_secondary_mutex;
};

#define sAccountMgr CAccountMgr::getSingleton()

#endif	//_ACCOUNTMEMORY_ACCOUNTCACHE_H_
