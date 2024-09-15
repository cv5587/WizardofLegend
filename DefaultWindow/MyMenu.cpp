#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Background1.bmp", L"BlackLogo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/TitleLogo.bmp", L"pTitle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Stage_fire.bmp", L"BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Stage_fireBoss.bmp", L"BOSSBACKGROUND");
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);


	CSoundMgr::Get_Instance()->PlayBGM(L"Earth_Jazz.wav", 1.f);
	CObj*	pObj = CAbstractFactory<CMyButton>::Create(400.f, 300.f,0.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 375.f,0.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 450.f,0.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);


}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BlackLogo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	HDC		TitleMemDC = CBmpMgr::Get_Instance()->Find_Img(L"pTitle");
	GdiTransparentBlt(hDC,
	0,
	-50,
	800,
	450,
	TitleMemDC,
	0,
	0,
	800,
	450,
	RGB(0, 0, 0));
	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
}
