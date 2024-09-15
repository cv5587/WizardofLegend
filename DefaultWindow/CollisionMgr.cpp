#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "HitEffect.h"
#include "Player.h"
#include "Coin.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

//void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
//{
//	// 1인자 : 결과 값을 저장할 렉트의 주소
//	// 2, 3인자 : 충돌을 수행할 렉트의 주소
//	//SRC가 캐릭터 넣기
//	RECT	rc{};
//
//	for (auto& DstList : Dst)
//	{
//		for (auto& SrcList : Src)
//		{
//			if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
//			{
//				DstList->Set_Dead();
//				SrcList->Set_Dead();
//			}
//		}
//	}
//
//
//}
//스킬 , 캐릭
void CCollisionMgr::Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;
	RECT	rc{};
	for (auto& Dst:DstList)
	{
		for (auto& Src:SrcList)
		{
			if (IntersectRect(&rc, &( Dst->Get_Rect() ), &( Src->Get_Rect() )))
			{
				Dst->Set_Dead();
				Src->Set_Hp(Dst->Get_Damage());

			}
		}
	}
}
void CCollisionMgr::Collision_UIRect(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;
	RECT	rc{};
	for (auto& Dst:DstList)
	{
		for (auto& Src:SrcList)
		{
			if (IntersectRect(&rc, &( Dst->Get_Rect() ), &( Src->Get_Rect() )))
			{
				Dst->Set_Dead();
			}
		}
	}
}
void CCollisionMgr::Collision_SlashRect(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;
	RECT	rc{};
	for (auto& Dst:DstList)
	{
		for (auto& Src:SrcList)
		{
			if (IntersectRect(&rc, &( Dst->Get_Rect() ), &( Src->Get_Rect() )))
			{
				Src->Set_Hp(Dst->Get_Damage());
				if (Dst->Get_Damage()>1)
				{
					Src->Set_Hit();
					Dst->Set_Damage();	
				}
				else if (Dst->Get_Damage()>0&&dynamic_cast< CPlayer* >( Src )->Get_Dashed())
				{
					Dst->Set_Damage();
				}
				else
				{
					Dst->Set_Damage();
				}

			}
		}
	}
}
void CCollisionMgr::Collision_FireRect(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;
	RECT	rc{};
	for (auto& Dst:DstList)
	{
		for (auto& Src:SrcList)
		{
			if (IntersectRect(&rc, &( Dst->Get_Rect() ), &( Src->Get_Rect() )))
			{
				//Dst->Set_Dead();
				Src->Set_Hp(Dst->Get_Damage());
			}
		}
	}
}
void CCollisionMgr::Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				if (fX > fY)	// 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Dst->Set_PosY(-fY);

					// 하 충돌
					else
						Dst->Set_PosY(fY);

				}
				else			// 좌우 충돌	
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Dst->Set_PosX(-fX);

					// 우 충돌
					else
						Dst->Set_PosX(fX);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_RectTile(CObj* Dst, vector<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;


		for (auto& Src:SrcList)
		{
			if (dynamic_cast< CTile* >(Src)->Get_DrawID()==1)
			{
				if (Check_Rect(&fX, &fY, Dst, Src))
				{
					if (fX>fY)	// 상하 충돌
					{
						// 상 충돌
						if (Dst->Get_Info().fY<Src->Get_Info().fY)
							Dst->Set_PosY(-fY);

						// 하 충돌
						else
							Dst->Set_PosY(fY);

					}
					else			// 좌우 충돌	
					{
						// 좌 충돌
						if (Dst->Get_Info().fX<Src->Get_Info().fX)
							Dst->Set_PosX(-fX);

						// 우 충돌
						else
							Dst->Set_PosX(fX);
					}
				}
			}
	
		}
	
}
void CCollisionMgr::Collision_MonsterRectTile(list<CObj*> DstList, vector<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst:DstList)
	{
		for (auto& Src:SrcList)
		{
			if (dynamic_cast< CTile* >( Src )->Get_DrawID()==1)
			{
				if (Check_Rect(&fX, &fY, Dst, Src))
				{
					if (fX>fY)	// 상하 충돌
					{
						// 상 충돌
						if (Dst->Get_Info().fY<Src->Get_Info().fY)
							Dst->Set_PosY(-fY);

						// 하 충돌
						else
							Dst->Set_PosY(fY);

					}
					else			// 좌우 충돌	
					{
						// 좌 충돌
						if (Dst->Get_Info().fX<Src->Get_Info().fX)
							Dst->Set_PosX(-fX);

						// 우 충돌
						else
							Dst->Set_PosX(fX);
					}
				}
			}

		}
	}

}
void CCollisionMgr::Collision_BOSSRectTile(CObj* Dst, vector<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;


	for (auto& Src:SrcList)
	{
		if (dynamic_cast< CTile* >( Src )->Get_DrawID()==1||dynamic_cast< CTile* >( Src )->Get_DrawID()==2)
		{
			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				if (fX>fY)	// 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info().fY<Src->Get_Info().fY)
						Dst->Set_PosY(-fY);

					// 하 충돌
					else
						Dst->Set_PosY(fY);

				}
				else			// 좌우 충돌	
				{
					// 좌 충돌
					if (Dst->Get_Info().fX<Src->Get_Info().fX)
						Dst->Set_PosX(-fX);

					// 우 충돌
					else
						Dst->Set_PosX(fX);
				}
			}
		}

	}

}
void CCollisionMgr::Collision_RectEffectTile(list<CObj*> DstList, vector<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst:DstList)	
	{
		for (auto& Src:SrcList)	
		{
			if (dynamic_cast< CTile* >( Src )->Get_DrawID()==1)	
			{
				if (Check_Rect(&fX, &fY, Dst, Src))
				{
					Dst->Set_Dead();
				}
			}

		}
	}
	

}

bool CCollisionMgr::Check_Rect(float * pX, float * pY, CObj * pDst, CObj * pSrc)
{
	float		fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY+12.f - pSrc->Get_Info().fY);

	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().fCY*0.5f + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

bool CCollisionMgr::CheckDamage_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc)
{
	float		fWidth = abs(pDst->Get_Info().fX-pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY-pSrc->Get_Info().fY);

	float		fRadiusX = ( pDst->Get_Info().fCX+pSrc->Get_Info().fCX )*0.5f;
	float		fRadiusY = ( pDst->Get_Info().fCY+pSrc->Get_Info().fCY )*0.5f;

	if (( fRadiusX>fWidth )&&( fRadiusY>fHeight ))
	{
		*pX = fRadiusX-fWidth;
		*pY = fRadiusY-fHeight;

		return true;
	}


	return false;
}
void CCollisionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				DstList->Set_Dead();
				SrcList->Set_Dead();
			}
		}
	}
}
void CCollisionMgr::Collision_CoinSphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList:Dst)
	{
		for (auto& SrcList:Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				if (!dynamic_cast< CCoin* >( SrcList )->Get_Get())
				{
					dynamic_cast< CPlayer* >( DstList )->Set_MyCoin(dynamic_cast< CCoin* >( SrcList )->Get_Price());
					dynamic_cast< CCoin* >( SrcList )->Set_Get();
				}

			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float		fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	
	return fRadius >= fDistance;
}

bool CCollisionMgr::Check_RangeSphere(CObj* pDst, CObj* pSrc)
{
	float		fWidth = abs(pDst->Get_Info().fX-pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY-pSrc->Get_Info().fY);

	float		fDistance = ( float ) sqrt(fWidth*fWidth+fHeight*fHeight);

	float		fRadius = 400.f;


	return fRadius>=fDistance;
}
