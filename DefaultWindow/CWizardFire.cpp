#include "stdafx.h"
#include "CWizardFire.h"
#include"PngMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Wizard_Fire_Explosion.h"
#include "ObjMgr.h"
#include"AbstractFactory.h"
CWizardFire::CWizardFire()
{
}

CWizardFire::~CWizardFire()
{
    Release();
}

void CWizardFire::Initialize()
{
	m_tInfo.fCX = 45.f;
	m_tInfo.fCY = 45.f;
	Motion_Change();
	m_fSpeed = 3.f;
	m_iDamage = 5;
	m_CheckAngle = false;
	m_dLifeTick = GetTickCount();
	m_dMotionTick = GetTickCount();

}

int CWizardFire::Update()
{
	if (!m_CheckAngle)
	{
		Check_Angle();
		m_CheckAngle = true;
	}

		Image_tInfo.fX = m_tInfo.fX;
		Image_tInfo.fY = m_tInfo.fY;
		if (m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(HITEFFECT, CAbstractFactory<CWizard_Fire_Explosion>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));

			CSoundMgr::Get_Instance()->StopSound(WIZARD_EFFECT);
			return OBJ_DEAD;
		}
		if (GetTickCount()>m_dLifeTick+1000)
		{
			m_tInfo.fX += m_fSpeed*cosf(m_fAngle*( PI/180.f ));
			m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*( PI/180.f ));
		}


	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CWizardFire::Late_Update()
{
}

void CWizardFire::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"WIZARDFIRE");

	Matrix _mt;

	_mt.RotateAt(-m_fAngle+180.f, PointF(m_tInfo.fX+iScrollX, m_tInfo.fY+iScrollY));
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
		0+( m_tFrame.iFrameProgress*90 )
		, 0+( m_tFrame.iMotion*90 ),
		90.f, 90.f,
		UnitPixel);

	}
	else
	{
		//Rectangle(hDC, m_tRect.left+iScrollX,
		//m_tRect.top+iScrollY,
		//m_tRect.right+iScrollX,
		//m_tRect.bottom+iScrollY);
		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*90 )
			, 0+( m_tFrame.iMotion*90 ),
			90.f, 90.f,
			UnitPixel);
	}

}

void CWizardFire::Release()
{
}

void CWizardFire::Check_Angle()
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	float width = m_pTarget->Get_Info().fX-m_tInfo.fX;
	float height = m_pTarget->Get_Info().fY-m_tInfo.fY;

	float distance = sqrtf(width*width+height*height);

	m_fAngle = acosf(width/distance)*180/PI;
	if (height>0.f)
	{
		m_fAngle = 360.f-( m_fAngle );
	}

	//m_fAngle = atanf(( height )/( width ))*180/PI;
	//if (height<0)
	//{
	//	m_fAngle = 360-m_fAngle;
	//	// 0~180 도는 구할 수 있지만, y1 > y2 인 경우.. 즉
	//	// 3사분면 4사분면은 360 - (180~360) 를 해줘서 [0,180]
	//	// 값으로 보정해준다.
	//}


}

void CWizardFire::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

void CWizardFire::Motion_Dead()
{
	if (GetTickCount()>m_dMotionTick+4000)
	{
		m_bDead = OBJ_DEAD;
	}
}
