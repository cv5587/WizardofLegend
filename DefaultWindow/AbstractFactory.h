#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	static CObj* Create(float _fX, float _fY,float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* CreateMonster(float _fX, float _fY, float _fAngle, int _MonsterID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_MonsterID(_MonsterID);

		return pObj;
	}
	static CObj* Create(float _fX, float _fY, float _fAngle,bool _bStretch)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Stretch(_bStretch);

		return pObj;
	}
	static CObj*		Create(float _fX, float _fY, CObj* pTarget)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Target(pTarget);

		return pObj;
	}

	static CObj* BossStageCreate(float _fX, float _fY, CObj* pTarget)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Target(pTarget);
		pObj->Set_Skill();		
		return pObj;
	}
	static CObj* Create(float _fX, float _fY, float _Angle,CObj* pTarget,int _Frame)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_Angle);
		pObj->Set_Target(pTarget);
		pObj->Set_iFrameProgress(_Frame);
		return pObj;
	}
	static CObj*		Create(CObj* pTarget)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(pTarget);

		return pObj;
	}

public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

