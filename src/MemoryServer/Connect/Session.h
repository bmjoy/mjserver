#ifndef __SESSION_H
#define __SESSION_H

#include "Common.h"
#include "Opcodes.h"
#include "../sharelib/FastQueue.h"
#include "Protocol.h"

#include <Network/Network.h>

static uint32 g_SessionMaxID = 1;

class SERVER_DECL CSession
{

public:
	CSession(Socket* sock);
	~CSession();

	int Update(uint32 InstanceID);

	void QueuePacket(Protocol* packet)
	{
		m_lastPing = (uint32)UNIXTIME;
		_recvQueue.Push(packet);
	}

	void SendPacket(Protocol* packet)
	{
		packet->clear();
		packet->WriteProtocol(*packet);
		if(_socket && _socket->IsConnected())
			_socket->SendPacket(packet);
	}

	void SetSocket(Socket* sock)
	{
		_socket = sock;
	}

	Socket* GetSocket(){return _socket;}
	
	void SetLogoutTimer(uint32 ms)
	{
		if(ms)  _logoutTime = m_currMsTime + ms;
		else	_logoutTime = 0;
	}

	void Disconnect()
	{
		if(_socket && _socket->IsConnected())
			_socket->Disconnect();
	}



public:
	uint32 m_lastPing;
	uint8 _updatecount;
	uint32 instanceId;
	bool bDeleted;

	uint32	server_type;		
	uint32	server_id;			
	
private:
	FastQueue<Protocol*, Mutex> _recvQueue;

	Socket* _socket;
	uint32 _logoutTime; // time we received a logout request -- wait 20 seconds, and quit
	uint32 m_currMsTime;
};


#endif	//__SESSION_H