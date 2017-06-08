#ifndef _CGAME_STOA_ITMECHANGE_H_
#define _CGAME_STOA_ITMECHANGE_H_

#include "Opcodes.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

class CGame_STOA_ItemChange : public Protocol
{
public:
	enum { PROTOCOL_TYPE = MSG_SERVER_ITEMCHANGE};

	uint16		VecSize;
	std::vector<TItemChange> VecItemChange;

	CGame_STOA_ItemChange()
	{
		m_opcode = PROTOCOL_TYPE;
		VecSize = 0;	
		VecItemChange.clear();
	}

	void ReadProtocol(Protocol & data)
	{
		data>>VecSize;

		TItemChange go;
		for (uint8 i = 0;i<VecSize;i++)
		{
			data>>go.itemType;
			data>>go.playerID;
			data>>go.itemID;
			data>>go.itemNum;
			VecItemChange.push_back(go);
		}
	}

	void WriteProtocol(Protocol & data)
	{
		data<<VecSize;

		for (std::vector<TItemChange>::iterator it = VecItemChange.begin();it!=VecItemChange.end();++it)
		{
			TItemChange& go = *it;
			data<<go.itemType;
			data<<go.playerID;
			data<<go.itemID;
			data<<go.itemNum;
		}
	}


};



#endif	//_CGAME_STOA_ITMECHANGE_H_