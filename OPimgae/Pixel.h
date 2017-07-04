#pragma once

#include "stdafx.h"

class CPixel // 불러온 이미지들을 픽셀화
{
public:
	CPixel(CImage &image)
	{
		m_nHeight = image.GetHeight();
		m_ppRow = new RGBTRIPLE*[m_nHeight];
		int nPitch = image.GetPitch();
		BYTE* pRow = (BYTE*)image.GetBits();
		for (int y = 0; y < m_nHeight; ++y)
		{
			m_ppRow[y] = (RGBTRIPLE*)pRow;
			pRow += nPitch;
		}
	}

	virtual ~CPixel()
	{
		delete[] m_ppRow;
	}

	// Access pixel as pixel[y][x]
	RGBTRIPLE* operator [](int index)
	{
		return m_ppRow[index];
	}
	RGBTRIPLE* operator [](LONG index)
	{
		return m_ppRow[index];
	}
	RGBTRIPLE* operator [](LONGLONG index)
	{
		return m_ppRow[index];
	}

private:
	RGBTRIPLE**  m_ppRow;
	int m_nHeight;
	
};