#ifndef _CROOMCTOSMATCHLIST_H
#define _CROOMCTOSMATCHLIST_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CRoom_STOC_MatchList : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHLIST};

	uint8	RoomSize;
	uint8	OptType;			// 默认1 完全覆盖   2 更新  3添加  4 删除
	std::list<TProtocolMatchRoom>	roomlist;

	CRoom_STOC_MatchList()
	{
		OptType = 1;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>RoomSize;
		data>>OptType;

		TProtocolMatchRoom nr;
		for (uint8 i = 0 ;i< RoomSize;++i)
		{
			data>>nr.MatchID;
			data>>nr.RoomID;
			data>>nr.RoomState;
			data>>nr.RoomTime;
			roomlist.push_back(nr);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RoomSize;
		data<<OptType;

		for (std::list<TProtocolMatchRoom>::iterator it = roomlist.begin();it!=roomlist.end();++it)
		{
			TProtocolMatchRoom& nr = *it;
			data<<nr.MatchID;
			data<<nr.RoomID;
			data<<nr.RoomState;
			data<<nr.RoomTime;
		}
	}
};

#endif	//_CROOMCTOSMATCHLIST_H