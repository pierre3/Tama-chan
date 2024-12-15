/*mapData.h*/

#ifndef MAPDATA_H
#define MAPDATA_H

#include "gameMain.h"
//BGマップデータ
typedef struct tag_BGDATA {
	BYTE	nPartsNum,//パーツ番号
		nPartsOld,//元のパーツ番号
		nType;//パーツのタイプ
	WORD	wFallCnt,//落下するタイミングをカウント（0になったら落下）
		wResetCnt;//初期位置に再配置するタイミングをカウント(0になったら配置)
	BOOL	fFallCnt,//TRUE：wFallCntをカウントダウンさせる
		fResetCnt;//TRUE：wResetCntをカウントダウンさせる
}_BGDATA, * _LPBGDATA;
typedef struct tag_CHARPOS {
	WORD	wX,
		wY;
}_CHARPOS, * _LPCHARPOS;
typedef struct tag_MAPDATA {
	_LPBGDATA	lpBgData;
	WORD		wMapW, wMapH;
	BYTE* lpFloorData;
	BYTE		nCageCount;
	_CHARPOS	myCharPos;
	_LPCHARPOS	lpEnemyPos;
}_MAPDATA, * _LPMAPDATA;

extern void FreeMap();
extern BOOL LoadMapData(LPCSTR);
extern _LPMAPDATA GetMapData();

#endif