#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "PngMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include"SoundMgr.h"
CMainGame::CMainGame() 
	: m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());

	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/HitEffect.bmp", L"HITEFFECT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/TeleportCircles.bmp", L"TELEPORT");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/gui.bmp", L"GUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/skillgui.bmp", L"SKILLGUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BossUI.bmp", L"BOSSGUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/UI_MONEY.bmp", L"UI_MONEY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/MONEY.bmp", L"MONEY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/Font.bmp", L"FONT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Merchant/ITEMSHOP_NPC.bmp", L"ITEMSHOP_NPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Merchant/SHOP_TABLE.bmp", L"SHOP_TABLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Merchant/POTION.bmp", L"POTION");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Merchant/GAIA_ARMOR_CARD.bmp", L"GAIA_ARMOR_CARD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/GAIA_ARMOR.bmp", L"GAIA_ARMOR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SUMMON_CARD_SWORDMAN.bmp", L"SUMMON_CARD_SWORDMAN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SUMMON_CARD_WIZARD.bmp", L"SUMMON_CARD_WIZARD");

	CSoundMgr::Get_Instance()->Initialize();

	if (::AllocConsole()==TRUE)
	{
		FILE* nfp[ 3 ];
		freopen_s(nfp+0, "CONOUT$", "rb", stdin);
		freopen_s(nfp+1, "CONOUT$", "wb", stdout);
		freopen_s(nfp+2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();


}

void CMainGame::Late_Update(void)
{

	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();

}

void CMainGame::Render(void)
{
#pragma region 프레임 출력

	++m_iFPS;

	if (
		+ 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

#pragma endregion 프레임 출력

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	// 윈도우 문자열 출력 함수

	//TCHAR	szBuff[32] = L"";

	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[BULLET].size()); 

	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	
	// wsprintf : winapi 라이브러리에서 제공하는 함수
	// swprintf_s : visual c++ 라이브러리에서 제공하는 함수, 모든 서식 문자를 지원

	//TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	//RECT	rc{ 100, 100, 200, 200 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);


}

void CMainGame::Release(void)
{
	CBmpMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	//CLineMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
