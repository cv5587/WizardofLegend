#pragma once
#include "Obj.h"
class CFireExploed :
    public CObj
{
public:
	CFireExploed();
	virtual ~CFireExploed();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Motion_Change();
	void		Motion_Dead();
};

