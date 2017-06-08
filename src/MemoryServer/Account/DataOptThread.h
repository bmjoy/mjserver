#ifndef _ACCOUNTMEMORY_DATAOPTTHREAD_H_
#define _ACCOUNTMEMORY_DATAOPTTHREAD_H_

#include "Common.h"
#include "../sharelib/CThreads.h"

class Account;
class FriendModuleQueue;

class CDataOptThread : public CThread
{
public:
	CDataOptThread();
	~CDataOptThread();

	bool run();

	//void SetAccountName(std::string str)
	//{
	//	AccountNameMutex.Acquire();
	//	preget_account_name = str;
	//	AccountNameMutex.Release();
	//}

	//void SetAccountPoint(Account* pAcc)
	//{
	//	AccountPointMutex.Acquire();
	//	pAccount = pAcc;
	//	AccountPointMutex.Release();
	//}

private:
	void DoGetAccountData();
	void DoSavePrimaryAccountData();
	void DoSaveSecondaryAccountData();
	void DoHttpRequest();
	//void DoProcessFriendData();
public:
	std::string		preget_account_name;
	uint32			preget_account_id;
	uint8			preget_queueType;

	Account*		m_pAccount;
	bool			m_bHasFriendMsg;

	// 操作类型  1为账号读取  2为首要数据写入  3为次要数据写入
	uint8			opt_type;
	uint8			opt_Result;	

//	uint8			http_opt_type;	
	//uint32			http_opt_value1;	

	bool			opt_b;	

	Mutex AccountNameMutex;
	Mutex AccountPointMutex;
	Mutex FriendQueueMutex;
};

#endif	// _ACCOUNTMEMORY_DATAOPTTHREAD_H_