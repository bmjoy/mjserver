#ifndef _CCREPORTCTOSLBSRELATED_H
#define _CCREPORTCTOSLBSRELATED_H

#include "Opcodes.h"
#include "Protocol.h"

class CReport_CTOS_LBSRelated : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_WH_LBSRELATEDMESSAGE};

	// 不需要用到的字符串填 ""
	uint32				m_strAccount;			//账号
	double				m_strLatitude;				// 维度  
	double				m_strLongitude;			// 经度
	uint8				m_page;					//请求页数;
	uint8				m_iRegisterType;		// 注册类型  Opcodes.h   enumRegisterType
	

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