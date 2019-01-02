#include "stdafx.h"
#include "Tile.h"




void CTile::TileDraw(CDC* pDC, CDC* memDC, CpuzzleDoc* pDoc) {
	if(iNum == 0) {
		//CBrush brush(RGB(80,80,80));
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		//pDC->SelectObject(brush);
		//pDC->Rectangle(iTileSize*x,iTileSize*y,iTileSize,iTileSize);
		//pDC->SelectObject(oldBrush);
	}else {
		pDC->TransparentBlt(ixTileSize*x+margin,iyTileSize*y+margin,ixTileSize,iyTileSize, memDC,
			ixImgSize*(pDoc->pos[iNum].x),iyImgSize*(pDoc->pos[iNum].y),ixImgSize,iyImgSize,SRCCOPY);
	}
		
}

