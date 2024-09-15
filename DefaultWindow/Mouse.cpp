#include "stdafx.h"
#include "Mouse.h"
#include "PngMgr.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Cursor/MouseCursor0.png", L"MOUSE");
	m_pFrameKey = L"MOUSE";

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	ShowCursor(false);

}

void CMouse::Render(HDC hDC)
{

	Graphics	graphics(hDC);
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"MOUSE");
	graphics.DrawImage(img,
		Rect((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) ,
			(int)(m_tInfo.fY - m_tInfo.fCY * 0.5) ,
			m_tInfo.fCX, m_tInfo.fCY),
		0 , 0 ,
		32.f, 32.f,
		UnitPixel);

}

void CMouse::Release()
{
}
