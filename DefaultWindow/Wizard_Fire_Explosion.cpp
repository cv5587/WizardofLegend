#include "stdafx.h"
#include "Wizard_Fire_Explosion.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CWizard_Fire_Explosion::CWizard_Fire_Explosion()
{
}

CWizard_Fire_Explosion::~CWizard_Fire_Explosion()
{
	Release();
}

void CWizard_Fire_Explosion::Initialize()
{
	m_tInfo.fCX = 60;
	m_tInfo.fCY = 50.f;
	Image_tInfo.fCX = 60.f;
	Image_tInfo.fCY = 50.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Wizard/WizardFireExplosion.png", L"WizardFireExplosion");
	CSoundMgr::Get_Instance()->PlaySound(L"FireBlastODEnd.wav", BOSSSOUND_EFFECT, 0.8f);
	Motion_Change();
	m_fSpeed = 0.f;
}

int CWizard_Fire_Explosion::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(BOSSSOUND_EFFECT);
		return OBJ_DEAD;
	}


	Move_Frame();
	Motion_Dead();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWizard_Fire_Explosion::Late_Update()
{

}

void CWizard_Fire_Explosion::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"WizardFireExplosion");

	graphics.DrawImage(img,
									Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
										( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
										Image_tInfo.fCX, Image_tInfo.fCY),
									0+( m_tFrame.iFrameProgress*60 )
									, 0+( m_tFrame.iMotion*50 ),
									60.f, 50.f,
									UnitPixel);
}

void CWizard_Fire_Explosion::Release()
{
}

void CWizard_Fire_Explosion::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 60;
	m_tFrame.dwTime = GetTickCount();
}

void CWizard_Fire_Explosion::Motion_Dead()
{
	if (m_bFrame_Cycle)
	{
		m_bDead = OBJ_DEAD;
	}
}
