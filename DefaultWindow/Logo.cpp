#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "PngMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	//CObj* pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f,0.f);

}

void CLogo::Update()
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Background0.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/TitleLogo.bmp", L"pTitle");

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

}

void CLogo::Late_Update()
{
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");	
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	HDC		TitleMemDC = CBmpMgr::Get_Instance()->Find_Img(L"pTitle");	
	GdiTransparentBlt(hDC,	
	0,
	100,
	800,
	450,
	TitleMemDC,
	0,
	0,
	800,
	450,
	RGB(0, 0, 0));	

}

void CLogo::Release()
{
}
