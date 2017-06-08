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


// ��ѯ����
enum EAccountQueueType
{
	ACCOUNTQUEUETYPE_NULL,
	ACCOUNTQUEUETYPE_LOGIN,
	ACCOUNTQUEUETYPE_RELOADUSERINFO,
	ACCOUNTQUEUETYPE_GETGAMEINFO,
};

// �˺Ų�ѯ״̬
enum EAccountQueueState
{
	ACCOUNTQUEUESTATE_NULL,
	ACCOUNTQUEUESTATE_BUSY,
	ACCOUNTQUEUESTATE_END,
	ACCOUNTQUEUESTATE_NUM,
};


#pragma pack(push, 1)

// ��Ϸͳ������
struct GameStatData
{
	uint32			gameID;					// ��ϷID
	uint32			account_escape;			// ����
	uint32			account_exp;			// ����
	uint32			account_lost;			// �����
	uint32			account_win;			// Ӯ����

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
	bool			account_bindip;			// ��ID 1��ʾ��

	uint8			account_bindpsw;		// 1��ʾ��½ʱ��Ҫ�ֻ���֤�룬2��ʾ��Ҫ������ 0 ��ʾ����Ҫ
	uint8			account_bindpswparam;	// �ֻ���֤�롢���߾�������к�;���ϵ��л�Ϊ������ʱ���ֵ��Ϊ0
	uint8			account_province;
	uint8			account_city;

	uint32			account_HeadVersion;
	uint32			account_id;				// �˺�ID		= 0 ����յ�ַλ

	uint64			account_gold;			// ����ֵ
	uint64			account_present;		// ��Ʒȯ

	std::string		account_name;			// �˺���
	std::string		account_password;		// ����
	std::string		account_PlayerName;
	
	//uint64			account_exp;			// ����
	//uint64			account_lost;			// �����
	//uint64			account_win;			// Ӯ����
		
	time_t			dirtytime_primary;		// ������ʱ�� 
	//time_t			dirtytime_secondary;	// ������ʱ��   �ǽ�Ҫ����
	time_t			account_activetime;		// ��󼤻�ʱ��		��ʱ�䲻����Ĵ��ڴ��ɾ��
	
	GameStatMap account_gameStatMap;

	Account();

	void DirtyData();

	GameStatData& GetGameStatData(uint32 gameID);
};

#pragma pack(pop)

typedef HM_NAMESPACE::hash_map<std::string, Account*> AccountNameHashMap;		// ����������
typedef HM_NAMESPACE::hash_map<uint32, Account*> AccountIDHashMap;					// ��ID����



class AccountQueue
{
public:
	uint8					queueType;				// ��������
	EAccountQueueState		queue_state_id;			// ��ѯ״̬
	std::string				account_name;			// �˺���
	uint32					account_id;				// �˺�id
	//unsigned long			account_hash;			// �˺�hashֵ

};



class CAccountMgr : public Singleton < CAccountMgr >
{
public:
	CAccountMgr()
		: m_primarySaveTick(0),
		m_secondarySaveTick(0)
	{
		lunchTime = time(NULL);

		// ���������
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

	//// �����ݿ��м��س�����˺���Ϣ
	//void AddAccount(Field* field){}

	// ���ڴ��л�ȡ�˺���Ϣ
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

	// ���ڴ��л�ȡ�˺���Ϣ
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

	// ���������ݱ��� һ��ֻ����N��
	void CheckPrimarySaveData();
	void CheckSecondaryData();

	// ��ȡһ������ȡ���˺���Ϣ
	AccountQueue* GetGainAccountInfo();

	void AddAccountInfo(Account * pAcc);

	// ��ӻ�ȡ�˺���Ϣ�б�
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


	//// ֻ���ڴ��в����˺�����
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

	// ��ȡ�����б�
	std::list<AccountQueue*>	pre_take_list;

	// ��ȡ�����б�
	//std::list<AccountQueue*>	take_data_list;

	// ������Ҫ���ݱ�
	std::queue<std::string>		save_primary_list;

	// �����Ҫ���ݱ�
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
