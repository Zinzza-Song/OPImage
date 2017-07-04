
// OPimgaeDoc.cpp : COPimgaeDoc Ŭ������ ����
//

#include "stdafx.h"

// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// COPimgaeDoc ����/�Ҹ�

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

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// COPimgaeDoc serialization

void COPimgaeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void COPimgaeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void COPimgaeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// COPimgaeDoc ����

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


// COPimgaeDoc ���


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


void COPimgaeDoc::OnImageInvert() // �̹��� ������ ���
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





void COPimgaeDoc::OnBw() // �̹��� ��� ���
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


void COPimgaeDoc::OnNoise() // �̹��� ������ ���
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



void COPimgaeDoc::OnOriginal() // ��� ��ȯ ���� �̹����� ���ư��� ���(��ȯ �ʱ�ȭ)
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

void COPimgaeDoc::Onadd() // �̹����� ����ϴ� ���
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


void COPimgaeDoc::Onremove() // �̹����� ��Ӱ� �ϴ� ���
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



void COPimgaeDoc::Ongmred() // ������ �迭�� ���� ����
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


void COPimgaeDoc::Ongmblue() // �Ķ��� �迭�� ���� ����
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


void COPimgaeDoc::Ongmgreen() // �ʷϻ� �迭�� ���� ����
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


void COPimgaeDoc::OnMirror() // �̹��� �¿� ��Ī
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


void COPimgaeDoc::OnFlip() // �̹��� ���� ��Ī
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
