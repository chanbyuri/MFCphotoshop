﻿
// MFCphotoshopDoc.cpp: CMFCphotoshopDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCphotoshop.h"
#endif

#include "MFCphotoshopDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCphotoshopDoc

IMPLEMENT_DYNCREATE(CMFCphotoshopDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCphotoshopDoc, CDocument)
END_MESSAGE_MAP()


// CMFCphotoshopDoc 생성/소멸

CMFCphotoshopDoc::CMFCphotoshopDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCphotoshopDoc::~CMFCphotoshopDoc()
{
}

BOOL CMFCphotoshopDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCphotoshopDoc serialization

void CMFCphotoshopDoc::Serialize(CArchive& ar)
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
void CMFCphotoshopDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCphotoshopDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCphotoshopDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCphotoshopDoc 진단

#ifdef _DEBUG
void CMFCphotoshopDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCphotoshopDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCphotoshopDoc 명령


unsigned char** CMFCphotoshopDoc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char **p;
	p = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		p[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	return p;
}


void CMFCphotoshopDoc::freeInputImage(int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage != NULL) {
		for (int i = 0; i < h; i++)
			free(m_InputImage[i]);
		free(m_InputImage);
	}
	m_InputImage = NULL;
}

void CMFCphotoshopDoc::freeOutputImage(int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_OutputImage != NULL) {
		for (int i = 0; i < h; i++)
			free(m_OutputImage[i]);
		free(m_OutputImage);
	}
	m_OutputImage = NULL;
}

BOOL CMFCphotoshopDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	long fsize = (long)File.GetLength();
	//기존 메모리 해제
	freeInputImage(m_old_height);

	//핵심 코드
	m_height = m_width = (int)sqrt((double)fsize);
	m_old_height = m_height;
	m_old_width = m_width;

	//메모리 할당
	m_InputImage = malloc2D(m_height, m_width);

	//파일 --> 입력 메모리
	for (int i = 0; i < m_height; i++)
		File.Read(m_InputImage[i], m_width);

	File.Close();

	return TRUE;
}

void CMFCphotoshopDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	freeInputImage(m_height);
	freeOutputImage(m_Re_height);
	CDocument::OnCloseDocument();
}


void CMFCphotoshopDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			m_OutputImage[i][k] = m_InputImage[i][k];
		}
	}

}


void CMFCphotoshopDoc::OnNegativeImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			m_OutputImage[i][k] = 255 - m_InputImage[i][k];
		}
	}
}
#include "CConstantDlg.h"
void CMFCphotoshopDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	int value = (int)dlg.m_value1;
	int s;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			s = m_InputImage[i][k] + value;
			if (s > 255) m_OutputImage[i][k] = 255;
			else if (s < 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = s;
		}
	}
}

void CMFCphotoshopDoc::OnSubImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	int value = (int)dlg.m_value1;
	int s;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			s = m_InputImage[i][k] - value;
			if (s > 255) m_OutputImage[i][k] = 255;
			else if (s < 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = s;
		}
	}
}


void CMFCphotoshopDoc::OnMulImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	double value = dlg.m_value1;
	int s;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			s = m_InputImage[i][k] * value;
			if (s > 255) m_OutputImage[i][k] = 255;
			else if (s < 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = s;
		}
	}
}


void CMFCphotoshopDoc::OnDivImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	double value = dlg.m_value1;
	int s;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			s = m_InputImage[i][k] / value;
			if (s > 255) m_OutputImage[i][k] = 255;
			else if (s < 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = s;
		}
	}
}


void CMFCphotoshopDoc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	unsigned char **t = malloc2D(m_Re_height, m_Re_width);
	FILE *rfp;
	rfp = fopen("C:/Images/Etc_Raw(squre)/circle512.raw", "rb");
	//if (rfp == NULL) exit(-1);

	for (int i = 0; i < m_Re_height; i++)
		fread(t[i], sizeof(unsigned char), m_Re_width, rfp);
	fclose(rfp);
	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			m_OutputImage[i][k] = m_InputImage[i][k] & t[i][k];
		}
	}

	for (int i = 0; i < m_Re_height; i++)
		free(t[i]);
	t = NULL;
}

void CMFCphotoshopDoc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	return;
}


void CMFCphotoshopDoc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	return;
}


void CMFCphotoshopDoc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;
	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	// **** 진짜 영상 처리 알고리즘 ***
	int res;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			res = pow(m_InputImage[i][k], 1.0 / dlg.m_value1);

			if (res > 255)
				m_OutputImage[i][k] = 255;
			else if (res < 0)
				m_OutputImage[i][k] = 0;
			else
				m_OutputImage[i][k] = (int)res;
		}
	}
}

void CMFCphotoshopDoc::OnBinaryImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;
	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			if (m_InputImage[i][k] >= 128) m_OutputImage[i][k] = 255;
			else m_OutputImage[i][k] = 0;
		}
	}
}

void CMFCphotoshopDoc::OnAverageBinaryImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;
	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	// **** 진짜 영상 처리 알고리즘 ***
	int sum = 0;
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			sum += m_InputImage[i][k];
		}
	}
	int avr = (float)sum / (m_height*m_width);
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			if (m_InputImage[i][k] >= avr) m_OutputImage[i][k] = 255;
			else m_OutputImage[i][k] = 0;
		}
	}
}
#include "CXYDIALOG.h"
void CMFCphotoshopDoc::OnTranslation()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CXYDIALOG dlg;
	if (dlg.DoModal() != IDOK)
		return;

	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;
	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	// **** 진짜 영상 처리 알고리즘 ***
	int x, y;
	
	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			x = k - dlg.m_xvalue;
			y = i - dlg.m_yvalue;
			if((0 <= x && x< m_width) && (0<=y && y<m_height))
			m_OutputImage[i][k] = m_InputImage[y][x];
		}
	}
}
#include "CZoomRotate.h"
void CMFCphotoshopDoc::OnZoomIn()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CZoomRotate dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 1radian = 180 / pi*degree
	float r = 3.141592 * dlg.m_rotatevalue / 180.0;
	int scale = dlg.m_zvalue;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height * scale;
	m_old_Re_height = m_Re_width = m_width * scale;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);
	unsigned char **OI = malloc2D(m_Re_height, m_Re_width);

	for (int i = 0; i < m_height; i++) {
		for (int k = 0; k < m_width; k++) {
			m_OutputImage[i * scale][k * scale] = m_InputImage[i][k];
		}
	}

	int cx = m_Re_width / 2;
	int cy = m_Re_height / 2;
	int hy = m_Re_height - 1;
	int x, y;
	for (int i = 0; i < m_height - 1; i++) {
		for (int k = 0; k < m_width - 1; k++) {
			x = k * scale; y = i * scale;
			Recur(scale, x, y);
		}
	}
	for (int i = 0; i < m_Re_height; i++)
		for (int k = 0; k < m_Re_width; k++)
			OI[i][k] = m_OutputImage[i][k];
	freeOutputImage(m_Re_height);
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	int new_i, new_k;
	for (int i = 0; i < m_Re_height; i++) {
		for (int k = 0; k < m_Re_width; k++) {
			new_k = cx + (i - cy) * sin(r) + (k - cx) * cos(r);
			new_i = cy + (i - cy) * cos(r) - (k - cx) * sin(r);
			if ((0 <= new_i && new_i < m_Re_height) && (0 <= new_k && new_k < m_Re_width))
				m_OutputImage[i][k] = OI[new_i][new_k];
		}
	}

	for (int i = 0; i < m_Re_height; i++)
		free(OI[i]);
	OI = NULL;
}

void CMFCphotoshopDoc::Recur(int s, int x, int y)
{
	int hs = s / 2;

	m_OutputImage[y][x + hs] = (m_OutputImage[y][x] + m_OutputImage[y][x + s]) / 2;
	m_OutputImage[y + hs][x] = (m_OutputImage[y][x] + m_OutputImage[y + s][x]) / 2;
	m_OutputImage[y + hs][x + hs] = (m_OutputImage[y][x] + m_OutputImage[y + s][x + s]) / 2;
	m_OutputImage[y + hs][x + s] = (m_OutputImage[y][x + s] + m_OutputImage[y + s][x + s]) / 2;
	m_OutputImage[y + s][x + hs] = (m_OutputImage[y + s][x] + m_OutputImage[y + s][x + s]) / 2;

	if (hs > 1) {
		Recur(hs, x, y);
		Recur(hs, x + hs, y);
		Recur(hs, x, y + hs);
		Recur(hs, x + hs, y + hs);
	}
}

void CMFCphotoshopDoc::OnZoomOut()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	int scale = dlg.m_value1;
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height / scale;
	m_old_Re_height = m_Re_width = m_width / scale;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_Re_height; i++) {
		for (int k = 0; k < m_Re_width; k++) {
			m_OutputImage[i][k] = m_InputImage[i*scale][k*scale];
		}
	}
}

void CMFCphotoshopDoc::OnMirrorLR()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_Re_height; i++) {
		for (int k = 0; k < m_Re_width; k++) {
			m_OutputImage[i][k] = m_InputImage[i][m_Re_width-k-1];
		}
	}
}

void CMFCphotoshopDoc::OnMirrorUD()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_Re_height; i++) {
		for (int k = 0; k < m_Re_width; k++) {
			m_OutputImage[i][k] = m_InputImage[m_Re_height-i-1][k];
		}
	}
}

void CMFCphotoshopDoc::OnMirror()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImage == NULL)
		return;
	// *중요* 출력영상의 크기 결정 --> 알고리즘에 따름..
	freeOutputImage(m_old_Re_height);
	m_old_Re_height = m_Re_height = m_height;
	m_old_Re_height = m_Re_width = m_width;

	// 출력 이미지 메모리 할당
	m_OutputImage = malloc2D(m_Re_height, m_Re_width);

	// **** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_Re_height; i++) {
		for (int k = 0; k < m_Re_width; k++) {
			m_OutputImage[i][k] = m_InputImage[m_Re_height - i - 1][m_Re_width - k - 1];
		}
	}
}

BOOL CMFCphotoshopDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_OutputImage == NULL)
		return false;

	CFile File;
	// static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");
	static TCHAR BASED_CODE szFilter[] = _T("RAW 파일(*.RAW) | *.raw |모든파일(*.*)|*.*||");

	CFileDialog SaveDlg(TRUE, _T("*.raw"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_Re_height; i++)
			File.Write(m_OutputImage[i], m_Re_width);
		File.Close();
	}
	return true;
}