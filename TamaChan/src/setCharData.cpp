/*setCharData.cpp*/
//***********************
//インクルード
//**********************
#include "SetCharData.h"
#include "mapData.h"
#include "chkCharHit.h"
#include "MIDIStream.h"
//********************************************
//キャラクタの初期設定を行う関数
//********************************************
//マイキャラ
void SetMyChar(_CHAR *lpChar,int nXStart,int nYStart)
{
	ZeroMemory(lpChar,sizeof(_CHAR));
	lpChar->nXPos			=nXStart;
	lpChar->nYPos			=nYStart;
	
	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;

	lpChar->nDashSPD		=0;

	lpChar->nLife			=LIFE_MAX;
	SetRect(&lpChar->rcSrc,0,0,0,0);
	
	lpChar->hitChk.nHitW	=(CHAR_W - 2) * _ONE;
	lpChar->hitChk.nHitH	=(CHAR_H - 2) * _ONE;
	SetHitRect(lpChar,1*_ONE,1*_ONE);
	lpChar->hitChk.rcHitOld		=lpChar->hitChk.rcHit;
	
	lpChar->fLive			=TRUE;
	lpChar->fDraw			=TRUE;
	lpChar->nType			=TYPE_MC;
	lpChar->nStatus		=_STATUS_JUMP;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex	=0;
	lpChar->wCharNum		=CHAR_MAX;
}
//敵キャラ（No00）
void SetEn00(_CHAR *lpChar,WORD wChNum,int nXStart,int nYStart)
{
	ZeroMemory(lpChar,sizeof(_CHAR));
	lpChar->nXPos			=nXStart;
	lpChar->nYPos			=nYStart;
	
	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;

	lpChar->nDashSPD		=0;

		
	SetRect(&lpChar->rcSrc,0,0,0,0);
	
	lpChar->hitChk.nHitW			=(CHAR_W-2)* _ONE;
	lpChar->hitChk.nHitH			=(CHAR_H-2) * _ONE;
	SetHitRect(lpChar,1*_ONE,1*_ONE);
	lpChar->hitChk.rcHitOld		=lpChar->hitChk.rcHit;
	
	lpChar->fLive			=TRUE;
	lpChar->fDraw			=TRUE;
	lpChar->nType			=TYPE_ENEM00;
	lpChar->nStatus		=0;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex	=0;
	lpChar->wCharNum		=wChNum;
}
//敵キャラ（No01）
void SetEn01(_CHAR *lpChar,WORD wChNum,int nXStart,int nYStart)
{
	ZeroMemory(lpChar,sizeof(_CHAR));
	lpChar->nXPos			=nXStart;
	lpChar->nYPos			=nYStart;
	
	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;

	lpChar->hitChk.nHitW			=(CHAR_W-2)* _ONE;
	lpChar->hitChk.nHitH			=(CHAR_H-2) * _ONE;
	SetHitRect(lpChar,1*_ONE,1*_ONE);
	lpChar->hitChk.rcHitOld		=lpChar->hitChk.rcHit;
	
	lpChar->fLive			=TRUE;
	lpChar->fDraw			=FALSE;
	lpChar->nType			=TYPE_ENEM01;
	lpChar->nStatus		=0;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex	=0;
	lpChar->wCharNum		=wChNum;
}
//敵キャラ（No02）
void SetEn02(_CHAR *lpChar,WORD wChNum,int nXStart,int nYStart)
{
	ZeroMemory(lpChar,sizeof(_CHAR));
	lpChar->nXPos		=nXStart;
	lpChar->nYPos		=nYStart;
	
	lpChar->nXDsp		=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp		=(lpChar->nYPos +_HALF)>>16;

	lpChar->hitChk.nHitW	=(CHAR_W-2)* _ONE;
	lpChar->hitChk.nHitH	=(CHAR_H-2) * _ONE;
	SetHitRect(lpChar,1*_ONE,1*_ONE);
	lpChar->hitChk.rcHitOld		=lpChar->hitChk.rcHit;
	
	lpChar->fLive		=TRUE;
	lpChar->fDraw		=FALSE;
	lpChar->nType		=TYPE_ENEM02;
	lpChar->nStatus		=0;
	
	lpChar->wAnimeCnt	=0;
	lpChar->nAnimeIndex	=0;
	lpChar->wCharNum	=wChNum;
}

//ブロック
void SetBlk00(_CHAR* lpChar,WORD wChNum,int nXIndex,int nYIndex){
	ZeroMemory(lpChar,sizeof(_CHAR));
	lpChar->nXPos			=(nXIndex<<5)<<16;
	lpChar->nYPos			=(nYIndex<<5)<<16;

	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;

	lpChar->nDashSPD		=0;
	
	lpChar->nXSPD			=0;
	lpChar->nYSPD			=0;
	
	SetRect(&lpChar->rcSrc,CHAR_W,BMP_BL_Y,2*CHAR_W,BMP_BL_Y + CHAR_H);
	lpChar->hitChk.nHitW	=(CHAR_W-8)* _ONE;
	lpChar->hitChk.nHitH	=CHAR_H * _ONE;
	SetHitRect(lpChar,4*_ONE,0*_ONE);
	lpChar->hitChk.rcHitOld	=lpChar->hitChk.rcHit;
	
	lpChar->nMapX			=nXIndex;
	lpChar->nMapY			=nYIndex;

	lpChar->fLive			=TRUE;
	lpChar->fDraw			=TRUE;
	lpChar->nType			=TYPE_BLK00;
	lpChar->nStatus		=0;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex	=0;
	lpChar->wCharNum		=wChNum;

}

void SetBlk02(_CHAR* lpChar,WORD wChNum,int nXIndex,int nYIndex){
	ZeroMemory(lpChar,sizeof(_CHAR));

	lpChar->nXPos			=(nXIndex<<5)<<16;
	lpChar->nYPos			=(nYIndex<<5)<<16;	
	
	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;

	lpChar->nDashSPD		=0;
	
	lpChar->nXSPD			=0;
	lpChar->nYSPD			=0;
	
	SetRect(&lpChar->rcSrc,
		2*CHAR_W,BMP_BL_Y + CHAR_H,
		3*CHAR_W,BMP_BL_Y + 2*CHAR_H);
	
	lpChar->hitChk.nHitW	=(CHAR_W-16)* _ONE;
	lpChar->hitChk.nHitH	=CHAR_H * _ONE;
	
	SetHitRect(lpChar,8*_ONE,0*_ONE);
	lpChar->hitChk.rcHitOld		=lpChar->hitChk.rcHit;
	
	lpChar->nMapX			=nXIndex;
	lpChar->nMapY			=nYIndex;

	lpChar->fLive			=TRUE;
	lpChar->fDraw			=TRUE;
	lpChar->nType			=TYPE_BLK02;
	lpChar->nStatus			=0;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex		=0;
	lpChar->wCharNum		=wChNum;

}
void SetItem(_CHAR* lpChar,WORD wCharNum,int nXPos,int nYPos)
{
	ZeroMemory(lpChar,sizeof(_CHAR));

	lpChar->nXPos			=nXPos;
	lpChar->nYPos			=nYPos;	
	
	lpChar->nXDsp			=(lpChar->nXPos +_HALF)>>16;
	lpChar->nYDsp			=(lpChar->nYPos +_HALF)>>16;
	
	lpChar->hitChk.nHitW	=16* _ONE;
	lpChar->hitChk.nHitH	=16* _ONE;
	
	lpChar->fLive			=TRUE;
	lpChar->fDraw			=TRUE;
	lpChar->nType			=TYPE_HART;
	lpChar->nStatus			=0;
	
	lpChar->wAnimeCnt		=0;
	lpChar->nAnimeIndex		=0;
	lpChar->wCharNum		=wCharNum;	
}
/////////////////////////////////////////////////////////////////////////
//キャラデータの初期設定
/////////////////////////////////////////////////////////////////////////
void SetUpChar(_CHAR* lpChar)
{
	register int i;
	_LPMAPDATA lpMap;
	int X,Y;
	
	/////////////////////////////////////////////
	lpMap=GetMapData();
	
	ZeroMemory(lpChar,sizeof(_CHAR) * CHAR_MAX);
	
	
	//マイキャラ
	X=((int)(lpMap->myCharPos.wX)<<5)<<16;
	Y=((int)(lpMap->myCharPos.wY)<<5)<<16;
	SetMyChar(lpChar + CHAR_MAX,X,Y);//マイキャラは配列の最後の要素に作る
	
	//敵キャラ
	
	for(i=0;i<lpMap->nCageCount;i++)
	{
		X=((int)((lpMap->lpEnemyPos + i)->wX)<<5)<<16;
		Y=((int)((lpMap->lpEnemyPos + i)->wY)<<5)<<16;
		SetEn00(lpChar + i,i,X,Y);									
	}

}
