/*hitCheck.h*/
#ifndef HITCHK
#define HITCHK
//************************
//インクルード
//************************
#include "gameMain.h"

//*******************************

//********************************
//当り判定
//********************************
extern void SetHitRect(_CHAR*, int, int);
extern BOOL ChkHitRect(_HITCHK, _HITCHK);
//********************************
//*******************************
//判定後の処理
//*******************************
extern void HitActDamy(_CHAR*, _CHAR*);
extern void Enem(_CHAR*, _CHAR*);

extern void PiyoChar2(_CHAR*, _CHAR*);
extern void PiyoChar1(_CHAR*, _CHAR*);
extern void PiyoEn02_1(_CHAR*, _CHAR*);
extern void PiyoEn02_2(_CHAR*, _CHAR*);

extern void HitBlk_En01(_CHAR*, _CHAR*);
extern void HitEn01_Blk(_CHAR*, _CHAR*);

extern void HitEn02_En(_CHAR*, _CHAR*);
extern void HitEn_En02(_CHAR*, _CHAR*);

extern void HitMy_En(_CHAR*, _CHAR*);
extern void HitEn_My(_CHAR*, _CHAR*);

extern void HitBlk02_En(_CHAR*, _CHAR*);
extern void HitEn_Blk02(_CHAR*, _CHAR*);

extern void PiyoMyChar1(_CHAR*, _CHAR*);
extern void PiyoMyChar2(_CHAR*, _CHAR*);

extern void HitMy_Hart(_CHAR*, _CHAR*);
extern void HitHart_My(_CHAR*, _CHAR*);

#endif