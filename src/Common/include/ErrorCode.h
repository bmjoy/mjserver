#ifndef _CErrorCode_H
#define _CErrorCode_H


//网关返回错误类型

enum enumHttpErrorCode
{
	ErrorCode_NULL=0,
	ErrorCode_UserAccountRegisterFail,			// 账号注册失败
	ErrorCode_PhoneRegisterFail,			// 手机注册失败
	ErrorCode_FastRegisterFail,					//快速注册失败
	ErrorCode_PhoneVerify_FindFail,				// 手机账号找回失败
	ErrorCode_DeviceVerify_FindFail,		//设备号找回失败
	ErrorCode_DeviceVerifyRequestFail,		//验证码请求失败
	ErrorCode_LBSFindsFriendsNearbyFail,		//LBS查找附近好友失败
};


enum enumErrorCode
{
	ErrorCode_AccountVerifyFail,			// 账号验证失败
	ErrorCode_AccountVerifySuccess,			// 账号验证成功

	ErrorCode_AccountRegisterFail,			// 注册返回错误（暂时是错误产生源地是网关）;

	ErrorCode_AccountOtherGameLogin,		// 该账号已经在其他游戏登陆
	ErrorCode_AccountRepeatLogin,			// 重复登录
	ErrorCode_AccountUnLoginSuc,			// 退出登陆成功
	ErrorCode_UnLogin_InRoom,				// 在房间中  不允许退出游戏


	ErrorCode_EnterRoomSuccess,				// 进入房间成功
	ErrorCode_ExitRoomSuccess,				// 退出房间成功
	ErrorCode_EnterRoomFailed,				// 进入房间失败
	ErrorCode_NoReadyExitRoom,				// 长时间不准备退出房间

	ErrorCode_Http_NoAccoutID,				// 没有这个账号  账号ID错误

	ErrorCode_Http_ChangeGoldSuc,			// 加减金币成功


	ErrorCode_Match_Begin,
	ErrorCode_Match_NotAtSignup,			// 不在报名阶段
	ErrorCode_Match_HaveRoomID,				// 房间内已有房间ID
	ErrorCode_Match_LvLimit,				// 等级不够
	ErrorCode_Match_VipLvLimit,				// Vip等级不够
	ErrorCode_Match_NoMoney,				// 报名经费不足
	ErrorCode_Match_SignupSuc,				// 报名成功
	ErrorCode_Match_UnSignupSuc,			// 退赛成功
	ErrorCode_Match_ReSignupSuc,			// 重复报名
	ErrorCode_Match_MaxPlayer,				// 报名人数已满
	
	ErrorCode_Match_End,

	ErrorCode_FriendAdd_Fail,				//新增好友失败
	ErrorCode_FriendDel_Fail,				//删除好友失败
	ErrorCode_FriendAgree_Fail,				//同意添加好友失败
	ErrorCode_FriendRefuse_Fail,			//拒绝添加好友失败
	ErrorCode_FriendFind_NoFriend,			//好友不存在
	ErrorCode_FriendFind_Fail,				//查找好友失败
	ErrorCode_FriendList_Fail,				//查找好友列表失败
	ErrorCode_FriendTalk_Fail,				//发送好友消息失败
	ErrorCode_FriendRecord_Fail,			//获取聊天记录失败
	ErrorCode_FriendRecordList_Fail,		//获取聊天记录列表失败
	ErrorCode_FriendAdd_Repeat,				//重复添加好友请求


	ErrorCode_Game_NoMoney,					// 钱不够了
	ErrorCode_Game_NoMoneyToEnterRoom,		// 钱不够进入房间

	ErrorCode_Game_PlayerWarning,			//玩家报警
};


enum enumBackCodeErrorType					//php 错误返回 错误总类型宏 （）
{
	
	enumBackCodeErrorNull =0,
	//账号注册接口
	enumBackCodeError_RegisterLackParameter =1,				//缺失参数
	enumBackCodeError_RegisterParameterError,				//参数错误
	enumBackCodeError_RegisterValidationFail,				//验证错误
	enumBackCodeError_RegisterAccountThere,					//账号存在
	enumBackCodeError_RegisterDataUpdataError,				//数据跟新失败



	//快速注册接口
	enumBackCodeError_FastRegisterLackParameter =10,				//缺失参数
	enumBackCodeError_FastRegisterParameterError,					//参数错误
	enumBackCodeError_FastRegisterValidationFail,					//验证错误
	enumBackCodeError_FastRegisterGetAorPError,						//获取账号密码失败

	//手机验证码请求接口

	enumBackCodeError_ValidationLackParameter =20,				//缺失参数
	enumBackCodeError_ValidationParameterError,					//参数错误
	enumBackCodeError_ValidationFail,							//验证错误
	enumBackCodeError_ProduceValidationError,				//生成验证码失败

	//手机注册
	enumBackCodeError_PhoneRegisterLackParameter =30,				//缺失参数
	enumBackCodeError_PhoneRegisterParameterError,					//参数错误
	enumBackCodeError_PhoneRegisterValidationFail,					//验证错误
	enumBackCodeError_PhoneRegisterAccountThere,					//账号存在
	enumBackCodeError_PhoneRegisterDataUpdataError,					//数据跟新失败
	enumBackCodeError_PhoneRegisterLackParameterPthoneorVal,		//电话或者验证码缺失;
	enumBackCodeError_PhoneRegisterValidationFailure ,				//验证码失效
	enumBackCodeError_PhoneRegisterDataExtractError,				//数据提取失败





};


#endif	//_CErrorCode_H