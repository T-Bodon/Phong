
// PhongModel.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPhongModelApp: 
// �йش����ʵ�֣������ PhongModel.cpp
//

class CPhongModelApp : public CWinApp
{
public:
	CPhongModelApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPhongModelApp theApp;