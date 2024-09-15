#include "stdafx.h"
#include "MeteorExploed.h"
#include"BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMeteorExploed::CMeteorExploed()
{
}

CMeteorExploed::~CMeteorExploed()
{
    Release();
}

void CMeteorExploed::Initialize()
{
	m_bImageMove = false;
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 96.f;
	m_tInfo.fX += 80;
	m_tInfo.fY += 96;
	Image_tInfo.fCX = 80.f;
	Image_tInfo.fCY = 96.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySound(L"MeteorExplosion.wav", BOSSMETEOR, 0.2f);
	Motion_Change();
	m_fSpeed = 0.f;
	m_iDamage = 25;
	m_dLifeTick = GetTickCount();
	m_dMotionTick = GetTickCount();
}

int CMeteorExploed::Update()
{
	if (m_bDead)
	{

		CSoundMgr::Get_Instance()->StopSound(BOSSMETEOR);
		return OBJ_DEAD;
	}
	if (!m_bImageMove)
	{
		m_tInfo.fX += 50;
		m_tInfo.fY += 130;
		m_bImageMove = true;
	}

	//m_tInfo.fX += m_fSpeed*cosf(m_fAngle*( PI/180.f ));
	//m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*( PI/180.f ));

	__super::Update_Rect();

	Move_Frame();


	return OBJ_NOEVENT;

}

void CMeteorExploed::Late_Update()
{
	if (GetTickCount()>m_dLifeTick+1000)
	{
		m_bDead = OBJ_DEAD;
	}
}

void CMeteorExploed::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"METEOREFFECT");
	//Rectangle(hDC, m_tRect.left+iScrollX,
	//						m_tRect.top+iScrollY,
	//						m_tRect.right+iScrollX,
	//						m_tRect.bottom+iScrollY);
	GdiTransparentBlt(hDC,
		m_tInfo.fX-80+iScrollX,
		m_tInfo.fY-96+iScrollY,
		160,
		192,
		FireMemDC,
		( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
		( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
		( int ) Image_tInfo.fCX,
		( int ) Image_tInfo.fCY,
		RGB(0, 0, 0));


}

void CMeteorExploed::Release()
{
}

void CMeteorExploed::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}
