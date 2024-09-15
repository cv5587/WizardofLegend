#pragma once
#include "Obj.h"
class CDash :
    public CObj
{
public:
	CDash();
	~CDash();
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

