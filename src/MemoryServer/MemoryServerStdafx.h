#ifndef _MEMORYSERVER_H_
#define _MEMORYSERVER_H_

#include <string>
#include <vector>

#include "Common.h"
#include "../sharelib/Database/DatabaseEnv.h"
#include "../sharelib/Log.h"
#include "Config/ConfigEnv.h"
#include "../sharelib/Threading/RWLock.h"
#include <Network/Network.h>



#include "Connect/CConsole/BaseConsole.h"
#include "Connect/CConsole/CConsole.h"
#include "Connect/CConsole/ConsoleCommands.h"

//#include "Connect/Client/SeversConnect.h"
//#include "Connect/Client/ClientSocket.h"

#include "Connect/Server/ServerSocket.h"
#include "Connect/Session.h"
#include "Connect/SessionsManager.h"

#include "../Common/include/RegisterProtocol.h"

#include "Account/DataOptThread.h"
#include "Account/AccountCache.h"

#include "Main.h"
#include "ProcessManager.h"
#include "GameRunnable.h"
#include "GameLogic.h"
//#include "FriendModule.h"

// �汾��Ϣ
#define BUILD_TAG "0.0.1-TRUNK"
#define BUILD_HASH 0x0
#define COMMIT_TIMESTAMP 0
#define BUILD_HASH_STR "0"
#define BUILD_USER_STR "administrator"
#define BUILD_HOST_STR "LBDZ-20140512EM"

enum OUTPACKET_RESULT
{
	OUTPACKET_RESULT_SUCCESS = 1,
	OUTPACKET_RESULT_NO_ROOM_IN_BUFFER = 2,
	OUTPACKET_RESULT_NOT_CONNECTED = 3,
	OUTPACKET_RESULT_SOCKET_ERROR = 4,
};

enum GAMETYPE
{
	GAMETYPE_NULL,
	GAMETYPE_PDK = 1,
};

enum EServerType
{
	SERVERTYPE_ACCOUNTMGRCLIENT = 1,
	SERVERTYPE_ACCOUNTMGRSERVER ,

	SERVERTYPE_GAMEDATABASESERVER ,

};

//extern Database* sLandSQL;			// �ǽ�Ҫ����			Ĭ��1������
extern Database* sGameinfoSQL;		// ��Ҫ������Ϸ��ҵ�	Ĭ��5������
extern Database* sGetdataSQL;		// ȡ����  �˺ŵ�½ʱ	Ĭ��5������

#endif // _MEMORYSERVER_H_