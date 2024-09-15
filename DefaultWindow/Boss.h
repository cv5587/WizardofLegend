#pragma once
#include "Monster.h"
#include "Obj.h"
class CBoss :
    public CMonster
{
public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:

	void		Motion_Change();

public:
	void		Spawn();
	void		WarmUp();
	void		FireBall();
	void		Fire_Metor();
	void		Create_Skill();
	void		FireDash();
	void		Check_Angle();
	void		Change_Stretch();
	void		Skill_Frame();
	void		Chasing();
	void		Dead();
	void		Hit();

private:
	BOSSSTATE		m_eBossCurState;
	BOSSSTATE		m_eBossPreState;
	bool					m_bSpawn;
	bool					m_bTeleport;
	bool					m_bSKILL_USE;
	bool					m_bDie;

	bool					m_bFreezed;
	float					m_fSpawntime;
	float					m_fFireballTick;
	float					m_fFireDashTick;
	float					m_fMeteorTick;
	float					m_fCheckAngle;
	DWORD				m_dwTime = GetTickCount();
	DWORD				m_dSpawnTime ;
	DWORD				m_dSkillTime ;
};	

