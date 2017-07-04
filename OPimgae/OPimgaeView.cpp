
// OPimgaeView.cpp : COPimgaeView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_SIZE_ORIGINALSIZE, &COPimgaeView::OnSizeOriginalsize)
	ON_COMMAND(ID_SIZE_ZOOMSIZE, &COPimgaeView::OnSizeZoomsize)
	ON_COMMAND(ID_SIZE_ZOOMOUTSIZE, &COPimgaeView::OnSizeZoomoutsize)
	ON_BN_CLICKED(IDOK, &COPimgaeView::OnBnClickedOk)
END_MESSAGE_MAP()

// COPimgaeView ����/�Ҹ�

COPimgaeView::COPimgaeView()
	: m_nMagnify(1)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

COPimgaeView::~COPimgaeView()
{
}

BOOL COPimgaeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// COPimgaeView �׸���

void COPimgaeView::OnDraw(CDC* pDC) // �̹����� �׷���
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


// COPimgaeView �μ�

BOOL COPimgaeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void COPimgaeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void COPimgaeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// COPimgaeView ����

#ifdef _DEBUG
void COPimgaeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COPimgaeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COPimgaeDoc* COPimgaeView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPimgaeDoc)));
	return (COPimgaeDoc*)m_pDocument;
}
#endif //_DEBUG


// COPimgaeView �޽��� ó����


void COPimgaeView::OnSizeOriginalsize() // ���� ������ ũ��� ����
{
	m_nMagnify = 1;
	ResizeView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void COPimgaeView::OnSizeZoomsize() // ������ Ȯ��
{
	++m_nMagnify;
	ResizeView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void COPimgaeView::OnSizeZoomoutsize() // ������ ���
{
	--m_nMagnify;
	ResizeView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
void COPimgaeView::ResizeView(void) // ������ ����� ���⼭ ������
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}
