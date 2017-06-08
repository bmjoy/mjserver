#include "Protocol.h"

typedef std::map<Protocol::Type, Protocol::Stub *> StubMap;

StubMap & stubMap() { static StubMap stubs; return stubs; }

void Protocol::AddStub(Stub * stub)
{
	if (!stubMap().insert(std::make_pair(stub->type, stub)).second)
		abort();
}

void Protocol::DelStub(Type type)
{
	stubMap().erase(type);
}

Protocol * Protocol::Create(Type type)
{
	StubMap::iterator it = stubMap().find(type);
	if (it != stubMap().end())
		return it->second->create();
	return NULL;
}