#include "ConnectTestStdafx.h"

CRoleData::CRoleData()
:mRoleID(0),
mStrAcc(""),
mStrPass()
{

}

CRoleData::~CRoleData()
{

}


void CRoleData::SetRoleID(int id)
{
	mRoleID = id;
}

void CRoleData::SetAcc(std::string acc)
{
	mStrAcc = acc;
}

void CRoleData::SetPass(std::string pass)
{
	mStrPass = pass;
}