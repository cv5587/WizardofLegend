#pragma once
#include "Obj.h"
class CFireburn :
    public CObj
{
public:
    CFireburn();
    ~CFireburn();
public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Motion_Change();
private:
	DWORD	m_dLifeTick;

};

