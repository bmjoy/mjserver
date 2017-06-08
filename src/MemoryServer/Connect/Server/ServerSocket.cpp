#include "MemoryServerStdafx.h"


#define CLIENTSOCKET_SENDBUF_SIZE 131078
#define CLIENTSOCKET_RECVBUF_SIZE 16384

#pragma pack(push, 1)

typedef struct
{
	uint16 opcode;
	uint32 size;
} logonpacket;

#pragma pack(pop)

static void swap32(uint32* p) { *p = ((*p >> 24) & 0xff) | ((*p >> 8) & 0xff00) | ((*p << 8) & 0xff0000) | (*p << 24); }

CServerSocket::CServerSocket(SOCKET fd): Socket(fd, 65536, 524288)
{
	last_ping.SetVal((uint32)UNIXTIME);
	mRemaining = mOpcode = 0;
	removed = true;

	use_crypto = false;
}

CServerSocket::~CServerSocket()
{

}


void CServerSocket::OnRead()
{
	while(true)
	{
		if(mRemaining == 0)
		{
			if(readBuffer.GetSize() < 6)
			{
				// No header in the packet, let's wait.
				return;
			}

			// Copy from packet buffer into header local var
			ClientPktHeader Header;
			readBuffer.Read((uint8*)&Header, sizeof(ClientPktHeader));

			// Decrypt the header
			//rc4 rc4_cona((uint8 *)Key,40);
			//rc4_cona.rc4_encode((uint8 *)&Header,sizeof(ClientPktHeader));

			//_crypt.rc4_encode((uint8*)&Header, sizeof(ClientPktHeader));

			mRemaining = mSize = ntohs(Header.size) - 3;
			mOpcode = Header.cmd;
		}

		Protocol* Packet;

		if(mRemaining > 0)
		{
			if(readBuffer.GetSize() < mRemaining)
			{
				// We have a fragmented packet. Wait for the complete one before proceeding.
				return;
			}
		}

		Packet = Protocol::Create(mOpcode);
		assert(Packet);
		//Packet = new WorldPacket(static_cast<uint16>(mOpcode), mSize);
		Packet->resize(mSize);

		if(mRemaining > 0)
		{
			// Copy from packet buffer into our actual buffer.
			///Read(mRemaining, (uint8*)Packet->contents());
			readBuffer.Read((uint8*)Packet->contents(), mRemaining);

			//rc4 rc4_cona((uint8 *)Key,40);
			//rc4_cona.rc4_encode((uint8 *)Packet->contents(),mRemaining);
			//_crypt.rc4_encode((uint8*)Packet->contents(), mRemaining);
			Packet->ReadProtocol(*Packet);
		}

		//sWorldLog.LogPacket(mSize, static_cast<uint16>(mOpcode), mSize ? Packet->contents() : NULL, 0, (mSession ? mSession->GetAccountId() : 0));
		mRemaining = mSize = mOpcode = 0;

		// Check for packets that we handle
		switch(Packet->GetOpcode())
		{
			//case CMSG_PING:
			//	{
			//		_HandlePing(Packet);
			//		delete Packet;
			//	}
			//	break;
		case MSG_NULL:
			{
				//_HandleAuthSession(Packet);
			}
			break;
		default:
			{
				if(mSession) mSession->QueuePacket(Packet);
				else delete Packet;

			}
			break;
		}
	}
}

void CServerSocket::OnDisconnect()
{
	sLog.outString("CServerSocket::OnDisconnect()");

	//bool _isdisconnetct = true;
	if(mSession)
	{
		mSession->SetSocket(0);
		mSession = NULL;
	}
}

void CServerSocket::OnConnect()
{
	sLog.outString("CServerSocket::OnConnect()");
	static uint32 AuthenticatedID = 1;

	//_crypt.Init(K);
	//_crypt.prepare_key((unsigned char *)Key,40);

	//rc4 rc4_cona((unsigned char *)K,40);

	//OutDecryptPacket(MSG_DECRYPT,40,&Key);

	OutDecryptPacket(MSG_REGISTERED,4,&AuthenticatedID);

	++AuthenticatedID;

	CSession* pSession = new CSession(this);
	mSession = pSession;
	mSession->instanceId = g_SessionMaxID++;
	sSessionsManager.AddGlobalSession(mSession);
}


void CServerSocket::OutPacket(uint16 opcode, size_t len, const void* data)
{
	uint8 res;
	if((len + 10) > CLIENTSOCKET_SENDBUF_SIZE)
	{
		LOG_ERROR("WARNING: Tried to send a packet of %u bytes (which is too large) to a socket. Opcode was: %u (0x%03X)", (unsigned int)len, (unsigned int)opcode, (unsigned int)opcode);
		return;
	}

	res = _OutPacket(opcode, len, data);
	if(res == OUTPACKET_RESULT_SUCCESS)
		return;

	if(res == OUTPACKET_RESULT_NO_ROOM_IN_BUFFER)
	{
		/* queue the packet */
		queueLock.Acquire();

		Protocol* Packet = Protocol::Create(mOpcode);

		Packet->SetOpcode(mOpcode);
		Packet->reserve(len);

		if (len)
		{
			Packet->append((const uint8*)data, len);
		}

		_queue.Push(Packet);

		queueLock.Release();
	}
}


void CServerSocket::UpdateQueuedPackets()
{
	queueLock.Acquire();
	if(!_queue.HasItems())
	{
		queueLock.Release();
		return;
	}

	Protocol* pck;
	while((pck = _queue.front()) != NULL)
	{
		/* try to push out as many as you can */
		switch(_OutPacket(pck->GetOpcode(), pck->size(), pck->size() ? pck->contents() : NULL))
		{
		case OUTPACKET_RESULT_SUCCESS:
			{
				delete pck;
				_queue.pop_front();
			}
			break;

		case OUTPACKET_RESULT_NO_ROOM_IN_BUFFER:
			{
				/* still connected */
				queueLock.Release();
				return;
			}
			break;

		default:
			{
				/* kill everything in the buffer */
				while((pck == _queue.Pop()) != 0)
				{
					delete pck;
				}
				queueLock.Release();
				return;
			}
			break;
		}
	}
	queueLock.Release();
}

uint8 CServerSocket::_OutPacket(uint16 opcode, size_t len, const void* data)
{
	bool rv;
	if(!IsConnected())
		return OUTPACKET_RESULT_NOT_CONNECTED;

	BurstBegin();
	//if((m_writeByteCount + len + 4) >= m_writeBufferSize)
	if(writeBuffer.GetSpace() < (len + 4))
	{
		BurstEnd();
		return OUTPACKET_RESULT_NO_ROOM_IN_BUFFER;
	}

	// Packet logger :)
	//sWorldLog.LogPacket((uint32)len, opcode, (const uint8*)data, 1, (mSession ? mSession->GetAccountId() : 0));

	// Encrypt the packet
	// First, create the header.
	ServerPktHeader Header;

	Header.cmd = opcode;
	Header.size = ntohs((uint16)len + 2);

	//rc4 rc4_cona((uint8 *)Key,40);
	//rc4_cona.rc4_encode((uint8*)&Header,sizeof(ServerPktHeader));
	//_crypt.EncryptSend((uint8*)&Header, sizeof(ServerPktHeader));

	// Pass the header to our send buffer
	rv = BurstSend((const uint8*)&Header, 4);

	// Pass the rest of the packet to our send buffer (if there is any)
	if(len > 0 && rv)
	{
		//rc4 rc4_cona((uint8 *)Key,40);
		//rc4_cona.rc4_encode((uint8*)data,(uint32)len);
		//_crypt.EncryptSend((uint8*)data, (uint32)len);
		rv = BurstSend((const uint8*)data, (uint32)len);
	}

	if(rv) BurstPush();
	BurstEnd();
	return rv ? OUTPACKET_RESULT_SUCCESS : OUTPACKET_RESULT_SOCKET_ERROR;
}

uint8 CServerSocket::OutDecryptPacket(uint16 opcode, size_t len, const void* data)
{
	bool rv;
	if(!IsConnected())
		return OUTPACKET_RESULT_NOT_CONNECTED;

	BurstBegin();
	//if((m_writeByteCount + len + 4) >= m_writeBufferSize)
	if(writeBuffer.GetSpace() < (len + 4))
	{
		BurstEnd();
		return OUTPACKET_RESULT_NO_ROOM_IN_BUFFER;
	}

	// Packet logger :)
	//sWorldLog.LogPacket((uint32)len, opcode, (const uint8*)data, 1, (mSession ? mSession->GetAccountId() : 0));

	// Encrypt the packet
	// First, create the header.
	ServerPktHeader Header;

	Header.cmd = opcode;
	Header.size = ntohs((uint16)len + 2);

	//_crypt.EncryptSend((uint8*)&Header, sizeof(ServerPktHeader));

	// Pass the header to our send buffer
	rv = BurstSend((const uint8*)&Header, 4);

	// Pass the rest of the packet to our send buffer (if there is any)
	if(len > 0 && rv)
	{
		rv = BurstSend((const uint8*)data, (uint32)len);
	}

	if(rv) BurstPush();
	BurstEnd();
	return rv ? OUTPACKET_RESULT_SUCCESS : OUTPACKET_RESULT_SOCKET_ERROR;
}