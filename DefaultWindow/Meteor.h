#pragma once
#include "Obj.h"
class CMeteor :
    public CObj
{
public:
	CMeteor();
	~CMeteor();
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
	DWORD	m_dMotionTick;
	bool			m_bCreate;

};

