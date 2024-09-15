#include "stdafx.h"
#include "Fireburn.h"
#include"BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CFireburn::CFireburn()
{
}

CFireburn::~CFireburn()
{
	Release();
}

void CFireburn::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	Image_tInfo.fCX = 16.f;
	Image_tInfo.fCY = 16.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySoundLoop(L"FireBurn.wav", BOSSSOUND_EFFECTLOOP, 0.5f);
	Motion_Change();
	m_fSpeed =0.f;
	m_iDamage = 5;
	m_dLifeTick = GetTickCount();
}

int CFireburn::Update()
{
	//Timer_Update();

	if (m_bDead)
	{
		//CSoundMgr::Get_Instance()->StopSound(BOSSSOUND_EFFECTLOOP);
		return OBJ_DEAD;
	}

	//m_tInfo.fX += m_fSpeed*cosf(m_fAngle*( PI/180.f ));
	//m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*( PI/180.f ));
	__super::Update_Rect();

	Move_Frame();


	return OBJ_NOEVENT;

}

void CFireburn::Late_Update()
{
//	m_fLifeTick += m_fDeltaTick;
	if (GetTickCount()>m_dLifeTick+3000)
	{
		m_bDead = OBJ_DEAD;		
	}
}

void CFireburn::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"FIREBURN");

	GdiTransparentBlt(hDC,
		m_tInfo.fX+iScrollX,
		m_tInfo.fY+iScrollY,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		FireMemDC,
		( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
		( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
		( int ) Image_tInfo.fCX,
		( int ) Image_tInfo.fCY,
		RGB(0, 0, 0));

}

void CFireburn::Release()
{
}

void CFireburn::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}
