#pragma once


// CGamma 대화 상자입니다.

class CGamma : public CDialogEx
{
	DECLARE_DYNAMIC(CGamma)

public:
	CGamma(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGamma();
	CFont m_font;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Gamma };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	double scroll_val;
};
