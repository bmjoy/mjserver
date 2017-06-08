#ifndef _LOGINDATA_H_
#define _LOGINDATA_H_

// 


class CLoginData : public Singleton<CLoginData>
{
public:
	CLoginData();
	~CLoginData();

private:
	void InitTestData();

};


#endif	//_LOGINDATA_H_