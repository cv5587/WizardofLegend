#pragma once
#include "Obj.h"
class CFireball :
    public CObj
{
public:
	CFireball();
	virtual ~CFireball();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Motion_Change();

};

