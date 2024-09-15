#include "stdafx.h"
#include "KnightSpawn.h"
#include"BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Knight.h"
#include "Wizard.h"

CKnightSpawn::CKnightSpawn()
{
}

CKnightSpawn::~CKnightSpawn()
{
    Release();
}

void CKnightSpawn::Initialize()
{
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 115.f;
	Image_tInfo.fCX = 150.f;
	Image_tInfo.fCY = 230.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySound(L"CardSpawn.wav", MONSTER_SPAWN, 0.8f);
	Motion_Change();
	m_fSpeed = 0.f;

	m_dLifeTick = GetTickCount();
}

int CKnightSpawn::Update()
{
	if (m_bDead)
	{
		if (m_iMonsterID==0)
		{
			CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnight>::Create(m_tInfo.fX, m_tInfo.fY, CObjMgr::Get_Instance()->Get_Player()));

		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CWizard>::Create(m_tInfo.fX, m_tInfo.fY, CObjMgr::Get_Instance()->Get_Player()));

		}
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	Move_Frame();


	return OBJ_NOEVENT;
}

void CKnightSpawn::Late_Update()
{
	if (m_tFrame.iFrameProgress==30)
	{
		m_bDead = OBJ_DEAD;
	}
}

void CKnightSpawn::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		FireMemDC = {};
	if (m_iMonsterID==0)
	{
				FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"SUMMON_CARD_SWORDMAN");

	}
	else
	{
				FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"SUMMON_CARD_WIZARD");
	}

	GdiTransparentBlt(hDC,
		m_tInfo.fX+iScrollX-m_tInfo.fCX*0.5,
		m_tInfo.fY+iScrollY-m_tInfo.fCY*0.5,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		FireMemDC,
		( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
		( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
		( int ) Image_tInfo.fCX,
		( int ) Image_tInfo.fCY,
		RGB(0, 0, 0));

}

void CKnightSpawn::Release()
{
}

void CKnightSpawn::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 31;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}
