#ifndef _CGAMESTOMATCHMESSAGE_H
#define _CGAMESTOMATCHMESSAGE_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_MatchMessage : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHMESSAGE};

	//  比赛状态
	//  MATCHSTATE_NULL,					// 0
	//	MATCHSTATE_PREPARE,					// 1准备状态
	//	MATCHSTATE_SIGNUP,					// 2可报名状态
	//	MATCHSTATE_MATCH,					// 3比赛阶段
	//	MATCHSTATE_OVER,					// 4比赛结束(指此比赛所有时间段结束)
	//	,					// 5 发放赛制奖励  eNumMessage 奖励的金币数量
	//	,					// 6 被淘汰  
	//	,					// 7 比赛人数变化  eNumMessage 比赛ID   eMessageParam  现在的人数
	//	,					// 8 比赛拉人  eNumMessage 剩余时间  秒
	//	,					// 9 比赛开始 未进入比赛房间  eNumMessage 比赛ID
	//	,					// 10 人数不足比赛取消   eNumMessage 比赛ID
	//	,					// 11 比赛赛制改变   eNumMessage: 1 打立出局  2 淘汰赛 3 瑞士移位  eMessageParam 第几轮赛制
	//	,					// 12 比赛多少名  eNumMessage 比赛名次
	//	,					// 13 淘汰分数线增长  eNumMessage 比赛ID  eMessageParam 增加后的值
	//	,					// 14 倍率增长  eNumMessage 比赛ID   eMessageParam 增加后的值
	//	,					// 15 比赛轮空  
	//  ,					// 16 离比赛剩余秒数 eNumMessage 剩余秒数 eMessageParam 比赛ID
	//  ,					// 17 打立出局模式还需要等待eNumMessage人开始配比
	//  ,					// 18 通知玩家  共分配了多少桌eNumMessage
	//  ,					// 19 通知玩家  还需要等待多少桌打完eNumMessage

	uint8				eMessageType;	
	uint32				eNumMessage;
	uint32				eMessageParam;

	CGame_STOC_MatchMessage()
	{
		m_opcode = PROTOCOL_TYPE;
		eMessageType = 0;
		eNumMessage = 0;
		eMessageParam = 0;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>eMessageType;
		data>>eNumMessage;
		data>>eMessageParam;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<eMessageType;
		data<<eNumMessage;
		data<<eMessageParam;
	}


};



#endif	//_CGAMESTOMATCHMESSAGE_H