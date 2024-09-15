#pragma once
#include "Obj.h"
class CMerchant :
    public CObj
{
public:
	CMerchant();
	virtual ~CMerchant();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	void Motion_Change();

	bool		m_bTeleport;
};

