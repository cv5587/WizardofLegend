#pragma once
#include "MyPng.h"
class CPngMgr :
    public CMyPng
{
private :
    CPngMgr();
    ~CPngMgr();

public:
	void		insert_Png(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Release();
	Image*			Find_Img(const TCHAR* pImgKey);

public:
	static	CPngMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CPngMgr;

		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CPngMgr* m_pInstance;

	map<const WCHAR*, CMyPng*>		m_mapPng;

};

