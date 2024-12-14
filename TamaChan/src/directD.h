/***directD.h***/
#ifndef DDRAW_H
#define DDRAW_H

//********************************************
//インクルード
//********************************************
#include "gameMain.h"
//*********************************************
//マクロ
//********************************************
#define BPP 24 //カラーモード（24bit）
#define COLOR_KEY_R 156
#define COLOR_KEY_G 220
#define COLOR_KEY_B 220
//**********************************************
//構造体定義
//**********************************************
typedef struct tagDDRAW {
	LPDIRECTDRAW		lpDD;//Direct Draw オブジェクト
	LPDIRECTDRAWSURFACE lpDDPR;//プライマリサーフィス
	LPDIRECTDRAWSURFACE lpDDBK;//バックバッファ
	LPDIRECTDRAWSURFACE lpDDOF[OFFSCRN_COUNT];//オフスクリーンサーフィス
	LPDIRECTDRAWPALETTE lpDDPL;//パレット
	LPDIRECTDRAWCLIPPER lpDDCL;//クリッパー
	BOOL				fInitDD;//Direct Draw の準備ができたか...TRUE：準備OK
	BOOL				fFull;//TRUE：フルスクリーンモード時　FALSE：ウインドウモード時
	PALETTEENTRY		ape2[256];
	//DirectDrawの設定をウインドウモードで行う
	BOOL	DDCreateWin();

	//DirectDrawの設定をフルスクリーンモードで行う
	BOOL	DDCreateFull();

	//DirectDraw関連のオブジェクトの解放
	void	DDReleaseFull();
	void	DDReleaseWin();

	//スクリーンモードの切り替え
	BOOL	ChangeScreenMode();

	//オフスクリーンサーフィスを作成
	BOOL	DDCreateOffScreen(
		LPDIRECTDRAWSURFACE*,//作成したオフスクリーンを受け取るポインタのアドレス
		BYTE,//カラーキーとする色のR
		BYTE,//カラーキーとする色のR
		BYTE,//カラーキーとする色のR
		DWORD,//作成するオフスクリーンの幅
		DWORD,//作成するオフスクリーンの高さ
		DWORD);//メモリーフラグ

	//ビットマップファイルをオフスクリーンサーフィスに読み込む
	BOOL	DDLoadBmp(
		LPDIRECTDRAWSURFACE*,//画像データを格納するオフスクリーンサーフィス
		LPSTR,//ファイル名
		DWORD,
		DWORD,
		DWORD,
		DWORD,
		DWORD,
		DWORD);

	//オフスクリーンの作成とビットマップの読み込み
	BOOL	SetBitmap();
	void	VRAMCheck();
	DWORD	RgbToDword(LPDIRECTDRAWSURFACE lpDDPR, BYTE r, BYTE g, BYTE b);
}_DDRAW;

//*********************************************************
//プロトタイプ宣言
//*********************************************************
//画面モードチェック用
HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC, LPVOID);

#endif