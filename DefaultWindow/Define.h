#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI		3.141592f
#define			VK_MAX		 0xff

#define			TILEX		32
#define			TILEY		20

#define			BOSSTILEX		20
#define			BOSSTILEY		20 

#define			TILECX		64
#define			TILECY		64

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;

}INFO;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };
enum OBJID	   {  MERCHANT, ITEM, SKILLCARD, PLAYER, POTAL, COIN, MONSTER, BACK_BLAST, BOSS, MAGIC,MONSTERMAGIC, SHOTMAGIC, BOSSMAGIC, BOSSMETEORID, SHIELD, BUTTON, GUI, MOUSE, TILE, HITEFFECT,OBJ_END };
enum SCENEID	{ SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE,SC_BOSSSTAGE, SC_END };
enum CHANNELID { SOUND_EFFECT,PALYER_EFFECT, MONSTER_EFFECT, WIZARD_EFFECT,BOSSSOUND_EFFECT, BOSSMETEOR, BOSSSOUND_EFFECTLOOP,SKILL_EFFECT,SOUND_BGM,HITSOUND,ITEM_DROP,MONSTER_SPAWN, MAXCHANNEL };
enum UIID { HP ,STATEBAR, SKILLSLOT, KEYBOARD, SKILLICON, BOSSHP, BOSSSTATEBAR, BOSSNAME,CLICK,COINUI, COINFONTUI1,COINFONTUI10 ,UI_END };

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct CDeleteObj
{
	template<typename T>
	void	operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

struct CDeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

struct CTagFinder
{
	CTagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool		operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}


	const TCHAR*		m_pString;
};



typedef struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {  }

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& tLeft, LINEPOINT& tRight)
		: tLPoint(tLeft), tRPoint(tRight) {}

}LINE;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameProgress;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;



extern		HWND		g_hWnd;
