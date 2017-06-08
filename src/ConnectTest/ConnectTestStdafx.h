#ifndef _CONNECTTEST_H_
#define _CONNECTTEST_H_

#include <string>
#include <vector>

#include "Common.h"
#include "../sharelib/Database/DatabaseEnv.h"
#include "../sharelib/Log.h"
#include "../sharelib/Config/ConfigEnv.h"
#include "../sharelib/Threading/RWLock.h"
#include <Network/Network.h>

#include "CAccount_STOA_Find.h"



#include "Connect/CConsole/BaseConsole.h"
#include "Connect/CConsole/CConsole.h"
#include "Connect/CConsole/ConsoleCommands.h"

//#include "Connect/Client/SeversConnect.h"
//#include "Connect/Client/ClientSocket.h"

#include "Connect/Server/ServerSocket.h"
#include "Connect/Session.h"
#include "Connect/SessionsManager.h"

#include "GameModule/ModuleBase.h"
#include "GameModule/LoginModule.h"
#include "GameModule/ModuleManager.h"


#include "../Common/include/RegisterProtocol.h"

#include "Main.h"
#include "ProcessManager.h"
#include "GameRunnable.h"
#include "GameLogic.h"

#include "LoginData.h"
#include "RoleData.h"
#include "RoleManager.h"


// 版本信息
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


enum EServerType
{
	SERVERTYPE_ACCOUNTMGRCLIENT = 1,
	SERVERTYPE_ACCOUNTMGRSERVER ,

	SERVERTYPE_GAMEDATABASESERVER ,

};

#endif // _CONNECTTEST_H_