#ifndef _ROLEDATA_H_
#define _ROLEDATA_H_

// 


class CRoleData 
{
public:
	friend class CRoleManager;

	CRoleData();
	~CRoleData();


	int GetRoleID(){ return mRoleID; }
	

private:
	void SetAcc(std::string acc);
	void SetPass(std::string pass);
	void SetRoleID(int id);

	int mRoleID;
	std::string mStrAcc;
	std::string mStrPass;

};


#endif	//_ROLEDATA_H_