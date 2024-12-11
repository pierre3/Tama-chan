/*chkCharHit.cpp*/
//************************
//インクルード
//************************
#include "chkCharHit.h"
#include "enemyWait.h"
#include "directS.h"
#include "setCharData.h"
#include "catchCount.h"
#include "mapData.h"

//****************************
//
//****************************
//************************************************************
//判定用座標の設定
void SetHitRect(_CHAR*lpChar,
				int nXAdj,	//X修正値
				int nYAdj){	//Y修正値
	lpChar->hitChk.rcHit.left  =lpChar->nXPos+nXAdj;
	lpChar->hitChk.rcHit.right =lpChar->hitChk.rcHit.left
								+ lpChar->hitChk.nHitW;
	lpChar->hitChk.rcHit.top=lpChar->nYPos+nYAdj;
	lpChar->hitChk.rcHit.bottom=lpChar->hitChk.rcHit.top 
								+ lpChar->hitChk.nHitH;
}
//当りチェック
BOOL ChkHitRect(_HITCHK hit1,_HITCHK hit2){
	int L1,R1,T1,B1,
		L2,R2,T2,B2;
	if(hit1.nHitW >= hit2.nHitW){
		L1	=hit1.rcHit.left;
		R1	=hit1.rcHit.right;
		L2	=hit2.rcHit.left;
		R2	=hit2.rcHit.right;
	}else{
		L1	=hit2.rcHit.left;
		R1	=hit2.rcHit.right;
		L2	=hit1.rcHit.left;
		R2	=hit1.rcHit.right;
	}

	if(hit1.nHitH >= hit2.nHitH){
		T1	=hit1.rcHit.top;
		B1	=hit1.rcHit.bottom;
		T2	=hit2.rcHit.top;
		B2	=hit2.rcHit.bottom;
	}else{
		T1	=hit2.rcHit.top;
		B1	=hit2.rcHit.bottom;
		T2	=hit1.rcHit.top;
		B2	=hit1.rcHit.bottom;
	}
	if((L2>=L1 && L2<= R1)||(R2>=L1 && R2<=R1 ))
		if((T2>=T1 && T2<=B1)||(B2>=T1 && B2<=B1))
			return TRUE;

	
	return FALSE;		
}



//**********************************************************
//当り発生後の処理
//***********************************************************

////////////////////////////////////////////////////////////
//ダミー
void HitActDamy(_CHAR* lpChar1,_CHAR* lpChar2)
{
	return;
}

//////////////////////////////////////////////////////////
//敵キャラを気絶させる
/////////////////////////////////////////////////////////
void PiyoChar1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	//敵キャラが逃げようとしている
	if((lpChar1->nStatus & _ENEM_CAGE)
		&& (lpChar1->nStatus & _ENEM_ESCAPE))
	{
		lpChar1->nStatus &=~_ENEM_ESCAPE;
		lpChar1->wCageCnt=0;
		DSoundPlay(SOUND_HITCAGE);
	}//それ以外
	else{
		lpChar1->nStatus |=_ENEM_PIYO;
		DSoundPlay(SOUND_HIT);
	}
	lpChar2->fLive	=FALSE;
	
	
}
void PiyoChar2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar2->nStatus & _ENEM_CAGE)
		&& (lpChar2->nStatus & _ENEM_ESCAPE))
	{
		lpChar2->nStatus &=~_ENEM_ESCAPE;
		lpChar2->wCageCnt=0;
		DSoundPlay(SOUND_HITCAGE);
	}else{
		lpChar1->nStatus |=_ENEM_PIYO;
		DSoundPlay(SOUND_HIT);
	}
	lpChar1->fLive =FALSE;
	
}
////////////////////////////////////////////////////////
//enemy02を気絶させてenemy01に変える
///////////////////////////////////////////////////////
void PiyoEn02_1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar1->nType	=TYPE_ENEM01;
		lpChar1->nStatus |=_ENEM_PIYO;
	}
	lpChar2->fLive =FALSE;
	DSoundPlay(SOUND_HIT);
}
void PiyoEn02_2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar2->nType	=TYPE_ENEM01;
		lpChar2->nStatus |=_ENEM_PIYO;
	}
	lpChar1->fLive =FALSE;
	DSoundPlay(SOUND_HIT);
}
////////////////////////////////////////////////////////////
//enemy01とブロックが当たったとき（enemy01をenemy02に変える）
////////////////////////////////////////////////////////////
void HitEn01_Blk(_CHAR *lpChar1,_CHAR *lpChar2)
{
	_CHAR* lpChar00=NULL;
	register int i;
	int nXPos,nYPos;

	if(!(lpChar1->nStatus & _ENEM_CAGE)
		&& (!(lpChar1->nStatus & _ENEM_PIYO)))
	{	
		//タイプの変更
		lpChar1->nType=TYPE_ENEM02;
		
		//アイテム"ハート"を出現させる
		lpChar00 =lpChar1 - (lpChar1->wCharNum);
		if(lpChar1->nStatus & _ENEM_RIGHT)
		{
			nXPos	=lpChar1->nXPos + CHAR_W*_ONE;
		}else{
			nXPos	=lpChar1->nXPos;
		}
		nYPos	=lpChar1->nYPos + 8*_ONE;

		for(i=0;i<CHAR_MAX;i++)
		{
			if(!(lpChar00+i)->fLive)	
			{
				SetItem(lpChar00 + i,i,nXPos,nYPos);
				break;
			}
		}
			
	}

	lpChar2->fLive=FALSE;
	DSoundPlay(SOUND_HIT);
	
}
void HitBlk_En01(_CHAR *lpChar1,_CHAR *lpChar2)
{
	_CHAR* lpChar00=NULL;
	int nXPos,nYPos;
	register int i;

	if(!(lpChar2->nStatus & _ENEM_CAGE)
		&& (!(lpChar2->nStatus & _ENEM_PIYO)))
	{	
		//タイプの変更
		lpChar2->nType=TYPE_ENEM02;
		
		//アイテム"ハート"を出現させる
		lpChar00	=lpChar2 - (lpChar2->wCharNum);
	
		if(lpChar2->nStatus & _ENEM_RIGHT)
		{
			nXPos	=lpChar2->nXPos + CHAR_W*_ONE;
		}else{
			nXPos	=lpChar2->nXPos;	
		}
		nYPos		=lpChar2->nYPos;
		
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!(lpChar00+i)->fLive)	
			{
				SetItem(lpChar00 + i,i,nXPos,nYPos);
				break;
			}
		}
			
	}

	lpChar1->fLive=FALSE;
	DSoundPlay(SOUND_HIT);
}
////////////////////////////////////////////////////////////////
//マイキャラと敵キャラが当たったとき
///////////////////////////////////////////////////////////////
void HitMy_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar2->nStatus & _ENEM_PIYO)
		&&(!(lpChar2->nStatus & _ENEM_CAGE)))
	{
		if(!(lpChar1->nStatus & _STATUS_DAMAGE))
		{
			lpChar1->nLife--;
			
			if(!lpChar1->nLife)
			{
				lpChar1->fLive=FALSE;
				DSoundPlay(SOUND_HIT);
			}else{
				lpChar1->nStatus |=_STATUS_DAMAGE;
				lpChar1->nStatus &=~_STATUS_PIYO;
				lpChar1->wPiyoCnt =0;
				DSoundPlay(SOUND_DAMAGE);
			}
			
		}

	}
}
void HitEn_My(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_PIYO)
		&&(!(lpChar1->nStatus & _ENEM_CAGE)))
	{
		if(!(lpChar2->nStatus & _STATUS_DAMAGE))
		{
			lpChar2->nLife--;
			if(lpChar2->nLife==0)
			{
				lpChar2->fLive=FALSE;
				DSoundPlay(SOUND_GOVER);
			}else{
				
				lpChar2->nStatus	|=_STATUS_DAMAGE;
				lpChar2->nStatus	&=~_STATUS_PIYO;
				lpChar2->wPiyoCnt	=0;
				DSoundPlay(SOUND_DAMAGE);
			}
		}
	}
}
/////////////////////////////////////////////////////////////////
//Blk02(檻)と敵キャラ（enemy00）があたった時(enemy00を捕まえる)
////////////////////////////////////////////////////////////////
void HitBlk02_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	BYTE nCatchCount;
	register int i;
	
	
	//先頭アドレス
	_CHAR* lpChar00	=NULL;
	lpChar00=lpChar1+lpChar1->wCharNum;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	//あたったブロックは消す
	lpChar1->fLive=FALSE;

	//すでに檻に入っている場合
	if(lpChar2->nStatus & _ENEM_CAGE)
		return;
	
	//復活するブロックをBlk00にする
	(lpBg + lpMap->wMapW * lpChar1->nMapY)[lpChar1->nMapX].nPartsOld =PARTS_BLK00;
	//敵キャラのステータスを"檻"にする
	lpChar2->nStatus |=_ENEM_CAGE;
	lpChar2->nMapX	=lpChar1->nMapX;
	lpChar2->nMapY	=lpChar1->nMapY;
	lpChar2->wCageCnt=0;
	DSoundPlay(SOUND_CAGE);
	
	//捕まえている敵のカウントを１増やす
	CatchCountCatch();

	//現在捕まえている敵の数を受け取る
	nCatchCount=GetCatchCount();
	
	//新たな敵を出現させる
	if(nCatchCount==(lpMap->nCageCount - 2))
	{
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!((lpChar00+i)->fLive))
			{
				SetEn01(lpChar00 + i,i,1*CHAR_W*_ONE,(lpMap->wMapH - 3)*CHAR_H*_ONE);
				break;
			}
		}
	}
	
	
	
}

void HitEn_Blk02(_CHAR *lpChar1,_CHAR *lpChar2)
{
	BYTE nCatchCount;
	register int i;
	_CHAR* lpChar00	=NULL;
	lpChar00=lpChar2-lpChar2->wCharNum;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	lpChar2->fLive=FALSE;
	if(lpChar1->nStatus & _ENEM_CAGE)
		return;
	
	(lpBg + lpMap->wMapW * lpChar2->nMapY)[lpChar2->nMapX].nPartsOld =PARTS_BLK00;
	
	lpChar1->nStatus |=_ENEM_CAGE;
	lpChar1->nMapX	=lpChar2->nMapX;
	lpChar1->nMapY	=lpChar2->nMapY;
	lpChar1->wCageCnt=0;
	DSoundPlay(SOUND_CAGE);
	//捕まえている敵のカウントを１増やす
	CatchCountCatch();
	//現在捕まえている敵の数を受け取る
	nCatchCount=GetCatchCount();
	//新たな敵を出現させる
	if(nCatchCount==(lpMap->nCageCount - 2))
	{
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!((lpChar00+i)->fLive))
			{
				SetEn01(lpChar00 + i,i,1*CHAR_W*_ONE,(lpMap->wMapH - 2)*CHAR_H*_ONE);
				break;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////
//マイキャラとアイテムとの接触（Item Get!!）
/////////////////////////////////////////////////////////////////
void HitMy_Hart(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(lpChar1->nLife< LIFE_MAX)	
	{
		lpChar1->nLife++;
		DSoundPlay(SOUND_ITEM);
	}
	lpChar2->fLive=FALSE;
}
void HitHart_My(_CHAR*lpChar1,_CHAR*lpChar2)
{
	lpChar1->fLive=FALSE;
	if(lpChar2->nLife < LIFE_MAX)
	{
		lpChar2->nLife++;
		DSoundPlay(SOUND_ITEM);
	}
}
/////////////////////////////////////////////////////////////////////
//マイキャラを気絶させる
//////////////////////////////////////////////////////////////////////
void PiyoMyChar1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	lpChar1->nStatus |=_STATUS_PIYO;
	lpChar2->fLive	=FALSE;
	DSoundPlay(SOUND_HIT);
}
void PiyoMyChar2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	lpChar2->nStatus |=_STATUS_PIYO;
	lpChar1->fLive	=FALSE;
	DSoundPlay(SOUND_HIT);
}

//////////////////////////////////////////////////////////////
//敵キャラ同士がぶつかった時
/////////////////////////////////////////////////////////////

//enemy02の移動を優先させる（ほかのキャラを待たせる）
void HitEn02_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar1->nStatus &_ENEM_PIYO)
		||(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar1->fWait=TRUE;
		lpChar2->fWait=FALSE;
	}else{
		lpChar2->fWait=TRUE;
		lpChar1->fWait=FALSE;
	}
}	
void HitEn_En02(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar2->nStatus &_ENEM_PIYO)
		||(lpChar2->nStatus & _ENEM_CAGE))
	{
		lpChar2->fWait=TRUE;
		lpChar1->fWait=FALSE;
	}else{
		lpChar1->fWait=TRUE;
		lpChar2->fWait=FALSE;
	}
}
//
//敵キャラの移動方向によってどちらのキャラが待たされるかを決める
//
//キャラを待たせる関数のテーブル
void (*tblEnemyWait[6][6])(_CHAR*,_CHAR*)={
	//0:左			1:右			2:落下				3:はしご下り		4:はしご上り		5:気絶												
	EnemyWait_Right,EnemyWait_Right,EnemyWait_1,		EnemyWait_Lower,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_Right,EnemyWait_Left,	EnemyWait_1,		EnemyWait_Lower,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_2,	EnemyWait_2,	EnemyWait_NoWait,	EnemyWait_2,		EnemyWait_2,		EnemyWait_2,
	EnemyWait_Lower,EnemyWait_Lower,EnemyWait_1,		EnemyWait_Lower,	EnemyWait_NoWait,	EnemyWait_2,
	EnemyWait_Upper,EnemyWait_Upper,EnemyWait_1,		EnemyWait_NoWait,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_1,	EnemyWait_1,	EnemyWait_1,		EnemyWait_1,		EnemyWait_1,		EnemyWait_NoWait
};

//移動方向のテーブル
BYTE tblChkMoveFlag[]={
	0,1,2,2,0,1,2,2,3,3,3,3,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
};
//---------------------------------------------------
void Enem(_CHAR *lpChar1,_CHAR *lpChar2)
{
	WORD wIndex1,wIndex2;
	wIndex1=tblChkMoveFlag[lpChar1->nStatus & _STATUS_MASK];
	wIndex2=tblChkMoveFlag[lpChar2->nStatus & _STATUS_MASK];
	tblEnemyWait[wIndex1][wIndex2](lpChar1,lpChar2);	
	
}	
/////////////////////////////////////////////////////////////////
