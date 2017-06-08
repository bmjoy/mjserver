#ifndef _PROTOCOL_H
#define _PROTOCOL_H


#include "Common.h"
#include "ByteBuffer.h"
#include "StackBuffer.h"

typedef unsigned int Type;

#pragma pack(push, 1)

struct ClientPktHeader
{
	uint16 size;
	uint32 cmd;
};

struct ServerPktHeader
{
	uint16 size;
	uint16 cmd;
};

class ProtoProtocol
{
public:
	const uint8* contents() const { return &_storage[0]; };
	ARCEMU_INLINE size_t size() const { return _storage.size(); };
	__inline uint16 GetCmd() const { return mcmd; }

	void resize(size_t newsize)
	{
		_storage.resize(newsize);
	};

	void setcmd(uint16 cmd)
	{
		mcmd = cmd;
	};

	void append(const uint8* src, size_t cnt)
	{
		if (!cnt) return;

		assert(size() < 10000000);

		if (_storage.size() < cnt)
			_storage.resize(cnt);
		memcpy(&_storage[0], src, cnt);
	}

private:
	uint16 mcmd;
	std::vector<uint8> _storage;
};

#pragma pack(pop)

class SERVER_DECL Protocol : public ByteBuffer
{
public:
	typedef unsigned int Type;

	__inline Protocol() : ByteBuffer(), m_opcode(0) { }
	__inline Protocol(uint16 opcode, size_t res) : ByteBuffer(res), m_opcode(opcode) {}
	__inline Protocol(size_t res) : ByteBuffer(res), m_opcode(0) { }
	__inline Protocol(const Protocol & packet) : ByteBuffer(packet), m_opcode(packet.m_opcode) {}

	//! Clear packet and set opcode all in one mighty blow
	__inline void Initialize(uint16 opcode)
	{
		clear();
		m_opcode = opcode;
	}

	__inline uint16 GetOpcode() const { return m_opcode; }
	__inline void SetOpcode(uint16 opcode) { m_opcode = opcode; }


	virtual void ReadProtocol(Protocol & data){}

	virtual void WriteProtocol(Protocol & data){}

public:
	struct Stub
	{
		Type type;
		virtual Protocol * create() = 0;
	};

	static Protocol * Create(Type type);
	static void AddStub(Stub * stub);
	static void DelStub(Type type);
	static void DelStub(Stub * stub) { DelStub(stub->type); }

	template < typename T >
	struct TStub : public Stub
	{
		TStub() { type = T::PROTOCOL_TYPE; }
		virtual Protocol * create() { return new T(); }
	};
protected:
	uint16 m_opcode;
};






#endif	//_PROTOCOL_H