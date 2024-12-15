/*directD.cpp*/
#include "directD.h"
#include "directS.h"
//****************************************************
//		DirectDrawの設定(Window Mode)
//****************************************************
BOOL _DDRAW::DDCreateWin() {
	//グローバル変数
	HRESULT			err;
	DDSURFACEDESC	ddsd;
	HDC				hdc;
	//---------------------------------------
	//DD_Object
	//---------------------------------------
	//DDオブジェクトの作成
	err = DirectDrawCreate(NULL, &lpDD, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "DDオブジェクトの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//協調レベルの設定
	err = lpDD->SetCooperativeLevel(gData.hwnd,
		DDSCL_NORMAL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "協調レベルの設定に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------
	//Primary_Surface
	//---------------------------------------------
	//プライリサーフィスの設定
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE
		| DDSCAPS_VIDEOMEMORY;

	//プライマリサーフィスの作成
	err = lpDD->CreateSurface(&ddsd, &lpDDPR, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "プライマリサーフィスの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//-------------------------------------------------------
	//Clipper_Object
	//-------------------------------------------------------
	//クリッパーオブジェクトの作成
	err = lpDD->CreateClipper(0, &lpDDCL, NULL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "クリッパーオブジェクトの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//クリッパーオブジェクトをウインドウへ設定
	err = lpDDCL->SetHWnd(0, gData.hwnd);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "ウインドウへのクリッパーの設定に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//クリッパーオブジェクトをプライマリーサーフィスへ設定
	err = lpDDPR->SetClipper(lpDDCL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "プライマリサーフィスへのクリッパーの設定に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------
	//BackBuffer
	//---------------------------------------------------
	//バックバッファの作成
	if (!DDCreateOffScreen(&lpDDBK, 0, 0, 0, SCREEN_W, SCREEN_H,
		DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}

	return(TRUE);
}
//******************************************************************
//			DirectDrawの設定(Full Screen Mode)
//******************************************************************
BOOL _DDRAW::DDCreateFull() {

	HRESULT			err;
	DDSURFACEDESC	ddsd;
	DDSCAPS			caps;
	HDC				hdc;
	DWORD			dwResult = 0;
	//---------------------------------------------------
	//DD_Object
	//---------------------------------------------------
	//DDオブジェクトの作成
	err = DirectDrawCreate(NULL, &lpDD, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "DDオブジェクトの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//協調レベルの設定
	err = lpDD->SetCooperativeLevel(gData.hwnd,
		DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN
		| DDSCL_ALLOWREBOOT);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "協調レベルの設定に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//ディスプレイモードの設定
	lpDD->EnumDisplayModes(
		DDEDM_REFRESHRATES,
		NULL,
		(LPVOID)&dwResult,
		EnumModesCallback);

	if (dwResult) {

		err = lpDD->SetDisplayMode(SCREEN_W, SCREEN_H, BPP);

		if (err != DD_OK) {
			MessageBox(gData.hwnd, "ディスプレイモードの設定に失敗",
				"エラーメッセージ", MB_OK | MB_ICONSTOP);
			return(FALSE);
		}

	}
	else {
		MessageBox(gData.hwnd, "指定された解像度は使用できません",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//--------------------------------------------------------
	//Primary_Surface
	//--------------------------------------------------------
	//プライリサーフィスの設定
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.dwBackBufferCount = 1;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE
		| DDSCAPS_FLIP
		| DDSCAPS_COMPLEX
		| DDSCAPS_VIDEOMEMORY;

	//プライマリサーフィスの作成
	err = lpDD->CreateSurface(&ddsd, &lpDDPR, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "プライマリサーフィスの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//バックバッファをプライマリサーフィスと組み合わせる
	caps.dwCaps = DDSCAPS_BACKBUFFER;

	err = lpDDPR->GetAttachedSurface(&caps, &lpDDBK);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "サーフィスの組み合わせに失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	return(TRUE);
}
//*************************************************
//		DirectDraw関連オブジェクトの解放
//*************************************************
void _DDRAW::DDReleaseWin() {
	RELEASEDX((lpDDBK));
	RELEASEDX((lpDDCL));
	RELEASEDX((lpDDPL));
	RELEASEDX((lpDDPR));
	RELEASEDX((lpDD));
}
void _DDRAW::DDReleaseFull() {
	RELEASEDX((lpDDPL));
	RELEASEDX((lpDDPR));
	RELEASEDX((lpDD));
}
//********************************************************************
//オフスクリーンサーフィスの作成
//********************************************************************
BOOL _DDRAW::DDCreateOffScreen(LPDIRECTDRAWSURFACE* lplpDDOF,
	BYTE colorKeyR,
	BYTE colorKeyG,
	BYTE colorKeyB,
	DWORD dwWidth,
	DWORD dwHeight,
	DWORD dwMemoryFlag)
{

	HRESULT			err;
	DDSURFACEDESC	ddsd;
	DDCOLORKEY		ddck;
	DWORD			dwColorKey;

	//オフスクリーンサーフィスの設定
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = dwWidth;
	ddsd.dwHeight = dwHeight;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN
		| dwMemoryFlag;

	//オフスクリーンサーフィスの作成
	err = lpDD->CreateSurface(&ddsd, lplpDDOF, NULL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "オフスクリーンサーフィスの作成に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	dwColorKey = RgbToDword(*lplpDDOF, colorKeyR, colorKeyG, colorKeyB);
	//オフスクリーンサーフィスにカラーキーを設定
	ddck.dwColorSpaceLowValue = dwColorKey;
	ddck.dwColorSpaceHighValue = dwColorKey;
	err = (*lplpDDOF)->SetColorKey(DDCKEY_SRCBLT, &ddck);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "カラーキーの設定に失敗",
			"エラーメッセージ", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	return(TRUE);
}

//**********************************************************************
//ビットマップを読み込み、オフスクリーンサーフィスに転送
//**********************************************************************
BOOL _DDRAW::DDLoadBmp(LPDIRECTDRAWSURFACE* lplpDDOF,
	LPSTR lpszFileName,
	DWORD dwStartingEntry,
	DWORD dwCount,
	DWORD dwXDest,
	DWORD dwYDest,
	DWORD dwWidth,
	DWORD dwHeight)
{
	HDC	hdc, hMemDC;
	HBITMAP	hBitmap;

	//ビットマップを読み込む
	hdc = GetDC(gData.hwnd);
	hBitmap = (HBITMAP)LoadImage(gData.hInst, lpszFileName,
		IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(gData.hwnd, hdc);

	//ビットマップをオフスクリーンサーフィスに転送
	(*lplpDDOF)->GetDC(&hdc);
	BitBlt(hdc, dwXDest, dwYDest, dwWidth, dwHeight,
		hMemDC, 0, 0, SRCCOPY);

	(*lplpDDOF)->ReleaseDC(hdc);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);

	return(TRUE);
}

//*************************************************************************
//列挙CALLBACK関数(使用可能なスクリーンモードを調べる)
//*************************************************************************
HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC lpDdsd,
	LPVOID lpContext) {
	if (lpDdsd->dwWidth == SCREEN_W
		&& lpDdsd->dwHeight == SCREEN_H
		&& lpDdsd->ddpfPixelFormat.dwRGBBitCount == BPP) {
		*(DWORD*)lpContext = TRUE;
		return(DDENUMRET_CANCEL);
	}
	return(DDENUMRET_OK);
}

//******************************************************************
//スクリーンモードの切り替え
//******************************************************************
BOOL _DDRAW::ChangeScreenMode()
{
	RECT rcAdj;

	if (GetAsyncKeyState(VK_F1) & 0xff00) {

		DSoundPlay(SOUND_OPEN);
		fInitDD = FALSE;
		fFull ^= TRUE;
		RELEASEDX(lpDDOF[0]);
		RELEASEDX(lpDDOF[1]);
		RELEASEDX(lpDDOF[2]);
		if (!fFull) {
			//--------------------------------------
			//フルスクリーンモードのオブジェクトを解放
			//--------------------------------------
			DDReleaseFull();
			//--------------------------------------
			//ウインドウをウインドウモード用に変更
			//--------------------------------------
			//ウインドウの幅,高さを求める
			SetRect(&rcAdj, 0, 0, SCREEN_W, SCREEN_H);
			AdjustWindowRect(&rcAdj,
				WS_POPUP | WS_BORDER | WS_CAPTION
				| WS_VISIBLE, FALSE);
			//ウインドウスタイルを変更する
			SetWindowLong(gData.hwnd, GWL_STYLE,
				WS_POPUP | WS_CAPTION
				| WS_BORDER | WS_VISIBLE);
			//ウインドウの幅、高さを変更する
			SetWindowPos(gData.hwnd, HWND_NOTOPMOST, 0, 0,
				rcAdj.right - rcAdj.left,
				rcAdj.bottom - rcAdj.top, SWP_DRAWFRAME);
			//---------------------------------------
			//DirectDrawの準備(Window Mode)
			//---------------------------------------
			if (!DDCreateWin())		return(FALSE);
		}
		else {
			//------------------------------------------
			//ウインドウモードのオブジェクトを解放
			//------------------------------------------
			DDReleaseWin();
			//-------------------------------------------
			//ウインドウをフルスクリーン用に変更
			//-------------------------------------------
			//ウインドウスタイルの変更
			SetWindowLong(gData.hwnd, GWL_STYLE, WS_POPUP);
			SetWindowLong(gData.hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
			//---------------------------------------
			//DirectDrawの準備(Full Screen Mode)
			//---------------------------------------
			if (!DDCreateFull())		return(FALSE);

		}
		if (!SetBitmap())
			return(FALSE);

	}
	static int count;
	if (fFull)
	{
		if (count <= 16)
			lpDDPL->SetEntries(0, 10, 236, &ape2[10]);
		count++;
	}
	else
		count = 0;


	return(fInitDD = TRUE);
}
//--------------------------------------------
//オフスクリーンの作成、ビットマップの読み込み
//--------------------------------------------
BOOL _DDRAW::SetBitmap()
{
	//オフスクリーンサーフィスの作成____________
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_CHAR], COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, OFFSCREEN_W,
		OFFSCREEN_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_GOVER], COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, OFF_GOVER_W,
		OFF_GOVER_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_TITLE], COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, OFF_TITLE_W,
		OFF_TITLE_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	//ビットマップの読み込み___________________
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\MyChar.bmp"),
		10, 236, BMP_X, BMP_MC_Y, BMP_MC_W, BMP_MC_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\Block.bmp"),
		10, 236, BMP_X, BMP_BL_Y, BMP_BL_W, BMP_BL_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\Enemy.bmp"),
		10, 236, BMP_X, BMP_EN_Y, BMP_EN_W, BMP_EN_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_GOVER], const_cast<char*>("bitmap\\gover.bmp"),
		10, 236, 0, 0, OFF_GOVER_W, OFF_GOVER_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_TITLE], const_cast<char*>("bitmap\\title.bmp"),
		10, 236, 0, 0, OFF_TITLE_W, OFF_TITLE_H)) {
		return(FALSE);
	}
	return(TRUE);
}

//---------------------------------------------------------------------
//VRAMの開き領域を調べる
//--------------------------------------------------------------------
void _DDRAW::VRAMCheck() {

	DDCAPS hwCaps, swCaps;
	HDC hdc;
	char str[64];

	ZeroMemory(&hwCaps, sizeof(hwCaps));
	hwCaps.dwSize = sizeof(hwCaps);
	ZeroMemory(&swCaps, sizeof(swCaps));
	swCaps.dwSize = sizeof(swCaps);

	lpDD->GetCaps(&hwCaps, &swCaps);

	lpDDBK->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);
	wsprintf(str, "VRAM全体の容量:%08d",
		hwCaps.dwVidMemTotal);
	TextOut(hdc, 0, 60, str, lstrlen(str));

	wsprintf(str, "VRAMの残り容量:%08d",
		hwCaps.dwVidMemFree);
	TextOut(hdc, 0, 80, str, lstrlen(str));

	wsprintf(str, "消費したVRAM  :%08d",
		hwCaps.dwVidMemTotal - hwCaps.dwVidMemFree);
	TextOut(hdc, 0, 100, str, lstrlen(str));

	lpDDBK->ReleaseDC(hdc);
}

//DDSurfaceのPixelFormatのBitMask値を見てRGB値からDWORD値を組み立てる
DWORD tagDDRAW::RgbToDword(LPDIRECTDRAWSURFACE lpDDPR, BYTE r, BYTE g, BYTE b)
{
	DWORD
		dwRBits = 0, dwGBits = 0, dwBBits = 0,
		dwR = 0, dwG = 0, dwB = 0,
		dwRMask = 0, dwGMask = 0, dwBMask = 0;
	int
		nRStart = -1, nGStart = -1, nBStart = -1,
		bRBitOn = FALSE, bGBitOn = FALSE, bBBitOn = FALSE;

	DDSURFACEDESC ddsdPR;
	ZeroMemory(&ddsdPR, sizeof(ddsdPR));
	ddsdPR.dwSize = sizeof(ddsdPR);
	lpDDPR->GetSurfaceDesc(&ddsdPR);

	dwRMask = ddsdPR.ddpfPixelFormat.dwRBitMask;
	dwGMask = ddsdPR.ddpfPixelFormat.dwGBitMask;
	dwBMask = ddsdPR.ddpfPixelFormat.dwBBitMask;

	for (int i = 0; i < 32; i++)
	{
		bRBitOn = (dwRMask >> i) & 1;
		bGBitOn = (dwGMask >> i) & 1;
		bBBitOn = (dwBMask >> i) & 1;
		if (bRBitOn) {
			if (nRStart == -1) {
				nRStart = i;
			}
			dwRBits++;
		}
		if (bGBitOn) {
			if (nGStart == -1) {
				nGStart = i;
			}
			dwGBits++;
		}
		if (bBBitOn) {
			if (nBStart == -1) {
				nBStart = i;
			}
			dwBBits++;
		}
	}
	r = r >> (8 - dwRBits);
	g = g >> (8 - dwGBits);
	b = b >> (8 - dwBBits);
	dwR = ((DWORD)r) << nRStart;
	dwG = ((DWORD)g) << nGStart;
	dwB = ((DWORD)b) << nBStart;

	return(dwR | dwG | dwB);
}

