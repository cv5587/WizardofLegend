#include "stdafx.h"
#include "Teleport.h"
#include "PngMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CTeleport::CTeleport()
{
}

CTeleport::~CTeleport()
{
}

void CTeleport::Initialize()
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 256.f;
	Image_tInfo.fCX = 64.f;
	Image_tInfo.fCY = 256.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	Motion_Change();
	m_fSpeed = 0.f;
}

int CTeleport::Update()
{

	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		return OBJ_DEAD;
	}



	return OBJ_NOEVENT;
}

void CTeleport::Late_Update()
{
	Move_Frame();	
	Motion_Dead();
}

void CTeleport::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"TELEPORT");



	GdiTransparentBlt(hDC,
		m_tInfo.fX-32+iScrollX,
		m_tInfo.fY-200+iScrollY,
		64,
		256,
		FireMemDC,
		( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
		( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
		( int ) Image_tInfo.fCX,
		( int ) Image_tInfo.fCY,
		RGB(0, 0, 0));

}

void CTeleport::Release()
{
}

void CTeleport::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();
}

void CTeleport::Motion_Dead()
{
	if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
}
