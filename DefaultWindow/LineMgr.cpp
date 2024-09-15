#include "stdafx.h"
#include "LineMgr.h"
#include "ObjMgr.h"
CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter:m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Update()
{
	if (m_eSceneId==SC_STAGE)
	{
		float currentX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
		float currentY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;

		if (currentX-m_fPrevX>=400.f)
		{
			LINEPOINT tmp[ 2 ]{ {m_fMapMaxX , 500.f}, {m_fMapMaxX+400.f,500.f } };
			m_LineList.push_back(new CLine(tmp[ 0 ], tmp[ 1 ]));
			m_fMapMaxX += 400.f;
			m_fPrevX = currentX;


			Safe_Delete<CLine*>(m_LineList.front());
			m_LineList.pop_front();

		}

		if (currentX-m_fPrevX>=200.f)
		{
			LINEPOINT tmp[ 2 ]{ {m_fMapMaxX2 , 400.f}, {m_fMapMaxX2+50.f,400.f } };
			LINEPOINT tmp2[ 2 ]{ {m_fMapMaxX2+50.f , 300.f}, {m_fMapMaxX2+100.f,300.f } };
			m_LineList.push_back(new CLine(tmp[ 0 ], tmp[ 1 ]));
			m_LineList.push_back(new CLine(tmp2[ 0 ], tmp2[ 1 ]));
			m_fMapMaxX2 += 200.f;
			m_fPrevX2 = currentX;
		}

	}
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float* pHeight, float& _fX)
{
	if (m_LineList.empty())
		return false;


	CLine* pTargetLine = nullptr;

	for (auto& iter:m_LineList)
	{

		if (_fX>=iter->Get_Info().tLPoint.fX&&
			_fX<iter->Get_Info().tRPoint.fX)
		{

			pTargetLine = iter;
			break;
		}

	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;

	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;

	*pHeight = ( ( y2-y1 )/( x2-x1 ) )*( _fX-x1 )+y1;

	return true;
}

bool CLineMgr::Collision_Line(float* pHeight, float& _fX, int _HOffset)
{
	if (m_LineList.empty())
		return false;


	CLine* pTargetLine = nullptr;

	for (auto& iter:m_LineList)
	{
		if (_fX>=iter->Get_Info().tLPoint.fX&&
			_fX<iter->Get_Info().tRPoint.fX)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;

	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;

	int tmpHeight = ( ( y2-y1 )/( x2-x1 ) )*( _fX-x1 )+y1;

	if (*pHeight>=tmpHeight-_HOffset)
	{
		*pHeight = tmpHeight-_HOffset;
		return true;
	}
	else
		return false;
}

bool CLineMgr::Collision_Line(float* pPrevHeight, float* pCurHeight, float& _fX, int _HOffset)
{
	if (m_LineList.empty())
		return false;
	float tmpHeight = 0;
	float minHeight = INT32_MAX;

	CLine* pTargetLine = nullptr;

	for (auto& iter:m_LineList)
	{
		if (_fX>=iter->Get_Info().tLPoint.fX&&
			_fX<iter->Get_Info().tRPoint.fX)
		{
			float x1 = iter->Get_Info().tLPoint.fX;
			float y1 = iter->Get_Info().tLPoint.fY;

			float x2 = iter->Get_Info().tRPoint.fX;
			float y2 = iter->Get_Info().tRPoint.fY;

			tmpHeight = ( ( y2-y1 )/( x2-x1 ) )*( _fX-x1 )+y1;

			if (( *pPrevHeight<=tmpHeight )&&( *pCurHeight+_HOffset>=tmpHeight ))
			{
				if (abs(*pPrevHeight+_HOffset-tmpHeight)<=abs(*pPrevHeight+_HOffset-minHeight))
					minHeight = tmpHeight;
			}
			pTargetLine = iter;
		}
	}


	if (!pTargetLine||( *pCurHeight+_HOffset )<=minHeight)
		return false;

	*pCurHeight = minHeight-_HOffset;
	return true;


}

void CLineMgr::Load_Line()
{
	// CreateFile: API ���� �����Լ�
	HANDLE			hFile = nullptr;

	switch (m_eSceneId)
	{
	case SC_STAGE:
		hFile = CreateFile(L"../Data/Line.dat",		// ���� ��ο� �̸��� ���
			GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ���, GENERIC_READ : ���� �Է�)
			NULL,					// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���α׷��� �����ϰ��� �� �� �������� ���θ� ����, NULL ���� �� �������� ����
			NULL,					// ���� ��� ����, NULL�� ��� �⺻ �� ���� ����
			OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
			FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ������ ����
			NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ����̱� ������ NULL)
		break;
	case SC_END:
		break;
	default:
		return;
	}


	if (INVALID_HANDLE_VALUE==hFile)
	{
		MessageBox(g_hWnd, L"����", L"����", MB_OK);
		return;
	}

	DWORD		dwByte(0);
	LINE		tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0==dwByte)
			break;

		m_LineList.push_back(new CLine(tLine));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
