// DialogN.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "puzzle.h"
#include "DialogN.h"
#include "afxdialogex.h"


// CDialogN 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogN, CDialogEx)

CDialogN::CDialogN(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogN::IDD, pParent)
	, N(0)
{

}

CDialogN::~CDialogN()
{
}

void CDialogN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_N, N);
	DDV_MinMaxInt(pDX, N, 1, 20);
}


BEGIN_MESSAGE_MAP(CDialogN, CDialogEx)
END_MESSAGE_MAP()


// CDialogN 메시지 처리기입니다.


void CDialogN::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	UpdateData(true);
	CDialogEx::OnOK();
}
