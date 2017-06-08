#ifndef _CGAME_STOC_MATCHRECONNECT_H_
#define _CGAME_STOC_MATCHRECONNECT_H_

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_MatchReconnect : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHRECONNECT};
	
	uint16 m_MatchID;			// ����ID
	uint16 m_PlayerState;		// ���״̬
	uint16 m_TableIndex;		// ����ID
	uint16 m_TableRound;		// ���ӵڼ���

	uint16 m_MatchFormatRound;	// �ڼ�������
	uint16 m_MatchFormat;		// ��ǰ���� 1 �������� 2 ���� 3 ��ʿ��λ
	uint16 m_MatchWaitParam1;	// ��m_MatchFormat==1ʱ m_MatchWaitParam1Ϊ��Ҫ�ȴ�������  ����2������Ϊ��Ҫ�ȴ�������
	uint16 m_MatchWaitParam2;	// m_MatchFormat==1ʱm_MatchWaitParam2=0   ����2������Ϊ�ܷ��������

	uint64 m_MatchStartTime;	// ������ʼʱ��

	uint16 m_RankNum;			
	std::list<TMatchRank> m_RankList;// ��������

	
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