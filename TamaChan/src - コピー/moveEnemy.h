/*moveEnemy.h*/
#ifndef MOVENEM_H
#define MOVENEM_H



#define ITEM_MOVE_Y 0x8000
//************************************
//関数のプロトタイプ
//*************************************
//キャラの移動処理
void EnemyMove00(_CHAR*,_BGSCROLL*);
void BlkMove(_CHAR*,_BGSCROLL*);
void DamyMove(_CHAR*,_BGSCROLL*);
void ItemMove(_CHAR*,_BGSCROLL*);


void SetDrawFlag(_CHAR*);
/***SetDrawFlag関数********************************
	表示フラグのON-OFF
	
	キャラクタが画面の外に出ているか調べて、
	画面外ならそのキャラクタの表示フラグ
	(_CHAR構造体のfDrawメンバ)をFALSE(非表示)にし,
	画面内ならTRUE(表示)にする
	
	引数：調べるキャラクタのアドレス
**************************************************/
#endif 