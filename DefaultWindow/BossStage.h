#pragma once
#include "Scene.h"
class CBossStage :
    public CScene
{
public:
	CBossStage();
	virtual ~CBossStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dTick;
};

