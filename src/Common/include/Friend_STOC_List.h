#ifndef _CFRIDENSTOCLIST_H
#define _CFRIDENSTOCLIST_H

#include "Opcodes.h"
#include "Protocol.h"

struct FRIEND_INFO
{
	// 游戏具体数据根据数据表定义
	uint32				PlayerID;
	uint64				PlayerGold;			// 手气值
	bool				PlayerOnline;		//玩家是否在线
	uint8				PlayerProvince; 		// 省代码
	uint8				PlayerCity; 			// 市代码

	uint32				PlayerHeadVersion;	// 头像版本号
	bool				PlayerSex;			// 性别

	uint64				PlayerExp;			
	uint64				PlayerLost;			
	uint64				PlayerWin;			

	std::string			m_strName;			// 昵称

};

class CFriend_STOC_List : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDLIST};
	uint32 playID;
	uint8	friendSize;

	std::list<FRIEND_INFO> friendList;

	CFriend_STOC_List()
	{
		friendSize = 0;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>friendSize;
		FRIEND_INFO pInfo;
		for (uint8 i = 0 ;i< friendSize;++i)
		{
			data>>pInfo.PlayerID;
			data>>pInfo.PlayerGold;
			data>>pInfo.PlayerOnline;
			data>>pInfo.PlayerExp;
			data>>pInfo.PlayerLost;
			data>>pInfo.PlayerWin;

			data>>pInfo.PlayerSex;
			data>>pInfo.m_strName;
			data>>pInfo.PlayerHeadVersion;
			data>>pInfo.PlayerProvince;
			data>>pInfo.PlayerCity;

			friendList.push_back(pInfo);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<friendSize;

		for (std::list<FRIEND_INFO>::iterator it = friendList.begin();it!=friendList.end();++it)
		{
			FRIEND_INFO& pInfo = *it;

			data<<pInfo.PlayerID;
			data<<pInfo.PlayerGold;
			data<<pInfo.PlayerOnline;
			data<<pInfo.PlayerExp;
			data<<pInfo.PlayerLost;
			data<<pInfo.PlayerWin;

			data<<pInfo.PlayerSex;
			data<<pInfo.m_strName;
			data<<pInfo.PlayerHeadVersion;
			data<<pInfo.PlayerProvince;
			data<<pInfo.PlayerCity;
		}
	}

};
#endif	//_CFRIDENSTOCLIST_H