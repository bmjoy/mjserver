#ifndef _CPDKGAMESTOCSTART_H
#define _CPDKGAMESTOCSTART_H

#include "Opcodes.h"
#include "Protocol.h"


//struct TPDKGame_PLAYERINFO
//{
//	uint32				PlayerID;					// 先手玩家ID
//	uint32				PlayerHeadVersion;			// 头像版本
//	uint32				PlayerGold;					// 比赛时是积分  其他时候是金币
//	bool				PlayerSex;					
//	std::string			PlayerNick;					// 先手玩家昵称
//	std::vector<uint8>	CardVec;		
//};

class CPDKGame_STOC_Start : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMESTART};
	
	uint8				RoundNum;					// 回合数
	uint32				TableID;					// 桌子ID
	
	uint32				PlayerID;					// 先手玩家ID
	uint32				PlayerHeadVersion;			// 头像版本
	uint32				PlayerGold;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex;					
	std::string			PlayerNick;					// 先手玩家昵称
	std::vector<uint8>	CardVec;		

	uint32				PlayerID2;
	uint32				PlayerHeadVersion2;			// 头像版本
	uint32				PlayerGold2;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex2;					
	std::string			PlayerNick2;     			// 先手玩家昵称
	std::vector<uint8>	CardVec2;		

	uint32				PlayerID3;	
	uint32				PlayerHeadVersion3;			// 头像版本
	uint32				PlayerGold3;				// 比赛时是积分  其他时候是金币
	bool				PlayerSex3;					
	std::string			PlayerNick3;     			// 先手玩家昵称
	std::vector<uint8>	CardVec3;		

	CPDKGame_STOC_Start()
	{
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>RoundNum;
		data>>TableID;
		data>>PlayerID;
		data>>PlayerHeadVersion;
		data>>PlayerGold;
		data>>PlayerSex;
		data>>PlayerNick;
		data>>CardVec;
		data>>PlayerID2;
		data>>PlayerHeadVersion2;
		data>>PlayerGold2;
		data>>PlayerSex2;
		data>>PlayerNick2;
		data>>CardVec2;
		data>>PlayerID3;
		data>>PlayerHeadVersion3;
		data>>PlayerGold3;
		data>>PlayerSex3;
		data>>PlayerNick3;
		data>>CardVec3;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<RoundNum;
		data<<TableID;
		data<<PlayerID;
		data<<PlayerHeadVersion;
		data<<PlayerGold;
		data<<PlayerSex;
		data<<PlayerNick;
		data<<CardVec;
		data<<PlayerID2;
		data<<PlayerHeadVersion2;
		data<<PlayerGold2;
		data<<PlayerSex2;
		data<<PlayerNick2;
		data<<CardVec2;
		data<<PlayerID3;
		data<<PlayerHeadVersion3;
		data<<PlayerGold3;
		data<<PlayerSex3;
		data<<PlayerNick3;
		data<<CardVec3;
	}

};



#endif	//_CPDKGAMESTOCSTART_H