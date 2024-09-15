#include "stdafx.h"
#include "Shield.h"
#include"BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CShield::CShield()
{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.fX -= 24.f;
	m_tInfo.fY -= 24.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 52.5f;
	Image_tInfo.fCX = 100.f;
	Image_tInfo.fCY = 105.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CSoundMgr::Get_Instance()->PlaySoundLoop(L"EarthCrumble.wav", SKILL_EFFECT, 0.5f);

	m_fSpeed = 0.f;

	m_dLifeTick = GetTickCount();
	m_fDistance = 60.f;
	m_fCheckAngle = m_fAngle;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iMotion = 0;
}

int CShield::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	m_fAngle = (int)m_fAngle%360;

	if (m_fCheckAngle>=360)
	{
		m_fCheckAngle = 0;
	}
	

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{


	m_fAngle += m_fSpeed;
	Motion_Change();
	if (GetTickCount()>m_dLifeTick+10000)
	{
	m_bDead = OBJ_DEAD;
	}
	if (m_fSpeed==0.f)
	{
		m_fSpeed = 3.f;
	}
}

void CShield::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	//Rectangle(hDC,
	//	m_tRect.left+iScrollX,
	//	m_tRect.top+iScrollY,
	//	m_tRect.right+iScrollX,
	//	m_tRect.bottom+iScrollY);



	HDC		FireMemDC = CBmpMgr::Get_Instance()->Find_Img(L"GAIA_ARMOR");

	GdiTransparentBlt(hDC,
		m_tInfo.fX+iScrollX-( int ) m_tInfo.fCX*0.5f,	
		m_tInfo.fY+iScrollY-( int ) m_tInfo.fCY*0.5f,	
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		FireMemDC,
		( int ) Image_tInfo.fCX*m_tFrame.iFrameProgress,//가로줄
		( int ) Image_tInfo.fCY*m_tFrame.iMotion,		//세로줄
		( int ) Image_tInfo.fCX,
		( int ) Image_tInfo.fCY,
		RGB(0, 0, 0));
}

void CShield::Release()
{
}

void CShield::Motion_Change()
{

	if (m_fCheckAngle+30<=m_fAngle)
	{
		m_tFrame.iFrameProgress++;

		m_fCheckAngle = m_fAngle;
		if (m_tFrame.iFrameProgress>m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameProgress = m_tFrame.iFrameStart;
		}
	}


}
