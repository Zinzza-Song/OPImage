#pragma once


// CGamma ��ȭ �����Դϴ�.

class CGamma : public CDialogEx
{
	DECLARE_DYNAMIC(CGamma)

public:
	CGamma(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGamma();
	CFont m_font;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Gamma };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	double scroll_val;
};
