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



///////////////////////////////////////////////////�ܵÿ���Ϸ��ض���
typedef uint8	CARD;

//��ͬ�Ƶ�����
enum CARDSPRITETYPE {
	csNULL = 0,
	csPDKCard ,      // �ܵÿ�
	csDDZCard        //������
	// ......
};
// �¶�����ƵĻ�ɫ
enum NEWCARDCOLOR {
	ccColorNULL = 0,
	newccFangKuai = 1,
	newccMeiHua ,
	newccHongTao,
	newccHeiTao,
	newccBlack=0x0f
};

// �¶�����Ƶĵ���    ��3 ����� ���ε���
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
//�¶�����Ƶ�ԭʼ����
struct CardSprite
{
	NEWCARDCOLOR spc;      //�ƵĻ�ɫ
	NEWCARDPOINT spp;     //�Ƶĵ���
};


//��ͬ������
enum CARDTYPE {
	ctNone,
	ct0,
	ct1,     //һ��
	ct2,    //һ��
	ct3,    //����
	ctBomb,  //ը��
	ctRocket, //���
	ct1s,    //˳��
	ct2s,   //����  3->A
	ct3s,   //�ɻ�
	ct3s1s,  //����һ �����Ƕ��
	ct3s2s,  //������ �����Ƕ��
	ct4s1s,  //�Ĵ�һ
	ct4s2d, //�Ĵ�����
	ct4s3,  //�Ĵ���
};

// ��Ҳ���
enum enumPLAYERPARAM
{
	PLAYERPARAM_NULL = 0,
	PLAYERINFO_GOLDADD,			// �������
	PLAYERINFO_GOLDSUB,			// �۽��
	PLAYERINFO_EXP,				// ����
	PLAYERPARAM_MAX,
};
///////////////////////////////////////////////////�ܵÿ���Ϸ��ض���

enum EnumGameObjType
{
	GAMEOBJTYPE_ITEM,		//(��Ϸ����)
	GAMEOBJTYPE_GOLD,		//(��Ϸ���)
	GAMEOBJTYPE_MONEY,		//(��ϷԪ��)
	GAMEOBJTYPE_INTEGRAL,	//(��������)
};

enum EnumItemChangeType
{
	ITEMCHANGE_NULL,
	ITEMCHANGE_BOMB,			// ը��
	ITEMCHANGE_SETINTEGRAL,		// ���Ż���
	ITEMCHANGE_OVERCHECK,		// ���ƽ�������

};


#pragma pack(push, 1)


// һ���˵Ľ�������
struct TGameSettlement
{
	bool	isEscape;			// �Ƿ�����
	uint8	RemainCardNum;		// ʣ������
	uint32	ChrID;				// ��ɫID
	uint32	AddExp;				// ���Ӿ���
	int32	AddMoney;			// ���ӽ�Ǯ
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
	uint8	TableLimit;	// ��ֹͬIP 1λ ��������  2λ 
	uint8	RoomState;	// ����״̬		����״̬
	uint16	RoomRat;	// ���䱶��		��������
	uint16	LevelLimit;	// �ȼ�Ҫ��		
	uint32	GoldLimit;	// ����Ҫ��		��������
	uint32	RoomID;		// ����ID
	uint32	RoomTime;	// ����ʱ��
	std::string	RoomName;
};

struct TProtocolRoom
{
	uint32	RoomID;		// ����ID
	uint32	RoomType;	// �������� 1 ��ͨ���� 2��������
	uint8	TableLimit;	// ��ֹͬIP 1λ ��������  2λ 
	uint8	RoomState;	// ����״̬		����״̬
	uint16	RoomRat;	// ���䱶��		��������
	uint16	LevelLimit;	// �ȼ�Ҫ��		
	uint32	GoldLimit;	// ����Ҫ��		��������
	uint32	RoomTime;	// ����ʱ��
	std::string	RoomName;
};

//�����¼
struct TProtocolTalkRecord
{
	uint32 sendPlayer; //�������ID
	time_t sendTime;	//����ʱ��
	std::string	strRecord; //��Ϣ��¼
};

//�����¼
struct TProtocolPlayerRecord
{
	uint32	     PlayerID;			//�������ID
	uint32		 PlayerHeadVersion;	// ͷ��汾��
	uint32		 RecordRow;			// ��¼����
	uint32       RecordTime;		// ��¼ʱ��
	uint8		 RecordType;		// 0Ϊ��Ӻ��ѣ�1Ϊ��Ϣ��¼
	bool		 PlayerSex;	        // �Ա�	
	std::string	 m_strName;			// �ǳ�
	bool			friend_online;		    //����Ƿ�����
	uint64			friend_gold;			// ����ֵ
	uint64			friend_exp;				// ����
	uint64			friend_lost;			// �����
	uint64			friend_win;				// Ӯ����
};

struct TProtocolMatchRoom
{
	uint32	MatchID;	// ����ID
	uint32	RoomID;		// ����ID
	uint8	RoomState;	// ����״̬
	uint64	RoomTime;	// ����ʱ��
};


enum GameResultType {
	GResultT_Win,
	GResultT_Fail,
};

struct TGameOver
{
	bool	isEscape;		// �Ƿ�����
	uint32	PlayerID;		// ���ID
	uint8	GameResult;		// �������
	int32	MoneyChange;	// ��Ҹı�
	uint32	ExpAdd;			// ��������

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
	uint32	MatchID;		// ����ID
	uint32	MatchRank;		// ��������

	uint32	MatchReward;	// ��������
	uint64	MatchTime;		// ����ʱ��
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
	uint32				PlayerID;					// �������ID
	uint32				PlayerHeadVersion;			// ͷ��汾
	uint32				PlayerGold;					// ����ʱ�ǻ���  ����ʱ���ǽ��
	bool				PlayerSex;					
	std::string			PlayerNick;					// ��������ǳ�
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
