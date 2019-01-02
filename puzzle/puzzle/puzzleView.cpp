
// puzzleView.cpp : CpuzzleView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
		// ǥ�� �μ� ����Դϴ�.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_LBUTTONDOWN()
		ON_COMMAND(ID_PUZZLE_NEWGAME, &CpuzzleView::OnPuzzleNewgame)
		ON_COMMAND(ID_PUZZLE_N, &CpuzzleView::OnIddDialog1)
	END_MESSAGE_MAP()


	// CpuzzleView ����/�Ҹ�

	class CTile;

	CpuzzleView::CpuzzleView()
	{
		MAXTILE=4;
		srand(time(NULL));
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}

	CpuzzleView::~CpuzzleView()
	{
	}

	BOOL CpuzzleView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
		//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

		return CView::PreCreateWindow(cs);
	}

	// CpuzzleView �׸���
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

		//���� ���������� ������ġ�� �̵�
		//���� �Ұ����� ��찡 ����
		/*
		for(int i = 0; i < 100; i++) {
		int n = rand()%(MAXTILE*MAXTILE);
		int m = rand()%(MAXTILE*MAXTILE);
		int tmp = pDoc->iNum[m];
		pDoc->iNum[m] = pDoc->iNum[n];
		pDoc->iNum[n] = tmp;
		}
		*/

		// ��ĭ�� 4���� �������� �̵���Ŵ���� ���� ������ ���� ����� ����
		// ���� �Ұ����� ��찡 �������� ����.
		// �߰������� ������ ���ÿ� ��Ƽ� �ǵ��ư��� ����� ���� �� ����.
		
		int iWhitePos = 0; // ��ĭ ��ġ
		for(int i = 0; i < 20000; i++) {
			int n = rand()%4;
			//0 ���� 1 �Ʒ� 2 ���� 3 ������
			switch(n) {
			case 0: {//��
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
			case 1: {//�Ʒ�
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
			case 2:{//��
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
			case 3: {//��
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
		// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

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
		str.Format(_T("�̵� Ƚ�� :: %d"), pDoc->iCount);
		pDC->TextOutW(1000,400,str);

		//hint!!
		pDC->TransparentBlt(1000,30,288,200,&(pDoc->memDC),0,0,577,400,SRCCOPY);
		pDC->Rectangle(1000,30,1000+288/MAXTILE,30+200/MAXTILE);

	}


	// CpuzzleView �μ�

	BOOL CpuzzleView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// �⺻���� �غ�
		return DoPreparePrinting(pInfo);
	}

	void CpuzzleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	}

	void CpuzzleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
	}


	// CpuzzleView ����

#ifdef _DEBUG
	void CpuzzleView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CpuzzleView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CpuzzleDoc* CpuzzleView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpuzzleDoc)));
		return (CpuzzleDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CpuzzleView �޽��� ó����


	void CpuzzleView::OnLButtonDown(UINT nFlags, CPoint point)
	{

		CpuzzleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		bool bCheck ;
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//}




	void CpuzzleView::OnPuzzleNewgame()
	{
		bInit = true;
		Invalidate();
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	}


	void CpuzzleView::OnIddDialog1()
	{

		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

		CDialogN dlg;

		UINT ans = dlg.DoModal();
		if(ans==IDOK){
			MAXTILE = dlg.N;

			bInit = true;


			Invalidate();
		}
	}
