#pragma once
#include "Obj.h"
class CMonsterSlash :
    public CObj
{
public:
	CMonsterSlash();
	~CMonsterSlash();
public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Motion_Change();
	void		 Motion_Dead();
private:
	DWORD	m_dLifeTick;
	DWORD	m_dMotionTick;
	bool			m_bCreate;
	bool			m_CheckAngle;
};

