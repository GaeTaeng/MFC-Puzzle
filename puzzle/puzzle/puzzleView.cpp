
// puzzleView.cpp : CpuzzleView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "puzzle.h"
#endif
#include "DialogN.h"
#include "puzzleDoc.h"
#include "puzzleView.h"
#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpuzzleView

IMPLEMENT_DYNCREATE(CpuzzleView, CView)

	BEGIN_MESSAGE_MAP(CpuzzleView, CView)
		// 표준 인쇄 명령입니다.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_LBUTTONDOWN()
		ON_COMMAND(ID_PUZZLE_NEWGAME, &CpuzzleView::OnPuzzleNewgame)
		ON_COMMAND(ID_PUZZLE_N, &CpuzzleView::OnIddDialog1)
	END_MESSAGE_MAP()


	// CpuzzleView 생성/소멸

	class CTile;

	CpuzzleView::CpuzzleView()
	{
		MAXTILE=4;
		srand(time(NULL));
		// TODO: 여기에 생성 코드를 추가합니다.
	}

	CpuzzleView::~CpuzzleView()
	{
	}

	BOOL CpuzzleView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CpuzzleView 그리기
	void CpuzzleView::Init(CDC &dc) {


		CpuzzleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->iCount = 0;
		pDoc->m_Tile.clear();

		if(bInit2) {
			pDoc->memDC.CreateCompatibleDC(&dc);

			pDoc->m_BitMap = (HBITMAP)LoadImage(NULL, L"../Texture/Image.bmp", IMAGE_BITMAP, 
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			pDoc->memDC.SelectObject(pDoc->m_BitMap);
			bInit2 = false;
		}
		for(int i = 0; i < MAXTILE*MAXTILE; i++) {
			pDoc->iNum[i] = i;
		}

		//퍼즐 조각조각을 랜덤위치로 이동
		//조립 불가능의 경우가 생김
		/*
		for(int i = 0; i < 100; i++) {
		int n = rand()%(MAXTILE*MAXTILE);
		int m = rand()%(MAXTILE*MAXTILE);
		int tmp = pDoc->iNum[m];
		pDoc->iNum[m] = pDoc->iNum[n];
		pDoc->iNum[n] = tmp;
		}
		*/

		// 흰칸을 4방향 랜덤으로 이동시킴으로 실제 게임을 섞는 모습을 구현
		// 조립 불가능의 경우가 존재하지 않음.
		// 추가적으로 방향을 스택에 담아서 되돌아가는 모습을 보일 수 있음.
		
		int iWhitePos = 0; // 흰칸 위치
		for(int i = 0; i < 20000; i++) {
			int n = rand()%4;
			//0 위로 1 아래 2 왼쪽 3 오른쪽
			switch(n) {
			case 0: {//위
				if(iWhitePos < MAXTILE ) {
					i--;
					break;
				}
				int iTmp = pDoc->iNum[iWhitePos];
				pDoc->iNum[iWhitePos] = pDoc->iNum[iWhitePos-MAXTILE];
				pDoc->iNum[iWhitePos-MAXTILE] = iTmp;
				iWhitePos -= MAXTILE;
				break;
					}
			case 1: {//아래
				if(iWhitePos > MAXTILE &&MAXTILE*MAXTILE - iWhitePos <= MAXTILE ) {
					i--;
					break;
				}

				int iTmp = pDoc->iNum[iWhitePos];
				pDoc->iNum[iWhitePos] = pDoc->iNum[iWhitePos+MAXTILE];
				pDoc->iNum[iWhitePos+MAXTILE] = iTmp;
				iWhitePos+=MAXTILE;
				break;

				break;
					}
			case 2:{//좌
				if((!iWhitePos) || iWhitePos%MAXTILE == 0) {
					i--;
					break;
				}

				int iTmp = pDoc->iNum[iWhitePos];
				pDoc->iNum[iWhitePos] = pDoc->iNum[iWhitePos-1];
				pDoc->iNum[iWhitePos-1] = iTmp;
				iWhitePos--;
				break;
				   }
			case 3: {//우
				if(iWhitePos && MAXTILE*(iWhitePos/MAXTILE+1) - iWhitePos ==  1) {
					i--;
					break;
				}

				int iTmp = pDoc->iNum[iWhitePos];
				pDoc->iNum[iWhitePos] = pDoc->iNum[iWhitePos+1];
				pDoc->iNum[iWhitePos+1] = iTmp;
				iWhitePos++;
				break;
					}
			}
		}
		for(int i = 0; i < MAXTILE; i ++) {
			for(int j = 0; j < MAXTILE; j++) {
				pDoc->m_Tile.push_back(new CTile(pDoc->iNum[i*MAXTILE+j], j, i, 864/MAXTILE, 600/MAXTILE, 576/MAXTILE, 400/MAXTILE));
				pDoc->pos[i*MAXTILE+j] = CPoint(j,i);
			}
		}



		bInit = false;
		Invalidate();
	}
	void CpuzzleView::OnDraw(CDC* pDC)
	{
		if(bInit) Init(*pDC);
		CpuzzleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		CRect rect;
		GetClientRect(&rect);
		pDC->FillSolidRect(rect,RGB(100,100,150));
		// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

		CPen pen(PS_SOLID,3,RGB(0,0,0));
		CPen* oldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(18,18,886,622);
		for(int i = 0; i < MAXTILE; i ++) {
			for(int j = 0; j < MAXTILE; j++) {
				(pDoc->m_Tile[i*MAXTILE+j])->TileDraw(pDC,&(pDoc->memDC), pDoc);
			}

		}
		pDC->Rectangle(998,28,1290,232);
		pDC->SelectObject(oldPen);
		CString str;
		str.Format(_T("이동 횟수 :: %d"), pDoc->iCount);
		pDC->TextOutW(1000,400,str);

		//hint!!
		pDC->TransparentBlt(1000,30,288,200,&(pDoc->memDC),0,0,577,400,SRCCOPY);
		pDC->Rectangle(1000,30,1000+288/MAXTILE,30+200/MAXTILE);

	}


	// CpuzzleView 인쇄

	BOOL CpuzzleView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CpuzzleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CpuzzleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// CpuzzleView 진단

#ifdef _DEBUG
	void CpuzzleView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CpuzzleView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CpuzzleDoc* CpuzzleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpuzzleDoc)));
		return (CpuzzleDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CpuzzleView 메시지 처리기


	void CpuzzleView::OnLButtonDown(UINT nFlags, CPoint point)
	{

		CpuzzleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		bool bCheck ;
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		for(int i = 0; i < MAXTILE; i ++) {
			for(int j = 0; j < MAXTILE; j++) {
				bCheck = (pDoc->m_Tile[i*MAXTILE+j])->colli(point);

				if(bCheck) {
					if((i-1)*MAXTILE+j >= 0 && (pDoc->m_Tile[(i-1)*MAXTILE+j])->iNum == 0) {
						int tmp = ((pDoc->m_Tile[(i-1)*MAXTILE+j])->iNum);
						((pDoc->m_Tile[(i-1)*MAXTILE+j])->iNum) = ((pDoc->m_Tile[i*MAXTILE+j])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j])->iNum) = tmp;
						pDoc->iCount++;
						Invalidate();
						return;
					}else if(i*MAXTILE+j+1 < (MAXTILE*MAXTILE) && (pDoc->m_Tile[i*MAXTILE+j+1])->iNum == 0) {
						int tmp = ((pDoc->m_Tile[i*MAXTILE+j+1])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j+1])->iNum) = ((pDoc->m_Tile[i*MAXTILE+j])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j])->iNum) = tmp;
						pDoc->iCount++;
						Invalidate();
						return;
					}else if(i*MAXTILE+j-1 >= 0 && (pDoc->m_Tile[i*MAXTILE+j-1])->iNum == 0) {
						int tmp = ((pDoc->m_Tile[i*MAXTILE+j-1])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j-1])->iNum) = ((pDoc->m_Tile[i*MAXTILE+j])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j])->iNum) = tmp;
						pDoc->iCount++;
						Invalidate();
						return;
					}else if( ((i+1)*MAXTILE+j<(MAXTILE*MAXTILE)) && (pDoc->m_Tile[(i+1)*MAXTILE+j])->iNum == 0) {

						int tmp = ((pDoc->m_Tile[(i+1)*MAXTILE+j])->iNum);
						((pDoc->m_Tile[(i+1)*MAXTILE+j])->iNum) = ((pDoc->m_Tile[i*MAXTILE+j])->iNum);
						((pDoc->m_Tile[i*MAXTILE+j])->iNum) = tmp;
						pDoc->iCount++;
						Invalidate();
						return;

					}
					bCheck = false;
					break;
				}

			}

		}

		int a;
		a = 3;
		CView::OnLButtonDown(nFlags, point);
	}


	//void CpuzzleView::OnPuzzleN()
	//{
	//	pDlg = new CDialogN();
	//	pDlg->DoModal();
	//	
	//	MAXTILE = pDlg->N;
	//	bInit = true;
	//	Invalidate();
	//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//}




	void CpuzzleView::OnPuzzleNewgame()
	{
		bInit = true;
		Invalidate();
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	}


	void CpuzzleView::OnIddDialog1()
	{

		// TODO: 여기에 명령 처리기 코드를 추가합니다.

		CDialogN dlg;

		UINT ans = dlg.DoModal();
		if(ans==IDOK){
			MAXTILE = dlg.N;

			bInit = true;


			Invalidate();
		}
	}
