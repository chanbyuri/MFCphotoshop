
// MFCphotoshopDoc.h: CMFCphotoshopDoc 클래스의 인터페이스
//


#pragma once


class CMFCphotoshopDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCphotoshopDoc() noexcept;
	DECLARE_DYNCREATE(CMFCphotoshopDoc)

// 특성입니다.
public:

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
	virtual ~CMFCphotoshopDoc();
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
public:
	unsigned char**m_InputImage = NULL;
	unsigned char**m_OutputImage = NULL;
	int m_height;
	int m_width;
	int m_Re_height;
	int m_Re_width;
	int m_old_height;
	int m_old_width;
	int m_old_Re_height;
	int m_old_Re_width;
	unsigned char** malloc2D(int h, int w);
	void freeInputImage(int h);
	void freeOutputImage(int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnNegativeImage();
	void OnAddImage();
	void OnSubImage();
	void OnMulImage();
	void OnDivImage();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
	void OnGammaImage();
	void OnBinaryImage();
	void OnAverageBinaryImage();
	void OnTranslation();
	void OnZoomIn();
	void Recur(int s, int x, int y);
	void OnZoomOut();
	void OnMirrorLR();
	void OnMirrorUD();
	void OnMirror();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
