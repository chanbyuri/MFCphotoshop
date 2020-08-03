
// MFCphotoshopView.h: CMFCphotoshopView 클래스의 인터페이스
//

#pragma once


class CMFCphotoshopView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCphotoshopView() noexcept;
	DECLARE_DYNCREATE(CMFCphotoshopView)

// 특성입니다.
public:
	CMFCphotoshopDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCphotoshopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnNegativeImage();
	afx_msg void OnAddImage();
	afx_msg void OnSubImage();
	afx_msg void OnMulImage();
	afx_msg void OnDivImage();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
	afx_msg void OnGammaImage();
	afx_msg void OnBinaryImage();
	afx_msg void OnAverageBinaryImage();
	afx_msg void OnTranslation();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnMirrorLr();
	afx_msg void OnMirrorUd();
	afx_msg void OnMirror();
};

#ifndef _DEBUG  // MFCphotoshopView.cpp의 디버그 버전
inline CMFCphotoshopDoc* CMFCphotoshopView::GetDocument() const
   { return reinterpret_cast<CMFCphotoshopDoc*>(m_pDocument); }
#endif

