#ifndef _CGAMESTOCMATCHHISTORY_H
#define _CGAMESTOCMATCHHISTORY_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_MatchHistory : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_HISTORY};

	uint8				HistoryNum;	
	std::list<TMatchHistory> MatchList;

	CGame_STOC_MatchHistory()
	{
		m_opcode = PROTOCOL_TYPE;
		HistoryNum = 0;
		MatchList.clear();
	}

	void ReadProtocol(Protocol & data)
	{
		data>>HistoryNum;
		
		TMatchHistory nr;
		for (uint8 i = 0 ;i< HistoryNum;++i)
		{
			data>>nr.MatchID;
			data>>nr.MatchRank;
			data>>nr.MatchReward;
			data>>nr.MatchTime;

			MatchList.push_back(nr);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<HistoryNum;

		for (std::list<TMatchHistory>::iterator it = MatchList.begin();it!=MatchList.end();++it)
		{
			TMatchHistory& nr = *it;
			data<<nr.MatchID;
			data<<nr.MatchRank;
			data<<nr.MatchReward;
			data<<nr.MatchTime;
		}
	}


};



#endif	//_CGAMESTOCMATCHHISTORY_H