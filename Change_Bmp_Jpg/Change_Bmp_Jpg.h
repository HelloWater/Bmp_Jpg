
// Change_Bmp_Jpg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChange_Bmp_JpgApp:
// �йش����ʵ�֣������ Change_Bmp_Jpg.cpp
//

class CChange_Bmp_JpgApp : public CWinAppEx
{
public:
	CChange_Bmp_JpgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChange_Bmp_JpgApp theApp;