
// puzzleDoc.h : CpuzzleDoc 클래스의 인터페이스
//

#pragma once

#include <vector>
#include "Tile.h"

class CTile;
using namespace std;

class CpuzzleDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CpuzzleDoc();
	DECLARE_DYNCREATE(CpuzzleDoc)

// 특성입니다.
public:
	int iCount;
	CPoint pos[10000];
	int iNum[10000];
	vector<CTile*> m_Tile;
	HBITMAP m_BitMap;
	CDC memDC;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CpuzzleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
