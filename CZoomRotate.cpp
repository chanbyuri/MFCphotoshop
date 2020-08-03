// CZoomRotate.cpp: 구현 파일
//

#include "pch.h"
#include "MFCphotoshop.h"
#include "CZoomRotate.h"
#include "afxdialogex.h"


// CZoomRotate 대화 상자

IMPLEMENT_DYNAMIC(CZoomRotate, CDialogEx)

CZoomRotate::CZoomRotate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOM_ROTATE, pParent)
	, m_zvalue(0)
	, m_rotatevalue(0)
{

}

CZoomRotate::~CZoomRotate()
{
}

void CZoomRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZOOM, m_zvalue);
	DDX_Text(pDX, IDC_ROTATE, m_rotatevalue);
}


BEGIN_MESSAGE_MAP(CZoomRotate, CDialogEx)
END_MESSAGE_MAP()


// CZoomRotate 메시지 처리기
