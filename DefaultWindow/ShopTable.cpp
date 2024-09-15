#include "stdafx.h"
#include "ShopTable.h"
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

CShopTable::CShopTable()
{
}

CShopTable::~CShopTable()
{
}

void CShopTable::Initialize()
{
	m_tInfo.fCX = 202.f;
	m_tInfo.fCY = 98.f;
	Image_tInfo.fCX = 202.f;
	Image_tInfo.fCY = 78.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;

	Motion_Change();
	m_fSpeed = 0.f;
	m_iDamage = 0;
}

int CShopTable::Update()
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

void CShopTable::Late_Update()
{
}

void CShopTable::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"SHOP_TABLE");
	//Rectangle(hDC, m_tRect.left+iScrollX,
	//	m_tRect.top+iScrollY,
	//	m_tRect.right+iScrollX,
	//	m_tRect.bottom+iScrollY);
	GdiTransparentBlt(hDC,
			m_tInfo.fX+iScrollX-( int ) m_tInfo.fCX*0.5f,
			m_tInfo.fY+iScrollY-( int ) m_tInfo.fCY*0.5f,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			hMemDC,
			( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
			( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
			( int ) Image_tInfo.fCX,
			( int ) Image_tInfo.fCY,
			RGB(0, 0, 0));
}

void CShopTable::Release()
{
}

void CShopTable::Motion_Change()
{
}
