#pragma once


// CDialogN ��ȭ �����Դϴ�.

class CDialogN : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogN)
public:
public:
	CDialogN(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogN();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
//	int N;
//	int N;
//	int N;
	int N;
};
