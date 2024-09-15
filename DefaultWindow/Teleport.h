#pragma once
#include "Obj.h"
class CTeleport :
    public CObj
{
public:
	CTeleport();
	~CTeleport();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Motion_Change();
	void		Motion_Dead();


};

