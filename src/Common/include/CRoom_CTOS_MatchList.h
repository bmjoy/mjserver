#ifndef _CMATCHCTOSROOMLIST_H
#define _CMATCHCTOSROOMLIST_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CRoom_CTOS_MatchList : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHLIST};

	uint8	RoomSize;
	std::list<TNormalRoom>	roomlist;

	CRoom_CTOS_MatchList()
	{
		m_opcode = PROTOCOL_TYPE;
	}
	
	void ReadProtocol(Protocol & data)
	{
		data>>RoomSize;

		//for (std::list<TMatchRoom>::iterator it = roomlist.begin();it!=roomlist.end();++it)
		//{
		//	TMatchRoom& nr = *it;
		//	data>>nr.MatchState;
		//	data>>nr.MatchNum;
		//	data>>nr.MatchTime;
		//	data>>nr.MatchName;
		//}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RoomSize;

		//for (std::list<TMatchRoom>::iterator it = roomlist.begin();it!=roomlist.end();++it)
		//{
		//	TMatchRoom& nr = *it;
		//	data<<nr.MatchState;
		//	data<<nr.MatchNum;
		//	data<<nr.MatchTime;
		//	data<<nr.MatchName;
		//}

	}
};

#endif	//_CMATCHCTOSROOMLIST_H