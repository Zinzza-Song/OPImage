
// OPimgaeDoc.h : COPimgaeDoc Ŭ������ �������̽�
//


#pragma once
#include "Pixel.h"

class COPimgaeDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	COPimgaeDoc();
	DECLARE_DYNCREATE(COPimgaeDoc)

// Ư���Դϴ�.
public: // �̹����� ���� ����
	CImage m_Image;
	CImage m_Image1;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~COPimgaeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public: // ����� ��Ÿ���� �Լ� ����
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnImageInvert();
	afx_msg void OnBw();
	afx_msg void OnNoise();
	afx_msg void OnOriginal();
	afx_msg void Onadd();
	afx_msg void Onremove();

	template<typename T>
	inline T limit(const T& value)
	{
		return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
	}

	afx_msg void Ongmred();
	afx_msg void Ongmblue();
	afx_msg void Ongmgreen();
	afx_msg void OnMirror();
	afx_msg void OnFlip();
};
