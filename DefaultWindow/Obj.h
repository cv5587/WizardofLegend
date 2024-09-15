#pragma once

#include "Define.h"
enum PLAYERSTATE { IDLE, WALK, BREAK, DASH, ATTACK,STONESHIELD, HIT, DEAD, TELEPORT, PS_END };
enum PLAYERDIR { DOWN, RIGHT, LEFT, UP, PD_END };
enum BOSSSTATE { BOSSIDLE, FIREBALL, FIREDASH, BOSSBREAK, METEOR, BOSSHIT, BOSSTELEPORT, BOSSDEAD, WARMUP, BS_END };
enum MONSTERSTATE { MONSTERIDLE, MONSTERATTACK, MONSTERCHASING, MONSTERHIT, MONSTERDEAD, MS_END };
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_Direction(DIRECTION eDir)
	{
		m_eDir = eDir;
	}
	void			Set_Dead() { m_bDead = true; }
	void			Set_Damage() { m_iDamage = 0; }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Stretch(float _bStretch) { m_bStretch = _bStretch; }
	void			Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void			Set_Hp(int _ihp) 
	{
		m_iHp -= _ihp;
		if (m_iMaxhp<m_iHp)
		{
			m_iHp = m_iMaxhp;
		}
	}
	void		Set_Skill() { m_bGetShield = true; }
	void			Set_UIx(int _x) { UI_x = _x; }

	void			Set_Hit() { m_bHit = true; }
	int			Get_Hp() { return m_iHp ; }
	int			Get_Damage() { return m_iDamage; }

	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }
	bool			Get_Dead() { return m_bDead; }
	int		Get_MyCoin() { return m_iCoin; }
	int		Get_MonsterID() { return m_iMonsterID; }
	void		Set_Coin(int  _coin) {  m_iCoin=_coin; }
	void		Set_MonsterID(int  _MonsterID) { m_iMonsterID =_MonsterID; }
	void		Set_ChangeCoin(int  _coin) {  m_iCoin-=_coin; }


	void			Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void			Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void			Set_Gui(UIID GUI) { m_pUI = GUI; }
	void			Set_iFrameProgress(int _Start) { m_tFrame.iFrameProgress = _Start; }
public:
	virtual void	Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;

protected:
	void		Update_Rect();
	void		Move_Frame();
protected:
	virtual void	Timer_Update();

protected:
	INFO		m_tInfo;
	INFO		Image_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	FRAME		m_tFrame;
	int			m_iMonsterID;
	CObj*		m_pTarget;

	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;
	float		m_fMoveSpeed;

	TCHAR*		m_pFrameKey;
	UIID				m_pUI;
	bool				m_bStretch;
	bool				m_bFrame_Cycle;
	bool				m_bSkillCreate;
	bool				m_bHit;

	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;
	PLAYERDIR				m_eCDirection;
	PLAYERDIR				m_ePDirection;

	int				m_iHp;
	int				m_iMaxhp;
	int				m_iDamage;
	int				UI_x;
	int				m_iCoin;
	bool				m_bGetShield;
	float			m_fSumTick;
	float			m_fDeltaTick;
	UINT64			m_fPrevTick;
	float			m_fLifeTick;
};

