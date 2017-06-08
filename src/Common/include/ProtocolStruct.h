#ifndef _PROTOCOLSTRUCT_H
#define _PROTOCOLSTRUCT_H

#include <string>

#if COMPILER != COMPILER_GNU
typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;

#else

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
//typedef uint32_t DWORD;

#endif



///////////////////////////////////////////////////跑得快游戏相关定义
typedef uint8	CARD;

//不同牌的类型
enum CARDSPRITETYPE {
	csNULL = 0,
	csPDKCard ,      // 跑得快
	csDDZCard        //斗地主
	// ......
};
// 新定义的牌的花色
enum NEWCARDCOLOR {
	ccColorNULL = 0,
	newccFangKuai = 1,
	newccMeiHua ,
	newccHongTao,
	newccHeiTao,
	newccBlack=0x0f
};

// 新定义的牌的点数    从3 到大鬼 依次递增
enum NEWCARDPOINT {

	ccNULL=0,
	cc3 = 1,
	cc4,
	cc5,
	cc6,
	cc7,
	cc8,
	cc9,
	cc10,
	ccJ,
	ccQ,
	ccK,
	ccA,
	cc2,
	ccSmallGui,
	ccBigGui
};
//新定义的牌的原始基类
struct CardSprite
{
	NEWCARDCOLOR spc;      //牌的花色
	NEWCARDPOINT spp;     //牌的点数
};


//不同的牌型
enum CARDTYPE {
	ctNone,
	ct0,
	ct1,     //一张
	ct2,    //一对
	ct3,    //三个
	ctBomb,  //炸弹
	ctRocket, //火箭
	ct1s,    //顺子
	ct2s,   //连队  3->A
	ct3s,   //飞机
	ct3s1s,  //三带一 可能是多个
	ct3s2s,  //三带二 可能是多个
	ct4s1s,  //四带一
	ct4s2d, //四带两队
	ct4s3,  //四带三
};

// 玩家参数
enum enumPLAYERPARAM
{
	PLAYERPARAM_NULL = 0,
	PLAYERINFO_GOLDADD,			// 金币增加
	PLAYERINFO_GOLDSUB,			// 扣金币
	PLAYERINFO_EXP,				// 经验
	PLAYERPARAM_MAX,
};
///////////////////////////////////////////////////跑得快游戏相关定义

enum EnumGameObjType
{
	GAMEOBJTYPE_ITEM,		//(游戏道具)
	GAMEOBJTYPE_GOLD,		//(游戏金币)
	GAMEOBJTYPE_MONEY,		//(游戏元宝)
	GAMEOBJTYPE_INTEGRAL,	//(比赛积分)
};

enum EnumItemChangeType
{
	ITEMCHANGE_NULL,
	ITEMCHANGE_BOMB,			// 炸弹
	ITEMCHANGE_SETINTEGRAL,		// 发放积分
	ITEMCHANGE_OVERCHECK,		// 打牌结束结算

};


#pragma pack(push, 1)


// 一个人的结算数据
struct TGameSettlement
{
	bool	isEscape;			// 是否逃跑
	uint8	RemainCardNum;		// 剩余牌数
	uint32	ChrID;				// 角色ID
	uint32	AddExp;				// 增加经验
	int32	AddMoney;			// 增加金钱
	TGameSettlement()
	{
		isEscape = false ;			
		RemainCardNum = 0;		
		ChrID = 0;				
		AddExp = 0;				
		AddMoney = 0;			
	}

	void Clear()
	{
		isEscape = false;			
		RemainCardNum = 0;		
		ChrID = 0;				
		AddExp = 0;				
		AddMoney = 0;			
	}
};

struct TNormalRoom
{
	uint8	TableLimit;	// 禁止同IP 1位 ，黑名单  2位 
	uint8	RoomState;	// 房间状态		比赛状态
	uint16	RoomRat;	// 房间倍率		比赛人数
	uint16	LevelLimit;	// 等级要求		
	uint32	GoldLimit;	// 手气要求		报名费用
	uint32	RoomID;		// 房间ID
	uint32	RoomTime;	// 比赛时间
	std::string	RoomName;
};

struct TProtocolRoom
{
	uint32	RoomID;		// 房间ID
	uint32	RoomType;	// 房间类型 1 普通房间 2比赛房间
	uint8	TableLimit;	// 禁止同IP 1位 ，黑名单  2位 
	uint8	RoomState;	// 房间状态		比赛状态
	uint16	RoomRat;	// 房间倍率		比赛人数
	uint16	LevelLimit;	// 等级要求		
	uint32	GoldLimit;	// 手气要求		报名费用
	uint32	RoomTime;	// 比赛时间
	std::string	RoomName;
};

//聊天记录
struct TProtocolTalkRecord
{
	uint32 sendPlayer; //发送玩家ID
	time_t sendTime;	//发送时间
	std::string	strRecord; //消息记录
};

//聊天记录
struct TProtocolPlayerRecord
{
	uint32	     PlayerID;			//发送玩家ID
	uint32		 PlayerHeadVersion;	// 头像版本号
	uint32		 RecordRow;			// 记录条数
	uint32       RecordTime;		// 记录时间
	uint8		 RecordType;		// 0为添加好友，1为消息记录
	bool		 PlayerSex;	        // 性别	
	std::string	 m_strName;			// 昵称
	bool			friend_online;		    //玩家是否在线
	uint64			friend_gold;			// 手气值
	uint64			friend_exp;				// 经验
	uint64			friend_lost;			// 输局数
	uint64			friend_win;				// 赢局数
};

struct TProtocolMatchRoom
{
	uint32	MatchID;	// 比赛ID
	uint32	RoomID;		// 房间ID
	uint8	RoomState;	// 比赛状态
	uint64	RoomTime;	// 比赛时间
};


enum GameResultType {
	GResultT_Win,
	GResultT_Fail,
};

struct TGameOver
{
	bool	isEscape;		// 是否逃跑
	uint32	PlayerID;		// 玩家ID
	uint8	GameResult;		// 比赛结果
	int32	MoneyChange;	// 金币改变
	uint32	ExpAdd;			// 经验增加

	TGameOver()
		: isEscape(false),
		PlayerID(0),
		GameResult(0),
		MoneyChange(0),
		ExpAdd(0)
	{

	}
};

struct TItemChange
{
	uint8				itemType;	
	uint32				playerID;	
	uint32				itemID;
	int32				itemNum;
};

struct TMatchHistory
{
	uint32	MatchID;		// 比赛ID
	uint32	MatchRank;		// 比赛排名

	uint32	MatchReward;	// 比赛奖励
	uint64	MatchTime;		// 比赛时间
};

struct TMatchRank
{
	uint8	PlayerState;		
	uint32	PlayerID;		
	uint32	RankIndex;		
	uint32	RankIntegral;	
	std::string	Name;		
};

struct TMatchPlayerReward
{
	uint8	ItmeType;
	uint32	ItmeID;
	uint32	ItmeNum;
};

struct TPDKGame_PLAYERINFO
{
	uint32				PlayerID;					// 先手玩家ID
	uint32				PlayerHeadVersion;			// 头像版本
	uint32				PlayerGold;					// 比赛时是积分  其他时候是金币
	bool				PlayerSex;					
	std::string			PlayerNick;					// 先手玩家昵称
	std::vector<uint8>	CardVec;		
};


enum LoginType {
	LoginType_NULL,
	LoginType_Login,
	LoginType_UnLogin,
	LoginType_Num,
};

#pragma pack(pop)



#endif	//_PROTOCOLSTRUCT_H
