#ifndef _CGAME_STOA_GAMEOVER_H_
#define _CGAME_STOA_GAMEOVER_H_

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CGame_STOA_GameOver : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SERVER_GAMEOVER};

	uint8		PlayerNum;
	uint32		GameID;			// ”Œœ∑ID
	std::vector<TGameOver> VecGameOverInfo;
		
	CGame_STOA_GameOver()
	{
		m_opcode = PROTOCOL_TYPE;
		PlayerNum = 0;
		GameID = 0;
		VecGameOverInfo.clear();
	}

	void ReadProtocol(Protocol & data)
	{
		data>>PlayerNum;
		data>>GameID;
		
		TGameOver go;
		for (uint8 i = 0;i<PlayerNum;i++)
		{
			data>>go.isEscape;
			data>>go.PlayerID;
			data>>go.GameResult;
			data>>go.MoneyChange;
			data>>go.ExpAdd;
			VecGameOverInfo.push_back(go);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<PlayerNum;
		data<<GameID;

		for (std::vector<TGameOver>::iterator it = VecGameOverInfo.begin();it!=VecGameOverInfo.end();++it)
		{
			TGameOver& go = *it;
			data<<go.isEscape;
			data<<go.PlayerID;
			data<<go.GameResult;
			data<<go.MoneyChange;
			data<<go.ExpAdd;
		}
	}


};



#endif	//_CGAME_STOA_GAMEOVER_H_