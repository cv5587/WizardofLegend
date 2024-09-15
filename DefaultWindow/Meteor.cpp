#include "stdafx.h"
#include "Meteor.h"
#include"BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MeteorExploed.h"

CMeteor::CMeteor()
{
}

CMeteor::~CMeteor()
{
	Release();
}

void CMeteor::Initialize()
{
	m_bCreate = false;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 256.f;
	Image_tInfo.fCX = 25.f;
	Image_tInfo.fCY = 64.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySoundLoop(L"MeteorLoop.wav", BOSSMETEOR, 0.3f);
	Motion_Change();
	m_fSpeed = 10.f;
	m_iDamage = 0;
	m_dLifeTick = GetTickCount();
	m_dMotionTick = GetTickCount();

}

int CMeteor::Update()
{
	//Timer_Update();

	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(BOSSMETEOR);
		return OBJ_DEAD;
	}

	//m_tInfo.fX += m_fSpeed*cosf(m_fAngle*( PI/180.f ));
	//m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*( PI/180.f ));
	if (GetTickCount()<m_dMotionTick+1400)
	{
		m_tInfo.fY += m_fSpeed;
	}
	if (m_tFrame.iFrameProgress==8&&!m_bCreate)
	{
	CObjMgr::Get_Instance()->Add_Object(BACK_BLAST, CAbstractFactory<CMeteorExploed>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
	m_bCreate = true;
	}


	__super::Update_Rect();

	Move_Frame();


	return OBJ_NOEVENT;

}

void CMeteor::Late_Update()
{
	if (GetTickCount()>m_dLifeTick+2200)
	{
		m_bDead = OBJ_DEAD;
	}
}

void CMeteor::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"METEOR");

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

void CMeteor::Release()
{
}

void CMeteor::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iMotion = 1;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}
