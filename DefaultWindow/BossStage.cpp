#include "stdafx.h"
#include "BossStage.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Mouse.h"
#include "GUI.h"
#include"LineMgr.h"
#include "CollisionMgr.h"
#include "PngMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Boss.h"
#include "Knight.h"
#include "SoundMgr.h"

CBossStage::CBossStage()
{
}

CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize()
{
	//void	Set_ScrollX(float _fX) { m_fScrollX += _fX; }

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Fire.bmp", L"FIREBURN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/MeteorStrike.bmp", L"METEOR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/MiscFireEffects.bmp", L"METEOREFFECT");
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	m_dTick = GetTickCount();
	// 플레이어 추가	
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::BossStageCreate(640.f, 940.f, CObjMgr::Get_Instance()->Get_Mouse()));
	CObjMgr::Get_Instance()->Add_Object(BOSS, CAbstractFactory<CBoss>::Create(640.f, 400.f, CObjMgr::Get_Instance()->Get_Player()));
	CSoundMgr::Get_Instance()->PlayBGM(L"Boss_Piano.wav", 1.f);

	/*for (int i = 0; i < 5; ++i)
	{
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY, 0.f));
	}*/
	CObj* pObj = CAbstractFactory<CGUI>::Create(100.f, 40.f, 0.f);
	pObj->Set_Gui(STATEBAR);
	pObj->Set_FrameKey(L"GUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(100.f, 40.f, 0.f);
	pObj->Set_Gui(HP);
	pObj->Set_FrameKey(L"GUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
	{
		pObj = CAbstractFactory<CGUI>::Create(336.f, 80.f, 0.f);
		pObj->Set_Gui(BOSSSTATEBAR);
		pObj->Set_FrameKey(L"BOSSGUI");
		CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

		pObj = CAbstractFactory<CGUI>::Create(336.f, 80.f, 0.f);
		pObj->Set_Gui(BOSSHP);
		pObj->Set_FrameKey(L"BOSSGUI");
		CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

		pObj = CAbstractFactory<CGUI>::Create(336.f, 60.f, 0.f);
		pObj->Set_Gui(BOSSNAME);
		pObj->Set_FrameKey(L"BOSSGUI");
		CObjMgr::Get_Instance()->Add_Object(GUI, pObj);
	}

	pObj = CAbstractFactory<CGUI>::Create(50.f, 550.f, 0.f);
	pObj->Set_Gui(SKILLSLOT);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(57.f, 557.f, 0.f);
	pObj->Set_Gui(SKILLICON);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(57.f, 518.f, 0.f);
	pObj->Set_Gui(KEYBOARD);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(100.f, 550.f, 0.f);
	pObj->Set_Gui(SKILLSLOT);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(107.f, 557.f, 0.f);
	pObj->Set_Gui(SKILLICON);
	pObj->Set_UIx(1);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(107.f, 518.f, 0.f);
	pObj->Set_Gui(KEYBOARD);
	pObj->Set_UIx(1);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(150.f, 550.f, 0.f);
	pObj->Set_Gui(SKILLSLOT);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(157.f, 557.f, 0.f);
	pObj->Set_Gui(SKILLICON);
	pObj->Set_UIx(2);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(157.f, 518.f, 0.f);
	pObj->Set_Gui(KEYBOARD);
	pObj->Set_UIx(2);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);
	//CLineMgr::Get_Instance()->Initialize();
	//CLineMgr::Get_Instance()->Set_SceneId(SC_STAGE);
	//CLineMgr::Get_Instance()->Load_Line();
	CTileMgr::Get_Instance()->Load_Data();
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

}

void CBossStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CBossStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	if (!CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty()&&!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{

		CCollisionMgr::Collision_BOSSRectTile(CObjMgr::Get_Instance()->Get_Objlist(BOSS).front(), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_SlashRect(CObjMgr::Get_Instance()->Get_Objlist(MAGIC), CObjMgr::Get_Instance()->Get_Objlist(BOSS));
		CCollisionMgr::Collision_RectTile(CObjMgr::Get_Instance()->Get_Player(), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(BOSSMAGIC), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
		CCollisionMgr::Collision_RectEffectTile(CObjMgr::Get_Instance()->Get_Objlist(BOSSMAGIC), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(BOSSMAGIC), CObjMgr::Get_Instance()->Get_Objlist(SHIELD));

			if (GetTickCount()>m_dTick+500)
			{
				CCollisionMgr::Collision_FireRect(CObjMgr::Get_Instance()->Get_Objlist(BACK_BLAST), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
				m_dTick = GetTickCount();
			}

	}



	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK)||CObjMgr::Get_Instance()->Get_Objlist(BOSS).empty())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

}

void CBossStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSSBACKGROUND");

	int		iScrollX = ( int ) CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = ( int ) CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 1280, 1280, hGroundDC, 0, 0, SRCCOPY);
	//BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	

	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CBossStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(BOSS);	
	CObjMgr::Get_Instance()->Delete_ID(BOSSMAGIC);
	CObjMgr::Get_Instance()->Delete_ID(MAGIC);
	CObjMgr::Get_Instance()->Delete_ID(GUI);
	CScrollMgr::Get_Instance()->Destroy_Instance();
}
