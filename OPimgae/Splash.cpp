// Splash.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OPimgae.h"
#include "Splash.h"
#include "afxdialogex.h"
#include "resource.h"


// CSplash 대화 상자입니다.

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


// CSplash 메시지 처리기입니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	EndDialog(0);
	CDialogEx::OnTimer(nIDEvent);
}
