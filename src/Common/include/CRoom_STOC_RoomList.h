#ifndef _CROOMCTOSROOMLIST_H
#define _CROOMCTOSROOMLIST_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CRoom_STOC_RoomList : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_ROOMLIST};

	uint8	RoomSize;
	std::list<TProtocolRoom>	roomlist;

	CRoom_STOC_RoomList()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>RoomSize;

		TProtocolRoom nr;
		for (uint8 i = 0 ;i< RoomSize;++i)
		{
			data>>nr.RoomID;
			data>>nr.RoomType;
			data>>nr.TableLimit;
			data>>nr.RoomState;
			data>>nr.RoomRat;
			data>>nr.LevelLimit;
			data>>nr.GoldLimit;
			data>>nr.RoomTime;
			data>>nr.RoomName;
			roomlist.push_back(nr);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RoomSize;

		for (std::list<TProtocolRoom>::iterator it = roomlist.begin();it!=roomlist.end();++it)
		{
			TProtocolRoom& nr = *it;
			data<<nr.RoomID;
			data<<nr.RoomType;
			data<<nr.TableLimit;
			data<<nr.RoomState;
			data<<nr.RoomRat;
			data<<nr.LevelLimit;
			data<<nr.GoldLimit;
			data<<nr.RoomTime;
			data<<nr.RoomName;
		}
	}
};

#endif	//_CROOMCTOSROOMLIST_H