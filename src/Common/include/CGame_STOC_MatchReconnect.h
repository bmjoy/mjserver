#ifndef _CGAME_STOC_MATCHRECONNECT_H_
#define _CGAME_STOC_MATCHRECONNECT_H_

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_MatchReconnect : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHRECONNECT};
	
	uint16 m_MatchID;			// 比赛ID
	uint16 m_PlayerState;		// 玩家状态
	uint16 m_TableIndex;		// 桌子ID
	uint16 m_TableRound;		// 桌子第几轮

	uint16 m_MatchFormatRound;	// 第几个赛制
	uint16 m_MatchFormat;		// 当前赛制 1 打立出局 2 积分 3 瑞士移位
	uint16 m_MatchWaitParam1;	// 如m_MatchFormat==1时 m_MatchWaitParam1为需要等待的人数  其他2个赛制为需要等待的桌数
	uint16 m_MatchWaitParam2;	// m_MatchFormat==1时m_MatchWaitParam2=0   其他2个赛制为总分配的桌数

	uint64 m_MatchStartTime;	// 比赛开始时间

	uint16 m_RankNum;			
	std::list<TMatchRank> m_RankList;// 比赛排行

	
	CGame_STOC_MatchReconnect()
	{
		m_opcode = PROTOCOL_TYPE;

		m_MatchID = 0;			
		m_PlayerState = 0;		

		m_TableIndex = 0;		
		m_TableRound = 0;		

		m_MatchFormatRound = 0;	
		m_MatchFormat = 0;		
		m_MatchWaitParam1 = 0;	
		m_MatchWaitParam2 = 0;	

		m_MatchStartTime = 0;	

		m_RankNum = 0;	
	}

	void ReadProtocol(Protocol & data)
	{
		
		data>>m_MatchID;
		data>>m_PlayerState;
		data>>m_TableIndex;
		data>>m_TableRound;

		data>>m_MatchFormatRound;
		data>>m_MatchFormat;
		data>>m_MatchWaitParam1;
		data>>m_MatchWaitParam2;
		data>>m_MatchStartTime;
		data>>m_RankNum;

		TMatchRank nr;
		for (uint8 i = 0 ;i< m_RankNum;++i)
		{
			data>>nr.PlayerState;
			data>>nr.PlayerID;
			data>>nr.RankIndex;
			data>>nr.RankIntegral;
			data>>nr.Name;
			m_RankList.push_back(nr);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_MatchID;
		data<<m_PlayerState;

		data<<m_TableIndex;
		data<<m_TableRound;

		data<<m_MatchFormatRound;
		data<<m_MatchFormat;
		data<<m_MatchWaitParam1;
		data<<m_MatchWaitParam2;
		data<<m_MatchStartTime;
		data<<m_RankNum;

		for (std::list<TMatchRank>::iterator it = m_RankList.begin();it!=m_RankList.end();++it)
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



#endif	//_CPDKGAMESTOCRECONNECT_H