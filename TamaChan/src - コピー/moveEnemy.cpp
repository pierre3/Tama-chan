/*moveEnemy.cpp*/
//*************************
//インクルード
//**************************
#include "gameMain.h"
#include "setCharData.h"
#include "changeBlock.h"
#include "chkCharHit.h"
#include "directS.h"
#include "chaceMyChar.h"
#include "enemyActPattern.h"
#include "moveEnemy.h"
#include "sin_data.h"
#include "mapData.h"

/////////////////////////////////////////////////////////
//キャラクタの表示、非表示を切り替える関数
/////////////////////////////////////////////////////////
void SetDrawFlag(_CHAR *lpChar){
	
	if((lpChar->nYDsp >= -CHAR_H)&&(lpChar->nYDsp <= SCREEN_H))
		lpChar->fDraw=TRUE;
	else
		lpChar->fDraw=FALSE;

	if((lpChar->nYDsp >= -CHAR_W)&&(lpChar->nYDsp <= SCREEN_W))
		lpChar->fDraw=TRUE;
	else
		lpChar->fDraw=FALSE;

}

///////////////////////////////////////////////////////////
//キャラクタの移動処理
///////////////////////////////////////////////////////////
//ダミー
void DamyMove(_CHAR*,_BGSCROLL*){
	return;
}
//////////////////////////////////////////////////////////
//ブロック
void BlkMove(_CHAR*lpChar,_BGSCROLL *lpBgScrl){
	
	WORD wLoopMax,
		wIMidX,wIBottom;
	int nShfXTmp,nShfYTmp;

	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	lpChar->nYSPD +=0x8000;
	
	wLoopMax	=lpChar->nYSPD >>15;
	
	for(WORD i=0;i<wLoopMax;i++){
		
		nShfXTmp	=(lpChar->nXPos+_HALF)>>16;
		nShfYTmp	=(lpChar->nYPos+_HALF)>>16;
		
		wIBottom	=(nShfYTmp +31)>>5;
		wIMidX		=(nShfXTmp + 15)>>5;
	
		
		if((lpBg + lpMap->wMapW * wIBottom)[wIMidX].nType==CHIP_TYPE_BLK){		
			lpChar->fLive=FALSE;
			DSoundPlay(SOUND_BLKBREAK);
			return;
		}
		lpChar->nYPos   +=0x8000;
	}
	
		
	if(lpChar->nYPos > lpMap->wMapW*CHAR_W*_ONE){
		lpChar->fLive=FALSE;
		return;
	}
		
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp = (lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	SetDrawFlag(lpChar);
	
	SetHitRect(lpChar,8*_ONE,0);
}
///////////////////////////////////////////////////////////////////
//敵キャラ
//-------------------------------------------------------


//敵キャラの移動処理テーブル（ステータス別に振り分ける）
void (*MoveTblEn00[])(_CHAR*)={
		EnemyLeft,EnemyRight,EnemyFall,EnemyFall,
		EnemyLeft,EnemyRight,EnemyFall,EnemyFall,
		EnemyDown,EnemyDown,EnemyDown,EnemyDown,
		EnemyUp,EnemyUp,EnemyUp,EnemyUp,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,

		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,

		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall
		
	};
//------------------------------------------------------
void EnemyMove00(_CHAR*lpChar,_BGSCROLL *lpBgScrl){
	
	//ローカル変数
	_CHAR* lpMyChar=NULL;//マイキャラのアドレスを受け取る
	
	int nXIndex,nYIndex,nXTmp,nYTmp,
		nMyXIndex,nMyYIndex,nMyXTmp,nMyYTmp;
	
	_LPMAPDATA lpMap=NULL;
	BYTE* lpFloorData=NULL;
	lpMap=GetMapData();
	lpFloorData=lpMap->lpFloorData;
	
	//マイキャラのアドレスを計算
	lpMyChar=lpChar +( CHAR_MAX - lpChar->wCharNum);
	
	//移動処理
	//nStatusで移動処理を振り分ける
	if(!lpChar->fWait)
		MoveTblEn00[lpChar->nStatus & _STATUS_MASK](lpChar);
	lpChar->fWait=FALSE;
	
	
	//マイキャラを追いかける
	
	//マップ上での位置を計算
	//敵キャラ
	nXTmp=(lpChar->nXPos+_HALF)>>16;
	nYTmp=(lpChar->nYPos+_HALF)>>16;
	nXIndex=(nXTmp+15)>>5;
	nYIndex=(nYTmp+31)>>5;
	//マイキャラ
	nMyXTmp=(lpMyChar->nXPos+_HALF)>>16;
	nMyYTmp=(lpMyChar->nYPos+_HALF)>>16;
	nMyXIndex=(nMyXTmp+15)>>5;
	nMyYIndex=(nMyYTmp+31)>>5;

	/*マイキャラとの位置関係を調べて
						マイキャラを追いかける処理*/
	
	//マイキャラが同じ階にいる
	if(lpFloorData[nYIndex]==lpFloorData[nMyYIndex])
	{

		if(lpMyChar->nStatus & _STATUS_UPDOWN)
		{
			if(lpChar->nYPos > lpMyChar->nYPos)
				ChaceMc_Up(lpChar);
			else
				ChaceMc_Lo(lpChar);
		}else if(nXIndex <= nMyXIndex)
			//同じ階でマイキャラが右にいる時の処理
			ChaceMc_Right(lpChar);
		else if(nXIndex > nMyXIndex)
			//同じ階でマイキャラが左にいる時の処理
			ChaceMc_Left(lpChar);
		
	//マイキャラが上にいる
	}else if(lpFloorData[nYIndex] > lpFloorData[nMyYIndex])
	{
		ChaceMc_Up(lpChar);
	//マイキャラが下にいる
	}else{
		ChaceMc_Lo(lpChar);
	}
	
	
	//表示座標の計算//////////////////////////////////////////////////////
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp =(lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	//表示フラグのon-off
	SetDrawFlag(lpChar);
	/////////////////////////////////////////////////
	//当り判定用RECTの更新
	SetHitRect(lpChar,1*_ONE,1*_ONE);
}
///////////////////////////////////////////////////////////////////////////////////////
//アイテム
void ItemMove(_CHAR	*lpChar,_BGSCROLL *lpBgScrl)
{
	static WORD wMoveCnt;
	
	lpChar->nXSPD	=(sin_tbl[wMoveCnt & 511]);
	lpChar->nYPos	-=ITEM_MOVE_Y;
	lpChar->nXPos	+=lpChar->nXSPD;
	
	wMoveCnt	+=4;
	if(lpChar->nYPos < 0)
		lpChar->fLive=FALSE;
	
	//表示座標の計算//////////////////////////////////////////////////////
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp =(lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	//表示フラグのon-off
	SetDrawFlag(lpChar);
	/////////////////////////////////////////////////
	//当り判定用RECTの更新
	SetHitRect(lpChar,0*_ONE,0*_ONE);

}