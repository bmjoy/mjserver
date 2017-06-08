/*
	�ͻ��˽��������������Э��;
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

	uint8				 m_CompetitionID;	//��������ID;
	//PropForCompetition	 m_ePropStyle;		//��Ҫ����;    buffer ������ö��;
	uint8				m_ePropStyle;		//Ԥ���ӿ� <�磺 1������Ҫ�׽�� 2.������Ҫ����ֵ;>
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