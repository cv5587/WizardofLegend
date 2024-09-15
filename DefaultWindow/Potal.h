#pragma once
#include "Obj.h"
class CPotal :
    public CObj
{
public:
	CPotal();
	virtual ~CPotal();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	void Motion_Change();

	bool		m_bTeleport;

};

