/*getImputData.h*/

#ifndef IMPUT_H
#define IMPUT_H
//************************
//インクルード
//************************
#include "gameMain.h"
//***************************
//マクロ
//***************************
//ボタン,キーフラグ
#define _R		(WORD)0x0001//右キー
#define _L		(WORD)0x0002//左キー
#define _D		(WORD)0x0004//下キー
#define _U		(WORD)0x0008//上キー
#define _A		(WORD)0x0010//Aボタン
#define _B		(WORD)0x0020//Bボタン
#define _ESC	(WORD)0x0040//エスケープキー
#define _ENT	(WORD)0x0080//エンターキー
#define _F1		(WORD)0x0100//ファンクションキー
#define _F2		(WORD)0x0200
#define _F3		(WORD)0x0400
#define _F4		(WORD)0x0800
//*************************************
//プロトタイプ宣言
//*************************************
extern BOOL GetJoyInfo(WORD*);
extern void GetKeyInfo(WORD*);

#endif