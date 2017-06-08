#include "MemoryServerStdafx.h"

CSession::CSession(Socket* sock)
{
	_socket = sock;
	_updatecount = 0;
	bDeleted = false;
	_logoutTime = 0;
	server_type = 0;
	server_id = 0;
	m_currMsTime = getMSTime();
	instanceId = 0;
}

CSession::~CSession()
{

}

int CSession::Update(uint32 InstanceID)
{
	m_currMsTime = getMSTime();

	// 找到待发送列表的数据 发送
	if(!((++_updatecount) % 2) && _socket)
		_socket->UpdateQueuedPackets();

	//if(InstanceID != instanceId)
	//{
	//	// We're being updated by the wrong thread.
	//	// "Remove us!" - 2
	//	return 2;
	//}

	Protocol* ptrPacket;

	if(!_socket)
	{
		return 1;
	}

	while((ptrPacket = _recvQueue.Pop()) != 0)
	{
		assert(ptrPacket != NULL);

		if(ptrPacket->GetOpcode() >= NUM_MSG_TYPES)
		{
			LOG_DETAIL("[Session] Received out of range packet with opcode 0x%.4X",	ptrPacket->GetOpcode());
		}
		else
		{
			sProcessManager.ProcessProtocols(ptrPacket->GetOpcode(),ptrPacket,this);
		}

		delete ptrPacket;

	}

	return 0;
}