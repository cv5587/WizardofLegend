#include "stdafx.h"
#include "Knight.h"
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
#include "Coin.h"


CKnight::CKnight():m_bFreezed(true)
{
}

CKnight::~CKnight()
{
	Release();
}

void CKnight::Initialize()
{
	m_bDie = false;
	m_iHp = 50;
	m_iMaxhp = 50;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Knight/SWORDMAN_ATTACK.png", L"MONSTERSLASH");
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/Knight/SWORDMAN.png", L"KNIGHT");
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	Image_tInfo.fCX = 100.f;
	Image_tInfo.fCY = 100.f;
	m_fDiagonal = 50.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	//CSoundMgr::Get_Instance()->PlaySound(L"WhipHit.wav", HITSOUND, 0.8f);
	m_fSpeed = 3.f;
	m_iDamage = 5;

	m_dAttackTime = GetTickCount();
}

int CKnight::Update()
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
					CObjMgr::Get_Instance()->Add_Object(COIN, CAbstractFactory<CCoin>::Create(m_tInfo.fX-rand()%10,m_tInfo.fY-rand()%20, CObjMgr::Get_Instance()->Get_Player()));
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
					Chasing();
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

void CKnight::Late_Update()
{
	Move_Frame();

	float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollY();
	if (CCollisionMgr::Check_RangeSphere(CObjMgr::Get_Instance()->Get_Player(), this))
	{
		m_bFreezed = false;
	}
	if (m_bFrame_Cycle)
	{
		m_bFrame_Cycle = false;
		m_bSkillCreate = false;
		m_bHit = false;
	}
}

void CKnight::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"KNIGHT");

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
		0+( m_tFrame.iFrameProgress*50 )
		, 0+( m_tFrame.iMotion*50 ),
		50.f, 50.f,
		UnitPixel);


	}
	else
	{

		graphics.DrawImage(img, destinationPoints, 3,
			0+( m_tFrame.iFrameProgress*50 )
			, 0+( m_tFrame.iMotion*50 ),
			50.f, 50.f,
			UnitPixel);

	}

}

void CKnight::Release()
{
}

void CKnight::Motion_Change()
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
				m_tFrame.dwSpeed = 200;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd =5;
				m_tFrame.iMotion = 1;
				m_tFrame.dwTime = GetTickCount();
				break;

		case MONSTERATTACK:	
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
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
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 400;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_eMonsterPreState = m_eMonsterCurState;
		m_ePDirection = m_eCDirection;
	}

}

void CKnight::Check_Angle()
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

void CKnight::Change_Stretch()
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

void CKnight::Check_State()
{
	if (!CCollisionMgr::Check_Sphere(m_pTarget, this))
	{
		m_eMonsterCurState = MONSTERCHASING;
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
		if (GetTickCount()>m_dAttackTime+2000)
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
			if (!m_bFrame_Cycle)
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

	

}
void CKnight::Chasing()
{
	if (m_eMonsterCurState == MONSTERCHASING)
	{
		m_tInfo.fX += m_fSpeed*cosf(m_fAngle*PI/180);
		m_tInfo.fY -= m_fSpeed*sinf(m_fAngle*PI/180);
	}
}
void CKnight::Dead()
{
	if (m_iHp<0)
	{
		m_bDie = true;
		m_bDead = OBJ_DEAD;
		m_eMonsterCurState = MONSTERDEAD;
	}
}

void CKnight::Hit()
{
	if (m_bHit)
	{
		CObjMgr::Get_Instance()->Add_Object(HITEFFECT, CAbstractFactory<CHitEffect>::
		Create(m_tInfo.fX-m_tInfo.fCX*0.5+rand()%20, m_tInfo.fY-m_tInfo.fCY*0.5+rand()%10, m_fAngle));
		m_eMonsterCurState = MONSTERHIT;
		m_bHit = false;
	}

}

void CKnight::Attack()
{

		if (m_eMonsterCurState==MONSTERATTACK)	
		{
			if (m_tFrame.iFrameProgress==1&&!m_bSkillCreate)
			{
				m_bSkillCreate = true;
				CObjMgr::Get_Instance()->Add_Object(MONSTERMAGIC, CAbstractFactory<CMonsterSlash>::Create(m_tPosin.x, m_tPosin.y, m_fAngle, m_bStretch));
				CSoundMgr::Get_Instance()->PlaySound(L"KnightAttack.wav", MONSTER_EFFECT, 0.5f);
				m_dAttackTime = GetTickCount();	
			}

		}
	

}
