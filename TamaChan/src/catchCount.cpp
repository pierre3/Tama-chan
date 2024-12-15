/*ctachCount.cpp*/

#include "catchCount.h"
/////////////////////////////////////
//グローバル変数
/////////////////////////////////////
BYTE nCatchCount = 0;
//////////////////////////////////////////////////
//檻に捕らえた敵の数を数える
/////////////////////////////////////////////////

//１匹捕まえた時
void CatchCountCatch()
{
	nCatchCount++;
}

//１匹逃げた時
void CatchCountEscape()
{
	nCatchCount--;
}
//0に初期化
void CatchCountZero()
{
	nCatchCount = 0;
}
//nCatchCountを取得する
BYTE GetCatchCount()
{
	return(nCatchCount);
}