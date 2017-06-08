#ifndef _CFRIDENSTOCRECORD_H
#define _CFRIDENSTOCRECORD_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CFriend_STOC_Record : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDRECORD};

	uint32 playID;	    //玩家
	uint32 friendID;	//要查找玩家ID
	uint32  recordSize;	//记录条数
	uint8  msgType;		//0为查看留言，1为查看聊天记录
	std::list<TProtocolTalkRecord>  tkRecordList;

	CFriend_STOC_Record()
	{
		recordSize = 0;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>friendID;
		data>>recordSize;
		data>>msgType;

		TProtocolTalkRecord tkRecordInfo;
		for (uint8 i = 0 ;i< recordSize;++i)
		{
			data>>tkRecordInfo.sendPlayer;
			data>>tkRecordInfo.sendTime;
			data>>tkRecordInfo.strRecord;
			
			tkRecordList.push_back(tkRecordInfo);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendID;
		data<<recordSize;
		data<<msgType;

		for (std::list<TProtocolTalkRecord>::iterator it = tkRecordList.begin();it!=tkRecordList.end();++it)
		{
			TProtocolTalkRecord& tkRecordInfo = *it;

			data<<tkRecordInfo.sendPlayer;
			data<<tkRecordInfo.sendTime;
			data<<tkRecordInfo.strRecord;
		}
	}

};
#endif	//_CFRIDENSTOCRECORD_H