
// OPimgaeView.h : COPimgaeView Ŭ������ �������̽�
//

#pragma once


class COPimgaeView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	COPimgaeView();
	DECLARE_DYNCREATE(COPimgaeView)

// Ư���Դϴ�.
public:
	int m_nMagnify;
	COPimgaeDoc* GetDocument() const;
	void ResizeView();

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~COPimgaeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizeOriginalsize();
	afx_msg void OnSizeZoomsize();
	afx_msg void OnSizeZoomoutsize();
	afx_msg void OnBnClickedOk();
};

#ifndef _DEBUG  // OPimgaeView.cpp�� ����� ����
inline COPimgaeDoc* COPimgaeView::GetDocument() const
   { return reinterpret_cast<COPimgaeDoc*>(m_pDocument); }
#endif

