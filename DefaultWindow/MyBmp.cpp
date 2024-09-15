#include "stdafx.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : �Ű������� ȣȯ�Ǵ� dc�� ����

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);


	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// ���α׷� �ν��Ͻ� �ڵ�(�̹����� ���α׷����� ������ ���� �ƴϱ� ������ NULL)
									pFilePath,	// ������ ��� ����
									IMAGE_BITMAP,  // � Ÿ���� �о������ ����
									0,		// ���� ũ��
									0,		// ���� ũ��
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);
									// LR_LOADFROMFILE : ���Ϸ� ���� �̹��� �ҷ�����
									// LR_CREATEDIBSECTION : ���̿� ������ DIB ���·� ��ȯ

	// SelectObject : GDI ������Ʈ�� �����ϱ� ���� ������ ���� �ִ� ������Ʈ�� ��ȯ�ϴ� �Լ�

	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}


void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
