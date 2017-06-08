#ifndef _CCREPORTCTOSLBSRELATED_H
#define _CCREPORTCTOSLBSRELATED_H

#include "Opcodes.h"
#include "Protocol.h"

class CReport_CTOS_LBSRelated : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_WH_LBSRELATEDMESSAGE};

	// ����Ҫ�õ����ַ����� ""
	uint32				m_strAccount;			//�˺�
	double				m_strLatitude;				// ά��  
	double				m_strLongitude;			// ����
	uint8				m_page;					//����ҳ��;
	uint8				m_iRegisterType;		// ע������  Opcodes.h   enumRegisterType
	

	CReport_CTOS_LBSRelated()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>m_strAccount;	
		data>>m_strLatitude;	
		data>>m_strLongitude;
		data>>m_page;
		data>>m_iRegisterType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<m_strAccount;	
		data<<m_strLatitude;	
		data<<m_strLongitude;
		data<<m_page;
		data<<m_iRegisterType;
	}

};



#endif	//_CCREPORTCTOSLBSRELATED_H