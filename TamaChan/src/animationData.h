/*animationData.h*/
#ifndef ANIMEDATA_H
#define ANIMEDATA_H
//**********************
//インクルード
//********************
#include "gameMain.h"
//*****************************
//構造体の定義
//*****************************
//アニメーションデータ
typedef struct tagACTDATA{
	RECT	rcSrc;//画像データ
	WORD	wAnimeCntMax;//画像を続けて表示するフレーム数
	BYTE	nAnimeIndexMax;//1パターンのアニメーションで使用する画像の枚数
}_ACTDATA;
//************************************
//関数のプロトタイプ
//***********************************
/*表示する絵を切り替える関数
	引数：アニメーションさせるキャラクタのアドレス*/
void PicChange(_CHAR*);


#endif 