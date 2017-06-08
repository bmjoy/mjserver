#ifndef _CACCOUNTATOSINFO_H
#define _CACCOUNTATOSINFO_H

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CAccount_ATOS_Info : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_AS_ACCOUNTINFO};

	uint8			account_update_type;	// ��������

	uint32			account_id;				// �˺�ID		= 0 ����յ�ַλ
	std::string		account_name;			// �˺���
	std::string		account_password;		// ����
	std::string		account_PlayerName;		// �ǳ�

	uint64			account_gold;			// ����ֵ
	uint64			account_present;		// ��Ʒȯ
	uint64			account_exp;			// ����
	uint64			account_lost;			// �����
	uint64			account_win;			// Ӯ����

	bool			account_sex;			// �Ա� 0 �� 1Ů

	uint32			account_HeadVersion; 	// ͷ��汾��
	uint8			account_province; 		// ʡ����
	uint8			account_city; 			// �д���
	
	//uint16			account_gameID; 		// ��ϷID
	uint32			account_roomID; 		// ����ID

	bool			account_bindip;			// ��ID 1��ʾ��
	uint8			account_bindpsw;		// 1��ʾ��½ʱ��Ҫ�ֻ���֤�룬2��ʾ��Ҫ������ 0 ��ʾ����Ҫ
	uint8			account_bindpswparam;	// �ֻ���֤�롢���߾�������к�;���ϵ��л�Ϊ������ʱ���ֵ��Ϊ0

	CAccount_ATOS_Info()
	{
		account_update_type = AMUPDATETYPE_All;
		m_opcode = PROTOCOL_TYPE;
	}

	void ReadProtocol(Protocol & data)
	{
		data>>account_update_type;
		data>>account_id;
		data>>account_name;
		data>>account_password;
		data>>account_PlayerName;
		data>>account_gold;

		data>>account_present;
		data>>account_exp;
		data>>account_lost;
		data>>account_win;

		data>>account_sex;			

		data>>account_HeadVersion; 	
		data>>account_province; 	
		data>>account_city; 		

		//data>>account_gameID; 		
		data>>account_roomID; 		

		data>>account_bindip;
		data>>account_bindpsw;
		data>>account_bindpswparam;
	}

	void WriteProtocol(Protocol & data)
	{
		data<<account_update_type;
		data<<account_id;
		data<<account_name;
		data<<account_password;
		data<<account_PlayerName;
		data<<account_gold;
		data<<account_present;
		data<<account_exp;
		data<<account_lost;
		data<<account_win;
		data<<account_sex;			
		data<<account_HeadVersion; 	
		data<<account_province; 	
		data<<account_city; 	
		//data<<account_gameID; 		
		data<<account_roomID; 		

		data<<account_bindip;
		data<<account_bindpsw;
		data<<account_bindpswparam;
	}
};

#endif	//_CACCOUNTATOSINFO_H