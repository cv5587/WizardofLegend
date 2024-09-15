#pragma once
#include "Obj.h"
class CCoin :
    public CObj
{
public:
    CCoin();
    ~CCoin();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
	void Motion_Change();
	void			Set_Get() { m_bGet = true; }
	bool			Get_Get() { return m_bGet ; }
	int			Get_Price() { return  m_iPrice; }
public:
	void	Drop();
private:
	float			m_fDropDis;
	int			m_iPrice;
	bool			m_bGet;
	float			m_fdistance;
};

//생성시 플레이어 받아오기
//일정거리 이하면 코인이 캐릭터 몸으로 들어가기.