#include "stdafx.h"
#include "Dash.h"
#include "PngMgr.h"
#include "ScrollMgr.h"
#include	"SoundMgr.h"

CDash::CDash()
{
}

CDash::~CDash()
{
    Release();
}

void CDash::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 102.f;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Player/Dash.png", L"DASH");
	Motion_Change();
	m_fSpeed = -5.f;
}

int CDash::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		return OBJ_DEAD;
	}
	m_tInfo.fX += m_fSpeed*cos(m_fAngle*PI/180.f);
	m_tInfo.fY -= m_fSpeed*sin(m_fAngle*PI/180.f);
	Move_Frame();
	Motion_Dead();
	return OBJ_NOEVENT;
}

void CDash::Late_Update()
{
}

void CDash::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"DASH");

	Point destinationPoints[ ] = {
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY+m_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original
	Matrix _mt;
	_mt.RotateAt(-m_fAngle, PointF(m_tInfo.fX+iScrollX, m_tInfo.fY+iScrollY));
	graphics.SetTransform(&_mt);

	if (!m_bStretch)
	{
		graphics.DrawImage(img,
		Rect(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY,
			m_tInfo.fCX, m_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*15 )
		, 0+( m_tFrame.iMotion*51 ),
		15.f, 51.f,
		UnitPixel);


	}
	else
	{
		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*15 )
			, 0+( m_tFrame.iMotion*51 ),
			15.f, 51.f,
			UnitPixel);
	}
}

void CDash::Release()
{
}

void CDash::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
}

void CDash::Motion_Dead()
{
	if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
}
