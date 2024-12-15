#ifndef MACRO
#define MACRO
//************************************
//インクルード
//*********************************** 
#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>
//***********************************
//マクロ定義
//***********************************

//ウインドウのサイズ(ピクセル)
#define SCREEN_W 640
#define SCREEN_H 480
//----------------------
//ビットマップ
//---------------------
//各ビットマップの幅、高さ
#define BMP_MC_W	192	/*マイキャラ*/
#define BMP_MC_H	128

#define BMP_BL_W	128	/*ブロック*/
#define BMP_BL_H	64

#define BMP_EN_W	576	/*敵キャラ*/
#define BMP_EN_H	128



//各ビットマップのオフスクリーン上での配置位置
//X座標
#define BMP_X		0	/*X座標は0*/
//Y座標
#define BMP_MC_Y	0	/*マイキャラ*/
#define BMP_BL_Y	BMP_MC_H	/*ブロック*/
#define BMP_EN_Y	BMP_BL_Y + BMP_BL_H	/*敵キャラ*/

//オフスクリーンの幅高さ///////////////////////
/*キャラクタ*/
#define OFFSCREEN_W BMP_EN_W
#define OFFSCREEN_H BMP_EN_Y + BMP_EN_H 
/*GAME OVER*/
#define OFF_GOVER_W	473
#define OFF_GOVER_H 164
/*タイトル画面*/
#define OFF_TITLE_W 640
#define OFF_TITLE_H 480
//////////////////////////////////////////////////////////////
//オフスクリーン番号
#define OFFSCRN_CHAR 0//キャラクタ用
#define OFFSCRN_GOVER 1//GameOverメッセージ
#define OFFSCRN_TITLE 2//タイトル画面
//オフスクリーンの数
#define OFFSCRN_COUNT 3
//---------------------------------
//キャラクタデータ
//----------------------------------
//キャラクタ数の最大値
#define CHAR_MAX 32	

//キャラクタの幅高さ
#define CHAR_W 32
#define CHAR_H 32

//キャラタイプ
#define TYPE_MC 0
#define TYPE_ENEM00 1
#define TYPE_BLK00 2
#define TYPE_ENEM01 3
#define TYPE_ENEM02 4
#define TYPE_BLK02 5
#define TYPE_HART	6
//-----------------------------
////Mapデータ
//----------------------------
//パーツ番号
#define PARTS_BG	0
#define PARTS_BLK00	1
#define PARTS_STP	2
#define PARTS_BLK01	3
#define PARTS_BLK02	4
//BGチップタイプ
#define CHIP_TYPE_BG	0/*背景*/
#define CHIP_TYPE_BLK	1/*ブロック*/
#define CHIP_TYPE_STP	2/*はしご*/

//ブロックの落下時間
#define FALL_CNT		32//点滅し始めてから落下しはじめるまでのフレーム数
#define RESET_CNT		256//落下し終わってから元の位置に復活するまでのフレーム数




//-----------------------------------
//固定小数計算
//-----------------------------------
#define _ONE 0x10000	//固定小数での１
#define _HALF 0x8000	//固定小数での１/２

//重力加速度
#define _G 0x8000
//---------------------------------
//インプットデータ取得フラグ
//--------------------------------
//Aボタン
#define _A_MASK		(WORD)0x0070
#define _A_PRS		(WORD)0x0010
#define _A_RLS		(WORD)0x0020
#define _A_KEP		(WORD)0x0040
//Bボタン.
#define _B_MASK		(WORD)0x0380
#define _B_PRS		(WORD)0x0080
#define _B_RLS		(WORD)0x0100
#define _B_KEP		(WORD)0x0200
//エスケープキー
#define _ESC_PRS	(WORD)0x0400
//ENTERキー
#define _ENT_PRS	(WORD)0x0800
//Functionキ－
#define _F1_PRS		(WORD)0x1000		
#define _F2_PRS		(WORD)0x2000
#define _F3_PRS		(WORD)0x4000
#define _F4_PRS		(WORD)0x8000
//ボタン全体
#define _BTN_MASK	(WORD)0x03f0
//方向キー
#define _DIR_MASK	(WORD)0x000f
#define _RIGHT		(WORD)0x01
#define _LEFT		(WORD)0x02
#define _DOWN		(WORD)0x04
#define _UP			(WORD)0x08
//Func,Enter,Esc Key ビットマスク
#define _FUNC_KEY	(WORD)0xfc00
//-----------------------------------
//キャラクタステータスフラグ
//----------------------------------
#define _STATUS_WALK	0x01	//歩行(on-bit:歩く)
#define _STATUS_RIGHT	0x02	//左右(on-bit:右)
#define _STATUS_JUMP	0x04	//ジャンプ(on-bit:ジャンプ中又は落下中)
#define _STATUS_DASH	0x08	//ダッシュ中
#define _STATUS_UPDOWN	0x10	//はしごの上り下り
#define _STATUS_PIYO	0x20	//気絶
#define _STATUS_DAMAGE	0x40	//ダメージ後の無敵状態

#define _ENEM_RIGHT		0x01
#define _ENEM_FALL		0x02
#define _ENEM_UP		0x04
#define _ENEM_UPDOWN	0x08
#define _ENEM_PIYO		0x10
#define _ENEM_CAGE		0x20
#define _ENEM_ESCAPE	0x40

#define _STATUS_MASK 0x7f


//----------------------------
//マクロ関数
//---------------------------
//オブジェクトの解放
#define RELEASEDX(x)	\
	if(x){				\
		x->Release();	\
		x=NULL;			\
	}
//絶対値を求める
#define _ABS(x) ((x >=0)? x : -x)



//***************************************
//構造体の定義
//***************************************

//キャラクタ

typedef struct tagHITCHK {
	int nHitW, nHitH;
	RECT rcHit, rcHitOld;
}_HITCHK;

typedef struct tagCHAR {
	int		nXDsp, nYDsp,//表示用座標
		nXPos, nYPos,//計算用座標
		nDashSPD,//ダッシュ移動量（マイキャラのみ使用）
		nXSPD, nYSPD,//移動量
		nMapX, nMapY;//bgDataとして再配置する時の配置位置（ブロックのみ使用）
	RECT	rcSrc;//オフスクリーン上のビットマップ座標
	_HITCHK	hitChk;//当り判定用
	BOOL	fLive,//存在しているか
		fDraw,//表示するか
		fWait;//移動処理の一時停止
	BYTE	nType,//キャラのタイプ
		nStatus, nStatusOld,//キャラの状態
		nLife;
	WORD	wAnimeCnt,//表示絵のフレーム数をカウント
		wPiyoCnt,//ピヨリフレーム数をカウント
		wCageCnt;
	BYTE	nAnimeIndex;//表示する絵の指定
	WORD	wCharNum;//chDataの何番目の要素か、要素番号を入れておく
}_CHAR;


//ゲームデータ
typedef struct tagGAMEDATA {

	HWND				hwnd;/*ウインドウのハンドル*/
	HINSTANCE			hInst;/*インスタンスハンドル*/
	RECT				rcClient;/*クライアント領域の矩形座標*/
	BOOL				fActive;/*ウインドウがアクティブか*/
}_GAMEDATA;



//スクロールデータ
typedef struct tagBGSCROLL {

	int		nBgX, nBgY,//スクロール座標
		nXAdj, nYAdj,//スクロール座標の修正値
		/*(スクロール座標)/(BGチップのサイズ)の剰余*/
		nXMin, nYMin,//スクロール座標の最小値
		nXMax, nYMax;//スクロール座標の最大値
	WORD	wXIndex, wYIndex;//bgData配列での要素番号
	/*(スクロール座標)/(BGチップのサイズ)の整数部（.以下切り捨て）*/
}_BGSCROLL;



//******************************************
//グローバル変数
//******************************************
extern _GAMEDATA gData;




#endif


