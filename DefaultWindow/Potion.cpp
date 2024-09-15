#include "stdafx.h"
#include "Potion.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include	"TileMgr.h"
#include"Tile.h"
#include "SoundMgr.h"
#include "Teleport.h"

CPotion::CPotion()
{
}

CPotion::~CPotion()
{
}

void CPotion::Initialize()
{
	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 78.f;
	Image_tInfo.fCX = 53.f;
	Image_tInfo.fCY = 78.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	Motion_Change();
	m_fSpeed = 0.f;
	m_iDamage = 0;
	m_fDropDis = 0.f;
	m_iPrice = 3;
	m_bGet = false;
	m_fdistance = 0;
	m_iDamage = -20;
}

int CPotion::Update()
{




	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"HealRegen.wav", ITEM_DROP, 0.5f);
		return OBJ_DEAD;
	}


	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPotion::Late_Update()
{

	if (m_bGet)
	{
		m_bDead = OBJ_DEAD;
	}
}

void CPotion::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"POTION");
	//Rectangle(hDC, m_tRect.left+iScrollX,
	//	m_tRect.top+iScrollY,
	//	m_tRect.right+iScrollX,
	//	m_tRect.bottom+iScrollY);
	GdiTransparentBlt(hDC,
			m_tInfo.fX+iScrollX-( int ) m_tInfo.fCX*0.5f,
			m_tInfo.fY+iScrollY-( int ) 78.f,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			hMemDC,
			( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
			( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
			( int ) Image_tInfo.fCX,
			( int ) Image_tInfo.fCY,
			RGB(0, 0, 0));
}

void CPotion::Release()
{
}

void CPotion::Motion_Change()
{
	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}
