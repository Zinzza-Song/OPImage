#pragma once


// CSplash ��ȭ �����Դϴ�.

class CSplash : public CDialogEx
{
	DECLARE_DYNAMIC(CSplash)

public:
	CSplash(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSplash();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
