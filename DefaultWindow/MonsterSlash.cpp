#include "stdafx.h"
#include "MonsterSlash.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CMonsterSlash::CMonsterSlash()
{
}

CMonsterSlash::~CMonsterSlash()
{
    Release();
}

void CMonsterSlash::Initialize()
{
		m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	Motion_Change();
	m_fSpeed = 1.f;
	m_iDamage = 2;
	m_CheckAngle = false;

}

int CMonsterSlash::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
		return OBJ_DEAD;
	}
	if (!m_CheckAngle)
	{
		if (m_fAngle>0&&m_fAngle<=180)
		{
			m_fAngle -= 90.f;
		}
		else
		{
			m_fAngle += 90.f;
		}
		m_CheckAngle = true;
	}

	Move_Frame();
	Motion_Dead();
	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CMonsterSlash::Late_Update()
{
}

void CMonsterSlash::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"MONSTERSLASH");

	Matrix _mt;

	_mt.RotateAt(m_fAngle, PointF(m_tInfo.fX+iScrollX, m_tInfo.fY+iScrollY));
	graphics.SetTransform(&_mt);

	Point destinationPoints[ ] = {
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY+m_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original


	if (!m_bStretch)
	{
		//Rectangle(hDC, m_tRect.left+iScrollX,
		//m_tRect.top+iScrollY,
		//m_tRect.right+iScrollX,
		//m_tRect.bottom+iScrollY);
		graphics.DrawImage(img,
		Rect(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY,
			m_tInfo.fCX, m_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*200 )
		, 0+( m_tFrame.iMotion*200 ),
		200.f, 200.f,
		UnitPixel);

	}
	else
	{
		//Rectangle(hDC, m_tRect.left+iScrollX,
		//m_tRect.top+iScrollY,
		//m_tRect.right+iScrollX,
		//m_tRect.bottom+iScrollY);
		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*200 )
			, 0+( m_tFrame.iMotion*200 ),
			200.f, 200.f,
			UnitPixel);
	}

}

void CMonsterSlash::Release()
{
}

void CMonsterSlash::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}
void CMonsterSlash::Motion_Dead()
{
	if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
}