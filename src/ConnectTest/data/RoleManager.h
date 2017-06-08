#ifndef _ROLEMANAGER_H_
#define _ROLEMANAGER_H_

// 

class CRoleManager : public Singleton<CRoleManager>
{
public:
	CRoleManager();
	~CRoleManager();

	CRoleData* GetRoleInfo(int roleID);

	bool CheckLogin(std::string acc, std::string pass);

private:
	void ClearData();
	void SimulateData(int num = 10);
	

	std::vector<CRoleData*> roleVec;
};


#endif	//_ROLEMANAGER_H_