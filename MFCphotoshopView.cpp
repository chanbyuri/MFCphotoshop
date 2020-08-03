
// MFCphotoshopView.cpp: CMFCphotoshopView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCphotoshop.h"
#endif

#include "MFCphotoshopDoc.h"
#include "MFCphotoshopView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCphotoshopView

IMPLEMENT_DYNCREATE(CMFCphotoshopView, CView)

BEGIN_MESSAGE_MAP(CMFCphotoshopView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EQUAL_IMAGE, &CMFCphotoshopView::OnEqualImage)
	ON_COMMAND(ID_NEGATIVE_IMAGE, &CMFCphotoshopView::OnNegativeImage)
	ON_COMMAND(ID_ADD_IMAGE, &CMFCphotoshopView::OnAddImage)
	ON_COMMAND(ID_SUB_IMAGE, &CMFCphotoshopView::OnSubImage)
	ON_COMMAND(ID_MUL_IMAGE, &CMFCphotoshopView::OnMulImage)
	ON_COMMAND(ID_DIV_IMAGE, &CMFCphotoshopView::OnDivImage)
	ON_COMMAND(ID_AND_IMAGE, &CMFCphotoshopView::OnAndImage)
	ON_COMMAND(ID_OR_IMAGE, &CMFCphotoshopView::OnOrImage)
	ON_COMMAND(ID_XOR_IMAGE, &CMFCphotoshopView::OnXorImage)
	ON_COMMAND(ID_GAMMA_IMAGE, &CMFCphotoshopView::OnGammaImage)
	ON_COMMAND(ID_BINARY_IMAGE, &CMFCphotoshopView::OnBinaryImage)
	ON_COMMAND(ID_AVERAGE_BINARY_IMAGE, &CMFCphotoshopView::OnAverageBinaryImage)
	ON_COMMAND(ID_TRANSLATION, &CMFCphotoshopView::OnTranslation)
	ON_COMMAND(ID_ZOOM_IN, &CMFCphotoshopView::OnZoomIn)
END_MESSAGE_MAP()

// CMFCphotoshopView 생성/소멸

CMFCphotoshopView::CMFCphotoshopView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCphotoshopView::~CMFCphotoshopView()
{
}

BOOL CMFCphotoshopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCphotoshopView 그리기

void CMFCphotoshopView::OnDraw(CDC* pDC)
{
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	unsigned char R, G, B;
	for (int i = 0; i < pDoc->m_height; i++)
		for (int k = 0; k < pDoc->m_width; k++) {
			R = G = B = pDoc->m_InputImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}

	for (int i = 0; i < pDoc->m_Re_height; i++)
		for (int k = 0; k < pDoc->m_Re_width; k++) {
			R = G = B = pDoc->m_OutputImage[i][k];
			pDC->SetPixel(k + 5 + pDoc->m_height + 5, i + 5, RGB(R, G, B));
		}

}


// CMFCphotoshopView 인쇄

BOOL CMFCphotoshopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCphotoshopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCphotoshopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCphotoshopView 진단

#ifdef _DEBUG
void CMFCphotoshopView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCphotoshopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCphotoshopDoc* CMFCphotoshopView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCphotoshopDoc)));
	return (CMFCphotoshopDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCphotoshopView 메시지 처리기


void CMFCphotoshopView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CMFCphotoshopView::OnNegativeImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegativeImage();
	Invalidate(TRUE);
}


void CMFCphotoshopView::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CMFCphotoshopView::OnSubImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSubImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnMulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMulImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnDivImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDivImage();
	Invalidate(TRUE);
}


void CMFCphotoshopView::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAndImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnOrImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnXorImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGammaImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnBinaryImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBinaryImage();
	Invalidate(TRUE);
}


void CMFCphotoshopView::OnAverageBinaryImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAverageBinaryImage();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnTranslation();
	Invalidate(TRUE);
}

void CMFCphotoshopView::OnZoomIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCphotoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZoomIn();
	Invalidate(TRUE);
}
