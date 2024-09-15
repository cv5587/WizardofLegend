#include "stdafx.h"
#include "GUI.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Define.h"
#include "Player.h"
#include "ScrollMgr.h"
CGUI::CGUI()
{
}

CGUI::~CGUI()
{
}

void CGUI::Initialize()
{

	if (!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{
		Current_Hp = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	}
	if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
	{
		Current_BossHp = CObjMgr::Get_Instance()->Get_Objlist(BOSS).front()->Get_Hp();
	}
	
		
}

int CGUI::Update()
{
	switch (m_pUI)
	{
	case HP:
		m_tInfo.fCX = 142.f;
		m_tInfo.fCY = 40.f;
		break;
	case STATEBAR:
		m_tInfo.fCX = 142.f;
		m_tInfo.fCY = 40.f;
		break;
	case SKILLSLOT:
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;
		break;
	case KEYBOARD:
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;
		break;
	case SKILLICON:
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;
		break;
	case BOSSHP:
		m_tInfo.fCX = 128.f;
		m_tInfo.fCY = 16.f;
		break;
	case BOSSSTATEBAR:
		m_tInfo.fCX = 128.f;
		m_tInfo.fCY = 16.f;
		break;
	case BOSSNAME:
		m_tInfo.fCX = 128.f;
		m_tInfo.fCY = 16.f;
		break;
	case CLICK:
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;
		break;
	case COINUI:
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;
		break;
	case COINFONTUI1:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 24.f;
		break;
	case COINFONTUI10:
		m_tInfo.fCX = 24.f;
		m_tInfo.fCY = 24.f;
		break;
	case UI_END:
		break;
	default:
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CGUI::Late_Update()
{
	Hp_Check();	
	Coin_Check();
}

void CGUI::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_pUI==HP)
	{
	GdiTransparentBlt(hDC,
	m_tRect.left,
	m_tRect.top,
	( int ) m_tInfo.fCX-Change_Hp,
	( int ) m_tInfo.fCY,
	hMemDC,	
	0,
	m_pUI*( int ) m_tInfo.fCY,
	( int ) m_tInfo.fCX-Change_Hp,
	( int ) m_tInfo.fCY,
	RGB(0, 0, 0));
	}
	else if (m_pUI==CLICK)
	{
		if (dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player())->Get_Click()||
			dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_Buy()||
			dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_BuySkill())
		{

			GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			hMemDC,
			64,
			0*( int ) m_tInfo.fCY,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			RGB(0, 0, 0));
		}
	}
	else if (m_pUI==BOSSHP)
	{
		if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
		{
			GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			( ( int ) m_tInfo.fCX-Change_BossHp )*2,
			( int ) m_tInfo.fCY*2,
			hMemDC,
			0,
			1*( int ) m_tInfo.fCY,
			( int ) m_tInfo.fCX-Change_BossHp,
			( int ) m_tInfo.fCY,
			RGB(0, 0, 0));
		}

	}
	else if (m_pUI==COINUI)
	{
	
			GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			( ( int ) m_tInfo.fCX*0.5 ),
			( int ) m_tInfo.fCY*0.5,
			hMemDC,
			0,
			0*( int ) m_tInfo.fCY,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			RGB(0, 0, 0));
		

	}
	else if (m_pUI==COINFONTUI1)
	{

		GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		( ( int ) m_tInfo.fCX ),
		( int ) m_tInfo.fCY,
		hMemDC,
		(int)( m_iCoin%10 )*( int ) m_tInfo.fCX,
		0*( int ) m_tInfo.fCY,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		RGB(0, 0, 0));


	}
	else if (m_pUI==COINFONTUI10)	
	{

		GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		( ( int ) m_tInfo.fCX ),
		( int ) m_tInfo.fCY,
		hMemDC,
		(int)( m_iCoin*0.1 )*( int ) m_tInfo.fCX,
		0*( int ) m_tInfo.fCY,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		RGB(0, 0, 0));


	}
	else if (m_pUI==BOSSNAME)
	{
		if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
		{
			GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			( ( int ) m_tInfo.fCX )*2,
			( int ) m_tInfo.fCY*2,
			hMemDC,
			0,
			2*( int ) m_tInfo.fCY,
			( int ) m_tInfo.fCX,
			( int ) m_tInfo.fCY,
			RGB(0, 0, 0));
		}
	}
	else if(m_pUI==SKILLSLOT)	
	{
		GdiTransparentBlt(hDC,	
		m_tRect.left,
		m_tRect.top,
		( int ) m_tInfo.fCX+15,
		( int ) m_tInfo.fCY+15,
		hMemDC,
		0,
		0,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		RGB(0, 0, 0));	
	}
	else if (m_pUI==KEYBOARD&&UI_x==0||m_pUI==KEYBOARD&&UI_x==1||m_pUI==KEYBOARD&&UI_x==2
		||m_pUI==SKILLICON&&UI_x==0||m_pUI==SKILLICON&&UI_x==1)
	{
		GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		hMemDC,
		0+( UI_x*32 ),
		0+( m_pUI-2 )*m_tInfo.fCY,
		( int ) m_tInfo.fCX,
		( int ) m_tInfo.fCY,
		RGB(0, 0, 0));

	}
	else 		if (m_pUI==SKILLICON&&UI_x==2&&!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{
		
		if (( dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_Skill() ))
		{
			GdiTransparentBlt(hDC,
									m_tRect.left,
									m_tRect.top,
									( int ) m_tInfo.fCX,
									( int ) m_tInfo.fCY,
									hMemDC,
									64,
									64,
									( int ) m_tInfo.fCX,
									( int ) m_tInfo.fCY,
									RGB(0, 0, 0));
		}
	}
		
	else if(m_pUI==STATEBAR)
	{
		GdiTransparentBlt(hDC,
	m_tRect.left,
	m_tRect.top,
	( int ) m_tInfo.fCX,
	( int ) m_tInfo.fCY,
	hMemDC,
	0,
	m_pUI*( int ) m_tInfo.fCY,
	( int ) m_tInfo.fCX,
	( int ) m_tInfo.fCY,
	RGB(0, 0, 0));
	}
	else if (m_pUI==BOSSSTATEBAR)
	{
		if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
		{
			GdiTransparentBlt(hDC,
									m_tRect.left,
									m_tRect.top,
									( int ) m_tInfo.fCX*2,
									( int ) m_tInfo.fCY*2,
									hMemDC,
									0,
									0*( int ) m_tInfo.fCY,
									( int ) m_tInfo.fCX,
									( int ) m_tInfo.fCY,
									RGB(0, 0, 0));
		}
	}
}

void CGUI::Release()
{
}

void CGUI::Hp_Check()
{
	int new_BossiHp = 0;
	int new_iHp = 0;
	if (!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{
		new_iHp = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	}
	if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
	{
		new_BossiHp = CObjMgr::Get_Instance()->Get_Objlist(BOSS).front()->Get_Hp();
	}

	Change_Hp = Current_Hp-new_iHp;
	Current_Hp = m_iHp;
	Change_BossHp = Current_BossHp-new_BossiHp;
	Current_BossHp = m_iHp;
}

void CGUI::Coin_Check()
{
	if (!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{
		m_iCoin = dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_MyCoin();
	}

}
