
// puzzleView.h : CpuzzleView Ŭ������ �������̽�
//

#pragma once
#include "DialogN.h"

class CpuzzleView : public CView
{
protected: // serialization������ ��������ϴ�.
	CpuzzleView();
	DECLARE_DYNCREATE(CpuzzleView)

// Ư���Դϴ�.
public:
	CpuzzleDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	bool bInit;
	bool bInit2;
	int MAXTILE;
	CDialogN* pDlg;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:

	void Init(CDC &dc);
	virtual ~CpuzzleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnPuzzleN();
	afx_msg void OnPuzzleNewgame();
	afx_msg void OnIddDialog1();
};

#ifndef _DEBUG  // puzzleView.cpp�� ����� ����
inline CpuzzleDoc* CpuzzleView::GetDocument() const
   { return reinterpret_cast<CpuzzleDoc*>(m_pDocument); }
#endif


