#pragma once
#include "Obj.h"
class CShopTable :
    public CObj
{
public:
	CShopTable();
	virtual ~CShopTable();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	void Motion_Change();

};

