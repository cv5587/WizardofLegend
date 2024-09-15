#pragma once
#include "Monster.h"
class CKnight :
    public CMonster
{
public:
	CKnight();
	virtual ~CKnight();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:

	void		Motion_Change();
	void		Check_Angle();
	void		Change_Stretch();
	void		Check_State();
	void		Chasing();
	void		Dead();
	void		Hit();
	void		Attack();
private:
	bool					m_bFreezed;
	bool					m_bDie;
	MONSTERSTATE		m_eMonsterCurState;
	MONSTERSTATE		m_eMonsterPreState;
	DWORD					m_dAttackTime;
	POINT				m_tPosin;
	float				m_fDiagonal;
};

