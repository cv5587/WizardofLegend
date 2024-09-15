#pragma once
#include "Define.h"

class CMyPng
{
public:
	CMyPng();
	~CMyPng();

public:
	Image* Get_Image() { return	Img; }
	void	Load_Png(const TCHAR* pFilePath);
private:
	Image* Img;
};

