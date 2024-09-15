#pragma once
#include "Obj.h"
class CMagic :	public CObj
{
public:
	CMagic();
	virtual ~CMagic();

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

