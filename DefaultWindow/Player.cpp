#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include	"TileMgr.h"
#include"Tile.h"
#include	"PngMgr.h"
#include	"Magic.h"
#include "SoundMgr.h"
#include "Dash.h"
#include "HitEffect.h"
#include "Teleport.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "GUI.h"
#include "Shield.h"
float		g_fVolume(1.f);

CPlayer::CPlayer()  : m_bDash(false), m_fPower(0.f), m_fAccelTime(0.f), m_bDie(false)

{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_iCoin = 0;
	m_iHp = 100;
	m_iMaxhp = 100;
	m_tInfo = { 100.f, 300.f, 50.f, 50.f };
	Image_tInfo.fCX = 64.f;
	Image_tInfo.fCY = 96.f;
	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	m_bDash = false;
	m_bStretch = false;
	m_bAttack = false;
	m_bTeleport = false;
	m_bClick = false;
	m_bBuy = false;
	m_bShield = false;
	m_bBuySkill = false;
	m_bGetShield = false;
	m_fSpeed	= 4.f;
	m_fDiagonal = 50.f;
	m_fPower = 20.f;
	m_fAngle = 0.f;
	m_fDeltaSpeed = 0.05f;

	CPngMgr::Get_Instance()->insert_Png(L"../Image/Player/NormalSprite.png", L"PLAYER");
	CPngMgr::Get_Instance()->insert_Png(L"../Image/Player/PlayerMarker.png", L"MARKER");
	m_pFrameKey = L"PLAYER";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameProgress = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
	m_fMoveSpeed = m_fSpeed;

	m_eCDirection = DOWN;
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

 if (CSceneMgr::Get_Instance()->Get_ScenceID()==SC_BOSSSTAGE)
{
	CScrollMgr::Get_Instance()->Set_ScrollX(-250);
 }
}

int CPlayer::Update()
{

	Image_tInfo.fX = m_tInfo.fX;
	Image_tInfo.fY = m_tInfo.fY;
	if (!CObjMgr::Get_Instance()->Get_Objlist(POTAL).empty())
	{
		if (CCollisionMgr::Check_Sphere(this, CObjMgr::Get_Instance()->Get_Objlist(POTAL).front()))
		{
			m_bClick = true;
		}
		else
		{
			m_bClick = false;
		}
	}
	if (!CObjMgr::Get_Instance()->Get_Objlist(MERCHANT).empty())
	{

		if (!CObjMgr::Get_Instance()->Get_Objlist(ITEM).empty()&&CCollisionMgr::Check_Sphere(this, CObjMgr::Get_Instance()->Get_Objlist(ITEM).front()))
		{
			m_bBuy = true;
		}
		else 	if (!CObjMgr::Get_Instance()->Get_Objlist(SKILLCARD).empty()&&CCollisionMgr::Check_Sphere(this, CObjMgr::Get_Instance()->Get_Objlist(SKILLCARD).front()))
		{
			m_bBuySkill = true;
		}
		else 
		{
			m_bBuy = false;
			m_bBuySkill = false;
		}


	}


	if (!m_bTeleport)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Teleport.wav", BOSSSOUND_EFFECT, 0.5f);
		CObjMgr::Get_Instance()->Add_Object(BOSSMAGIC, CAbstractFactory<CTeleport>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
		m_bTeleport = true;
	}
		if (m_bDead)
		{
			if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)	
			{
				CSoundMgr::Get_Instance()->PlaySound(L"DisplayGlassShatter.wav", PALYER_EFFECT, 0.5f);

				return OBJ_DEAD;
			}
			else
			{
				return OBJ_NOEVENT;
			}
		}
		else
		{
			Dash();
			Attack();
			Posin();
			Hit();
			if (!m_bDash)
			{

				Key_Input();
				Speed_Up();

			}
			if (!m_bDie)
			{
				Dead();
			}


			Motion_Change();
			__super::Update_Rect();

			return OBJ_NOEVENT;
		}
	
}

void CPlayer::Late_Update()
{
	Offset();
	End_Map();
	Move_Frame();

	if (m_bFrame_Cycle&&m_eCurState==HIT)
	{
		m_bFrame_Cycle = false;
		m_bDash = false;
		m_bHit = false;
	}

	if (m_dShieldCooldown+10000<GetTickCount())
	{
		m_bShield = false;
	}
#ifdef _DEBUG

	if (m_dwTime+1000<GetTickCount())
	{
		float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		//cout<<"마우스 각도 : "<<m_fAngle<<endl;
		cout<<"플레이어 좌표 : "<<m_tInfo.fX<<"\t"<<m_tInfo.fY<<endl;
		//cout<<"속도"<<"\t"<<m_fSpeed<<"\t"<<m_fMoveSpeed<<"\t"<<m_fDeltaSpeed<<endl;
		//cout<<"scrollX:"<<"\t"<<iScrollX<<endl;
		//cout<<"scrollY:"<<"\t"<<iScrollY<<endl;
		m_dwTime = GetTickCount();
	}

#endif

}

void CPlayer::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	

	Graphics	g(hDC);	

		Image* imgMarker = CPngMgr::Get_Instance()->Find_Img(L"MARKER");
		Matrix _matrix;
		_matrix.RotateAt(-m_fAngle,	PointF(Image_tInfo.fX  + iScrollX, Image_tInfo.fY+24.f+ iScrollY));
		g.SetTransform(&_matrix);
		g.DrawImage(imgMarker,	
		Rect((int)( Image_tInfo.fX-48.f ) + iScrollX,
			(int)( Image_tInfo.fY-24.f) + iScrollY,
			96.f, 96.f),
		0 	, 0,
		48.f, 48.f,
		UnitPixel);	

	Graphics	graphics(hDC);	
	Image* img = CPngMgr::Get_Instance()->Find_Img(L"PLAYER");

	Point destinationPoints[] = {
   Point((int)(Image_tInfo.fX + Image_tInfo.fCX * 0.5) + iScrollX,
			 (int)(Image_tInfo.fY - Image_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
   Point((int)(Image_tInfo.fX - Image_tInfo.fCX * 0.5) + iScrollX,
			(int)(Image_tInfo.fY - Image_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
   Point((int)(Image_tInfo.fX + Image_tInfo.fCX * 0.5) + iScrollX,
			 (int)(Image_tInfo.fY + Image_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original

	if (!m_bStretch)
	{
			graphics.DrawImage(img,
			Rect(( int ) ( Image_tInfo.fX-Image_tInfo.fCX*0.5 )+iScrollX,
				( int ) ( Image_tInfo.fY-Image_tInfo.fCY*0.5 )+iScrollY,
				Image_tInfo.fCX, Image_tInfo.fCY),
			0+( m_tFrame.iFrameProgress*32 )
			, 0+( m_tFrame.iMotion*48 ),
			32.f, 48.f,
			UnitPixel);

			//Rectangle(hDC, m_tRect.left+iScrollX,
			//		m_tRect.top+iScrollY,
			//		m_tRect.right+iScrollX,
			//		m_tRect.bottom+iScrollY);
	}
	else
	{
		graphics.DrawImage(img, destinationPoints, 3,
			0 + (m_tFrame.iFrameProgress * 32) 
			, 0 + (m_tFrame.iMotion * 48) ,
			32.f , 48.f ,
			UnitPixel);

		//Rectangle(hDC, m_tRect.left+iScrollX,
		//			m_tRect.top+iScrollY,
		//			m_tRect.right+iScrollX,
		//			m_tRect.bottom+iScrollY);
	}



}

void CPlayer::Release()
{

	
		
}

void CPlayer::Posin()
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	float m_pMouse_X = m_pTarget->Get_Info().fX-iScrollX- Image_tInfo.fX;
	float m_pMouse_Y = m_pTarget->Get_Info().fY-iScrollY- Image_tInfo.fY;
	float m_pMouse_R = sqrtf(m_pMouse_X * m_pMouse_X + m_pMouse_Y * m_pMouse_Y);

	m_fAngle = acosf(m_pMouse_X / m_pMouse_R) * 180 / PI;

	if (m_pMouse_Y >0)
	{
		m_fAngle = 360.f-( m_fAngle );
	}
	m_tPosin.x = LONG(Image_tInfo.fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f)));
	m_tPosin.y = LONG(Image_tInfo.fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f)));

}

void CPlayer::Speed_Up()
{
	if ((m_ePreState == WALK && m_eCurState == WALK)
		&&m_fSpeed<= 8.f)
	{
		m_fSpeed += m_fDeltaSpeed;
	}
	else if ( m_eCurState != WALK
		&& m_fMoveSpeed >= 7.f&& m_eCurState!=DASH)
	{
		m_eCurState = BREAK;	
		m_bDash = true;
	}

}


void CPlayer::Key_Input()
{

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerFootstepAlt.wav", PALYER_EFFECT, 1.f);	

		if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fY -= m_fMoveSpeed;
			m_tInfo.fX -= m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = UP;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))	
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fY += m_fMoveSpeed;
			m_tInfo.fX -= m_fMoveSpeed;
			m_eCurState = WALK;	
			m_eCDirection = DOWN;	
			m_bStretch = false;

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))	
		{
			m_fMoveSpeed = 120.f;
			m_tInfo.fX -= m_fMoveSpeed;
			m_eCurState = DASH;
			m_eCDirection = LEFT;
			m_bStretch = true;
			m_bDash = true;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 180.f, m_bStretch));	
			CSoundMgr::Get_Instance()->StopSound(PALYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"AirJet.wav", PALYER_EFFECT, g_fVolume-0.5f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_fAngle>=225.f&&m_fAngle<315.f)
			{
				m_eCDirection = DOWN;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
								CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=135.f&&m_fAngle<225.f)
			{
				m_eCDirection = LEFT;
				m_eCurState = ATTACK;
				m_bStretch = true;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
								CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=45.f&&m_fAngle<135.f)
			{
				m_eCDirection = UP;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
								CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
		}
		else
		{
			m_fMoveSpeed = m_fSpeed;
			m_tInfo.fX -= m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = LEFT;
			m_bStretch = true;

		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerFootstepAlt.wav", PALYER_EFFECT, 1.f);

		if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fY -= m_fMoveSpeed;
			m_tInfo.fX += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = UP;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))	
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fY += m_fMoveSpeed;
			m_tInfo.fX += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = DOWN;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_fMoveSpeed = 120.f;
			m_tInfo.fX += m_fMoveSpeed;
			m_eCurState = DASH;
			m_eCDirection = RIGHT;
			m_bStretch = false;
			m_bDash = true;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 0.f, m_bStretch));
			CSoundMgr::Get_Instance()->StopSound(PALYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"AirJet.wav", PALYER_EFFECT, g_fVolume-0.5f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_fAngle>=225.f&&m_fAngle<315.f)
			{
				m_eCDirection = DOWN;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=135.f&&m_fAngle<225.f)
			{
				m_eCDirection = LEFT;
				m_eCurState = ATTACK;
				m_bStretch = true;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=45.f&&m_fAngle<135.f)
			{
				m_eCDirection = UP;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
		}
		else 
		{
			m_fMoveSpeed = m_fSpeed;
			m_tInfo.fX += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = RIGHT;
			m_bStretch = false;
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerFootstepAlt.wav", PALYER_EFFECT, 1.f);

		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fX += m_fMoveSpeed;
			m_tInfo.fY -= m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = UP;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fX -= m_fMoveSpeed;
			m_tInfo.fY -= m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = UP;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_fMoveSpeed = 120.f;
			m_tInfo.fY -= m_fMoveSpeed;
			m_eCurState = DASH;
			m_eCDirection = UP;
			m_bStretch = false;
			m_bDash = true;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 90.f, m_bStretch));
			CSoundMgr::Get_Instance()->StopSound(PALYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"AirJet.wav", PALYER_EFFECT, g_fVolume-0.5f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_fAngle>=225.f&&m_fAngle<315.f)
			{
				m_eCDirection = DOWN;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=135.f&&m_fAngle<225.f)
			{
				m_eCDirection = LEFT;
				m_eCurState = ATTACK;
				m_bStretch = true;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=45.f&&m_fAngle<135.f)
			{
				m_eCDirection = UP;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
		}
		else
		{
			m_fMoveSpeed = m_fSpeed;
			m_tInfo.fY -= m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = UP;
			m_bStretch = false;
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerFootstepAlt.wav", PALYER_EFFECT, 1.f);

		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fX += m_fMoveSpeed;
			m_tInfo.fY += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = DOWN;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			m_fMoveSpeed = m_fSpeed / sqrtf(2);
			m_tInfo.fX -= m_fMoveSpeed;
			m_tInfo.fY += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = DOWN;
			m_bStretch = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_fMoveSpeed = 120.f;
			m_tInfo.fY += m_fMoveSpeed;
			m_eCurState = DASH;
			m_eCDirection = DOWN;
			m_bStretch = false;
			m_bDash = true;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 270.f, m_bStretch));
			CSoundMgr::Get_Instance()->StopSound(PALYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"AirJet.wav", PALYER_EFFECT, g_fVolume-0.5f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{

			if (m_fAngle>=225.f&&m_fAngle<315.f)
			{
				m_eCDirection = DOWN;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=135.f&&m_fAngle<225.f)
			{
				m_eCDirection = LEFT;
				m_eCurState = ATTACK;
				m_bStretch = true;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
			else if (m_fAngle>=45.f&&m_fAngle<135.f)
			{
				m_eCDirection = UP;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			}
		}
		else
		{
			m_fMoveSpeed = m_fSpeed;
			m_tInfo.fY += m_fMoveSpeed;
			m_eCurState = WALK;
			m_eCDirection = DOWN;
			m_bStretch = false;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_bDash = true;
		m_fMoveSpeed = 120.f;
		CSoundMgr::Get_Instance()->StopSound(PALYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"AirJet.wav", PALYER_EFFECT, g_fVolume-0.5f);
		if (m_eCDirection==DOWN)
		{
			m_tInfo.fY += m_fMoveSpeed;
			m_bStretch = false;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 270.f, m_bStretch));

		}
		else	if (m_eCDirection == UP)	
		{
			m_tInfo.fY -= m_fMoveSpeed;
			m_bStretch = false;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 90.f, m_bStretch));

		}
		else	if (m_eCDirection == RIGHT)
		{
			m_tInfo.fX += m_fMoveSpeed;
			m_bStretch = false;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 0.f, m_bStretch));

		}
		else	if (m_eCDirection == LEFT)
		{
			m_tInfo.fX -= m_fMoveSpeed;
			m_bStretch = true;
			CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, 180.f, m_bStretch));

		}
		m_eCurState = DASH;
		}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_fAngle>=225.f&&m_fAngle<315.f)
			{
				m_eCDirection = DOWN;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, m_bStretch));
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);

			}
			else if (m_fAngle>=0.f&&m_fAngle<45.f||m_fAngle>=315.f&&m_fAngle<360.f)
			{
				m_eCDirection = RIGHT;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, m_bStretch));
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
			}
			else if (m_fAngle>=135.f&&m_fAngle<225.f)
			{
				m_eCDirection = LEFT;
				m_eCurState = ATTACK;
				m_bStretch = true;
				m_bDash = true;
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, m_bStretch));
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
			}
			else if (m_fAngle>=45.f&&m_fAngle<135.f)
			{
				m_eCDirection = UP;
				m_eCurState = ATTACK;
				m_bStretch = false;
				m_bDash = true;
				CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CMagic>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, m_bStretch));
				CSoundMgr::Get_Instance()->PlaySound(L"Hit1.wav", SOUND_EFFECT, g_fVolume-0.5f);
			}
		}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		if (m_bGetShield)
		{
			if (!m_bShield)
			{
				m_dShieldCooldown = GetTickCount();
				m_eCDirection = DOWN;
				m_eCurState = STONESHIELD;
				m_bStretch = false;
				m_bShield = true;
				m_bDash = true;
			}
		}


	}
	else
		{
			m_eCurState = IDLE;

		}
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		{
			m_iHp = m_iMaxhp;
		}

}

void CPlayer::Attack()
{
	if (m_eCurState==ATTACK)
	{
		if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bDash = false;
		}
	}
}

void CPlayer::Dash()
{
	 if (m_eCurState == DASH)
	{			
		 m_fMoveSpeed = 6.f;
		 m_fSpeed = 6.f;
		if (m_tFrame.iFrameProgress == m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bDash = false;
		}
	}
	 if (m_eCurState==BREAK)
	 {
		 m_fSpeed = 6.f;
		 m_fMoveSpeed = 6.f;
		 if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		 {
			 m_eCurState = IDLE;
			 m_bDash = false;
		 }
	 }
	 if (m_eCurState==STONESHIELD)
	 {

		 if (m_tFrame.iFrameProgress==m_tFrame.iFrameEnd)
		 {
			 m_eCurState = IDLE;
			 m_bDash = false;
			 CObjMgr::Get_Instance()->Add_Object(SHIELD, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY, 0.f, this, 3));
			 CObjMgr::Get_Instance()->Add_Object(SHIELD, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY, 90.f, this, 6));
			 CObjMgr::Get_Instance()->Add_Object(SHIELD, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY, 180.f, this, 9));
			 CObjMgr::Get_Instance()->Add_Object(SHIELD, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY, 270.f, this, 0));
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,30.f,this,4));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,60.f,this,5));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,120.f,this,7));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,150.f,this,8));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,210.f,this,10));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,240.f,this,11));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,300.f,this,1));	
			 //CObjMgr::Get_Instance()->Add_Object(MAGIC, CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY,330.f,this,2));	

		 }
	 }
}

void CPlayer::Offset()
{
	float		iOffSetX = float(WINCX >> 1);
	float		iOffSetY = float(WINCY >> 1);
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetX+5 > (m_tInfo.fX + iScrollX))
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fMoveSpeed);
	if (iOffSetX-5 < (m_tInfo.fX + iScrollX))
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fMoveSpeed);

	if (iOffSetY+5 > (m_tInfo.fY + iScrollY))
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fMoveSpeed);
	if (iOffSetY -5< (m_tInfo.fY + iScrollY))
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fMoveSpeed);
}


void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState|| m_eCDirection!= m_ePDirection)
	{
		switch (m_eCurState)
		{
		case TELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_bStretch = false;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case IDLE:

			if (m_eCDirection==DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_bStretch = false;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == RIGHT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == LEFT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == UP)
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameProgress = 2;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 0;
				m_bStretch = false;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}

		case WALK:
			if (m_eCDirection == DOWN)	
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == UP)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 3;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			} 
		case	BREAK:
			if (m_eCDirection == DOWN)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.iMotion = 4;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == RIGHT)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameProgress = 3;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == LEFT)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameProgress = 3;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == UP)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameProgress = 1;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion =6;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case DASH:
			if (m_eCDirection == DOWN)	
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 4;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == UP)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 6;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == RIGHT)	
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection == LEFT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameProgress = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 5;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		case ATTACK:
			if (m_eCDirection==DOWN	)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 0;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==RIGHT)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==LEFT)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 1;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			else if (m_eCDirection==UP)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameProgress = 7;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 2;

				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			
		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 8;

			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;

		case STONESHIELD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 9;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameProgress = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 7;

			m_tFrame.dwSpeed = 700;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
		m_ePDirection = m_eCDirection;
	}

}

void CPlayer::End_Map()
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	if (m_tInfo.fX + iScrollX < 0.f + iScrollX)
		m_tInfo.fX += m_fMoveSpeed;
	if (m_tInfo.fX + iScrollX  > WINCX)
		m_tInfo.fX -= m_fMoveSpeed;

	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_tInfo.fY + iScrollY < 0.f + iScrollY)	
		m_tInfo.fY += m_fMoveSpeed;
	if (m_tInfo.fY + iScrollY > WINCY)
		m_tInfo.fY -= m_fMoveSpeed;
}

void CPlayer::Hit()
{
	if (m_bHit)
	{
		CObjMgr::Get_Instance()->Add_Object(HITEFFECT, CAbstractFactory<CHitEffect>::
		Create(m_tInfo.fX-m_tInfo.fCX*0.5+rand()%20, m_tInfo.fY-m_tInfo.fCY*0.5+rand()%10, m_fAngle));
		m_eCurState = HIT;
		m_bHit = false;
	}

}
void CPlayer::Dead()
{
	if (m_iHp<0)
	{
		m_bDie = true;
		m_bDead = OBJ_DEAD;
		m_eCurState = DEAD;
	}
}