/*dash.cpp*/
//***********************
//インクルード
//***********************
#include "gameMain.h"
#include "dash.h"
//*******************************************************
//ダッシュ関数
//******************************************************
//移動量に加算するダッシュ移動量を変化させる

//左にダッシュ
void DashL(_CHAR* lpMC) {
	lpMC->nStatus |= _STATUS_DASH;//ダッシュフラグON
	lpMC->nDashSPD -= _ADD_SPD;//ダッシュ値を_ADD_SPDだけ減らす
	if (lpMC->nDashSPD < -_DASH_MAX)//最小値以下にはしない
		lpMC->nDashSPD = -_DASH_MAX;

}
//右にダッシュ
void DashR(_CHAR* lpMC) {
	lpMC->nStatus |= _STATUS_DASH;//ダッシュフラグON
	lpMC->nDashSPD += _ADD_SPD;//ダッシュ値を_ADD_SPDだけ加算
	if (lpMC->nDashSPD > _DASH_MAX)//最大値以上にはしない
		lpMC->nDashSPD = _DASH_MAX;

}
//右ダッシュを減速 
void DashRBrake(_CHAR* lpMC) {
	lpMC->nDashSPD -= _ADD_SPD;
	if (lpMC->nDashSPD < 0)
		lpMC->nDashSPD = 0;
}
//左ダッシュを減速
void DashLBrake(_CHAR* lpMC) {
	lpMC->nDashSPD += _ADD_SPD;
	if (lpMC->nDashSPD > 0)
		lpMC->nDashSPD = 0;
}
//右ダッシュを減速（2倍）
void DashRBrake2(_CHAR* lpMC) {
	lpMC->nDashSPD -= _ADD_SPD << 1;
	if (lpMC->nDashSPD < 0)
		lpMC->nDashSPD = 0;
}
//左ダッシュを減速（2倍）
void DashLBrake2(_CHAR* lpMC) {
	lpMC->nDashSPD += _ADD_SPD << 1;
	if (lpMC->nDashSPD > 0)
		lpMC->nDashSPD = 0;
}
//ダッシュ終了
void DashOff(_CHAR* lpMC) {
	lpMC->nStatus &= ~_STATUS_DASH;
}
//何もしない
void NoChange(_CHAR* lpMC) {
	return;
}