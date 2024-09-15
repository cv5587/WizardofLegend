#include "stdafx.h"
#include "FireExploed.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CFireExploed::CFireExploed()
{
}

CFireExploed::~CFireExploed()
{
	Release();
}

void CFireExploed::Initialize()
{
	m_tInfo.fCX = 240;
	m_tInfo.fCY = 200.f;
	Image_tInfo.fCX = 180.f;
	Image_tInfo.fCY = 150.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/FireExplosion.png", L"FIREEXPLOSION");
	CSoundMgr::Get_Instance()->StopSound(BOSSSOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"FireBlastODEnd.wav", BOSSSOUND_EFFECT, 0.8f);
	Motion_Change();
	m_fSpeed = 0.f;
}

int CFireExploed::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
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

void CFireExploed::Late_Update()
{
}

void CFireExploed::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"FIREEXPLOSION");

	graphics.DrawImage(img,
									Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
										( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
										Image_tInfo.fCX, Image_tInfo.fCY),
									0+( m_tFrame.iFrameProgress*120 )
									, 0+( m_tFrame.iMotion*100 ),
									120.f, 100.f,
									UnitPixel);
	

}

void CFireExploed::Release()
{
}

void CFireExploed::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 60;
	m_tFrame.dwTime = GetTickCount();
}

void CFireExploed::Motion_Dead()
{
	if (m_bFrame_Cycle )
	{
		m_bDead = OBJ_DEAD;
	}

}
