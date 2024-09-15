#include "stdafx.h"
#include "Merchant.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include	"TileMgr.h"
#include"Tile.h"
#include	"PngMgr.h"
#include "SoundMgr.h"
#include "Teleport.h"

CMerchant::CMerchant()
{
}

CMerchant::~CMerchant()
{
}

void CMerchant::Initialize()
{
	m_bTeleport = false;
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 99.f;
	Image_tInfo.fCX = 128.f;
	Image_tInfo.fCY = 197.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;

	Motion_Change();
	m_fSpeed = 0.f;
	m_iDamage = 0;
}

int CMerchant::Update()
{

	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;


	if (m_bDead)
	{
		return OBJ_DEAD;
	}



	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CMerchant::Late_Update()
{
}

void CMerchant::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"ITEMSHOP_NPC");

	GdiTransparentBlt(hDC,
			m_tInfo.fX+iScrollX,
			m_tInfo.fY+iScrollY,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			hMemDC,
			( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
			( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
			( int ) Image_tInfo.fCX,
			( int ) Image_tInfo.fCY,
			RGB(0, 0, 0));
}

void CMerchant::Release()
{
}

void CMerchant::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}
