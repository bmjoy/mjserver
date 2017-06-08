/*
	客户端进入比赛房间请求协议;
	create by wushikui 2014-08-14;
*/




#ifndef _CAPPLYCTOENTERCOMPETITION_H
#define _CAPPLYCTOENTERCOMPETITION_H

#include "Opcodes.h"
#include "Protocol.h"

class CApply_CTOS_EnterCompetition : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_CApplyEnterCompetition};

	uint8				 m_CompetitionID;	//比赛房间ID;
	//PropForCompetition	 m_ePropStyle;		//需要道具;    buffer 不接受枚举;
	uint8				m_ePropStyle;		//预留接口 <如： 1代表需要白金点 2.代表需要手气值;>
	CApply_CTOS_EnterCompetition()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_CompetitionID;
		data>>m_ePropStyle;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_CompetitionID;
		data<<m_ePropStyle;
	}

};



#endif	//_CAPPLYCTOENTERCOMPETITION_H