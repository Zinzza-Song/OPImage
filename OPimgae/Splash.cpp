// Splash.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OPimgae.h"
#include "Splash.h"
#include "afxdialogex.h"
#include "resource.h"


// CSplash ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSplash, CDialogEx)

CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CSplash::~CSplash()
{
}

void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplash, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSplash �޽��� ó�����Դϴ�.
BOOL CSplash::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	SetTimer(0, 2000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSplash::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	EndDialog(0);
	CDialogEx::OnTimer(nIDEvent);
}
