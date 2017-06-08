#ifndef _OPCODES_H
#define _OPCODES_H

enum eMessageFromSeverToClientType
{
	eTypeNULL =	 0x000	,
	eTypeISMATCH,							//比赛开始
	eTypeISSECONETURN,						//是否进入复赛
	eTypeISPLAYERGETOUT,					//被淘汰
	eTypeISCHANGETABLE,						//是否跟换桌子
	eTypeNUMPLAYONTABLE,					//桌子上的轮数
	eTypeTHEPLACEONMATCH,					//获得的名次
	eTypeWAITFOROTHERS,						//等待其他玩家完成	
	eTypeROOMBASECHANGED,					//房间倍率跟换
	eTypeMATCHEXIT,							//人数不足比赛取消;
};


enum enumRegisterType
{
	RegisterType_NULL=0,
	RegisterType_PhoneVerify_Register,		// 获得手机验证注册码
	RegisterType_PhoneVerify_Find,			// 手机找回获取验证码
	RegisterType_NormalRegister,			// 普通注册
	RegisterType_FastRegister,				// 快速注册
	RegisterType_PhoneRegister,				// 手机号注册
	RegisterType_DeviceVerify_Find,			// 设备号找回
	RegisterType_GetPhoneVerify_Find,		// 手机账号找回通过验证码
	RegisterType_SendLatitudeAndLongitude,	//经纬度;
	RegisterType_LBSFriendsNear,			//LBS 查找附近好友;
};

enum enumHttpRequest
{
	REQUESTTYPE_NULL=0,
	REQUESTTYPE_RELOADUSERINFO,			// 重新载入userinfo信息
	REQUESTTYPE_REQUESTGAMEINFO,		// 请求gameinfo信息
};

enum enumAccountMemUpdateType
{
	AMUPDATETYPE_NULL = 0,		
	AMUPDATETYPE_All,
	AMUPDATETYPE_USERINFO,				// 只更新USERINFO部分信息
};

enum enumFriendReqType
{
	REQUESTADD_FRIEND = 0,				//新增好友
	REQUESTDEL_FRIEND,					//删除好友	
	REQUESTAGREE_FRIEND,				//同意加为好友
	REQUESTREFUSE_FRIEND,				//拒绝加为好友
	REQUESTFIND_FRIEND,					//查找好友
};

enum enumMatchRequest
{
	MATCHREQUEST_HISTORYNULL = 0,		
	MATCHREQUEST_HISTORY,
	
};

enum Opcodes
{
	MSG_NULL								= 0x000	,
	
	///通用============================================================================================================================
	MSG_GENERAL_NULL					= 0,
	MSG_SERVERREGISTERED	,			// 服务器连接注册
	MSG_REGISTERED	,					// 注册
	MSG_DECRYPT	,

	MSG_PING,							// PING
	MSG_PONG,							// PING
	MSG_ERROR,							// 通用错误信息

	MSG_PROTOTEST,						// GOOGLE PROTOBUF 测试协议

	///HTTP相关============================================================================================================================
	MSG_HTTP_NULL						= 100,			// 100-299
	MSG_HTTPTOA_INFO,					// HTTP请求重载userinfo数据					
	MSG_SA_HTTPACCOUNTINFO,				// HTTP网关返回账号数据
	MSG_SC_RESETUSERINFO	,			// 重置用户信息
	MSG_WH_GOLDSCHANGED,				// web 发给网关的更改金币;
	MSG_WH_LBSRELATEDMESSAGE,			// LBS相关协议;

	///服务器之间通信======================================================================================================================
	MSG_SERVER_NULL						= 300,			// 300-499
	MSG_SERVER_STATENOTIFY,				// 玩家状态变化（GF->AM）				CGame_STOA_PlayerStateNotify.h
	MSG_SERVER_ITEMCHANGE,				// 玩家金钱道具变化（GF->AM->DB）		CGame_STOA_ItemChange.h
	MSG_SERVER_MATCHHIS,				// 玩家比赛历史变化（GF->AM->DB）		CGame_STOA_MatchHis.h
	MSG_SERVER_GAMEOVER,				// 游戏桌结束（GF->AM->DB）				CGame_STOA_GameOver.h
	MSG_SERVER_LOGIN,					// 玩家登入登出服务器（GF->AM）			CAccount_STOA_Login.h
	




	///登陆相关============================================================================================================================
	MSG_LOGIN_NULL						= 500,
	MSG_CS_LOGIN,						// 登陆相关 弃用
	MSG_CS_LOGINLOGIN	,				
	MSG_SC_LOGININFO	,				// 登陆信息
	MSG_SC_REGISTER	,					// 注册
	MSG_CS_REGISTER	,					// 

	MSG_SA_ACCOUNTFIND,					// 服务器向账号服请求账号数据
	MSG_SA_ACCOUNTREGISTER,				// 服务器向账号服请求注册账号数据
	MSG_AS_ACCOUNTINFO,	
	MSG_MEM_GAMEINFO	,				// 从内存数据库返回gameinfo


	///游戏房间相关=========================================================================================================================
	MSG_ROOM_NULL						= 600,
	MSG_SC_ROOMLIST	,
	MSG_SC_MATCHLIST	,
	MSG_CS_ENTERROOM	,	

	///游戏打牌通用相关=====================================================================================================================
	MSG_CARDGAME_NULL					= 700,
	MSG_WH_CLIENTTRUSTEESHIP, 			// 客户端设置托管
	MSG_SC_CHANGEGOLD,					

	///游戏跑得快相关=====================================================================================================================
	MSG_PDKGAME_NULL					= 800,
	MSG_SC_GAMESTART,					// 游戏开始 发牌
	MSG_SC_GAMEOVER,					// 游戏结束
	MSG_SC_TURNROUND,					// 轮换出牌人
	MSG_CS_GAMEOUTCARD,					// 出牌
	MSG_SC_GAMEOUTCARD,					// 通知其他人出的牌
	MSG_CS_GAMEREADY,					// 准备
	MSG_SC_GAMENOTCANOUT,				// 要不起
	MSG_SC_GAMERECONNECT,				// 重连牌局


	///游戏比赛相关相关=====================================================================================================================
	MSG_MATCH_NULL						= 900,
	MSG_CS_Match_Signup,				// 比赛报名
	MSG_CS_Competition,					// 比赛相关;
	MSG_CS_CApplyEnterCompetition,		// 客户端申请进入比赛房间
	MSG_SC_MATCHMESSAGE,				// 比赛通知信息
	MSG_SC_HISTORY,						// 比赛历史;
	MSG_CS_MATCHREQUEST,				// 比赛请求
	MSG_CS_MATCHRANK,					// 比赛排名
	MSG_SC_MATCHRECONNECT,				// 比赛重连


	//好友相关
	MSG_FRIEND_NULL						= 1000,
	MSG_CS_FRIENDREQUEST,				//服务器向账号服请求添加好友数据
	MSG_SC_FRIENDREQUEST,				//内存服务器向账号服务器返回好友数据
	MSG_CS_FRIENDLIST,					//好友列表	
	MSG_SC_FRIENDLIST,					//好友列表返回
	MSG_CS_FRIENDTALK,					//发送好友聊天
	MSG_SC_FRIENDTALK,					//接收好友聊天
	MSG_CS_FRIENDRECORD,				//请求查看聊天记录
	MSG_SC_FRIENDRECORD,				//接收好友聊天记录
	MSG_CS_FRIENDRECORDLIST,			//请求查看聊天记录列表
	MSG_SC_FRIENDRECORDLIST,			//接收好友聊天记录列表数据
	MSG_SC_FRIENDTALKWINDOW,			//发送打开窗口状态

	MSG_CS_PLAYERINFO,					//玩家信息保存
	NUM_MSG_TYPES	,	// max msg number
};

#endif	//_OPCODES_H
