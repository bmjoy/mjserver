#ifndef _CPDKGAMESTOCRECONNECT_H
#define _CPDKGAMESTOCRECONNECT_H

#include "Opcodes.h"
#include "Protocol.h"

class CPDKGame_STOC_Reconnect : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMERECONNECT};
	
	bool				isWarnining;
	uint32				PlayerID;					// 先手玩家ID
	uint32				PlayerHeadVersion;			// 头像版本
	uint32				PlayerGold;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex;			
	std::string			PlayerNick;					// 先手玩家昵称
	std::vector<uint8>	CardVec;		

	bool				isWarnining2;
	uint32				PlayerID2;
	uint32				PlayerHeadVersion2;			// 头像版本
	uint32				PlayerGold2;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex2;			

	std::string			PlayerNick2;     			// 先手玩家昵称
	std::vector<uint8>	CardVec2;		

	bool				isWarnining3;
	uint32				PlayerID3;	
	uint32				PlayerHeadVersion3;			// 头像版本
	uint32				PlayerGold3;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex3;			

	std::string			PlayerNick3;     			// 先手玩家昵称
	std::vector<uint8>	CardVec3;		

	uint8				leftTime;					// 轮到他的剩余时间 （秒）
	uint8				curIndex;					// 现在轮到谁index
	uint8				lastIndex;					// 最后出牌玩家index
	std::vector<uint8>	lastCards;					// 最后出的一手牌
	
	CPDKGame_STOC_Reconnect()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>isWarnining;
		data>>PlayerID;
		data>>PlayerHeadVersion;
		data>>PlayerGold;
		data>>PlayerSex;
		data>>PlayerNick;
		data>>CardVec;
		data>>isWarnining2;
		data>>PlayerID2;
		data>>PlayerHeadVersion2;
		data>>PlayerGold2;
		data>>PlayerSex2;
		data>>PlayerNick2;
		data>>CardVec2;
		data>>isWarnining3;
		data>>PlayerID3;
		data>>PlayerHeadVersion3;
		data>>PlayerGold3;
		data>>PlayerSex3;
		data>>PlayerNick3;
		data>>CardVec3;
			
		
		data>>leftTime;					
		data>>curIndex;					
		data>>lastIndex;				
		data>>lastCards;				
	}

	void WriteProtocol(Protocol & data)
	{
		data<<isWarnining;
		data<<PlayerID;
		data<<PlayerHeadVersion;
		data<<PlayerGold;
		data<<PlayerSex;
		data<<PlayerNick;
		data<<CardVec;
		data<<isWarnining2;
		data<<PlayerID2;
		data<<PlayerHeadVersion2;
		data<<PlayerGold2;
		data<<PlayerSex2;
		data<<PlayerNick2;
		data<<CardVec2;
		data<<isWarnining3;
		data<<PlayerID3;
		data<<PlayerHeadVersion3;
		data<<PlayerGold3;
		data<<PlayerSex3;
		data<<PlayerNick3;
		data<<CardVec3;
			
		data<<leftTime;					
		data<<curIndex;					
		data<<lastIndex;				
		data<<lastCards;				
	}


};



#endif	//_CPDKGAMESTOCRECONNECT_H