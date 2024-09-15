#include "stdafx.h"
#include "MyPng.h"
CMyPng::CMyPng()
{
}

CMyPng::~CMyPng()
{
}

void CMyPng::Load_Png(const TCHAR* pFilePath)
{
	Img=Image::FromFile( pFilePath);
}
