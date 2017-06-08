#ifndef _CFRIDENSTOCREQUEST_H
#define _CFRIDENSTOCREQUEST_H

#include "Opcodes.h"
#include "Protocol.h"

class CPlayerData;

class CFriend_STOC_Request : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_FRIENDREQUEST};

	uint8  msgType;     //����Ϣ����
	uint32 playID;	    //���

	uint32			friend_id;				// �˺�ID		= 0 ����յ�ַλ
	std::string		friend_PlayerName;		// �ǳ�
	bool			friend_online;		    //����Ƿ�����
	uint64			friend_gold;			// ����ֵ
	uint64			friend_exp;				// ����
	uint64			friend_lost;			// �����
	uint64			friend_win;				// Ӯ����

	bool			friend_sex;				// �Ա� 0 �� 1Ů

	uint32			friend_HeadVersion; 	// ͷ��汾��
	uint8			friend_province; 		// ʡ����
	uint8			friend_city; 			// �д���

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