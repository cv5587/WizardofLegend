#include "stdafx.h"
#include "MyEdit.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CTileMgr::Get_Instance()->Initialize();
}

void CMyEdit::Update()
{
	Key_Input();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CMyEdit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSSBACKGROUND");

	int		iScrollX = ( int ) CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = ( int ) CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 1280	, 1280, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release()
{
	CTileMgr::Destroy_Instance();
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollX();
		ptMouse.y -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking(ptMouse, 1, 0, true);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
	{
		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollX();
		ptMouse.y -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking(ptMouse, 2, 0, true);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollX();
		ptMouse.y -= ( int ) CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking(ptMouse, 0, 0, true);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Data();
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		CTileMgr::Get_Instance()->Load_Data();
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

}

