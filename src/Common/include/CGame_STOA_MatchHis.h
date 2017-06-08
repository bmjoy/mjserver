#ifndef _CGAME_STOA_MATCHHIS_H_
#define _CGAME_STOA_MATCHHIS_H_

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOA_MatchHis : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SERVER_MATCHHIS};

	uint32				playerID;
	uint32				matchID;
	uint32				matchRank;
	uint64				matchStartTime;
	uint8				RewardSize;
	std::list<TMatchPlayerReward> m_RewardList;

	CGame_STOA_MatchHis()
	{
		m_opcode = PROTOCOL_TYPE;
		playerID = 0;
		matchID = 0;
		matchRank = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playerID;
		data>>matchID;
		data>>matchRank;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playerID;
		data<<matchID;
		data<<matchRank;
	}


};



#endif	//_CGAME_STOA_MATCHHIS_H_