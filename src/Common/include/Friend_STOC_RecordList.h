#ifndef _CFRIDENSTOCRECORDLIST_H
#define _CFRIDENSTOCRECORDLIST_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CFriend_STOC_RecordList : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDRECORDLIST};

	uint32 playID;	    //玩家
	uint32  recordListSize;	//记录条数
	std::list<TProtocolPlayerRecord>  pyRecordList;

	CFriend_STOC_RecordList()
	{
		recordListSize = 0;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>recordListSize;

		TProtocolPlayerRecord pyRecordInfo;
		for (uint8 i = 0 ;i< recordListSize;++i)
		{
			data>>pyRecordInfo.PlayerID;
			data>>pyRecordInfo.PlayerHeadVersion;
			data>>pyRecordInfo.RecordRow;
			data>>pyRecordInfo.RecordTime;
			data>>pyRecordInfo.RecordType;
			data>>pyRecordInfo.PlayerSex;			
			data>>pyRecordInfo.m_strName;
			data>>pyRecordInfo.friend_online;
			data>>pyRecordInfo.friend_gold;
			data>>pyRecordInfo.friend_exp;
			data>>pyRecordInfo.friend_lost;
			data>>pyRecordInfo.friend_win;

			pyRecordList.push_back(pyRecordInfo);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<recordListSize;

		for (std::list<TProtocolPlayerRecord>::iterator it = pyRecordList.begin();it!=pyRecordList.end();++it)
		{
			TProtocolPlayerRecord& pyRecordInfo = *it;

			data<<pyRecordInfo.PlayerID;
			data<<pyRecordInfo.PlayerHeadVersion;
			data<<pyRecordInfo.RecordRow;
			data<<pyRecordInfo.RecordTime;
			data<<pyRecordInfo.RecordType;
			data<<pyRecordInfo.PlayerSex;
			data<<pyRecordInfo.m_strName;
			data<<pyRecordInfo.friend_online;
			data<<pyRecordInfo.friend_gold;
			data<<pyRecordInfo.friend_exp;
			data<<pyRecordInfo.friend_lost;
			data<<pyRecordInfo.friend_win;
		}
	}

};
#endif	//_CFRIDENSTOCRECORDLIST_H