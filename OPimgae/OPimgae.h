
// OPimgae.h : OPimgae ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// COPimgaeApp:
// �� Ŭ������ ������ ���ؼ��� OPimgae.cpp�� �����Ͻʽÿ�.
//

class COPimgaeApp : public CWinApp
{
public:
	COPimgaeApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	void OnFileOpen();
	DECLARE_MESSAGE_MAP()
	
};

extern COPimgaeApp theApp;
