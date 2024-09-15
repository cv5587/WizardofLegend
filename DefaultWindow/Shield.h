#pragma once
#include "Obj.h"
class CShield :	public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	
public:
	void		Motion_Change();
private:
	float			m_fDistance;
	DWORD	m_dLifeTick;
	float			m_fCheckAngle;
};

