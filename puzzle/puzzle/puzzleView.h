
// puzzleView.h : CpuzzleView 클래스의 인터페이스
//

#pragma once
#include "DialogN.h"

class CpuzzleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CpuzzleView();
	DECLARE_DYNCREATE(CpuzzleView)

// 특성입니다.
public:
	CpuzzleDoc* GetDocument() const;

// 작업입니다.
public:
	bool bInit;
	bool bInit2;
	int MAXTILE;
	CDialogN* pDlg;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:

	void Init(CDC &dc);
	virtual ~CpuzzleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnPuzzleN();
	afx_msg void OnPuzzleNewgame();
	afx_msg void OnIddDialog1();
};

#ifndef _DEBUG  // puzzleView.cpp의 디버그 버전
inline CpuzzleDoc* CpuzzleView::GetDocument() const
   { return reinterpret_cast<CpuzzleDoc*>(m_pDocument); }
#endif


