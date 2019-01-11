#pragma once


// CDialogN 대화 상자입니다.

class CDialogN : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogN)
public:
public:
	CDialogN(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogN();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
//	int N;
//	int N;
//	int N;
	int N;
};
