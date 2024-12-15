/*chngeBlock.h*/
#include "directD.h"


//キャラクタのブロックに変換するタイミングをカウント
extern void ChgBlkCount(_DDRAW, _CHAR*, _BGSCROLL*);

//BGブロックをキャラクタのブロックに変換する
void ChangeBlock(_CHAR*, int, int);