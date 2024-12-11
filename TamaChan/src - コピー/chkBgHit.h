/**chkBgHit.h**/
#ifndef CHKBGHIT_H
#define CHKBGHIT_H

/*************************************************
ブロックにめり込まないように移動量を修正する関数
**************************************************/
//マイキャラの移動方向別に処理する
//引数：マイキャラのアドレス
extern void ChkBgHit_Stop(_CHAR*);//移動していない
extern void ChkBgHit_L(_CHAR*);//左に移動している時
extern void ChkBgHit_R(_CHAR*);//右
extern void ChkBgHit_U(_CHAR*);//真上
extern void ChkBgHit_D(_CHAR*);//真下
extern void ChkBgHit_UL(_CHAR*);//左上
extern void ChkBgHit_DL(_CHAR*);//左下
extern void ChkBgHit_UR(_CHAR*);//右上
extern void ChkBgHit_DR(_CHAR*);//右下

#endif