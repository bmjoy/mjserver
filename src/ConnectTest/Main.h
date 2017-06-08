#include "../sharelib/Singleton.h"
#include "Common.h"

struct AllowedIP
{
	unsigned int IP;
	unsigned char Bytes;
};

bool IsServerAllowed(unsigned int IP);

class CConnectTestServer : public Singleton< CConnectTestServer >
{
public:
	void Run();
};

#define sConnectTestServer CConnectTestServer::getSingleton()