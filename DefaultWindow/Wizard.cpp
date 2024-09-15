#include "stdafx.h"
#include "Wizard.h"
#include "ScrollMgr.h"
#include "PngMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Teleport.h"
#include "Fireball.h"
#include "Fireburn.h"
#include "Meteor.h"
#include "HitEffect.h"
#include "MonsterSlash.h"
#include "CWizardFire.h"
#include "Coin.h"

CWizard::CWizard() :m_bFreezed(true)
{
}

CWizard::~CWizard()
{
	Release();
}

void CWizard::Initialize()
{
	m_bDie = false;
	m_bSKILL_one = false;
	m_iHp = 50;
	m_iMaxhp = 50;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Wizard/WIZARD_FIRE.png", L"WIZARDFIRE");
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Wizard/WIZARD.png", L"WIZARD");
	m_tInfo.fCX = 85.f;
	m_tInfo.fCY = 120.f;
	Image_tInfo.fCX = 85.f;
	Image_tInfo.fCY = 120.f;
	m_fDiagonal = 50.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	//CSoundMgr::Get_Instance()->PlaySound(L"WhipHit.wav", HITSOUND, 0.8f);
	m_fSpeed = 3.f;
	m_iDamage = 10;

	m_dAttackTime = GetTickCount();
}

int CWizard::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (m_bFreezed)
	{
		return OBJ_NOEVENT;
	}
	else
	{
		if (m_bDead)
		{
			if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
			{
				CObjMgr::Get_Instance()->Add_Object(COIN, CAbstractFactory<CCoin>::Create(m_tInfo.fX-rand()%10, m_tInfo.fY-rand()%20, CObjMgr::Get_Instance()->Get_Player()));
				CObjMgr::Get_Instance()->Add_Object(COIN, CAbstractFactory<CCoin>::Create(m_tInfo.fX+rand()%10, m_tInfo.fY-rand()%20, CObjMgr::Get_Instance()->Get_Player()));

				return OBJ_DEAD;
			}
			else
			{
				return OBJ_NOEVENT;
			}
		}
		else
		{

			Check_Angle();
			Check_State();
			if (!m_bHit)
			{
				Attack();
				if (!m_bDie)
				{
					Dead();
				}

			}

			Hit();
			Change_Stretch();
			Motion_Change();
			__super::Update_Rect();
			return OBJ_NOEVENT;
		}

	}
}

void CWizard::Late_Update()
{
	Move_Frame();

	float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollY();
	if (CCollisionMgr::Check_RangeSphere(CObjMgr::Get_Instance()->Get_Player(),this))
	{
		m_bFreezed = false;
	}
	if (m_bFrame_Cycle)
	{
		m_bFrame_Cycle = false;
		m_bSkillCreate = false;
		m_bSKILL_USE = false;
		m_bHit = false;
		m_bSKILL_one = false;
	}
}

void CWizard::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"WIZARD");

	Point destinationPoints[ ] = {
   Point(( int ) ( Image_tInfo.fX+Image_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( Image_tInfo.fX+Image_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( Image_tInfo.fY+Image_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original

	if (!m_bStretch)
	{

		graphics.DrawImage(img,
		Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
			Image_tInfo.fCX, Image_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*85 )
		, 0+( m_tFrame.iMotion*120 ),
		85.f, 120.f,
		UnitPixel);


	}
	else
	{

		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*85 )
			, 0+( m_tFrame.iMotion*120 ),
			85.f, 120.f,
			UnitPixel);

	}

}

void CWizard::Release()
{
}

void CWizard::Motion_Change()
{
	if (m_eMonsterPreState!=m_eMonsterCurState||m_eCDirection!=m_ePDirection)
	{
		switch (m_eMonsterCurState)
		{

		case MONSTERIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;


		case	MONSTERCHASING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTERATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 400;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTERHIT:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTERDEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 400;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_eMonsterPreState = m_eMonsterCurState;
		m_ePDirection = m_eCDirection;
	}

}

void CWizard::Check_Angle()
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
	m_tPosin.x = LONG(Image_tInfo.fX+m_fDiagonal*cosf(m_fAngle*( PI/180.f )));
	m_tPosin.y = LONG(Image_tInfo.fY-m_fDiagonal*sinf(m_fAngle*( PI/180.f )));
	//m_fAngle = atanf(( height )/( width ))*180/PI;
	//if (height<0)
	//{
	//	m_fAngle = 360-m_fAngle;
	//	// 0~180 도는 구할 수 있지만, y1 > y2 인 경우.. 즉
	//	// 3사분면 4사분면은 360 - (180~360) 를 해줘서 [0,180]
	//	// 값으로 보정해준다.
	//}


}

void CWizard::Change_Stretch()
{
	if (m_eCDirection==LEFT)
	{
		m_bStretch = false;
	}
	else
	{
		m_bStretch = true;
	}
}

void CWizard::Check_State()
{
	if (GetTickCount()>m_dAttackTime+3000)
	{
		m_eMonsterCurState = MONSTERATTACK;

		if (m_fAngle>=0.f&&m_fAngle<90.f||m_fAngle>=270.f&&m_fAngle<360.f)
		{
			m_eCDirection = RIGHT;
		}
		else
		{
			m_eCDirection = LEFT;
		}
	}
	else
	{
		if (!m_bSKILL_USE)
		{
			m_eMonsterCurState = MONSTERIDLE;

			if (m_fAngle>=0.f&&m_fAngle<90.f||m_fAngle>=270.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
			}
			else
			{
				m_eCDirection = LEFT;
			}
		}

	}
}

void CWizard::Dead()
{
	if (m_iHp<0)
	{
		m_bDie = true;
		m_bDead = OBJ_DEAD;
		m_eMonsterCurState = MONSTERDEAD;
	}
}

void CWizard::Hit()
{
	if (m_bHit)
	{
		CObjMgr::Get_Instance()->Add_Object(HITEFFECT, CAbstractFactory<CHitEffect>::
		Create(m_tInfo.fX-m_tInfo.fCX*0.5+rand()%20, m_tInfo.fY-m_tInfo.fCY*0.5+rand()%10, m_fAngle));
		m_eMonsterCurState = MONSTERHIT;
		m_bHit = false;
	}

}

void CWizard::Attack()
{
	if (m_eMonsterCurState==MONSTERATTACK)
	{
		if (m_tFrame.iFrameProgress==1&&!m_bSkillCreate)
		{
			if (!m_bSKILL_one)
			{
				CObjMgr::Get_Instance()->Add_Object(SHOTMAGIC, CAbstractFactory<CWizardFire>::Create(m_tInfo.fX-50.f, m_tInfo.fY, CObjMgr::Get_Instance()->Get_Player()));
				CObjMgr::Get_Instance()->Add_Object(SHOTMAGIC, CAbstractFactory<CWizardFire>::Create(m_tInfo.fX, m_tInfo.fY-50.f, CObjMgr::Get_Instance()->Get_Player()));
				CSoundMgr::Get_Instance()->PlaySoundLoop(L"FlameTrapIdle.wav", WIZARD_EFFECT, 0.5f);
				m_bSKILL_one = true;
			}

		}
		else if (m_tFrame.iFrameProgress==2&&!m_bSkillCreate)
		{
			CObjMgr::Get_Instance()->Add_Object(SHOTMAGIC, CAbstractFactory<CWizardFire>::Create(m_tInfo.fX+50.f, m_tInfo.fY, CObjMgr::Get_Instance()->Get_Player()));
			CObjMgr::Get_Instance()->Add_Object(SHOTMAGIC, CAbstractFactory<CWizardFire>::Create(m_tInfo.fX, m_tInfo.fY+50.f, CObjMgr::Get_Instance()->Get_Player()));
			m_bSkillCreate = true;
			m_dAttackTime = GetTickCount();
		}
	}


}
