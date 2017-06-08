#ifndef _CGAME_STOC_MATCHRANK_H_
#define _CGAME_STOC_MATCHRANK_H_

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CGame_STOC_MatchRank : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_MATCHRANK};

	uint16				RankNum;
	uint32				MatchID;
	std::list<TMatchRank>	ranklist;

	CGame_STOC_MatchRank()
	{
		m_opcode = PROTOCOL_TYPE;
		RankNum = 0;
		MatchID = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>RankNum;
		data>>MatchID;

		TMatchRank nr;
		for (uint8 i = 0 ;i< RankNum;++i)
		{
			data>>nr.PlayerState;
			data>>nr.PlayerID;
			data>>nr.RankIndex;
			data>>nr.RankIntegral;
			data>>nr.Name;
			ranklist.push_back(nr);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RankNum;
		data<<MatchID;

		for (std::list<TMatchRank>::iterator it = ranklist.begin();it!=ranklist.end();++it)
		{
			TMatchRank& nr = *it;
			data<<nr.PlayerState;
			data<<nr.PlayerID;
			data<<nr.RankIndex;
			data<<nr.RankIntegral;
			data<<nr.Name;
		}
	}


};



#endif	//_CGAME_STOC_MATCHRANK_H_