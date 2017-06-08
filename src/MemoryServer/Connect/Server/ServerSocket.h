#ifndef __SERVERSOCKET_H
#define __SERVERSOCKET_H

#include <RC4Engine.h>
#include "Network/Network.h"
#include "FastQueue.h"
#include "Protocol.h"

class CSession;

#include "../sharelib/Auth/WowCrypt.h"
//extern enum OUTPACKET_RESULT;

class CServerSocket : public Socket
{
	uint32 mRemaining;
	uint16 mOpcode;
	uint32 mSize;
	uint32 seed;
	RC4Engine sendCrypto;
	RC4Engine recvCrypto;

public:
	bool use_crypto;

	CServerSocket(SOCKET fd);
	~CServerSocket();

	void OnRead();
	void OnDisconnect();
	void OnConnect();
	//void SendPacket(WorldPacket* data);
	//void HandlePacket(WorldPacket & recvData);
	ARCEMU_INLINE void SetSession(CSession* session) { mSession = session; }

	void UpdateQueuedPackets();
	void OutPacket(uint16 opcode, size_t len, const void* data);
	virtual ARCEMU_INLINE void SendPacket(Protocol* packet) 
	{ 
		if(!packet) return; OutPacket(packet->GetOpcode(), packet->size(), (packet->size() ? (const void*)packet->contents() : NULL)); 
	}

	uint8 _OutPacket(uint16 opcode, size_t len, const void* data);
	uint8 OutDecryptPacket(uint16 opcode, size_t len, const void* data);

	Arcemu::Threading::AtomicCounter last_ping;
	
	bool removed;
	set<uint32> server_ids;	//HandleRegister ±ÃÌº”
	
private:
	CSession* mSession;

	Mutex queueLock;
	
	uint8 Key[40];

	FastQueue<Protocol* , DummyLock> _queue;
};

#endif	//__SERVERSOCKET_H
