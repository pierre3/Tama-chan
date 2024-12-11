/*chngeBlock.cpp*/
//**************************
//インクルード
//*************************
#include "changeBlock.h"
#include "SetCharData.h"
#include "mapData.h"
#include "drawFrame.h"
#include "chkCharHit.h"
//******************************************************
//マップデータのブロックをキャラクタデータに置きかえる関数
//******************************************************
void ChangeBlock(_CHAR* lpChar,int nXIndex,int nYIndex){
	register int i;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	//マップデータから削除
	
	(lpBg + lpMap->wMapW * nYIndex)[nXIndex].nType		=CHIP_TYPE_BG;
	(lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsNum	=PARTS_BG;
	//マップデータのブロックをキャラクタのデータに置き換える
	//配列の空き要素を探してブロックをキャラクタとして設定
	for(i=0;i<CHAR_MAX;i++)
	{
		if(!(lpChar + i)->fLive)
		{
			if((lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsOld==PARTS_BLK00)
				SetBlk00(lpChar + i,i,nXIndex,nYIndex);
			else if((lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsOld==PARTS_BLK02)
				SetBlk02(lpChar + i,i,nXIndex,nYIndex);
			break;
		}
	}
}
//************************************************************
//置き換えのタイミングをカウントする
//************************************************************
void ChgBlkCount(_DDRAW DDraw,_CHAR* lpChar,_BGSCROLL *lpBgScrl){
	RECT rcSrc={
		0,
		BMP_BL_Y + CHAR_H,
		CHAR_W,
		BMP_BL_Y + 2*CHAR_H
	};//ブロック点滅用画像データ
	int nXDest,nYDest;//点滅画像の転送先
	register int i,j,k;//ループカウンタ
	_HITCHK hitBlk;

	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	for(i=0;i<lpMap->wMapH;i++){
		for(j=0;j<lpMap->wMapW;j++){
			
			//落下カウント中
			if((lpBg + lpMap->wMapW * i)[j].fFallCnt){
				//カウントダウン
				(lpBg + lpMap->wMapW * i)[j].wFallCnt--;
				
				//ブロックの点滅描画
				if(!((lpBg + lpMap->wMapW * i)[j].wFallCnt & 0x07)){
					nXDest=(j<<5)-((lpBgScrl->nBgX + _HALF)>>16);
					nYDest=(i<<5)-((lpBgScrl->nBgY + _HALF)>>16);
					Clipping(&nXDest,&nYDest,&rcSrc);
					//----オフスクリーンからバックバファに転送---------
					DDraw.lpDDBK->BltFast(nXDest,nYDest,
						DDraw.lpDDOF[0],&rcSrc,
						DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				}
			}
			//落下カウントが０になった時
			if(!(lpBg + lpMap->wMapW * i)[j].wFallCnt){
				ChangeBlock(lpChar,j,i);//マップデータのBGチップをキャラクタデータに置きかえる
				(lpBg + lpMap->wMapW * i)[j].wFallCnt=FALL_CNT;//落下カウントを元に戻す
				(lpBg + lpMap->wMapW * i)[j].fFallCnt=FALSE;//落下カウントフラグをoffにする
				(lpBg + lpMap->wMapW * i)[j].fResetCnt=TRUE;//リセットカウントフラグon
			}
			//リセットカウント中
			if((lpBg + lpMap->wMapW * i)[j].fResetCnt)
				//カウントダウン
				(lpBg + lpMap->wMapW * i)[j].wResetCnt--;

			//リセットカウントが０になったら//////////////////////////////
			if(!(lpBg + lpMap->wMapW * i)[j].wResetCnt){
				//マップデータを元に戻す
				(lpBg + lpMap->wMapW * i)[j].nPartsNum	
					=(lpBg + lpMap->wMapW * i)[j].nPartsOld;
				(lpBg + lpMap->wMapW * i)[j].nType	=CHIP_TYPE_BLK;
				(lpBg + lpMap->wMapW * i)[j].wResetCnt=RESET_CNT;//リセットカウントを戻す
				(lpBg + lpMap->wMapW * i)[j].fResetCnt=FALSE;//リセットカウントフラグoff
				
				//復活する場所にキャラがいないか調べる
				hitBlk.rcHit.left	=(j<<5)<<16;
				hitBlk.rcHit.top	=(i<<5)<<16;
				hitBlk.rcHit.right	=hitBlk.rcHit.left + (CHAR_W<<16);
				hitBlk.rcHit.bottom=hitBlk.rcHit.top + (CHAR_H<<16);
				hitBlk.nHitW		=CHAR_W<<16;
				hitBlk.nHitH		=CHAR_H<<16;
				for(k=0;k<(CHAR_MAX + 1);k++)
				{
					if((lpChar + k)->fLive)
					{
						if(ChkHitRect((lpChar+k)->hitChk,hitBlk))
						{
							if((lpChar+k)->nYPos >= hitBlk.rcHit.top)
								(lpChar+k)->nYPos	=hitBlk.rcHit.bottom;
							else
								(lpChar+k)->nYPos	=hitBlk.rcHit.top - (CHAR_H<<16);
						}	
					}
				}
			}
			/////////////////////////////////////////////////////////////
		}
	}

}
