#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_pTarget(nullptr), m_bHit(false), m_bGetShield(false)
, m_pFrameKey(nullptr), m_fLifeTick(0), m_eCurState(IDLE), m_ePreState(PS_END), m_iDamage(0), m_iHp(100),m_iMaxhp(100)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame()
{

	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iFrameProgress;

		if (m_tFrame.iFrameProgress>m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameProgress = m_tFrame.iFrameStart;
			m_bFrame_Cycle = true;
		}

		m_tFrame.dwTime = GetTickCount();
	}

}

void CObj::Timer_Update()
{
	UINT64 fCurTick = ::GetTickCount64();
	m_fDeltaTick = ( fCurTick-m_fPrevTick )*0.001f;
	m_fPrevTick = fCurTick;

}
