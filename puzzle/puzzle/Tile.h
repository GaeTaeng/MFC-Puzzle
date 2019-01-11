#pragma once
#include "puzzleDoc.h"

class CpuzzleDoc;

class CTile
{
public:
	int ixTileSize;
	int iyTileSize;
	int ixImgSize;
	int iyImgSize;
	int iNum;
	int x, y;
	int margin;
public:
	void TileDraw(CDC* pDC, CDC* memDC, CpuzzleDoc* pDoc) ;
public:
	CTile(const CTile &s) {
		*this = s;
	}
	CTile(int num, int _x, int _y, int xTile, int yTile, int xImg, int yImg) {
		margin = 20;
		iNum = num;
		x = _x;
		y = _y;
		ixTileSize = xTile;
		iyTileSize = yTile;
		ixImgSize = xImg;
		iyImgSize = yImg;
	}


	bool colli(CPoint a) {
		if(a.x >= ixTileSize*x+margin && a.x <= ixTileSize*(x+1)+margin 
			&& a.y >= iyTileSize*y+margin && a.y <= iyTileSize*(y+1)+margin) {
				if(iNum == 0 ) return false;
				return true;
		}
		return false;
	}

};

