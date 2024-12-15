/*moveMyChar.cpp*/
//*************************
//インクルード
//**************************
#include "gameMain.h"
#include "directS.h"
#include "chkBgHit.h"
#include "dash.h"
#include "chkCharHit.h"
#include "moveEnemy.h"
#include "moveMyChar.h"
#include "mapData.h"
//*******************************************
//ダッシュスピードを求める関数のテーブル
//*******************************************

void (*tblDash[][32])(_CHAR*) = {
	{
	DashOff,	DashOff,	DashOff,	DashOff,
	DashOff,	DashR,		DashL,		DashOff,
	DashRBrake,	DashRBrake,	DashRBrake2,DashRBrake,
	DashRBrake,	DashR,		DashRBrake2,DashRBrake,
	DashLBrake,	DashLBrake2,DashLBrake,	DashLBrake,
	DashLBrake,	DashLBrake2,DashL,		DashLBrake,
	DashOff,	DashOff,	DashOff,	DashOff,
	DashOff,	DashOff,	DashOff,	DashOff,
	},
	{
	NoChange,	NoChange,	NoChange,	NoChange,
	NoChange,	NoChange,	NoChange,	NoChange,
	NoChange,	NoChange,	DashRBrake,NoChange,
	NoChange,	NoChange,	DashRBrake,NoChange,
	NoChange,	DashLBrake,NoChange,	NoChange,
	NoChange,	DashLBrake,NoChange,	NoChange,
	NoChange,	NoChange,	NoChange,	NoChange,
	}
};
//*************************************************************
//BGにめり込まないように移動量を修正する関数のテーブル
//************************************************************
//通常時(X,Y方向の移動量の符号を添え字とする...符号が±0の時が0,＋の時は1,－の時は2)
void (*chkBg_Normal[3][3])(_CHAR*) = {
	{ChkBgHit_Stop,	ChkBgHit_D,		ChkBgHit_U},
	{ChkBgHit_R,	ChkBgHit_DR,	ChkBgHit_UR},
	{ChkBgHit_L,	ChkBgHit_DL,	ChkBgHit_UL}
};
//はしごを移動している時（方向キーのインプットデータを添え字にする）
void (*chkBg_Step[])(_CHAR*) = {
	ChkBgHit_Stop,	ChkBgHit_R,		ChkBgHit_L,		ChkBgHit_Stop,
	ChkBgHit_D,		ChkBgHit_D,		ChkBgHit_D,		ChkBgHit_D,
	ChkBgHit_U,		ChkBgHit_U,		ChkBgHit_U,		ChkBgHit_U,
	ChkBgHit_Stop,	ChkBgHit_Stop,	ChkBgHit_Stop,	ChkBgHit_Stop,
};
//----------------------------------
//移動量テーブル	
//----------------------------------
//通常時のX方向の移動量
int tblXMove[] = {
		0,WALK_SPD,-WALK_SPD,0,
		0,WALK_SPD,-WALK_SPD,0,
		0,WALK_SPD,-WALK_SPD,0,
		0,0,0,0
};
//はしご移動時のY方向の移動量
int tblStepYMove[] = {
	0,0,0,0,
	STEP_SPD,STEP_SPD,STEP_SPD,0,
	-STEP_SPD,-STEP_SPD,-STEP_SPD,0,
	0,0,0,0
};
//はしご移動時のY方向の移動量
int tblStepXMove[] = {
	0,STEP_SPD,-STEP_SPD,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};
//-------------------------------------
//フラグ切り替えテーブル
//------------------------------------
//はしご上り下りのフラグのon-off
BOOL fUpDownKey[] = {
	0,0,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,0
};
/*キャラステ－タスの歩行フラグのON-OFFに使用*/
BYTE tblWalkFlag[] = {

	  0x00,0x01,0x01,0x00,
	  0x01,0x01,0x01,0x00,
	  0x01,0x01,0x01,0x00,
	  0x00,0x00,0x00,0x00
};
/*LRフラグの切り替えに使用*/
BYTE tblLRFlag[][16] = {
		{
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02
		},
		{
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02
		}
};
//*************************************************************
//マイキャラを移動させる関数
//*************************************************************
void MyCharMove(_CHAR* lpMC, _BGSCROLL* lpBgScrl, WORD wInputData)
{
	//------------------------------------------
	//ローカル変数
	//----------------------------------------
	//足元にブロックがあるか、
	//はしごに触れているかを調べる
	int nBottomIndex, nLeftIndex, nRightIndex,
		nYIndex1, nYIndex2, nXIndex;

	//スクロール
	int nScrlY0, nScrlY1, nScrlX0, nScrlX1;

	static BOOL fStep = FALSE;

	static WORD wMutekiCnt;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA lpBg = NULL;
	//気絶中は入力情報を０にする
	if (lpMC->nStatus & _STATUS_PIYO)
	{
		wInputData = 0;
		lpMC->nStatus &= ~_STATUS_UPDOWN;
		fStep = FALSE;
		lpMC->nStatus |= _STATUS_JUMP;
		lpMC->nDashSPD = 0;
		lpMC->wPiyoCnt++;
		if (lpMC->wPiyoCnt == PIYO_CNT_MC)
		{
			lpMC->wPiyoCnt = 0;
			lpMC->nStatus &= ~_STATUS_PIYO;
		}
	}
	//ダメージ後の無敵状態のカウント
	if (lpMC->nStatus & _STATUS_DAMAGE)
	{
		wMutekiCnt++;
		if (wMutekiCnt == MUTEKICOUNT_MAX)
		{
			lpMC->nStatus &= ~_STATUS_DAMAGE;
			wMutekiCnt = 0;
		}
	}
	//------------------------------------------------------------
	//Ｗａｌｋ、方向フラグ
	//------------------------------------------------------------
	if (wInputData & _DIR_MASK) {
		lpMC->nStatus
			|= tblWalkFlag[wInputData & _DIR_MASK];
		lpMC->nStatus
			^= tblLRFlag[(lpMC->nStatus & _STATUS_RIGHT) >> 1]
			[wInputData & _DIR_MASK];
	}
	else {
		lpMC->nStatus &= ~_STATUS_WALK;
	}


	if (fStep) {
		lpMC->nStatus |= _STATUS_UPDOWN;
		lpMC->nStatus &= ~_STATUS_JUMP;
		lpMC->nDashSPD = 0;
		lpMC->nYSPD = 0;
	}


	//-------------------------------------------
	//キャラクタの移動量を決める
	//------------------------------------------
	if (lpMC->nStatus & _STATUS_UPDOWN)
		//はしごの上り下り
		MCStepMove(lpMC, wInputData);
	else
		//通常移動
		MCNormalMove(lpMC, wInputData);


	//------------------------------------------
	//キャラクタを移動、スクロール
	//------------------------------------------
	nScrlX0 = lpBgScrl->nBgX + 6 * CHAR_W * _ONE;
	nScrlX1 = lpBgScrl->nBgX + (SCREEN_W - 7 * CHAR_W) * _ONE;
	nScrlY0 = lpBgScrl->nBgY + 6 * CHAR_H * _ONE;
	nScrlY1 = lpBgScrl->nBgY + (SCREEN_H - 7 * CHAR_H) * _ONE;
	//移動量を加える
	lpMC->nYPos += lpMC->nYSPD;
	lpMC->nXPos += lpMC->nXSPD;

	//スクロール
	//Y方向//////////
	//移動先がスクロール位置を超えていたら
	//（画面下のスクロール位置）
	if (lpMC->nYPos > nScrlY1) {
		//超えた分だけスクロールする
		lpBgScrl->nBgY += lpMC->nYPos - nScrlY1;

		//（画面上のスクロール位置）
	}
	else if (lpMC->nYPos < nScrlY0) {
		//超えた分だけスクロール
		lpBgScrl->nBgY -= nScrlY0 - lpMC->nYPos;

	}
	//スクロール座標が最大値(BGの端)を超えない様にする
	if (lpBgScrl->nBgY > lpBgScrl->nYMax)
	{
		lpBgScrl->nBgY = lpBgScrl->nYMax;
	}//スクロール座標が最小値を(BGの端)超えないようにする
	else if (lpBgScrl->nBgY < lpBgScrl->nYMin)
	{
		lpBgScrl->nBgY = lpBgScrl->nYMin;
	}


	//X方向////////////////////
	//移動先がスクロール位置を超えていたら
	//（画面右のスクロール位置）
	if (lpMC->nXPos > nScrlX1) {
		lpBgScrl->nBgX += lpMC->nXPos - nScrlX1;

		//（画面左のスクロール位置）
	}
	else if (lpMC->nXPos < nScrlX0) {
		lpBgScrl->nBgX -= nScrlX0 - lpMC->nXPos;

	}
	if (lpBgScrl->nBgX > lpBgScrl->nXMax)
	{
		lpBgScrl->nBgX = lpBgScrl->nXMax;
	}
	else if (lpBgScrl->nBgX < lpBgScrl->nXMin)
	{
		lpBgScrl->nBgX = lpBgScrl->nXMin;
	}
	//---------------------------------------------
	//キャラの足元にブロックがあるか、
	//キャラがはしごに触れているかを調べる
	//----------------------------------------------
	//ブロック用BG座標を計算
	nBottomIndex = (((lpMC->nYPos + _HALF) >> 16) + 32) >> 5;
	nLeftIndex = (((lpMC->nXPos + _HALF) >> 16) + 0) >> 5;
	nRightIndex = (((lpMC->nXPos + _HALF) >> 16) + 31) >> 5;

	//はしご用BG座標を計算
	nYIndex1 = (((lpMC->nYPos + _HALF) >> 16) + 0) >> 5;

	//降りる時は足元、それ以外は足元の１ピクセル上の座標を調べる
	if (wInputData & _DOWN)
		nYIndex2 = nBottomIndex;
	else
		nYIndex2 = (((lpMC->nYPos + _HALF) >> 16) + 31) >> 5;

	//はしごチェック用X座標はキャラクタの中央に設定
	nXIndex = (((lpMC->nXPos + _HALF) >> 16) + 15) >> 5;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;
	//足元にブロックがなければジャンプ(空中)フラグをON(落下させる)
	if ((!(lpBg + lpMap->wMapW * nBottomIndex)[nLeftIndex].nType)
		&& (!(lpBg + lpMap->wMapW * nBottomIndex)[nRightIndex].nType)) {
		lpMC->nStatus |= _STATUS_JUMP;
	}
	//はしごに触れている時
	if (((lpBg + lpMap->wMapW * nYIndex1)[nXIndex].nType == CHIP_TYPE_STP)
		|| ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_STP)) {
		//上キーか下キーが押されていたら
		if (fUpDownKey[wInputData & (_DIR_MASK)]) {
			//はしごフラグをONにし、キャラクタのX座標をはしごと合わせる
			fStep = TRUE;
			lpMC->nXPos = ((nXIndex << 16) - 15) << 5;
		}
		//足元にブロックがあったらはしごフラグをOFF（はしごを降りて地面まできた時）
		if ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_BLK) {
			lpMC->nStatus &= ~_STATUS_UPDOWN;
			fStep = FALSE;
		}
		//はしごに触れていないときは、はしごフラグをOFFにする
	}
	else {
		lpMC->nStatus &= ~_STATUS_UPDOWN;
		fStep = FALSE;
	}


	//-----表示用の座標に変換-----
	lpMC->nXDsp = (lpMC->nXPos - lpBgScrl->nBgX + _HALF) >> 16;
	lpMC->nYDsp = (lpMC->nYPos - lpBgScrl->nBgY + _HALF) >> 16;
	SetDrawFlag(lpMC);
	SetHitRect(lpMC, 1 * _ONE, 1 * _ONE);

}

//*******************************************************
//マイキャラの移動量を求める関数
//*******************************************************
//-----------------------------------------------------------
//通常時
//-----------------------------------------------------------
void MCNormalMove(_CHAR* lpMC, WORD wInputData) {

	//------------------------------------------
	//ローカル変数
	//---------------------------------------
	//Dash
	BYTE nDashFlag = 0;//ダッシュ時のインプットデータなどを取っておく
	//ダッシュ関数テーブルの添え字に使う
	int nSpdAdj;//DashSPDの修正値:0.5区切りにする

	//BGとの接触を調べる
	BYTE nXSign,//マイキャラの移動量の符号を取っておく
		nYSign;//移動量修正関数テーブルの添え字

	//----------------------------------------------
	//X方向の移動量を決める
	//---------------------------------------------

	//ダッシュフラグにインプットデータを入れる
		//（Bボタン＋右か左でダッシュON）
	nDashFlag |= (wInputData & _B_KEP) >> 7;
	nDashFlag |= wInputData & _LEFT;
	nDashFlag |= wInputData & _RIGHT;

	//現在のダッシュ方向のデータを入れる
	if (lpMC->nDashSPD > 0)//＋の時は右にダッシュしている
		nDashFlag |= 0x08;
	else if (lpMC->nDashSPD < 0)//－の時は左にダッシュ
		nDashFlag |= 0x10;
	else//0の時はダッシュしていない				
		nDashFlag &= 0x07;//インプットデータを残してbit_offする

	//ダッシュ加算値を求める
	//（ダッシュフラグによって処理を振り分ける）
	tblDash[(lpMC->nStatus & _STATUS_JUMP) >> 2]
		[nDashFlag & 0x1f](lpMC);

	//X方向の移動量を求める
	nSpdAdj = lpMC->nDashSPD & (0x8000 - 1);//ダッシュ加算値を0.5単位に丸める
	lpMC->nXSPD = tblXMove[wInputData & _DIR_MASK]//方向キーによる加算値
		+ lpMC->nDashSPD - nSpdAdj;//ダッシュ加算値

	//------------------------------------------
	//Y方向の移動量を決める
	//-----------------------------------------

	//ジャンプ
	//キャラが空中に居るとき
	if (lpMC->nStatus & _STATUS_JUMP) {

		//Y移動量に一定量を加算
		lpMC->nYSPD += _G;
		//ジャンプ時ボタンが離されたら上昇中止
		if (!(wInputData & _A_KEP) && (lpMC->nYSPD < 0))
			lpMC->nYSPD = 0;
	}
	else {	//着地時

		lpMC->nYSPD = 0;//Y方向の移動量を０にする
		//ジャンプボタンが押されたら
		if (wInputData & _A_PRS) {
			//フラグを立ててジャンプ
			lpMC->nStatus |= _STATUS_JUMP;
			//ダッシュスピードをジャンプの高さに加える
			lpMC->nYSPD = -_JUMP_HI
				- (_ABS(lpMC->nDashSPD + nSpdAdj));
			//ジャンプ音
			DSoundPlay(SOUND_JUMP);
		}
	}

	//-----------------------------------------
	//BGにめり込まないように移動量を修正する
	//----------------------------------------
	//移動量の符号を調べる
	if (!lpMC->nXSPD)	nXSign = 0;
	else if (lpMC->nXSPD > 0)	nXSign = 1;
	else	nXSign = 2;

	if (!lpMC->nYSPD)	nYSign = 0;
	else if (lpMC->nYSPD > 0)	nYSign = 1;
	else	nYSign = 2;
	//移動方向によって処理を振り分ける
	chkBg_Normal[nXSign][nYSign](lpMC);

}
//--------------------------------------------------------
//はしごを移動するとき
//---------------------------------------------------------
void MCStepMove(_CHAR* lpMC, WORD wInputData) {

	lpMC->nYSPD = tblStepYMove[wInputData & _DIR_MASK];
	lpMC->nXSPD = tblStepXMove[wInputData & _DIR_MASK];

	chkBg_Step[wInputData & _DIR_MASK](lpMC);

}
