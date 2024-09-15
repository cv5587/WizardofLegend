#include "stdafx.h"
#include "Boss.h"
#include "ScrollMgr.h"
#include "PngMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Teleport.h"
#include "Fireball.h"
#include "Fireburn.h"
#include "Meteor.h"
#include "HitEffect.h"
#include "CollisionMgr.h"

//float		g_fVolume(1.f);

CBoss::CBoss() : m_fCheckAngle(0.f)
{
}

CBoss::~CBoss()
{
    Release();
}

void CBoss::Initialize()
{
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/FireBoss.png", L"FIREBOSS");
	m_iHp = 100;
	m_iMaxhp = 100;
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	Image_tInfo.fCX = 96.f;
	Image_tInfo.fCY = 96.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	m_bSpawn = false;
	m_bStretch = false;
	m_bFreezed = false;
	m_bSKILL_USE = false;
	m_bFrame_Cycle = false;
	m_bSkillCreate = false;
	m_bTeleport = false;
	m_bDie = false;
	m_fSpeed = 10.f;
	m_pFrameKey = L"FIREBOSS";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 5;
	m_bStretch = false;
	m_tFrame.dwSpeed = 150;
	m_tFrame.dwTime = GetTickCount();

	CSoundMgr::Get_Instance()->PlaySound(L"IceBossLaugh.wav", BOSSMETEOR,1.f);

	m_fMoveSpeed = m_fSpeed;
}

int CBoss::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	Timer_Update();

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

				return OBJ_DEAD;
			}
			else
			{
				return OBJ_NOEVENT;	
			}
		}
		 Check_Angle();
			 if (!m_bSpawn)
			 {
				 Spawn();
				 m_fFireballTick = m_fPrevTick;
				 m_fFireDashTick = m_fPrevTick;
				 m_fMeteorTick = m_fPrevTick;
				 m_fSpawntime = m_fPrevTick;
			 }
			 else
			 {
				 WarmUp();
					 //여기부터 스킬 사용
				 if (!m_bSKILL_USE)
				 {
					 FireBall();
					 FireDash();
					 Fire_Metor();	
				 }
				 else
				 {
					 Create_Skill();
				 }
				 Chasing();
			 }

			 if (!m_bDie)	
			 {
			 Dead();
			 }
			 Hit();
		Change_Stretch();	
		Motion_Change();
		__super::Update_Rect();
		return OBJ_NOEVENT;
	}

}

void CBoss::Late_Update()
{
	Move_Frame();
		
	//프레임 끝날때까지 딴짓안하깅
	if (m_bFrame_Cycle)
	{
		if (m_eBossCurState ==FIREDASH)
		{
			m_eBossCurState = BOSSBREAK;

		}
		else
		{
			m_eBossCurState = BOSSIDLE;
		}
		m_bSKILL_USE = false;
		m_bFrame_Cycle = false;
		m_bSkillCreate = false;

	}

	//나중에 배치하고나서 거리계산해서 얼리고 풀고 하기.
	if (CCollisionMgr::Check_RangeSphere(CObjMgr::Get_Instance()->Get_Player(), this))
	{
		m_bFreezed = false;
	}


#ifdef _DEBUG

	if (m_dwTime+1000<GetTickCount())
	{
		float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		cout<<"대쉬 각도 : "<<m_fCheckAngle<<endl;
		cout<<"타겟 각도 : "<<m_fAngle<<endl;
		cout<<"보스 좌표 : "<<m_tInfo.fX<<"\t"<<m_tInfo.fY<<endl;
		//cout<<"속도"<<"\t"<<m_fSpeed<<"\t"<< m_fMoveSpeed<<"\t"<<m_fDeltaSpeed<<endl;
		//cout<<"scrollX:"<<"\t"<<iScrollX<<endl;
		//cout<<"scrollY:"<<"\t"<<iScrollY<<endl;
		m_dwTime = GetTickCount();
	}

#endif
}

void CBoss::Render(HDC hDC)
{
	if (!m_bSpawn)
	{
		return;	
	}
	else
	{
		float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
		Graphics	graphics(hDC);
		Image* img = CPngMgr::Get_Instance()->Find_Img(L"FIREBOSS");

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
			0+( m_tFrame.iFrameProgress*48 )
			, 0+( m_tFrame.iMotion*48 ),
			48.f, 48.f,
			UnitPixel);

			//Rectangle(hDC, m_tRect.left+iScrollX,
			//							m_tRect.top+iScrollY,
			//							m_tRect.right+iScrollX,
			//							m_tRect.bottom+iScrollY);
		}
		else
		{
			graphics.DrawImage(img, destinationPoints, 3,
				0+( m_tFrame.iFrameProgress*48 )
				, 0+( m_tFrame.iMotion*48 ),
				48.f, 48.f,
				UnitPixel);
		}
	}
	

}

void CBoss::Release()
{
}

void CBoss::Motion_Change()
{
	if (m_eBossPreState!=m_eBossCurState||m_eCDirection!=m_ePDirection)
	{
		switch (m_eBossCurState)
		{
		case BOSSTELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BOSSIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case FIREBALL:
			m_tFrame.dwSpeed = 1200;
			m_tFrame.dwTime = GetTickCount();
				if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameProgress = 4;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 1;
				break;
			}
				else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd =	1;
				m_tFrame.iMotion = 1;
				break;
			}
				else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 1;
				break;
			}
				else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameProgress = 2;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 1;
				break;
			}
		
		case	FIREDASH:
			m_tFrame.dwSpeed = 400;
			m_tFrame.dwTime = GetTickCount();
			m_dSpawnTime = GetTickCount();

			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameProgress = 4;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 2;
 				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress =0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 2;
 				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 2;
 				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameProgress = 2;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 2;

				break;
			}
		case METEOR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 5;

			m_tFrame.dwSpeed = 2500;
			m_tFrame.dwTime = GetTickCount();
			m_dSpawnTime = GetTickCount();
			break;

		case BOSSHIT:
			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 0;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case BOSSBREAK:

				m_tFrame.iFrameStart = 6;
				m_tFrame.iFrameProgress = 6;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 2;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			

		case BOSSDEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 6;

			m_tFrame.dwSpeed = 600;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WARMUP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_eBossPreState = m_eBossCurState;
		m_ePDirection = m_eCDirection;
	}


}

void CBoss::Spawn()
{

		if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		{
			m_eCDirection = DOWN;
			m_bStretch = false;
			if (!m_bTeleport)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Teleport.wav", BOSSSOUND_EFFECT, 0.5f);
				CObjMgr::Get_Instance()->Add_Object(BOSSMAGIC, CAbstractFactory<CTeleport>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
				m_bTeleport = true;

				m_eBossCurState = BOSSTELEPORT;
				m_bSpawn = true;
			}

		}
		m_fSpawntime = m_fPrevTick;		
	
}

void CBoss::WarmUp()
{
	if (m_eBossCurState == BOSSTELEPORT)	
	{
		if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		{
			m_eBossCurState = WARMUP;
		}
	}
	else 	if (m_eBossCurState==WARMUP)	
	{
		if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		{
			m_eBossCurState = BOSSIDLE;	

		}
	}
}

void CBoss::FireBall()
{

	if (m_fPrevTick>m_fFireballTick+4000)
	{


		if (m_fAngle>=225.f&&m_fAngle<315.f)
		{
			m_eCDirection = DOWN;
			m_eBossCurState = FIREBALL;
		}
		else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
		{
			m_eCDirection = RIGHT;
			m_eBossCurState = FIREBALL;
		}
		else if (m_fAngle>=135.f&&m_fAngle<225.f)
		{
			m_eCDirection = LEFT;
			m_eBossCurState = FIREBALL;
		}
		else if (m_fAngle>=45.f&&m_fAngle<135.f)
		{
			m_eCDirection = UP;
			m_eBossCurState = FIREBALL;
		}
		m_fFireballTick = m_fPrevTick;			
		m_bSKILL_USE = true;

	}
	
	
}

void CBoss::Fire_Metor()
{
	if (m_fPrevTick>m_fMeteorTick+8000)
	{


		if (m_fAngle>=225.f&&m_fAngle<315.f)
		{
			m_eCDirection = DOWN;
			m_eBossCurState = METEOR;
		}
		else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
		{
			m_eCDirection = RIGHT;
			m_eBossCurState = METEOR;
		}
		else if (m_fAngle>=135.f&&m_fAngle<225.f)
		{
			m_eCDirection = LEFT;
			m_eBossCurState = METEOR;
		}
		else if (m_fAngle>=45.f&&m_fAngle<135.f)
		{
			m_eCDirection = UP;
			m_eBossCurState = METEOR;
		}
		m_fMeteorTick = m_fPrevTick;
		m_bSKILL_USE = true;

	}

}

void CBoss::Create_Skill()
{
	if (m_eBossCurState==FIREBALL)
	{
		if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd&&!m_bSkillCreate)
		{
			m_bSkillCreate = true;
			CSoundMgr::Get_Instance()->PlaySound(L"FireBlastODStart.wav", BOSSSOUND_EFFECT, 0.5f);
			CObjMgr::Get_Instance()->Add_Object(BOSSMAGIC, CAbstractFactory<CFireball>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
		}
	}
	if (m_eBossCurState==FIREDASH)
	{		
		m_bSkillCreate = true;
		if (GetTickCount()>m_dSpawnTime+100)
		{
		CObjMgr::Get_Instance()->Add_Object(BACK_BLAST, CAbstractFactory<CFireburn>::Create(m_tInfo.fX+rand()%50, m_tInfo.fY+rand()%50, m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(BACK_BLAST, CAbstractFactory<CFireburn>::Create(m_tInfo.fX-rand()%50, m_tInfo.fY-rand()%50, m_fAngle));
		m_dSpawnTime = GetTickCount();
		}
	}
	if (m_eBossCurState==METEOR)
	{
		m_bSkillCreate = true;
		if (GetTickCount()>m_dSpawnTime+500)
		{
			CObjMgr::Get_Instance()->Add_Object(BOSSMETEORID, CAbstractFactory<CMeteor>::Create(rand()%1280, -( rand()%640 ), m_fAngle));
			m_dSpawnTime = GetTickCount();
		}
	}
}

void CBoss::FireDash()
{
	if (m_fPrevTick>m_fFireDashTick+7000)
	{
		m_fCheckAngle = m_fAngle;	
		if (m_fAngle>=225.f&&m_fAngle<315.f)
		{
			m_eCDirection = DOWN;
			m_eBossCurState = FIREDASH;

		}
		else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
		{
			m_eCDirection = RIGHT;
			m_eBossCurState = FIREDASH;
		}
		else if (m_fAngle>=135.f&&m_fAngle<225.f)
		{
			m_eCDirection = LEFT;
			m_eBossCurState = FIREDASH;
		}
		else if (m_fAngle>=45.f&&m_fAngle<135.f)
		{
			m_eCDirection = UP;
			m_eBossCurState = FIREDASH;
		}

		m_fFireDashTick = m_fPrevTick;
		m_bSKILL_USE = true;

	}


}



void CBoss::Check_Angle()
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
}

void CBoss::Change_Stretch()
{
	if (m_eCDirection==LEFT)
	{
		m_bStretch = true;
	}
	else
	{
		m_bStretch = false;
	}
}

void CBoss::Skill_Frame()
{
	if (m_tFrame.dwSpeed+m_tFrame.dwTime<GetTickCount())	
	{
		//if (m_tFrame.iFrameProgress==m_tFrame.iFrameStart)
		//{
		//	if (m_dSkillTime+1000>GetTickCount())
		//	{

		//	}
		//}
		//else
		//{
		//	//++m_tFrame.iFrameProgress;
		//}
		++m_tFrame.iFrameProgress;
			if (m_tFrame.iFrameProgress>m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameProgress = m_tFrame.iFrameStart;
				m_bFrame_Cycle = true;
			}

			m_tFrame.dwTime = GetTickCount();
		

	}
}

void CBoss::Chasing()
{
	if (m_eBossCurState==FIREDASH)
	{
		//float	testx = m_fSpeed*cosf(m_fCheckAngle*180/PI);
		m_tInfo.fX += m_fSpeed*cosf(m_fCheckAngle*PI/180);
		m_tInfo.fY -= m_fSpeed*sinf(m_fCheckAngle*PI/180);

	}
}

void CBoss::Dead()
{
	if (m_iHp<0)
	{
		m_bDie = true;
		m_bDead = OBJ_DEAD;
		m_eBossCurState = BOSSDEAD;		
	}
}

void CBoss::Hit()
{
	if (m_bHit)
	{
		CObjMgr::Get_Instance()->Add_Object(HITEFFECT, CAbstractFactory<CHitEffect>::
			Create(m_tInfo.fX-m_tInfo.fCX*0.5+rand()%20, m_tInfo.fY-m_tInfo.fCY*0.5+rand()%10, m_fAngle));
		m_bHit = false;	
	}

}
