#pragma once

#include "Obj.h"
#include "Shield.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

public:
	void		Posin();
	void		Speed_Up();
	void		Key_Input();
	void		Attack();
	void		Dash();
	void		Offset();
	void		Motion_Change();
	void		End_Map();
	void Hit();
	void Dead();

	bool		Get_Dashed() { return m_bDash; }
	bool		Get_Click() { return m_bClick; }
	bool		Get_Buy() { return m_bBuy; }
	bool		Get_BuySkill() { return m_bBuySkill; }
	void		Set_BuySkill() {  m_bBuySkill=true; }
	bool		Get_Skill() { return m_bGetShield; }
	void		Set_Skill() {  m_bGetShield=true; }
	void		Set_MyCoin(int _coin) { m_iCoin += _coin; }
private:
	POINT				m_tPosin;
	float				m_fDiagonal;

	
	bool				m_bDash;
	bool				m_bShield;

	bool				m_bAttack;
	bool				m_bDie;
	bool				m_bTeleport;
	bool				m_bClick;
	bool				m_bBuy;
	bool				m_bBuySkill;
	float				m_fPower;
	float				m_fAccelTime;
	DWORD		m_dShieldCooldown;

	float				m_fDeltaSpeed;

	DWORD				m_dwTime = GetTickCount();


};

// ������ ������ �̿��Ͽ� �÷��̾ �����ϴ� ���¸� ������

// Y = �Ŀ� * sin(��) * �ð� - �߷�(9.8f) * �ð��� ���� / 2

