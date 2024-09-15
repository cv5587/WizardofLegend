#pragma once

#include "Obj.h"
#include"Tile.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList);

	static void Collision_UIRect(list<CObj*> DstList, list<CObj*> SrcList);

	static void Collision_SlashRect(list<CObj*> DstList, list<CObj*> SrcList);

	static void Collision_FireRect(list<CObj*> DstList, list<CObj*> SrcList);

	static void	Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList);
	static void Collision_RectTile(CObj* Dst, vector<CObj*> SrcList);
	static	void Collision_MonsterRectTile(list<CObj*> DstList, vector<CObj*> SrcList);
	static void Collision_BOSSRectTile(CObj* Dst, vector<CObj*> SrcList);
	static void Collision_RectEffectTile(list<CObj*> DstList, vector<CObj*> SrcList);
	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);

	bool CheckDamage_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);

	static void	Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	static void Collision_CoinSphere(list<CObj*> Dst, list<CObj*> Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

	static bool Check_RangeSphere(CObj* pDst, CObj* pSrc);

};


