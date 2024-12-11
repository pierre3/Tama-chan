/*setCharData.h*/

#ifndef SETCHR_H
#define SETCHR_H
//**************************************
//インクルード
//**************************************
#include "gameMain.h"

//------------------------------------

#define LIFE_MAX 3
//**************************************
//キャラデータの初期設定を行う関数
//**************************************
//マイキャラの設定
extern void SetMyChar(_CHAR*,int,int);//マイキャラのアドレス


//マイキャラ以外
extern void SetEn00(_CHAR*,//セットするキャラクタのアドレス
			 WORD,//配列（chData[]）の何番目の要素に設定するかを指定
			 int,int);//キャラの初期座標
extern void SetEn01(_CHAR*,WORD,int,int);
extern void SetEn02(_CHAR*,WORD,int,int);
extern void SetBlk00(_CHAR*,WORD,int,int);
extern void SetBlk02(_CHAR*,WORD,int,int);
extern void SetItem(_CHAR*,WORD,int,int);


//キャラデータ，マップデータの初期設定
extern void SetUpChar(_CHAR*);
#endif