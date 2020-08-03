// CXYDIALOG.cpp: 구현 파일
//

#include "pch.h"
#include "MFCphotoshop.h"
#include "CXYDIALOG.h"
#include "afxdialogex.h"


// CXYDIALOG 대화 상자

IMPLEMENT_DYNAMIC(CXYDIALOG, CDialog)

CXYDIALOG::CXYDIALOG(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_XYDIALOG, pParent)
	, m_xvalue(0)
	, m_yvalue(0)
{

}

CXYDIALOG::~CXYDIALOG()
{
}

void CXYDIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X_VALUE, m_xvalue);
	DDX_Text(pDX, IDC_Y_VALUE, m_yvalue);
}


BEGIN_MESSAGE_MAP(CXYDIALOG, CDialog)
END_MESSAGE_MAP()


// CXYDIALOG 메시지 처리기
