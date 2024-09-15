#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	//0보다 작을때X
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	//0보다 작을때 Y
	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;
	if (CSceneMgr::Get_Instance()->Get_ScenceID()==SC_STAGE)
	{
		if (WINCX-TILECX*TILEX>m_fScrollX)
			m_fScrollX = float(WINCX-TILECX*TILEX);

		if (WINCY-TILECY*TILEY>m_fScrollY)
			m_fScrollY = float(WINCY-TILECY*TILEY);
	}
	else if (CSceneMgr::Get_Instance()->Get_ScenceID()==SC_BOSSSTAGE)
	{
		if (WINCX-TILECX*BOSSTILEX>m_fScrollX)
			m_fScrollX = float(WINCX-TILECX*BOSSTILEX);

		if (WINCY-TILECY*BOSSTILEY>m_fScrollY)
			m_fScrollY = float(WINCY-TILECY*BOSSTILEY);
	}
	//최대 타일 크기 보다 작을때


}
