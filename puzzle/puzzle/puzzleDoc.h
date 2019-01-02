
// puzzleDoc.h : CpuzzleDoc Ŭ������ �������̽�
//

#pragma once

#include <vector>
#include "Tile.h"

class CTile;
using namespace std;

class CpuzzleDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CpuzzleDoc();
	DECLARE_DYNCREATE(CpuzzleDoc)

// Ư���Դϴ�.
public:
	int iCount;
	CPoint pos[10000];
	int iNum[10000];
	vector<CTile*> m_Tile;
	HBITMAP m_BitMap;
	CDC memDC;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CpuzzleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
