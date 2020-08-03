#pragma once


// CZoomRotate 대화 상자

class CZoomRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CZoomRotate)

public:
	CZoomRotate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoomRotate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOM_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_zvalue;
	double m_rotatevalue;
};
