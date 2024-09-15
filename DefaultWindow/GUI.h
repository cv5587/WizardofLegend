#pragma once
#include "Obj.h"
class CGUI :
    public CObj
{
public:
    CGUI();
    ~CGUI();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	Hp_Check();
	void	Coin_Check();

private:
	int	Change_Hp;
	int	Current_Hp;
	int	Change_BossHp;
	int	Current_BossHp;


};

