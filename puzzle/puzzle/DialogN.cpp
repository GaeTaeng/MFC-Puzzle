// DialogN.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "puzzle.h"
#include "DialogN.h"
#include "afxdialogex.h"


// CDialogN ��ȭ �����Դϴ�.

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


// CDialogN �޽��� ó�����Դϴ�.


void CDialogN::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	UpdateData(true);
	CDialogEx::OnOK();
}
