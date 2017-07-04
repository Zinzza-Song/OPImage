
// OPimgaeDoc.cpp : COPimgaeDoc 클래스의 구현
//

#include "stdafx.h"

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OPimgae.h"
#endif
#include "resource.h"
#include "OPimgaeDoc.h"
#include "Gamma.h"
#include "Pixel.h"
#include <propkey.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COPimgaeDoc

IMPLEMENT_DYNCREATE(COPimgaeDoc, CDocument)

BEGIN_MESSAGE_MAP(COPimgaeDoc, CDocument)
	ON_COMMAND(Image_reversal, &COPimgaeDoc::OnImageInvert)
	ON_COMMAND(image_BW, &COPimgaeDoc::OnBw)
	ON_COMMAND(image_Noise, &COPimgaeDoc::OnNoise)
	ON_COMMAND(image_Original, &COPimgaeDoc::OnOriginal)
	ON_COMMAND(brightness_add, &COPimgaeDoc::Onadd)
	ON_COMMAND(brightness_remove, &COPimgaeDoc::Onremove)
	ON_COMMAND(image_gmRED, &COPimgaeDoc::Ongmred)
	ON_COMMAND(image_gmBlue, &COPimgaeDoc::Ongmblue)
	ON_COMMAND(image_gmGreen, &COPimgaeDoc::Ongmgreen)
	ON_COMMAND(image_Mirror, &COPimgaeDoc::OnMirror)
	ON_COMMAND(image_Flip, &COPimgaeDoc::OnFlip)
END_MESSAGE_MAP()


// COPimgaeDoc 생성/소멸

COPimgaeDoc::COPimgaeDoc()
{
	

}

COPimgaeDoc::~COPimgaeDoc()
{
}

BOOL COPimgaeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// COPimgaeDoc serialization

void COPimgaeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void COPimgaeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void COPimgaeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void COPimgaeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COPimgaeDoc 진단

#ifdef _DEBUG
void COPimgaeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COPimgaeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COPimgaeDoc 명령


BOOL COPimgaeDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	if (FAILED(m_Image.Load(lpszPathName)))
	{
		
		return FALSE;
	}
	m_Image1.Load(lpszPathName);
	return TRUE;
}


BOOL COPimgaeDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	if (FAILED(m_Image.Save(lpszPathName)))
		return FALSE;


	return TRUE;

	// return CDocument::OnSaveDocument(lpszPathName);
}


void COPimgaeDoc::OnImageInvert() // 이미지 색반전 기능
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{
			pixel[y][x].rgbtBlue = ~pixel[y][x].rgbtBlue;
			pixel[y][x].rgbtGreen = ~pixel[y][x].rgbtGreen;
			pixel[y][x].rgbtRed = ~pixel[y][x].rgbtRed;
		}

	UpdateAllViews(NULL);
}





void COPimgaeDoc::OnBw() // 이미지 흑백 기능
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{
			pixel[y][x].rgbtBlue = (pixel[y][x].rgbtBlue + pixel[y][x].rgbtGreen + pixel[y][x].rgbtRed) / 3;
			pixel[y][x].rgbtGreen = (pixel[y][x].rgbtBlue + pixel[y][x].rgbtGreen + pixel[y][x].rgbtRed) / 3;
			pixel[y][x].rgbtRed = (pixel[y][x].rgbtBlue + pixel[y][x].rgbtGreen + pixel[y][x].rgbtRed) / 3;
		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::OnNoise() // 이미지 노이즈 기능
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{
			if (rand() < 2000)
			{
				pixel[y][x].rgbtBlue = (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | rand() & 0xff;
				pixel[y][x].rgbtGreen = (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | rand() & 0xff;
				pixel[y][x].rgbtRed = (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | rand() & 0xff;
			}
			else
			{
				pixel[y][x].rgbtBlue = pixel[y][x].rgbtBlue;
				pixel[y][x].rgbtGreen = pixel[y][x].rgbtGreen;
				pixel[y][x].rgbtRed = pixel[y][x].rgbtRed;
				

			}

		}

	UpdateAllViews(NULL);
}



void COPimgaeDoc::OnOriginal() // 모든 변환 이전 이미지로 돌아가는 기능(변환 초기화)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	
	CPixel pixel(m_Image);
	CPixel pixel1(m_Image1);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{
			pixel[y][x].rgbtBlue = pixel1[y][x].rgbtBlue;
			pixel[y][x].rgbtGreen = pixel1[y][x].rgbtGreen;
			pixel[y][x].rgbtRed = pixel1[y][x].rgbtRed;
		}

	UpdateAllViews(NULL);
}

void COPimgaeDoc::Onadd() // 이미지를 밝게하는 기능
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{

			pixel[y][x].rgbtBlue = limit(pixel[y][x].rgbtBlue + 10);
			pixel[y][x].rgbtGreen = limit(pixel[y][x].rgbtGreen + 10);
			pixel[y][x].rgbtRed = limit(pixel[y][x].rgbtRed + 10);

		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::Onremove() // 이미지를 어둡게 하는 기능
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{

			pixel[y][x].rgbtBlue = limit(pixel[y][x].rgbtBlue - 10);
			pixel[y][x].rgbtGreen = limit(pixel[y][x].rgbtGreen - 10);
			pixel[y][x].rgbtRed = limit(pixel[y][x].rgbtRed - 10);

		}

	UpdateAllViews(NULL);
}



void COPimgaeDoc::Ongmred() // 빨간색 계열로 감마 보정
{
	float inv_gamma = 1.f / 2.1;
	float gamma_table[256];
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma);
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{

			pixel[y][x].rgbtBlue = pixel[y][x].rgbtBlue;
			pixel[y][x].rgbtGreen = pixel[y][x].rgbtGreen;
			pixel[y][x].rgbtRed = static_cast<BYTE>(limit(gamma_table[pixel[y][x].rgbtRed] * 255 + 0.5f));

		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::Ongmblue() // 파란색 계열로 감마 보정
{
	float inv_gamma = 1.f / 2.1;
	float gamma_table[256];
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma);
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{

			pixel[y][x].rgbtBlue = static_cast<BYTE>(limit(gamma_table[pixel[y][x].rgbtBlue] * 255 + 0.5f));
			pixel[y][x].rgbtGreen = pixel[y][x].rgbtGreen;
			pixel[y][x].rgbtRed = pixel[y][x].rgbtRed;

		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::Ongmgreen() // 초록색 계열로 감마 보정
{
	float inv_gamma = 1.f / 2.1;
	float gamma_table[256];
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma);
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth; ++x)
		{

			pixel[y][x].rgbtBlue = pixel[y][x].rgbtBlue;
			pixel[y][x].rgbtGreen = static_cast<BYTE>(limit(gamma_table[pixel[y][x].rgbtGreen] * 255 + 0.5f));
			pixel[y][x].rgbtRed = pixel[y][x].rgbtRed;

		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::OnMirror() // 이미지 좌우 대칭
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	CPixel pixel(m_Image);
	
	for (int y = 0; y < nHeight; ++y)
		for (int x = 0; x < nWidth/2; ++x)
		{
			int temp, temp1, temp2;

			temp = pixel[y][x].rgbtBlue;
			temp1 = pixel[y][x].rgbtGreen;
			temp2 = pixel[y][x].rgbtRed;

			pixel[y][x].rgbtBlue = pixel[y][nWidth-1-x].rgbtBlue;
			pixel[y][x].rgbtGreen = pixel[y][nWidth-1-x].rgbtGreen;
			pixel[y][x].rgbtRed = pixel[y][nWidth-1-x].rgbtRed;

			pixel[y][nWidth-1 - x].rgbtBlue = temp;
			pixel[y][nWidth-1 - x].rgbtGreen = temp1;
			pixel[y][nWidth-1 - x].rgbtRed = temp2;

		}

	UpdateAllViews(NULL);
}


void COPimgaeDoc::OnFlip() // 이미지 상하 대칭
{

	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	CPixel pixel(m_Image);

	for (int y = 0; y < nHeight/2; ++y)
		for (int x = 0; x < nWidth; ++x)
		{
			int temp, temp1, temp2;

			temp = pixel[y][x].rgbtBlue;
			temp1 = pixel[y][x].rgbtGreen;
			temp2 = pixel[y][x].rgbtRed;

			pixel[y][x].rgbtBlue = pixel[nHeight-1-y][x].rgbtBlue;
			pixel[y][x].rgbtGreen = pixel[nHeight - 1 - y][x].rgbtGreen;
			pixel[y][x].rgbtRed = pixel[nHeight - 1 - y][x].rgbtRed;

			pixel[nHeight - 1 - y][x].rgbtBlue = temp;
			pixel[nHeight - 1 - y][x].rgbtGreen = temp1;
			pixel[nHeight - 1 - y][x].rgbtRed = temp2;

		}

	UpdateAllViews(NULL);
}
