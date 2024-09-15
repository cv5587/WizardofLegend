#pragma once
#include "Obj.h"
class CPotion :
    public CObj
{
public:
	CPotion();
	~CPotion();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
	void Motion_Change();
	void			Set_Get() { m_bGet = true; }
	bool			Get_Get() { return m_bGet; }
	int			Get_Price() { return  m_iPrice; }

private:
	float			m_fDropDis;
	int			m_iPrice;
	bool			m_bGet;
	float			m_fdistance;
};

