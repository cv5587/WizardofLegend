#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	vector<CObj*>	Get_Tile() { return m_vecTile; }
	void		Picking(POINT _ptMouse, int _iDrawID, int _iOption,bool _bState);
	void		Save_Data();
	void		Load_Data();

public:
	static	CTileMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTileMgr*	m_pInstance;
	vector<CObj*>		m_vecTile;



};

