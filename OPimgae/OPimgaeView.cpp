
// OPimgaeView.cpp : COPimgaeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OPimgae.h"
#endif
#include "MainFrm.h"
#include "OPimgaeDoc.h"
#include "OPimgaeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COPimgaeView

IMPLEMENT_DYNCREATE(COPimgaeView, CScrollView)

BEGIN_MESSAGE_MAP(COPimgaeView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_SIZE_ORIGINALSIZE, &COPimgaeView::OnSizeOriginalsize)
	ON_COMMAND(ID_SIZE_ZOOMSIZE, &COPimgaeView::OnSizeZoomsize)
	ON_COMMAND(ID_SIZE_ZOOMOUTSIZE, &COPimgaeView::OnSizeZoomoutsize)
	ON_BN_CLICKED(IDOK, &COPimgaeView::OnBnClickedOk)
END_MESSAGE_MAP()

// COPimgaeView 생성/소멸

COPimgaeView::COPimgaeView()
	: m_nMagnify(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COPimgaeView::~COPimgaeView()
{
}

BOOL COPimgaeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// COPimgaeView 그리기

void COPimgaeView::OnDraw(CDC* pDC) // 이미지를 그려줌
{
	COPimgaeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (!pDoc->m_Image.IsNull())
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		if (m_nMagnify >= 1)
			pDoc->m_Image.Draw(pDC->m_hDC, 0, 0,
				pDoc->m_Image.GetWidth()*m_nMagnify,
				pDoc->m_Image.GetHeight()*m_nMagnify);
		else
			pDoc->m_Image.Draw(pDC->m_hDC, 0, 0,
				pDoc->m_Image.GetWidth() / (2 - m_nMagnify),
				pDoc->m_Image.GetHeight() / (2 - m_nMagnify));

		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CString strImageSize;
		strImageSize.Format(_T("Width = %d, Height = %d"),
			pDoc->m_Image.GetWidth(), pDoc->m_Image.GetHeight());
		pFrame->SetStatusBarText(1, strImageSize);
	}
}

void COPimgaeView::OnInitialUpdate()
{
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	COPimgaeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->m_Image.IsNull())
		sizeTotal = CSize(pDoc->m_Image.GetWidth(), pDoc->m_Image.GetHeight());

	// sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit();
}


// COPimgaeView 인쇄

BOOL COPimgaeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COPimgaeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COPimgaeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// COPimgaeView 진단

#ifdef _DEBUG
void COPimgaeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COPimgaeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COPimgaeDoc* COPimgaeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPimgaeDoc)));
	return (COPimgaeDoc*)m_pDocument;
}
#endif //_DEBUG


// COPimgaeView 메시지 처리기


void COPimgaeView::OnSizeOriginalsize() // 원래 사이즈 크기로 복구
{
	m_nMagnify = 1;
	ResizeView();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void COPimgaeView::OnSizeZoomsize() // 사이즈 확대
{
	++m_nMagnify;
	ResizeView();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void COPimgaeView::OnSizeZoomoutsize() // 사이즈 축소
{
	--m_nMagnify;
	ResizeView();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
void COPimgaeView::ResizeView(void) // 사이즈 변경시 여기서 변경함
{
	COPimgaeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CSize size;
	if (m_nMagnify >= 1)
		size = CSize(pDoc->m_Image.GetWidth()*m_nMagnify,
			pDoc->m_Image.GetHeight()*m_nMagnify);
	else
		size = CSize(pDoc->m_Image.GetWidth() / (2 - m_nMagnify),
			pDoc->m_Image.GetHeight() / (2 - m_nMagnify));

	SetScrollSizes(MM_TEXT, size);
	Invalidate();
}

void COPimgaeView::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}
