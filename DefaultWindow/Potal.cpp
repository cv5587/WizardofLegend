#include "stdafx.h"
#include "Potal.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include	"TileMgr.h"
#include"Tile.h"
#include	"PngMgr.h"
#include "SoundMgr.h"
#include "Teleport.h"
CPotal::CPotal()
{
}

CPotal::~CPotal()
{
}

void CPotal::Initialize()
{
	m_bTeleport = false;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 120.f;
	Image_tInfo.fCX = 100.f;
	Image_tInfo.fCY = 120.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Potal/Potal.png", L"POTAL");
	CSoundMgr::Get_Instance()->PlaySound(L"BallLightningLoop.wav", MONSTER_EFFECT, 0.8f);

	Motion_Change();
	m_fSpeed = 0.f;
	m_iDamage = 0;
}

int CPotal::Update()
{
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (!m_bTeleport)
	{
		CObjMgr::Get_Instance()->Add_Object(BOSSMAGIC, CAbstractFactory<CTeleport>::Create(m_tInfo.fX, m_tInfo.fY,  0.f));
		m_bTeleport = true;
	}

	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		return OBJ_DEAD;
	}


	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CPotal::Late_Update()
{
}

void CPotal::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	//ºñ¼®
	Graphics	graphics(hDC);
	Image* img01 = CPngMgr::Get_Instance()->Find_Img(L"POTAL");
	graphics.DrawImage(img01,
		Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
			Image_tInfo.fCX, Image_tInfo.fCY),
		100,
		0,
		50.f, 60.f,
		UnitPixel);
	//ºû
	Image* img02 = CPngMgr::Get_Instance()->Find_Img(L"POTAL");
	graphics.DrawImage(img02,
		Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
			Image_tInfo.fCX, Image_tInfo.fCY),
		150,
		0,
		50.f, 60.f,
		UnitPixel);
	//ÀÌÆåÆ®

	Image* img = CPngMgr::Get_Instance()->Find_Img(L"POTAL");
	graphics.DrawImage(img,
		Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
			( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
			Image_tInfo.fCX, Image_tInfo.fCY),
		0+( m_tFrame.iFrameProgress*50 )
		, 0+( m_tFrame.iMotion*60 ),
		50.f, 60.f,
		UnitPixel);


		//Rectangle(hDC, m_tRect.left+iScrollX,
		//								m_tRect.top+iScrollY,
		//								m_tRect.right+iScrollX,
		//								m_tRect.bottom+iScrollY);




}

void CPotal::Release()
{
}
void CPotal::Motion_Change()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_bStretch = false;
	m_tFrame.dwSpeed = 400;
	m_tFrame.dwTime = GetTickCount();
}
