#ifndef _CPDKGAMESTOCRECONNECT_H
#define _CPDKGAMESTOCRECONNECT_H

#include "Opcodes.h"
#include "Protocol.h"

class CPDKGame_STOC_Reconnect : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SC_GAMERECONNECT};
	
	bool				isWarnining;
	uint32				PlayerID;					// �������ID
	uint32				PlayerHeadVersion;			// ͷ��汾
	uint32				PlayerGold;					// ����ʱ�ǻ���  ����ʱ���ǽ��
	bool				PlayerSex;			
	std::string			PlayerNick;					// ��������ǳ�
	std::vector<uint8>	CardVec;		

	bool				isWarnining2;
	uint32				PlayerID2;
	uint32				PlayerHeadVersion2;			// ͷ��汾
	uint32				PlayerGold2;					// ����ʱ�ǻ���  ����ʱ���ǽ��
	bool				PlayerSex2;			

	std::string			PlayerNick2;     			// ��������ǳ�
	std::vector<uint8>	CardVec2;		

	bool				isWarnining3;
	uint32				PlayerID3;	
	uint32				PlayerHeadVersion3;			// ͷ��汾
	uint32				PlayerGold3;					// ����ʱ�ǻ���  ����ʱ���ǽ��
	bool				PlayerSex3;			

	std::string			PlayerNick3;     			// ��������ǳ�
	std::vector<uint8>	CardVec3;		

	uint8				leftTime;					// �ֵ�����ʣ��ʱ�� ���룩
	uint8				curIndex;					// �����ֵ�˭index
	uint8				lastIndex;					// ���������index
	std::vector<uint8>	lastCards;					// ������һ����
	
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