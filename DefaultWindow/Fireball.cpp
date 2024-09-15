#include "stdafx.h"
#include "Fireball.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "FireExploed.h"

CFireball::CFireball()
{
}

CFireball::~CFireball()
{
	Release();
}

void CFireball::Initialize()
{
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;
	Image_tInfo.fCX = 144.f;
	Image_tInfo.fCY = 72.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Fireball.png", L"FIREBALL");
	CSoundMgr::Get_Instance()->StopSound(BOSSSOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySoundLoop(L"FireBLastODLoop.wav", BOSSSOUND_EFFECT, 0.5f);
	Motion_Change();
	m_fSpeed =5.f;
	m_iDamage = 10;
}

int CFireball::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CObjMgr::Get_Instance()->Add_Object(BACK_BLAST, CAbstractFactory<CFireExploed>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed*cosf(m_fAngle*( PI/180.f ));
	m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*( PI/180.f ));

	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CFireball::Late_Update()
{
}

void CFireball::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"FIREBALL");


	Point destinationPoints[ ] = {
   Point(( int ) ( Image_tInfo.fX+Image_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( Image_tInfo.fX+Image_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( Image_tInfo.fY+Image_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original
	Matrix _mt;
	_mt.RotateAt(-m_fAngle, PointF(Image_tInfo.fX+iScrollX, Image_tInfo.fY+iScrollY));
	graphics.SetTransform(&_mt);

	if (!m_bStretch)
	{

		graphics.DrawImage(img,
		Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
			Image_tInfo.fCX, Image_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*96 )
		, 0+( m_tFrame.iMotion*48 ),
		96.f, 48.f,
		UnitPixel);

		//Rectangle(hDC, m_tRect.left+iScrollX,
		//								m_tRect.top+iScrollY,
		//								m_tRect.right+iScrollX,
		//								m_tRect.bottom+iScrollY);


	}
	else
	{
		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*96 )
			, 0+( m_tFrame.iMotion*48 ),
			96.f, 48.f,
			UnitPixel);
		//Rectangle(hDC, m_tRect.left+iScrollX,
		//						m_tRect.top+iScrollY,
		//						m_tRect.right+iScrollX,
		//						m_tRect.bottom+iScrollY);
	}

}

void CFireball::Release()
{
}

void CFireball::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

}

