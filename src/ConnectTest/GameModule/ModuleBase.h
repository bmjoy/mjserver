#ifndef _MODULEBASE_H
#define _MODULEBASE_H

#include <map>

class ProtoProtocol;
class CSession;


class CModuleBase 
{
public:
	CModuleBase()
	{
		m_mapOpcode.clear();
	}
	virtual ~CModuleBase()
	{
		m_mapOpcode.clear();
	}
	virtual void ProcessProtocol(uint16 Opcode, ProtoProtocol* ptrPacket, CSession * pSession){}
	//virtual void ProcessProtocol(uint16 Opcode, CStreamPtoto* ptrPacket,CSession * pSession){}
	
	virtual void RegisterProtocolIDs() = 0;
	
	bool IsRegisterOpcode(uint16 Opcode)
	{
		std::map<uint16,uint16>::const_iterator it = m_mapOpcode.find(Opcode);
		if (it == m_mapOpcode.end())
		{
			return false;
		}
		return true;
	}

protected:
	void RegisterProtocolID(uint16 Opcode)
	{
		m_mapOpcode[Opcode] = Opcode;
	}

	std::map<uint16,uint16> m_mapOpcode;

private:

};


#endif	//_MODULEBASE_H