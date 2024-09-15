#include "stdafx.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include	"TileMgr.h"
#include"Tile.h"
#include "SoundMgr.h"
#include "Teleport.h"
CCoin::CCoin()
{
}

CCoin::~CCoin()
{
}

void CCoin::Initialize()
{

	m_tInfo.fCX = 12.f;
	m_tInfo.fCY = 12.f;
	Image_tInfo.fCX = 24.f;
	Image_tInfo.fCY = 24.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySound(L"DropItem.wav", ITEM_DROP, 0.5f);
	Motion_Change();
	m_fSpeed = 4.f;
	m_iDamage = 0;
	m_fDropDis = 0.f;
	m_tFrame.iMotion = rand()%3;
	m_iPrice = 0;
	m_bGet = false;
	m_fdistance = 0;
}

int CCoin::Update()
{
	if (m_iPrice==0)
	{
		m_iPrice = m_tFrame.iMotion+1;
	}
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;


	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", ITEM_DROP, 0.5f);
		return OBJ_DEAD;
	}
	Drop();

	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CCoin::Late_Update()
{
	if (m_bGet)
	{
		float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		float width = m_pTarget->Get_Info().fX-m_tInfo.fX;
		float height = m_pTarget->Get_Info().fY-m_tInfo.fY;

		 m_fdistance = sqrtf(width*width+height*height);

		m_fAngle = acosf(width/m_fdistance)*180/PI;
		if (height>0.f)
		{
			m_fAngle = 360.f-( m_fAngle );
		}
		m_tInfo.fX += m_fSpeed*cosf(m_fAngle*PI/180);
		m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*PI/180);
		if (m_fdistance<3.f)
		{
			m_bDead = OBJ_DEAD;
		}
	}

}

void CCoin::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"MONEY");

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

void CCoin::Release()
{
}
void CCoin::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 1;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

void CCoin::Drop()
{
	if (m_fDropDis<30.f)
	{
		m_tInfo.fY += m_fSpeed;
		m_fDropDis += m_fSpeed;
	}
}
