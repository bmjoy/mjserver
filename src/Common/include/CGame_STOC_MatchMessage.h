#ifndef _CGAMESTOMATCHMESSAGE_H
#define _CGAMESTOMATCHMESSAGE_H

#include "Opcodes.h"
#include "Protocol.h"

class CGame_STOC_MatchMessage : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_MATCHMESSAGE};

	//  ����״̬
	//  MATCHSTATE_NULL,					// 0
	//	MATCHSTATE_PREPARE,					// 1׼��״̬
	//	MATCHSTATE_SIGNUP,					// 2�ɱ���״̬
	//	MATCHSTATE_MATCH,					// 3�����׶�
	//	MATCHSTATE_OVER,					// 4��������(ָ�˱�������ʱ��ν���)
	//	,					// 5 �������ƽ���  eNumMessage �����Ľ������
	//	,					// 6 ����̭  
	//	,					// 7 ���������仯  eNumMessage ����ID   eMessageParam  ���ڵ�����
	//	,					// 8 ��������  eNumMessage ʣ��ʱ��  ��
	//	,					// 9 ������ʼ δ�����������  eNumMessage ����ID
	//	,					// 10 �����������ȡ��   eNumMessage ����ID
	//	,					// 11 �������Ƹı�   eNumMessage: 1 ��������  2 ��̭�� 3 ��ʿ��λ  eMessageParam �ڼ�������
	//	,					// 12 ����������  eNumMessage ��������
	//	,					// 13 ��̭����������  eNumMessage ����ID  eMessageParam ���Ӻ��ֵ
	//	,					// 14 ��������  eNumMessage ����ID   eMessageParam ���Ӻ��ֵ
	//	,					// 15 �����ֿ�  
	//  ,					// 16 �����ʣ������ eNumMessage ʣ������ eMessageParam ����ID
	//  ,					// 17 ��������ģʽ����Ҫ�ȴ�eNumMessage�˿�ʼ���
	//  ,					// 18 ֪ͨ���  �������˶�����eNumMessage
	//  ,					// 19 ֪ͨ���  ����Ҫ�ȴ�����������eNumMessage

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