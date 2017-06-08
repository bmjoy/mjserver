#ifndef _CFRIDENCTOSRECORD_H
#define _CFRIDENCTOSRECORD_H

#include "Opcodes.h"
#include "Protocol.h"

class CFriend_CTOS_Record : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_CS_FRIENDRECORD};
		
	uint32 playID;	    //���
	uint32 friendID;	//��鿴˭�ļ�¼
	uint64 timeBase;	//ʱ���׼ֵ��Ϊ0����ȡ����ļ�¼
	uint16 pageSize;	//һҳ��ʾ��������¼
	uint8  msgType;		//0Ϊ�鿴���ԣ�1Ϊ�鿴�����¼

	CFriend_CTOS_Record()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>friendID;
		data>>timeBase;
		data>>pageSize;
		data>>msgType;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<timeBase;
		data<<pageSize;
		data<<msgType;
	}

};
#endif	//_CFRIDENCTOSRECORD_H