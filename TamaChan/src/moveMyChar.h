/*moveChar.h*/
#ifndef MOVECHR_H
#define MOVECHR_H

//********************************************
//マクロ
//******************************************
#define WALK_SPD 0x20000
#define STEP_SPD 0x18000
//JUMP
#define _JUMP_HI 0xa0000

#define PIYO_CNT_MC 128
#define MUTEKICOUNT_MAX 96
//************************************************
//プロトタイプ宣言
//************************************************
//マイキャラを動かす関数
void MyCharMove(_CHAR*, _BGSCROLL*, WORD);

//移動量を決める関数
void MCNormalMove(_CHAR*, WORD);
void MCStepMove(_CHAR*, WORD);





#endif