#include "../sharelib/Singleton.h"
#include "Common.h"

struct AllowedIP
{
	unsigned int IP;
	unsigned char Bytes;
};

bool IsServerAllowed(unsigned int IP);

class CGameDataBaseServer : public Singleton< CGameDataBaseServer >
{
public:
	void Run();
};

#define sGameDataBaseServer CGameDataBaseServer::getSingleton()