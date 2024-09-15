#pragma once
#include "Obj.h"
class CWizard_Fire_Explosion :
    public CObj
{
public:
	CWizard_Fire_Explosion();
	virtual ~CWizard_Fire_Explosion();

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

