
// puzzle.h : puzzle ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CpuzzleApp:
// �� Ŭ������ ������ ���ؼ��� puzzle.cpp�� �����Ͻʽÿ�.
//

class CpuzzleApp : public CWinApp
{
public:
	CpuzzleApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CpuzzleApp theApp;
