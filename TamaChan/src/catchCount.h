/*catchCount.h*/
#ifndef CATCHCNT_H
#define CATCHCNT_H

#include "gameMain.h"

//nCatchCount（捕まえた敵キャラの数）の操作
extern void CatchCountCatch();
extern void CatchCountEscape();
extern void CatchCountZero();
extern BYTE GetCatchCount();

#endif