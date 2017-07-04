// Gamma.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OPimgae.h"
#include "Gamma.h"
#include "afxdialogex.h"


// CGamma ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGamma, CDialogEx)

CGamma::CGamma(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Gamma, pParent)
{

}

CGamma::~CGamma()
{
}

void CGamma::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGamma, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CGamma �޽��� ó�����Դϴ�.




BOOL CGamma::OnInitDialog()
{
	scroll_val = 0;

	CScrollBar *pScroll;
	pScroll = (CScrollBar *)GetDlgItem(IDC_SCROLLBAR2);
	pScroll->SetScrollRange(0, 100);
	pScroll->SetScrollPos(0);

	SetDlgItemInt(IDC_EDIT1, scroll_val);



	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CGamma::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

	switch (nSBCode)
	{
	case SB_LINELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 1);
		break;
	case SB_LINERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 1);
		break;
	case SB_PAGELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 30);
		break;
	case SB_PAGERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 30);
		break;
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
	}
	scroll_val = pScrollBar->GetScrollPos();
	SetDlgItemInt(IDC_EDIT1, scroll_val);
}