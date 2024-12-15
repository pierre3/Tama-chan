
#include "mapData.h"
////////////////////////////////////
//グローバル変数
_MAPDATA mapData = { 0 };
//////////////////////////////////////
//マップデータを取ってくる
_LPMAPDATA GetMapData()
{
	return(&mapData);
}

//メモリ解放
void FreeMap()
{
	if (NULL != mapData.lpBgData)
	{
		GlobalFree(mapData.lpBgData);
		mapData.lpBgData = NULL;
	}
	if (NULL != mapData.lpFloorData)
	{
		GlobalFree(mapData.lpFloorData);
		mapData.lpFloorData = NULL;
	}
}

//マップデータのロード
BOOL LoadMapData(LPCSTR lpPathName)
{
	HFILE hFile;
	UINT err;

	FreeMap();
	ZeroMemory(&mapData, sizeof(_MAPDATA));
	//ファイルオープン
	hFile = _lopen(lpPathName, OF_READ);
	if (hFile == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE OPEN EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//ファイル読み込み////////////////////////////////////////////////////////

	//マップサイズ//////////////////////////////////////////////////////
	err = _lread(hFile, (WORD*)&mapData.wMapW, sizeof(WORD) * 2);
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//檻の数//////////////////////////////////////////////////////
	err = _lread(hFile, (BYTE*)&mapData.nCageCount, sizeof(BYTE));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//フロアデータ//////////////////////////////////////////////////////////
	//メモリ確保
	mapData.lpFloorData = (BYTE*)GlobalAlloc(GPTR,
		sizeof(BYTE) * (mapData.wMapH));
	if (NULL == mapData.lpFloorData)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗F",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//読み込み
	err = _lread(hFile, (BYTE*)mapData.lpFloorData, sizeof(BYTE) * (mapData.wMapH));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//MycharPos//////////////////////////////////////////////////
	err = _lread(hFile, (_LPCHARPOS)&mapData.myCharPos,
		sizeof(_CHARPOS));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//EnemyPos////////////////////////////////////////////////
	//メモリ確保
	mapData.lpEnemyPos = (_LPCHARPOS)GlobalAlloc(GPTR,
		sizeof(_CHARPOS) * mapData.nCageCount);
	if (NULL == mapData.lpEnemyPos)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗B",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//読み込み
	err = _lread(hFile, (_LPCHARPOS)mapData.lpEnemyPos,
		sizeof(_CHARPOS) * mapData.nCageCount);
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//BGデータ///////////////////////////////////////////////
	//メモリ確保
	mapData.lpBgData = (_LPBGDATA)GlobalAlloc(GPTR,
		sizeof(_BGDATA) * (mapData.wMapW) * (mapData.wMapH));
	if (NULL == mapData.lpBgData)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗B",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//読み込み
	err = _lread(hFile, (_LPBGDATA)mapData.lpBgData,
		sizeof(_BGDATA) * (mapData.wMapW) * (mapData.wMapH));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	////////////////////////////////////////////////////////////////
	//ファイルクローズ
	if (_lclose(hFile) == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "マップデータの読み込みに失敗",
			"FILE CLOSE EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	return(TRUE);
}

