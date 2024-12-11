
/*dash.h*/
#ifndef DASH_H
#define DASH_H

//***********************
//マクロ定義
//**********************
//B_DASH
#define _ADD_SPD 0xd00
#define _DASH_MAX 0x30000
//*****************************************
//関数のプロトタイプ
//******************************************
//ダッシュ時に移動量へ加算する値を求める関数
//引数：マイキャラのアドレス
extern void DashR(_CHAR*);
extern void DashL(_CHAR*);
extern void DashRBrake(_CHAR*);
extern void DashLBrake(_CHAR*);
extern void DashRBrake2(_CHAR*);
extern void DashLBrake2(_CHAR*);
extern void DashOff(_CHAR*);
extern void NoChange(_CHAR*);

#endif