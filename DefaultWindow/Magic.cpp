#include "stdafx.h"
#include "Magic.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CMagic::CMagic()
{
}

CMagic::~CMagic()
{
	Release();
}

void CMagic::Initialize()
{
	m_tInfo.fCX = 125.f;
	m_tInfo.fCY = 125.f;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Player/Slash.png", L"SLASH");
	Motion_Change();	
	m_fSpeed = 0.f;
	m_iDamage = 15;
}

int CMagic::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		return OBJ_DEAD;
	}


	Move_Frame();	
	Motion_Dead();
	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CMagic::Late_Update()
{
	

}

void CMagic::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"SLASH");

	Point destinationPoints[ ] = {
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY+m_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original
	Matrix _mt;
	_mt.RotateAt(-m_fAngle+90.f, PointF(m_tInfo.fX+iScrollX, m_tInfo.fY+iScrollY));
	graphics.SetTransform(&_mt);

	if (!m_bStretch)
	{
		graphics.DrawImage(img,
		Rect(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY,
			m_tInfo.fCX, m_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*32 )
		, 0+( m_tFrame.iMotion*48 ),
		32.f, 48.f,
		UnitPixel);
		//Rectangle(hDC, m_tRect.left+iScrollX,
		//			m_tRect.top+iScrollY,
		//			m_tRect.right+iScrollX,
		//			m_tRect.bottom+iScrollY);
	}
	else
	{
		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*32 )
			, 0+( m_tFrame.iMotion*48 ),
			32.f, 48.f,
			UnitPixel);
	}

}

void CMagic::Release()
{
}

void CMagic::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 2;
	m_bStretch = false;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
}

void CMagic::Motion_Dead()
{
	if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
}
