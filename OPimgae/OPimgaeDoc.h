
// OPimgaeDoc.h : COPimgaeDoc 클래스의 인터페이스
//


#pragma once
#include "Pixel.h"

class COPimgaeDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	COPimgaeDoc();
	DECLARE_DYNCREATE(COPimgaeDoc)

// 특성입니다.
public: // 이미지를 담을 변수
	CImage m_Image;
	CImage m_Image1;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~COPimgaeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public: // 기능을 나타내는 함수 선언
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
