#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void			Initialize(void);
	void			Render(HDC hDC);
	void			Update();
	void			Release();

	bool			Collision_Line(float* pHeight, float& _fX);
	bool			Collision_Line(float* pHeight, float& _fX, int _HOffset);
	bool			Collision_Line(float* pPrevHeight, float* pCurHeight, float& _fX, int _HOffset);
	void			Load_Line();

public:
	void  Set_SceneId(SCENEID _eID) { m_eSceneId = _eID; }

public:
	static	CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

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
	list<CLine*>		m_LineList;
	static CLineMgr* m_pInstance;
	SCENEID				m_eSceneId;


private:
	float				m_fPrevX;
	float				m_fPrevX2;

	float				m_fMapMaxX;
	float				m_fMapMaxX2;
};

