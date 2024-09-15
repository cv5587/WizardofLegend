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
	// x,y 위치와 angle 값을 받아 방향을 까지 설정해서 제작
	static CObj* Create(float _fX, float _fY,float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	//몬스터 id 를 추가로 받아 몬스터 종류 선택가능
	static CObj* CreateMonster(float _fX, float _fY, float _fAngle, int _MonsterID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_MonsterID(_MonsterID);

		return pObj;
	}
	//타겟을 설정하여 목표 지점을 설정
	static CObj* Create(float _fX, float _fY, CObj* pTarget)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Target(pTarget);

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

