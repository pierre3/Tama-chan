//****************************************
//インクルード
//****************************************
#include "gameMain.h"
#include "directD.h"
#include "directS.h"
#include "SetCharData.h"
#include "midiStream.h"
#include "drawFrame.h"
#include "mapData.h"
//*************************************
//グローバル変数
//*************************************
_GAMEDATA		gData;
_DDRAW			DDraw;
_CHAR			chData[CHAR_MAX + 1];/*キャラクタの管理*/;


char szClassName[] = "TamaChan";

//*********************************************************
//プロトタイプ宣言
//*********************************************************
/*ウインドウプロシージャ*/
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//変更したカラーモードを元に戻す
void ResetColorMode(BOOL, DWORD);


//*******************************************************************
//WinMain 関数
//******************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance,
	LPSTR lpszArgs, int nWinMode)
{
	//--------------------------
	//ローカル変数の宣言
	//---------------------------
	//ウインドウデータ
	MSG				msg;
	WNDCLASS		wcls;
	RECT			rcAdj;//ウインドウサイズ修正値
	//カラーモードチェック、修正用
	HDC				hDeviceDC;//デバイスDCのハンドル
	DEVMODE			dm;//デバイス設定用
	DWORD			dwColor;//元から設定してあるカラーモードを取得する
	BOOL			fChgColor = FALSE;//カラーモードを変更したらTRUE，しなかったらFALSE
	//インスタンスハンドルの取得
	gData.hInst = hInstance;

	register int i;
	//------------------------------------------
	//構造体の初期化
	//------------------------------------------
	/*各オブジェクトへのポインタはNULLで初期化*/
	DDraw.lpDD = NULL;
	DDraw.lpDDPR = NULL;
	DDraw.lpDDBK = NULL;
	DDraw.lpDDPL = NULL;
	DDraw.lpDDCL = NULL;
	for (i = 0; i < OFFSCRN_COUNT; i++)
	{
		DDraw.lpDDOF[i] = NULL;
	}

	DSoundClear();

	//---------------------------------------------------------------
	//ウインドウスケルトン作成
	//---------------------------------------------------------------
	//ウインドウ・クラス定義部_______________________________________
	wcls.hInstance = hInstance;
	wcls.lpszClassName = szClassName;
	wcls.lpfnWndProc = WinProc;
	wcls.style = CS_DBLCLKS
		| CS_BYTEALIGNCLIENT
		| CS_BYTEALIGNWINDOW;
	wcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.lpszMenuName = NULL;
	wcls.cbClsExtra = 0;
	wcls.cbWndExtra = 0;
	//作成ウインドウ・バックグラウンドカラー設定部______________________
	wcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);


	//ウインドウ・クラス作成部________________________________________
	if (!RegisterClass(&wcls))	return 0;


	//ウインドウサイズの修正_______________________
	SetRect(&rcAdj, 0, 0, SCREEN_W, SCREEN_H);
	AdjustWindowRect(&rcAdj,
		WS_POPUP | WS_BORDER | WS_CAPTION, FALSE);

	//表示ウインドウ・スタイル設定部_________________
	gData.hwnd = CreateWindowEx(NULL,
		szClassName,
		"珍獣ハンターTaMa_Chan",
		WS_POPUP | WS_BORDER | WS_CAPTION,
		0, 0,
		rcAdj.right - rcAdj.left,
		rcAdj.bottom - rcAdj.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//ディスプレイのDC取得＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	hDeviceDC = CreateDC("DISPLAY", NULL, NULL, NULL);

	//カラーモードの変更
	dwColor = GetDeviceCaps(hDeviceDC, BITSPIXEL);
	DeleteDC(hDeviceDC);
	if (dwColor != BPP) {
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = BPP;
		dm.dmFields = DM_BITSPERPEL;
		if (SUCCEEDED(ChangeDisplaySettings(&dm, CDS_TEST)))//一度テストする
		{
			ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);//切り替え用として保存
			fChgColor = TRUE;
		}
		else {
			MessageBox(gData.hwnd, "カラーモードの変更に失敗しました",
				"Direct Draw", MB_OK | MB_ICONSTOP);
			return(FALSE);
		}
	}
	//ウインドウ描画部____________________
	ShowWindow(gData.hwnd, nWinMode);
	UpdateWindow(gData.hwnd);

	//--------------------------------------------------------
	//DirectDrawの設定
	//--------------------------------------------------------
	if (!DDraw.DDCreateWin()) {
		//DDRawオブジェクトの解放
		DDraw.DDReleaseWin();
		//カラーモードを元に戻す
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}
	//オフスクリーンの作成およびビットマップの読み込み
	if (!DDraw.SetBitmap()) {
		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}

	DDraw.fInitDD = TRUE;
	//------------------------------------------------------------
	//DirectSoundの設定
	//------------------------------------------------------------
	if (!DSoundCreate()) {
		ReleaseDS();

		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}


	if (!mdsPlay(const_cast<char*>("mds\\ryuu.mds"), TRUE))
	{
		ReleaseDS();

		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}

	//----------------------------------------
	srand(time(NULL));
	//-----------------------------------------------
	//メッセージループ
	//-----------------------------------------------
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (gData.fActive)
			{

				/*画面モードの切り替え*/

				if (!DDraw.ChangeScreenMode())
				{
					//失敗したらオブジェクトの解放
					//DDraw
					for (i = 0; i < OFFSCRN_COUNT; i++)
					{
						RELEASEDX(DDraw.lpDDOF[i]);
					}
					if (DDraw.fFull)
						DDraw.DDReleaseFull();
					else
						DDraw.DDReleaseWin();
					FreeMap();
					//DSound
					ReleaseDS();
					mdsStop();
					ResetColorMode(fChgColor, dwColor);
					return(FALSE);
				}
				/*********メイン処理**************/


				if (!DrawFrame(&DDraw, chData))
				{
					//オブジェクト解放
					//DDraw
					for (i = 0; i < OFFSCRN_COUNT; i++)
					{
						RELEASEDX(DDraw.lpDDOF[i]);
					}
					if (DDraw.fFull)
						DDraw.DDReleaseFull();
					else
						DDraw.DDReleaseWin();
					FreeMap();
					//DSound
					ReleaseDS();
					mdsStop();
					ResetColorMode(fChgColor, dwColor);
					return(FALSE);
				}
				/*********************************/
			}
			else
				WaitMessage();
		}
	}//while(1)

	//*******************************************
	//終了処理
	//*******************************************
	FreeMap();
	//---------------------------
	//MIDIストリーム演奏停止
	//---------------------------
	mdsStop();
	//-------------------------------
	//オブジェクトの解放（正常終了時）
	//-------------------------------
	//DirectDraw
	for (i = 0; i < OFFSCRN_COUNT; i++)
	{
		RELEASEDX(DDraw.lpDDOF[i]);
	}
	if (DDraw.fFull)
		DDraw.DDReleaseFull();
	else
		DDraw.DDReleaseWin();

	//DirectSound
	ReleaseDS();

	//カラーモードを元に戻す
	ResetColorMode(fChgColor, dwColor);
	return msg.wParam;
}

//---------------------------------------------------------------------------
//ウインドウプロシージャ
//----------------------------------------------------------------------------
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_PAINT: {
		PAINTSTRUCT	ps;
		BeginPaint(hwnd, &ps);
		if (DDraw.fInitDD)
			if (!DrawFrame(&DDraw, chData))
				DestroyWindow(hwnd);

		EndPaint(hwnd, &ps);

	}break;

	case WM_ACTIVATEAPP:
		gData.fActive = (BOOL)wParam;
		break;

	case WM_PALETTECHANGED:
		if (wParam == (DWORD)hwnd)	break;
	case WM_QUERYNEWPALETTE:
		if (DDraw.lpDDPR) {
			DDraw.lpDDPR->SetPalette(DDraw.lpDDPL);
		}break;

	case WM_CREATE:
	case WM_MOVE:
		//---GET CLIENT RECT----
		GetClientRect(hwnd, &gData.rcClient);
		ClientToScreen(hwnd, (LPPOINT)&gData.rcClient);
		ClientToScreen(hwnd, (LPPOINT)&gData.rcClient + 1);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
//カラーモードを元に戻す
void ResetColorMode(BOOL fChgColor, DWORD dwColor)
{
	DEVMODE dm;
	if (fChgColor)
	{
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = dwColor;
		dm.dmFields = DM_BITSPERPEL;
		if (SUCCEEDED(ChangeDisplaySettings(&dm, CDS_TEST)))//一度テストする
			ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);//切り替え用として保存
	}
}