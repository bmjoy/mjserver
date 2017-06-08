#ifndef _CLOGINSTOCSUCCEED_H
#define _CLOGINSTOCSUCCEED_H

#include "Opcodes.h"
#include "Protocol.h"

class CLogin_STOC_Succeed : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_LOGININFO};

	uint32			account_id;				// 账号ID		= 0 代表空地址位

	uint64			account_gold;			// 手气值
	uint64			account_present;		// 礼品券
	uint64			account_exp;			// 经验
	uint64			account_lost;			// 输局数
	uint64			account_win;			// 赢局数

	std::string		account_PlayerName;		// 昵称
	bool			account_sex;			// 性别 0 男 1女
	uint32			account_HeadVersion; 	// 头像版本号
	uint8			account_province; 		// 省代码
	uint8			account_city; 			// 市代码

	bool			account_bindip;			// 绑定ID 1表示绑定
	uint8			account_bindpsw;		// 1表示登陆时需要手机验证码，2表示需要矩阵码 0 表示不需要
	uint8			account_bindpswparam;	// 手机验证码、或者矩阵码的列号;网上当切换为矩阵码时这个值变为0


	CLogin_STOC_Succeed()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>account_id;
		data>>account_gold;
		data>>account_present;
		data>>account_exp;
		data>>account_lost;
		data>>account_win;

		data>>account_PlayerName;	
		data>>account_sex;			
		data>>account_HeadVersion; 	
		data>>account_province; 	
		data>>account_city; 		

		data>>account_bindip;
		data>>account_bindpsw;
		data>>account_bindpswparam;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<account_id;
		data<<account_gold;
		data<<account_present;
		data<<account_exp;
		data<<account_lost;
		data<<account_win;
		data<<account_PlayerName;	
		data<<account_sex;			
		data<<account_HeadVersion; 	
		data<<account_province; 	
		data<<account_city; 		

		data<<account_bindip;
		data<<account_bindpsw;
		data<<account_bindpswparam;

	}

};

#endif	//_CLOGINSTOCSUCCEED_H