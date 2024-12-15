/*enemyWait.cpp*/
#include "gameMain.h"
#include "enemyWait.h"

//第一引数のキャラが待つ
void EnemyWait_1(_CHAR* lpChar1, _CHAR* lpChar2)
{
	lpChar1->fWait = TRUE;
	lpChar2->fWait = FALSE;
}
//第二引数のキャラが待つ
void EnemyWait_2(_CHAR* lpChar1, _CHAR* lpChar2)
{
	lpChar2->fWait = TRUE;
	lpChar1->fWait = FALSE;
}
//左にいるキャラが待つ
void EnemyWait_Left(_CHAR* lpChar1, _CHAR* lpChar2)
{
	if (lpChar1->nXPos <= lpChar2->nXPos)
	{
		lpChar1->fWait = TRUE;
		lpChar2->fWait = FALSE;
	}
	else {
		lpChar2->fWait = TRUE;
		lpChar1->fWait = FALSE;
	}
}
//右にいるキャラが待つ
void EnemyWait_Right(_CHAR* lpChar1, _CHAR* lpChar2)
{
	if (lpChar1->nXPos > lpChar2->nXPos)
	{
		lpChar1->fWait = TRUE;
		lpChar2->fWait = FALSE;
	}
	else {
		lpChar2->fWait = TRUE;
		lpChar1->fWait = FALSE;
	}
}
//上にいるキャラが待つ
void EnemyWait_Upper(_CHAR* lpChar1, _CHAR* lpChar2)
{
	if (lpChar1->nYPos >= lpChar2->nYPos)
	{
		lpChar1->fWait = TRUE;
		lpChar2->fWait = FALSE;
	}
	else {
		lpChar2->fWait = TRUE;
		lpChar1->fWait = FALSE;
	}
}
//下にいるキャラが待つ
void EnemyWait_Lower(_CHAR* lpChar1, _CHAR* lpChar2)
{
	if (lpChar1->nYPos < lpChar2->nYPos)
	{
		lpChar1->fWait = TRUE;
		lpChar2->fWait = FALSE;
	}
	else {
		lpChar2->fWait = TRUE;
		lpChar1->fWait = FALSE;
	}
}
//ダミー
void EnemyWait_NoWait(_CHAR* lpChar1, _CHAR* lpChar2) {
	return;
}