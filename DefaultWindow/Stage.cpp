#include "stdafx.h"
#include "Stage.h"
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
#include "Wizard.h"
#include	"SoundMgr.h"
#include "Potal.h"
#include "Coin.h"
#include "Merchant.h"
#include "ShopTable.h"
#include "Potion.h"
#include "SkillCard.h"
#include "KnightSpawn.h"
CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	m_bPotal = false;
	m_bSpawn01 = false;
	m_bSpawn02 = false;
	// 플레이어 추가	
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create(400.f, 400.f, CObjMgr::Get_Instance()->Get_Mouse()));
	CSoundMgr::Get_Instance()->PlayBGM(L"Fire_Jazz.wav", 1.f);

	//CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::Create(1000.f, 800.f, 0.f));


	

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

	 pObj = CAbstractFactory<CGUI>::Create(400.f, 250.f, 0.f);
	pObj->Set_Gui(CLICK);
	pObj->Set_FrameKey(L"SKILLGUI");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(400.f, 530.f, 0.f);
	pObj->Set_Gui(COINUI);
	pObj->Set_FrameKey(L"UI_MONEY");
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(430.f, 520.f, 0.f);
	pObj->Set_Gui(COINFONTUI10);
	pObj->Set_FrameKey(L"FONT");
	pObj->Set_Coin(dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_MyCoin()*0.1);
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);

	pObj = CAbstractFactory<CGUI>::Create(454.f, 520.f, 0.f);
	pObj->Set_Gui(COINFONTUI1);	
	pObj->Set_FrameKey(L"FONT");	
	pObj->Set_Coin(dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_MyCoin()%10);
	CObjMgr::Get_Instance()->Add_Object(GUI, pObj);	

//CLineMgr::Get_Instance()->Initialize();
//CLineMgr::Get_Instance()->Set_SceneId(SC_STAGE);
//CLineMgr::Get_Instance()->Load_Line();
	CTileMgr::Get_Instance()->Load_Data();
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

}

void CStage::Update()
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX>900.f&&!m_bSpawn01)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::CreateMonster(1000.f, 800.f, 0.f,0));
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::CreateMonster(900.f, 900.f, 0.f,1));
		m_bSpawn01 = true;
	}
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX>1400.f&&!m_bSpawn02)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::CreateMonster(1700.f, 650.f, 0.f, 0));
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::CreateMonster(1600.f, 700.f, 0.f, 0));
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CKnightSpawn>::CreateMonster(1700.f, 600.f, 0.f, 1));
		m_bSpawn02 = true;
	}

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CStage::Late_Update()
{
	if (CObjMgr::Get_Instance()->Get_Objlist(MONSTER).empty()&&!m_bPotal&&m_bSpawn02)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"BallLightningShort.wav", WIZARD_EFFECT, 0.8f);
		CObjMgr::Get_Instance()->Add_Object(POTAL, CAbstractFactory<CPotal>::Create(1600.f, 1000.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(MERCHANT, CAbstractFactory<CMerchant>::Create(1560.f, 460.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(MERCHANT, CAbstractFactory<CShopTable>::Create(1600.f, 570.f, 0.f));
		CObjMgr::Get_Instance()->Add_Object(ITEM, CAbstractFactory<CPotion>::Create(1550.f, 570.f, 0.f));	
		CObjMgr::Get_Instance()->Add_Object(SKILLCARD, CAbstractFactory<CSkillCard>::Create(1650.f, 570.f, 0.f));	
		m_bPotal = true;
	}
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	if (!CObjMgr::Get_Instance()->Get_Objlist(PLAYER).empty())
	{
		CCollisionMgr::Collision_RectTile(CObjMgr::Get_Instance()->Get_Player(), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->Get_Objlist(PLAYER), CObjMgr::Get_Instance()->Get_Objlist(MERCHANT));
		CCollisionMgr::Collision_MonsterRectTile(CObjMgr::Get_Instance()->Get_Objlist(MONSTER), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_SlashRect(CObjMgr::Get_Instance()->Get_Objlist(MONSTERMAGIC), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
		CCollisionMgr::Collision_SlashRect(CObjMgr::Get_Instance()->Get_Objlist(MAGIC), CObjMgr::Get_Instance()->Get_Objlist(MONSTER));
		CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(SHOTMAGIC), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
		CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(SHOTMAGIC), CObjMgr::Get_Instance()->Get_Objlist(SHIELD));
		//CCollisionMgr::Collision_RectEffectTile(CObjMgr::Get_Instance()->Get_Objlist(SHOTMAGIC), CTileMgr::Get_Instance()->Get_Tile());
		CCollisionMgr::Collision_CoinSphere(CObjMgr::Get_Instance()->Get_Objlist(PLAYER), CObjMgr::Get_Instance()->Get_Objlist(COIN));

	}

	//CCollisionMgr::Collision_RectEffectTile(CObjMgr::Get_Instance()->Get_Objlist(MONSTERMAGIC), CTileMgr::Get_Instance()->Get_Tile());

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		if (dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_Click())
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_BOSSSTAGE);
			return;
		}
		if (dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_Buy())	
		{

			if (dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_MyCoin()>=
				CObjMgr::Get_Instance()->Get_Objlist(ITEM).front()->Get_MyCoin())
			{
				dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Set_ChangeCoin( dynamic_cast< CPotion* >( CObjMgr::Get_Instance()->Get_Objlist(ITEM).front() )->Get_Price() );
			CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(ITEM), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
			}

		}
		if (( dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_BuySkill() ))
		{
			if (dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Get_MyCoin()>=CObjMgr::Get_Instance()->Get_Objlist(SKILLCARD).front()->Get_MyCoin())
			{
				dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Set_ChangeCoin(dynamic_cast< CSkillCard* >( CObjMgr::Get_Instance()->Get_Objlist(SKILLCARD).front() )->Get_Price());
				dynamic_cast< CPlayer* >( CObjMgr::Get_Instance()->Get_Player() )->Set_Skill();
				CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->Get_Objlist(SKILLCARD), CObjMgr::Get_Instance()->Get_Objlist(PLAYER));
			}
		}

	}
}

void CStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BACKGROUND");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 2048	, 1339, hGroundDC, 0, 0, SRCCOPY);
	//BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);


	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(BOSS);	
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);	
	CObjMgr::Get_Instance()->Delete_ID(BOSSMAGIC);
	CObjMgr::Get_Instance()->Delete_ID(MAGIC);
	CObjMgr::Get_Instance()->Delete_ID(GUI);	
	CObjMgr::Get_Instance()->Delete_ID(COIN);	
	CScrollMgr::Get_Instance()->Destroy_Instance();	
}
