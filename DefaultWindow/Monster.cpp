#include "stdafx.h"
#include "Monster.h"
#include "PngMgr.h"
#include "ScrollMgr.h"
CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Monster/FireBoss.png", L"FIREBOSS");

	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 96.f;

	m_fSpeed = 3.f;
	m_pFrameKey = L"FIREBOSS";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_fMoveSpeed = m_fSpeed;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Motion_Change();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	Move_Frame();

}

void CMonster::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();



	//Graphics	g(hDC);

	//Image* imgMarker = CPngMgr::Get_Instance()->Find_Img(L"MARKER");
	//Matrix _matrix;
	//_matrix.RotateAt(-m_fAngle, PointF(m_tInfo.fX+iScrollX, m_tInfo.fY+24.f+iScrollY));
	//g.SetTransform(&_matrix);
	//g.DrawImage(imgMarker,
	//Rect(( int ) ( m_tInfo.fX-48.f )+iScrollX,
	//	( int ) ( m_tInfo.fY-24.f )+iScrollY,
	//	96.f, 96.f),
	//0, 0,
	//48.f, 48.f,
	//UnitPixel);

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"FIREBOSS");

	Point destinationPoints[ ] = {
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),   // destination for upper-left point of original
   Point(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY),  // destination for upper-right point of original
   Point(( int ) ( m_tInfo.fX+m_tInfo.fCX*0.5 )+iScrollX,
			 ( int ) ( m_tInfo.fY+m_tInfo.fCY*0.5 )+iScrollY) };  // destination for lower-left point of original

	if (!m_bStretch)
	{
		graphics.DrawImage(img,
		Rect(( int ) ( m_tInfo.fX-m_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( m_tInfo.fY-m_tInfo.fCY*0.5 )+iScrollY,
			m_tInfo.fCX, m_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*48 )
		, 0+( m_tFrame.iMotion*48 ),
		48.f, 48.f,
		UnitPixel);
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

void CMonster::Release()
{
}

void CMonster::Motion_Change()
{
	if (m_ePreState!=m_eCurState||m_eCDirection!=m_ePDirection)
	{
		switch (m_eCurState)
		{
		case TELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_bStretch = false;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case IDLE:

			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_bStretch = false;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameProgress = 2;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 0;
				m_bStretch = false;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}

		case WALK:
			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 3;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case	BREAK:
			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.iMotion = 4;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameProgress = 3;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameProgress = 3;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 6;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case DASH:
			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 4;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 6;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case ATTACK:
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

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
		m_ePDirection = m_eCDirection;
	}

}
