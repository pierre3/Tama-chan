/*drawFrame.cpp*/
//************************
//インクルード
//************************
#include "drawFrame.h"
#include "directS.h"
#include "getImputData.h"
#include "moveMyChar.h"
#include "moveEnemy.h"
#include "animationData.h"
#include "midiStream.h"
#include "chkCharHit.h"
#include "setCharData.h"
#include "catchCount.h"
#include "mapData.h"
#include "changeBlock.h"
//**************************************************
//グローバル変数
//**************************************************
//ゲームの状態を取っておく、メイン処理のフラグ
BYTE nGameStatus=GSTATE_TITLE;
//現在のステージ番号
BYTE nStageNum;
//ライフゲージ(ハート)の表示用座標
RECT rcLife[]={
	{128,80,176,96},
	{128,64,176,80},
	{128,48,176,64},
	{128,32,176,48}
};

//メイン処理のテーブル
BOOL (*PlayGame[])(_DDRAW*,_CHAR*,_BGSCROLL*,WORD)={
		Game,		Scroll,		MyCharOut,	MyCharOut,
		GameOver,	GameOver,	GameOver,	GameOver,
		GameClear,	GameClear,	GameClear,	GameClear,
		GameClear,	GameClear,	GameClear,	GameClear,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title
};

//****************************************************
//		メイン処理,ビットマップの描画
//****************************************************
BOOL DrawFrame(_DDRAW *lpDDraw,_CHAR*lpChar)
{
	//------------------------------------------
	//ローカル変数
	//------------------------------------------
	//画像データ転送
	DDBLTFX				ddblt;//Blt関数の設定用
	RECT				rcBK;//転送元座標(バックバッファ-->クライアント領域)
	
	//BG Scrollデータ
	static _BGSCROLL	bgScrl;
	
	//インプットデータ
	WORD				wInputData,//インプットデータを格納
						wKeyInput,//キーボードの情報を受け取る
						wJoyInput;//ジョイスティクの情報を受け取る
	static BOOL			fJoyFlag,/*GetJoyInfoの戻り値を受け取る
								TRUE：ジョイスティク使用可能*/	
						fInput=TRUE;//ジョイスティックとキーボードの
							/*どちらを使うか
								TRUE--->JOY,FALSE--->KEY*/
	
	////////////////////////////////////////////////////////
	//*******入力データの取得*********
	fJoyFlag=GetJoyInfo(&wJoyInput);
	GetKeyInfo(&wKeyInput);
	
	//---Esc Key で終了----
	if(wKeyInput & _ESC_PRS)
		DestroyWindow(gData.hwnd);
	
	//---ジョイスティク<-->キーボードの切り替え
	if(fJoyFlag){
		if(wKeyInput & _F2_PRS)
			fInput ^= 1;
	}else
		fInput = FALSE;
	
	if(fInput)
		wInputData=wJoyInput | (wKeyInput & _FUNC_KEY);
	else
		wInputData=wKeyInput;
	
	//*********プライマリサーフィスを塗りつぶす*******
	ddblt.dwSize=sizeof(ddblt);
	ddblt.dwFillColor=0;
	lpDDraw->lpDDBK->Blt(NULL,NULL,NULL,
		DDBLT_WAIT | DDBLT_COLORFILL,&ddblt);
	//**********************************************************
	//メインの処理
	//**********************************************************
	if(!PlayGame[nGameStatus & GSTATE_MASK](lpDDraw,lpChar,&bgScrl,wInputData))
		return(FALSE);
	//*******************************************************

//*************************************************************

#if(0)
	lpDDraw->VRAMCheck();
	DDTextOut(*lpDDraw);
#endif
	

	if(lpDDraw->fFull)
	{
		//********フリップ処理******************
		lpDDraw->lpDDPR->Flip(NULL,DDFLIP_WAIT);
	}else{
		//********クライアント領域に転送********
		SetRect(&rcBK,0,0,SCREEN_W,SCREEN_H);
		lpDDraw->lpDDPR->Blt(&gData.rcClient,lpDDraw->lpDDBK,&rcBK,
			DDBLT_WAIT,NULL);
	}
	
	//フレームレートの調整
	FrameWait();

	return(TRUE);
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//ゲーム中の主な処理
//キャラクタの発生、移動、当り判定など
/////////////////////////////////////////////////////////////////////////////

//キャラクタの移動関数のテーブル
void (*tblEnemyMove[])(_CHAR*,_BGSCROLL*)={
	DamyMove,EnemyMove00,BlkMove,EnemyMove00,
	EnemyMove00,BlkMove,ItemMove,DamyMove
};

//当り判定後の処理のテーブル(キャラタイプ別)
void (*tblHitAct[][7])(_CHAR*,_CHAR*)={
//	My			En00		Blk			En01		En02		Blk02		Item
	HitActDamy,	HitMy_En,	PiyoMyChar1,HitMy_En,	HitMy_En,	PiyoMyChar1,HitMy_Hart,//My
	HitEn_My,	Enem,		PiyoChar1,	Enem,		HitEn_En02,	HitEn_Blk02,HitActDamy,//En00
	PiyoMyChar2,PiyoChar2,	HitActDamy,	HitBlk_En01,PiyoEn02_2,	HitActDamy,	HitActDamy,//Blk
	HitEn_My,	Enem,		HitEn01_Blk,Enem,		HitEn_En02,	HitEn01_Blk,HitActDamy,//En01
	HitEn_My,	HitEn02_En,	PiyoEn02_1,	HitEn02_En,	Enem,		PiyoEn02_1,	HitActDamy,//En02
	PiyoMyChar2,HitBlk02_En,HitActDamy,	HitBlk_En01,PiyoEn02_2,	HitActDamy,	HitActDamy,//Blk02
	HitHart_My,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy //Item
};

BOOL Game(_DDRAW *lpDDraw,_CHAR* lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	register int i,j;
	RECT rcSrc;

	BYTE nCatchCount;
	_LPMAPDATA lpMap=NULL;
	
	
	
	//BGM一時停止解除
	mdsRestert();
	
	//********Charの移動*********************
	MyCharMove(lpChar + CHAR_MAX,lpBgScrl,wInputData);
	
	for(i=0;i<CHAR_MAX;i++)
	{
		if((lpChar + i)->fLive)
			tblEnemyMove[((lpChar+i)->nType) & 0x07](lpChar+i,lpBgScrl);
	}
	
	//あたり判定*****************************************
	for(i=0;i<CHAR_MAX;i++)
	{
		for(j=i+1;j<CHAR_MAX+1;j++)
		{
			if(((lpChar + i)->fLive)&&((lpChar + j)->fLive))
			{
				if(ChkHitRect((lpChar+i)->hitChk,(lpChar+j)->hitChk))
				{
					tblHitAct[((lpChar + i)->nType) & 0x07]
						[((lpChar + j)->nType) & 0x07]
					(lpChar+i,lpChar+j);	
				}
			}
		}
	}
	
	//********キャラクタのアニメーション**********
	//表示する絵を切り替える
	//マイキャラ
	//ミスした時の処理
	if(!((lpChar + CHAR_MAX)->fLive)){
		
		nGameStatus |=GSTATE_OUT;
		//ミス時のマイキャラ画像
		(lpChar+CHAR_MAX)->rcSrc.left	=5*CHAR_W;
		(lpChar+CHAR_MAX)->rcSrc.top	=3*CHAR_H;
		(lpChar+CHAR_MAX)->rcSrc.right	=6*CHAR_W;
		(lpChar+CHAR_MAX)->rcSrc.bottom	=4*CHAR_H;
	}else//通常時の画像切り替え
		PicChange(lpChar+CHAR_MAX);
	
	//マイキャラ以外
	for(i=0;i<CHAR_MAX;i++)
	{
		if((lpChar + i)->fLive)	PicChange(lpChar+i);
	}
	//*************************************************
	//ビットマップの表示
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);//スクロール座標の更新	
	DrawBg(lpDDraw,lpBgScrl);//Bg表示
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//ライフ(ハート)の表示
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//ブロックを落とす処理
	ChgBlkCount(*lpDDraw,lpChar,lpBgScrl);
	/////////////////////////////////////////////////////
	//クリア判定
	nCatchCount=GetCatchCount();
	lpMap=GetMapData();
	if(nCatchCount==lpMap->nCageCount)
	{
		nGameStatus |=GSTATE_CLEAR;
		CatchCountZero();
		mdsStop();
	}

	//一時停止
	if(wInputData & _ENT_PRS)
		return(Pause());
	
	return(TRUE);	
}


//////////////////////////////////////////////////////////////////////////////////
//ポーズ時の処理
/////////////////////////////////////////////////////////////////////////////////
//スクロール移動量テーブル
int nXScrl[]={
	0,5*_ONE,-5*_ONE,0,
	0,5*_ONE,-5*_ONE,0,
	0,5*_ONE,-5*_ONE,0,
	0,0,0,0
};
int nYScrl[]={
	0,0,0,0,
	5*_ONE,5*_ONE,5*_ONE,0,
	-5*_ONE,-5*_ONE,-5*_ONE,0,
	0,0,0,0
};

//*************************************************************
BOOL Scroll(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	register int i;
	RECT rcSrc;
	mdsPause();
	
	//画面スクロール
	lpBgScrl->nBgX +=nXScrl[wInputData & _DIR_MASK];
	lpBgScrl->nBgY +=nYScrl[wInputData & _DIR_MASK];
	
	if(lpBgScrl->nBgX < lpBgScrl->nXMin)
		lpBgScrl->nBgX=lpBgScrl->nXMin;
	else if(lpBgScrl->nBgX > lpBgScrl->nXMax)
		lpBgScrl->nBgX = lpBgScrl->nXMax;

	if(lpBgScrl->nBgY < lpBgScrl->nYMin)
		lpBgScrl->nBgY=lpBgScrl->nYMin;
	else if(lpBgScrl->nBgY > lpBgScrl->nYMax)
		lpBgScrl->nBgY = lpBgScrl->nYMax;
	
	for(i=0;i<CHAR_MAX+1;i++)
	{
		(lpChar+i)->nXDsp =((lpChar+i)->nXPos-lpBgScrl->nBgX+_HALF)>>16;
		(lpChar+i)->nYDsp =((lpChar+i)->nYPos-lpBgScrl->nBgY+_HALF)>>16;
		SetDrawFlag(lpChar+i);
	}
	//*************************************************
	//ビットマップの表示
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//ライフ(ハート)の表示
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	
	//一時停止解除
	if(wInputData & _ENT_PRS)
		return(Pause());
	
	return(TRUE);		
}
///////////////////////////////////////////////////////////////////////////////


//*************************************************************
//ミス時の処理
//*************************************************************
BOOL MyCharOut(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
		
	_CHAR* lpMyChar=NULL;
	static int nYSpd =-0x98000;
	RECT rcSrc;
	lpMyChar=lpChar + CHAR_MAX;
	
	lpMyChar->nYPos +=nYSpd;
	nYSpd +=_G;
	lpMyChar->nXDsp =(lpMyChar->nXPos-lpBgScrl->nBgX+_HALF)>>16;
	lpMyChar->nYDsp =(lpMyChar->nYPos-lpBgScrl->nBgY+_HALF)>>16;
	
	if(lpMyChar->nYDsp > SCREEN_H)
	{
		nYSpd =-0x98000;
		nGameStatus |=GSTATE_GOVER;
		CatchCountZero();
		mdsStop();
	}
	//*************************************************
	//ビットマップの表示
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//ライフ(ハート)の表示
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	return (TRUE);
}
///////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
//ゲームオーバー時の処理
/////////////////////////////////////////////////////////////
BOOL GameOver(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT	rcGover={0,0,388,52},
			rcContinue={271,103,406,164},
			rcCurSor={406,103,420,131},
			rcSrc;
	int nYDest;
	static WORD wCount;
	static BOOL fCurSor=TRUE,fContinue=TRUE;
	/////////////////////////////////////////////////////////
	if(wInputData & _UP)
		fContinue=TRUE;
	else if(wInputData & _DOWN)
		fContinue=FALSE;

	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS))
	{
		if(fContinue)
		{
			return(GameStart(lpChar));
		}else
		{
			nStageNum=0;
			return(ToTitle());
		}
	}
	//////////////////////////////////////////////////////
	if(!mdsPlay(const_cast<char*>("mds\\gover.mds"),FALSE))
				return(FALSE);
	//*************************************************
	//ビットマップの表示
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//ライフ(ハート)の表示
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//GAME OVER メッセージ表示
	//***********************************************
	lpDDraw->lpDDBK->BltFast(120,96,
		lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcGover,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	lpDDraw->lpDDBK->BltFast(252,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcContinue,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fCurSor)
	{
		if(fContinue)
			nYDest=288;
		else
			nYDest=316;

		lpDDraw->lpDDBK->BltFast(224,nYDest,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcCurSor,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	if(!(++wCount & 0x07))
		fCurSor ^=TRUE;
	
	return(TRUE);
}
/////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////
//ゲームクリアー時の処理
/////////////////////////////////////////////////////////////
BOOL GameClear(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT rcClear={0,52,473,103};
	RECT rcEndKey={0,103,271,164};
	RECT rcSrc;
	static WORD wCount;
	static BOOL fEndKey;
	
	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS)){
		nStageNum++;
		if(nStageNum < STAGE_MAX)
			return(GameStart(lpChar));
		else{
			nStageNum=0;
			return(ToTitle());
		}
	}
	if(!mdsPlay(const_cast<char*>("mds\\gclear.mds"),FALSE))
				return(FALSE);
	//*************************************************
	//ビットマップの表示
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//ライフ(ハート)の表示
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//GAME CLEAR メッセージ表示
	//***********************************************
	lpDDraw->lpDDBK->BltFast(74,96,
		lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcClear,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fEndKey)
	{
		lpDDraw->lpDDBK->BltFast(176,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcEndKey,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	if(!(++wCount & 0x3f))
		fEndKey ^=TRUE;


	return(TRUE);
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//タイトル画面
////////////////////////////////////////////////////////////////////////////////
BOOL Title(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT rcTitle={0,0,OFF_TITLE_W,OFF_TITLE_H};
	RECT rcEndKey={0,103,271,164};
	static BOOL fEndKey=TRUE;
	static WORD wCount=0;

	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS))
		return(GameStart(lpChar));

	lpDDraw->lpDDBK->BltFast(0,0,
		lpDDraw->lpDDOF[OFFSCRN_TITLE],&rcTitle,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fEndKey)
	{
		lpDDraw->lpDDBK->BltFast(176,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcEndKey,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	
	if(!(++wCount & 0x3f))
		fEndKey ^=TRUE;
	
	return(TRUE);
}
////////////////////////////////////////////////////////////////////////////


//*****************************************************************************
///////////////////////////////////////////////////////////////////////////////
//ENTER KEY を押した時の処理
///////////////////////////////////////////////////////////////////////////////
//タイトルに戻る
BOOL ToTitle()
{
	DSoundPlay(SOUND_PAUSE);
	nGameStatus |=GSTATE_TITLE;
	mdsStop();
	if(!mdsPlay(const_cast<char*>("mds\\opning.mds"),TRUE))
		return(FALSE);
	
	return(TRUE);
}
//ポーズ<-->再生の切り替え
BOOL Pause()
{
	nGameStatus ^=GSTATE_PAUSE;
	DSoundPlay(SOUND_PAUSE);
	return(TRUE);
}
//ゲームスタート
BOOL GameStart(_CHAR* lpChar)
{
	
	DSoundPlay(SOUND_PAUSE);
	LPCSTR lpszFilePath[]={
		"mapData\\stage0.map",
		"mapData\\stage1.map",
		"mapData\\stage2.map",
		"mapData\\stage3.map",
		"mapData\\stage4.map"
	};

	//マップファイルの読み込み
	if(!LoadMapData(lpszFilePath[nStageNum]))
		return(FALSE);
	
	//キャラクタの配置
	SetUpChar(lpChar);
	
	//BGM再生
	mdsStop();
	if(!mdsPlay(const_cast<char*>("mds\\q2.mds"),TRUE))
		return(FALSE);

	//ゲームステータスフラグ切り替え
	nGameStatus =GSTATE_GAME;

	return(TRUE);
}
//******************************************************************************
//---------------------------------------------------------
//		クリッピング処理
//---------------------------------------------------------
void Clipping(int* lpXDsp,int* lpYDsp,RECT *lprcDsp)
{
	int nWidth,nHeight;
	nWidth	=lprcDsp->right - lprcDsp->left;
	nHeight	=lprcDsp->bottom - lprcDsp->top;
	if(*lpXDsp < 0){
		lprcDsp->left +=(~(*lpXDsp) + 1);
		*lpXDsp = 0;
	}else if(*lpXDsp >(SCREEN_W - nWidth)){
		lprcDsp->right -= *lpXDsp-(SCREEN_W - nWidth);
	}
	
	if(*lpYDsp < 0){
		lprcDsp->top +=~(*lpYDsp) + 1;
		*lpYDsp = 0;
	}else if(*lpYDsp >(SCREEN_H - nHeight)){
		lprcDsp->bottom -= *lpYDsp -(SCREEN_H - nHeight);
	}
}
////////////////////////////////////////////////////////////
//		文字の表示
////////////////////////////////////////////////////////////
void DDTextOut(_DDRAW *lpDDraw)
{
	HDC			hdc;
	char		str[256];	
	BYTE	nCatchCount;

	nCatchCount	=GetCatchCount();
	
	lpDDraw->lpDDBK->GetDC(&hdc);
	wsprintf(str,"捕まえている敵:%d匹",nCatchCount);
	TextOut(hdc,200,0,str,lstrlen(str));
	lpDDraw->lpDDBK->ReleaseDC(hdc);
	
}

/////////////////////////////////////////////////////////
//スクロールデータの設定
///////////////////////////////////////////////////////
void SetScrollData(_BGSCROLL *lpBgScrl)
{
	_LPMAPDATA lpMapData=NULL;

	lpMapData=GetMapData();

	lpBgScrl->nXMin	=0;//X座標は:0～マップ右端より一画面分左
	lpBgScrl->nXMax	=((lpMapData->wMapW - 20)<<5)*_ONE;
	lpBgScrl->nYMin	=0;//Y座標は:0～マップの下の端より１画面分上
	lpBgScrl->nYMax	=((lpMapData->wMapH - 15)<<5)*_ONE;
	if(lpBgScrl->nXMax<0)
		lpBgScrl->nXMax=0;
	if(lpBgScrl->nYMax<0)
		lpBgScrl->nYMax=0;
	//ブロック単位でのスクロール座標
	//スクロール座標が左上端から何番目のブロックを指しているか
	lpBgScrl->wXIndex	=((lpBgScrl->nBgX +_HALF)>>16)>>5;
	lpBgScrl->wYIndex	=((lpBgScrl->nBgY + _HALF)>>16)>>5;
	//
	lpBgScrl->nXAdj	=((lpBgScrl->nBgX + _HALF)>>16) & 31;
	lpBgScrl->nYAdj	=((lpBgScrl->nBgY + _HALF)>>16) & 31;
}
//////////////////////////////////////////////////////////////////////////////
//BGマップの表示
////////////////////////////////////////////////////////////////////////////
/*BGチップ画像データ*/
RECT rcBgSrc[]={
	{0,			BMP_BL_Y,		CHAR_W,		BMP_BL_Y + CHAR_H},
	{CHAR_W,	BMP_BL_Y,		2*CHAR_W,	BMP_BL_Y + CHAR_H},
	{2*CHAR_W,	BMP_BL_Y,		3*CHAR_W,	BMP_BL_Y + CHAR_H},
	{3*CHAR_W,	BMP_BL_Y,		4*CHAR_W,	BMP_BL_Y + CHAR_H},
	{2*CHAR_W,	BMP_BL_Y+CHAR_H,3*CHAR_W,	BMP_BL_Y + 2*CHAR_H}
};
void DrawBg(_DDRAW *lpDDraw,_BGSCROLL *lpBgScrl){	
	
	register int i,j;
	RECT rcSrc;
		
	int nXDest,nYDest;
	WORD X,Y;
	_LPBGDATA lpBgTmp=NULL;
	_LPMAPDATA lpMapData=NULL;
	
	lpMapData=GetMapData();
	WORD loopX,loopY;
	loopX=(lpMapData->wMapW < 21)? lpMapData->wMapW : 21;
	loopY=(lpMapData->wMapH < 16)? lpMapData->wMapH : 16;
	//---------------------------------------------------------------------------------
	//画面端、１番上の１列
	for(j=0;j<loopX;j++)
	{
		Y=lpBgScrl->wYIndex + 0;
		X=lpBgScrl->wXIndex + j;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;
		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=(j<<5)- lpBgScrl->nXAdj;
		nYDest	= 0 - lpBgScrl->nYAdj;
		//----クリッピング処理------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----オフスクリーンからバックバファに転送---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	//----------------------------------------------------------------------------------
	//上下の端以外
	for(i=1;i<(loopY - 1);i++)
	{
		//------------------------------------------------------
		//左端の縦１列
		Y=lpBgScrl->wYIndex + i;
		X=lpBgScrl->wXIndex + 0;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=0 - lpBgScrl->nXAdj;
		nYDest	=(i<<5)-lpBgScrl->nYAdj;;
		//----クリッピング処理------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----オフスクリーンからバックバファに転送---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		
		//--------------------------------------------------------
		//左右の端以外（真中のパーツはクリッピング不要）
		for(j=1;j<(loopX - 1);j++)
		{
			Y=lpBgScrl->wYIndex + i;
			X=lpBgScrl->wXIndex + j;
			X %=lpMapData->wMapW;
			Y %=lpMapData->wMapH;
			lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

			rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
			nXDest	=(j<<5) - lpBgScrl->nXAdj;
			nYDest	=(i<<5) - lpBgScrl->nYAdj;
			//----オフスクリーンからバックバファに転送---------
			lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
				lpDDraw->lpDDOF[0],&rcSrc,
				DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}

		//-------------------------------------------------------------------
		//右端の縦１列
		Y=lpBgScrl->wYIndex + i;
		X=lpBgScrl->wXIndex + (loopX - 1);
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=((loopX-1)<<5)-lpBgScrl->nXAdj;
		nYDest	=(i<<5)- lpBgScrl->nYAdj;
		//----クリッピング処理------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----オフスクリーンからバックバファに転送---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	
	}
	//--------------------------------------------------------------------------------
	//画面端、１番下の１列
	for(j=0;j<loopX;j++)
	{
		Y=lpBgScrl->wYIndex + (loopY-1);
		X=lpBgScrl->wXIndex + j;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=(j<<5)-lpBgScrl->nXAdj;
		nYDest	=((loopY-1)<<5) - lpBgScrl->nYAdj;
		//----クリッピング処理------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----オフスクリーンからバックバファに転送---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	
}
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//キャラクタの表示
/////////////////////////////////////////////////////////////////////////////////
void DrawCharctor(_DDRAW *lpDDraw,_CHAR* lpChar)
{
	RECT rcSrc;
	int nXDest,nYDest;
	register int i;
	for(i=0;i < CHAR_MAX ;i++)
	{	
		if(((lpChar + i)->fLive)&&((lpChar + i)->fDraw))
		{
			//--------------------------------
			rcSrc	=(lpChar + i)->rcSrc;
			nXDest	=(lpChar + i)->nXDsp;
			nYDest	=(lpChar + i)->nYDsp;
			//----クリッピング処理------------
			Clipping(&nXDest,&nYDest,&rcSrc);
			//----オフスクリーンからバックバファに転送---------
			lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
				lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
				DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
			//------------------------------------
		}
	}
	if((lpChar + CHAR_MAX)->fDraw)
	{
		//--------------------------------
		rcSrc	=(lpChar + i)->rcSrc;
		nXDest	=(lpChar + i)->nXDsp;
		nYDest	=(lpChar + i)->nYDsp;
		//----クリッピング処理------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----オフスクリーンからバックバファに転送---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		//------------------------------------
	}
}

////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//フレームレートの調整
//-------------------------------------------------------------------------------
void FrameWait(){
	static DWORD dwTimeNew,dwTimeOld;
	
	do{
		dwTimeNew=timeGetTime();
	}while(dwTimeNew-dwTimeOld<17);
	dwTimeOld=dwTimeNew;
}
/////////////////////////////////////////////////////////////////////////////////
