#ifndef _CFRIDENSTOCREQUEST_H
#define _CFRIDENSTOCREQUEST_H

#include "Opcodes.h"
#include "Protocol.h"

class CPlayerData;

class CFriend_STOC_Request : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDREQUEST};

	uint8  msgType;     //子消息类型
	uint32 playID;	    //玩家

	uint32			friend_id;				// 账号ID		= 0 代表空地址位
	std::string		friend_PlayerName;		// 昵称
	bool			friend_online;		    //玩家是否在线
	uint64			friend_gold;			// 手气值
	uint64			friend_exp;				// 经验
	uint64			friend_lost;			// 输局数
	uint64			friend_win;				// 赢局数

	bool			friend_sex;				// 性别 0 男 1女

	uint32			friend_HeadVersion; 	// 头像版本号
	uint8			friend_province; 		// 省代码
	uint8			friend_city; 			// 市代码

	CFriend_STOC_Request()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>playID;
		data>>msgType;
		data>>friend_id;
		data>>friend_PlayerName;
		data>>friend_gold;
		data>>friend_online;
		data>>friend_exp;
		data>>friend_lost;
		data>>friend_win;
		data>>friend_sex;
		data>>friend_HeadVersion; 	
		data>>friend_province; 	
		data>>friend_city; 		
	}

	void WriteProtocol(Protocol & data)
	{
		data<<playID;
		data<<msgType;
		data<<friend_id;
		data<<friend_PlayerName;
		data<<friend_gold;
		data<<friend_online;
		data<<friend_exp;
		data<<friend_lost;
		data<<friend_win;
		data<<friend_sex;			
		data<<friend_HeadVersion; 	
		data<<friend_province; 	
		data<<friend_city; 		
	}

};
#endif	//_CFRIDENSTOCREQUEST_H