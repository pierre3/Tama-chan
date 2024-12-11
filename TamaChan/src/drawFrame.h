/*drawFrame.h*/
#ifndef DFRAME
#define DFRAME
//**********************************
//インクルード
//*********************************
#include "directD.h"
#include "gameMain.h"
//****************************************
//ゲームステータス
#define GSTATE_GAME 0x00//通常時
#define GSTATE_PAUSE 0x01//ポーズ
#define GSTATE_OUT	0x02//ミス
#define GSTATE_GOVER 0x04//ゲームオーバー
#define GSTATE_CLEAR 0x08//ゲームクリアー
#define GSTATE_TITLE 0x10
//
#define GSTATE_MASK 0x1f
//
#define STAGE_MAX 5
//*************************************
//関数のプロトタイプ
//************************************
//メイン処理、描画を行う関数//////////////////////////////
extern BOOL	DrawFrame(_DDRAW*,//_DDRAW構造体
				  _CHAR*);//chData[]の先頭アドレス

//クリッピング処理//////////////////////////////////////////
extern void Clipping(int*,//転送先画像のX座標のアドレス
			  int*,//転送先画像のY座標のアドレス
			  RECT*);//転送元画像のRECT構造体のアドレス
	/*転送画像が転送先でスクリーンからはみ出さない
			様に各引数の値を修正する*/

//デバッグ用文字の表示////////////////////////////////////
void	DDTextOut(_DDRAW*);//引数：_DDRAW構造体


//メイン処理///////////////////////////////////////

//通常時
BOOL Game(_DDRAW*,
		  _CHAR*,//chData[]の先頭アドレス
		  _BGSCROLL*,//スクロールデータ
		  WORD);//インプットデータ
		//戻り値:失敗...FALSE/成功...TRUE
//ポーズ時
BOOL Scroll(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//ミス時
BOOL MyCharOut(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//ゲームオーバー画面
BOOL GameOver(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//ゲームクリアー画面
BOOL GameClear(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//タイトル画面
BOOL Title(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//フレームレートの調整///////////////////////////////
void FrameWait();

//スクロールデータの設定
void SetScrollData(_BGSCROLL*);

//描画処理///////////////////////////////////////////
void DrawBg(_DDRAW*,_BGSCROLL*);//BGチップ
void DrawCharctor(_DDRAW*,_CHAR*);//キャラクタ

//ENTER　KEYを押した時の処理,ゲームステータスの切り替え
BOOL ToTitle();
BOOL Pause();
BOOL GameStart(_CHAR*);
#endif