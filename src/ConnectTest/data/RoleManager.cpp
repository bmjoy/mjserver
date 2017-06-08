#include "ConnectTestStdafx.h"

initialiseSingleton(CRoleManager);

CRoleManager::CRoleManager()
{
	SimulateData();
}

CRoleManager::~CRoleManager()
{
	ClearData();
}

CRoleData* CRoleManager::GetRoleInfo(int roleID)
{
	for (std::vector<CRoleData*>::iterator it = roleVec.begin(); it != roleVec.end(); ++it)
	{
		if ((*it)->mRoleID == roleID)
		{
			return (*it);
		}
	}

	return nullptr;
}

bool CRoleManager::CheckLogin(std::string acc, std::string pass)
{
	for (std::vector<CRoleData*>::iterator it = roleVec.begin(); it != roleVec.end(); ++it)
	{
		if (0 == strcmp((*it)->mStrAcc.c_str(), acc.c_str()) && 
			0 == strcmp((*it)->mStrPass.c_str(), pass.c_str()))
		{
			return true;
		}
	}

	return false;
}


void CRoleManager::ClearData()
{
	for (std::vector<CRoleData*>::iterator it = roleVec.begin(); it != roleVec.end(); ++it)
	{
		delete (*it);
	}
	roleVec.clear();
}


void CRoleManager::SimulateData(int num)
{
	char buf[32] = "";
	for (int i = 0; i < num;++i)
	{
		CRoleData* pRole = new CRoleData();
		pRole->SetRoleID(i + 1);
		sprintf(buf, "acc%d", i + 1);
		pRole->SetAcc(buf);
		sprintf(buf, "pass%d", i + 1);
		pRole->SetAcc(buf);
		roleVec.push_back(pRole);
	}
}
