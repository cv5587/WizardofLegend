#include "stdafx.h"
#include "PngMgr.h"

CPngMgr* CPngMgr::m_pInstance = nullptr;

CPngMgr::CPngMgr()
{
}

CPngMgr::~CPngMgr()
{
	Release();
}

void CPngMgr::insert_Png(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapPng.begin(), m_mapPng.end(), CTagFinder(pImgKey));
	if (iter == m_mapPng.end())
	{
		CMyPng* pPng = new CMyPng;

		pPng->Load_Png(pFilePath);

		m_mapPng.emplace(pImgKey, pPng);
	}
}

void CPngMgr::Release()
{
	for_each(m_mapPng.begin(), m_mapPng.end(), CDeleteMap());
	m_mapPng.clear();

}

Image* CPngMgr::Find_Img(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapPng.begin(), m_mapPng.end(), CTagFinder(pImgKey));

	if (iter == m_mapPng.end())
		return nullptr;

	return iter->second->Get_Image();
}
