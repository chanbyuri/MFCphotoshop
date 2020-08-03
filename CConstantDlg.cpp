// CConstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCphotoshop.h"
#include "CConstantDlg.h"
#include "afxdialogex.h"


// CConstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDlg, CDialog)

CConstantDlg::CConstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT1, pParent)
	, m_value1(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialog)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기
