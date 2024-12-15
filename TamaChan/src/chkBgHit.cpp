/*chkBgHit.cpp*/
//************************
//インクルード
//************************
#include "gameMain.h"
#include "directS.h"//Hit音を鳴らす
#include "chkBgHit.h"
#include "mapData.h"
//**********************************************
//BGにめり込まないように移動量を修正する関数
//**********************************************
//---------------------------------------------
//動いていない時
//-----------------------------------------------
void ChkBgHit_Stop(_CHAR* lpChar) {
	return;
}
//---------------------------------------------
//左
//---------------------------------------------
void ChkBgHit_L(_CHAR* lpChar) {
	int nLoopMax,//細かい移動の回数
		nXMove,//細かい移動の移動量
		nXTmp, nYTmp,//移動先座標
		nShfXTmp, nShfYTmp,
		nXIndex, nYIndex1, nYIndex2;
	register int i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nLoopMax = (~lpChar->nXSPD + 1) >> 15;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;

	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nXIndex = (nShfXTmp - 1) >> 5;
		nYIndex1 = (nShfYTmp + 0) >> 5;
		nYIndex2 = (nShfYTmp + 31) >> 5;

		if (((lpBg + lpMap->wMapW * nYIndex1)[nXIndex].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			break;
		}
		nXTmp -= 0x8000;
		nXMove -= 0x8000;
	}

	lpChar->nXSPD = nXMove;

}
//---------------------------------------------
//右
//--------------------------------------------
void ChkBgHit_R(_CHAR* lpChar) {
	int nLoopMax,
		nXMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nXIndex, nYIndex1, nYIndex2;
	register int i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nLoopMax = lpChar->nXSPD >> 15;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;

	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nXIndex = (nShfXTmp + 32) >> 5;
		nYIndex1 = (nShfYTmp + 0) >> 5;
		nYIndex2 = (nShfYTmp + 31) >> 5;

		if (((lpBg + lpMap->wMapW * nYIndex1)[nXIndex].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			break;
		}
		nXTmp += 0x8000;
		nXMove += 0x8000;
	}

	lpChar->nXSPD = nXMove;

}
//------------------------------------------
//上
//-------------------------------------------
void ChkBgHit_U(_CHAR* lpChar) {
	int nLoopMax,
		nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nYIndex,
		nXIndex1, nXIndex2,
		nXIndexC;
	register int i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;


	nLoopMax = (~lpChar->nYSPD + 1) >> 15;
	nYMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;
	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nYIndex = (nShfYTmp - 1) >> 5;
		nXIndex1 = (nShfXTmp + 0) >> 5;
		nXIndex2 = (nShfXTmp + 31) >> 5;

		nXIndexC = (nShfXTmp + 15) >> 5;

		if (((lpBg + lpMap->wMapW * nYIndex)[nXIndex1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndex)[nXIndex2].nType == CHIP_TYPE_BLK)) {

			if (((lpBg + lpMap->wMapW * nYIndex)[nXIndexC].nPartsNum == PARTS_BLK00)
				|| ((lpBg + lpMap->wMapW * nYIndex)[nXIndexC].nPartsNum == PARTS_BLK02)) {
				//Hit音
				DSoundPlay(SOUND_HEAD);
				(lpBg + lpMap->wMapW * nYIndex)[nXIndexC].fFallCnt = TRUE;

			}

			break;
		}

		nYTmp -= 0x8000;
		nYMove -= 0x8000;

	}
	lpChar->nYSPD = nYMove;
}
//-----------------------------------------------
//下
//--------------------------------------------
void ChkBgHit_D(_CHAR* lpChar) {
	int nLoopMax,
		nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nYIndex, nXIndex1, nXIndex2;
	register int i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nLoopMax = lpChar->nYSPD >> 15;
	nYMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;
	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nYIndex = (nShfYTmp + 32) >> 5;
		nXIndex1 = (nShfXTmp + 0) >> 5;
		nXIndex2 = (nShfXTmp + 31) >> 5;

		if (((lpBg + lpMap->wMapW * nYIndex)[nXIndex1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndex)[nXIndex2].nType == CHIP_TYPE_BLK)) {
			lpChar->nStatus &= ~_STATUS_JUMP;
			break;
		}
		nYTmp += 0x8000;
		nYMove += 0x8000;

	}
	lpChar->nYSPD = nYMove;

}
//----------------------------------------------
//左上
//---------------------------------------------
void ChkBgHit_UL(_CHAR* lpChar) {
	int				nLoopMax,
		nXDist, nYDist,
		nXAdd, nYAdd,
		nXMove, nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nXIndexL, nYIndexL1, nYIndexL2,
		nYIndexU, nXIndexU1, nXIndexU2,
		nXIndexC;
	register int	i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXDist = _ABS(lpChar->nXSPD);
	nYDist = _ABS(lpChar->nYSPD);
	if (nXDist > nYDist) {
		nXAdd = 0x8000;
		nLoopMax = nXDist >> 15;
		nYAdd = (int)(nYDist / nLoopMax);
	}
	else if (nXDist < nYDist) {
		nYAdd = 0x8000;
		nLoopMax = nYDist >> 15;
		nXAdd = (int)(nXDist / nLoopMax);
	}
	else {
		nXAdd = 0x8000;
		nYAdd = 0x8000;
		nLoopMax = nXDist >> 15;
	}

	nYMove = 0;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;

	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nXIndexL = (nShfXTmp - 1) >> 5;
		nYIndexL1 = (nShfYTmp + 1) >> 5;
		nYIndexL2 = (nShfYTmp + 31) >> 5;

		nYIndexU = (nShfYTmp - 1) >> 5;
		nXIndexU1 = (nShfXTmp + 0) >> 5;
		nXIndexU2 = (nShfXTmp + 31) >> 5;

		nXIndexC = (nShfXTmp + 15) >> 5;



		if (((lpBg + lpMap->wMapW * nYIndexL1)[nXIndexL].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexL2)[nXIndexL].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			nXAdd = 0;
		}
		if (((lpBg + lpMap->wMapW * nYIndexU)[nXIndexU1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexU)[nXIndexU2].nType == CHIP_TYPE_BLK)) {
			nYAdd = 0;

			if (((lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].nPartsNum == PARTS_BLK00)
				|| ((lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].nPartsNum == PARTS_BLK02)) {
				//Hit音
				DSoundPlay(SOUND_HEAD);
				(lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].fFallCnt = TRUE;
			}
		}
		if (!nXAdd && !nYAdd)
			break;
		nXTmp -= nXAdd;
		nXMove -= nXAdd;
		nYTmp -= nYAdd;
		nYMove -= nYAdd;
	}
	lpChar->nXSPD = nXMove;
	lpChar->nYSPD = nYMove;
}
//----------------------------------------------
//左下
//---------------------------------------------
void ChkBgHit_DL(_CHAR* lpChar) {
	int				nLoopMax,
		nXDist, nYDist,
		nXAdd, nYAdd,
		nXMove, nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nXIndexL,
		nXIndexD1, nXIndexD2,
		nYIndexL1, nYIndexL2,
		nYIndexD;
	register int	i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXDist = _ABS(lpChar->nXSPD);
	nYDist = _ABS(lpChar->nYSPD);
	if (nXDist > nYDist) {
		nXAdd = 0x8000;
		nLoopMax = nXDist >> 15;
		nYAdd = (int)(nYDist / nLoopMax);
	}
	else if (nXDist < nYDist) {
		nYAdd = 0x8000;
		nLoopMax = nYDist >> 15;
		nXAdd = (int)(nXDist / nLoopMax);
	}
	else {
		nXAdd = 0x8000;
		nYAdd = 0x8000;
		nLoopMax = nXDist >> 15;
	}
	nYMove = 0;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;


	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nYIndexD = (nShfYTmp + 32) >> 5;
		nXIndexD1 = (nShfXTmp + 0) >> 5;
		nXIndexD2 = (nShfXTmp + 31) >> 5;

		nXIndexL = (nShfXTmp - 1) >> 5;
		nYIndexL1 = (nShfYTmp + 0) >> 5;
		nYIndexL2 = (nShfYTmp + 31) >> 5;


		if (((lpBg + lpMap->wMapW * nYIndexL1)[nXIndexL].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexL2)[nXIndexL].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			nXAdd = 0;
		}
		if (((lpBg + lpMap->wMapW * nYIndexD)[nXIndexD1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexD)[nXIndexD2].nType == CHIP_TYPE_BLK)) {
			lpChar->nStatus &= ~_STATUS_JUMP;
			nYAdd = 0;
		}
		if (!nXAdd && !nYAdd)
			break;
		nXTmp -= nXAdd;
		nXMove -= nXAdd;
		nYTmp += nYAdd;
		nYMove += nYAdd;
	}
	lpChar->nXSPD = nXMove;
	lpChar->nYSPD = nYMove;
}
//----------------------------------------------------
//右上
//-------------------------------------------
void ChkBgHit_UR(_CHAR* lpChar) {
	int				nLoopMax,
		nXDist, nYDist,
		nXAdd, nYAdd,
		nXMove, nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nXIndexR,
		nXIndexU1, nXIndexU2,
		nYIndexR1, nYIndexR2,
		nYIndexU, nXIndexC;
	register int	i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXDist = _ABS(lpChar->nXSPD);
	nYDist = _ABS(lpChar->nYSPD);
	if (nXDist > nYDist) {
		nXAdd = 0x8000;
		nLoopMax = nXDist >> 15;
		nYAdd = (int)(nYDist / nLoopMax);
	}
	else if (nXDist < nYDist) {
		nYAdd = 0x8000;
		nLoopMax = nYDist >> 15;
		nXAdd = (int)(nXDist / nLoopMax);
	}
	else {
		nXAdd = 0x8000;
		nYAdd = 0x8000;
		nLoopMax = nXDist >> 15;
	}

	nYMove = 0;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;

	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;
		//マイキャラの右側を調べる
		nXIndexR = (nShfXTmp + 32) >> 5;
		nYIndexR1 = (nShfYTmp + 0) >> 5;
		nYIndexR2 = (nShfYTmp + 31) >> 5;
		//マイキャラの上を調べる
		nYIndexU = (nShfYTmp - 1) >> 5;
		nXIndexU1 = (nShfXTmp + 0) >> 5;
		nXIndexU2 = (nShfXTmp + 31) >> 5;
		//頭突きしたブロック
		nXIndexC = (nShfXTmp + 15) >> 5;



		if (((lpBg + lpMap->wMapW * nYIndexR1)[nXIndexR].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexR2)[nXIndexR].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			nXAdd = 0;
		}
		if (((lpBg + lpMap->wMapW * nYIndexU)[nXIndexU1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexU)[nXIndexU2].nType == CHIP_TYPE_BLK)) {
			nYAdd = 0;

			if (((lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].nPartsNum == PARTS_BLK00)
				|| ((lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].nPartsNum == PARTS_BLK02)) {
				//Hit音
				DSoundPlay(SOUND_HEAD);
				(lpBg + lpMap->wMapW * nYIndexU)[nXIndexC].fFallCnt = TRUE;
			}

		}
		if (!nXAdd && !nYAdd)
			break;
		nXTmp += nXAdd;
		nXMove += nXAdd;
		nYTmp -= nYAdd;
		nYMove -= nYAdd;
	}
	lpChar->nXSPD = nXMove;
	lpChar->nYSPD = nYMove;
}
//---------------------------------------------------
//右下
//-------------------------------------------------
void ChkBgHit_DR(_CHAR* lpChar) {
	int				nLoopMax,
		nXDist, nYDist,
		nXAdd, nYAdd,
		nXMove, nYMove,
		nXTmp, nYTmp,
		nShfXTmp, nShfYTmp,
		nXIndexR,
		nXIndexD1, nXIndexD2,
		nYIndexR1, nYIndexR2,
		nYIndexD;
	register int	i;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA  lpBg = NULL;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXDist = _ABS(lpChar->nXSPD);
	nYDist = _ABS(lpChar->nYSPD);
	if (nXDist > nYDist) {
		nXAdd = 0x8000;
		nLoopMax = nXDist >> 15;
		nYAdd = (int)(nYDist / nLoopMax);
	}
	else if (nXDist < nYDist) {
		nYAdd = 0x8000;
		nLoopMax = nYDist >> 15;
		nXAdd = (int)(nXDist / nLoopMax);
	}
	else {
		nXAdd = 0x8000;
		nYAdd = 0x8000;
		nLoopMax = nXDist >> 15;
	}
	nYMove = 0;
	nXMove = 0;
	nXTmp = lpChar->nXPos;
	nYTmp = lpChar->nYPos;

	for (i = 0; i < nLoopMax; i++) {

		nShfXTmp = (nXTmp + _HALF) >> 16;
		nShfYTmp = (nYTmp + _HALF) >> 16;

		nXIndexR = (nShfXTmp + 32) >> 5;
		nYIndexR1 = (nShfYTmp + 0) >> 5;
		nYIndexR2 = (nShfYTmp + 31) >> 5;

		nYIndexD = (nShfYTmp + 32) >> 5;
		nXIndexD1 = (nShfXTmp + 0) >> 5;
		nXIndexD2 = (nShfXTmp + 31) >> 5;

		if (((lpBg + lpMap->wMapW * nYIndexR1)[nXIndexR].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexR2)[nXIndexR].nType == CHIP_TYPE_BLK)) {
			lpChar->nDashSPD = 0;
			nXAdd = 0;
		}
		if (((lpBg + lpMap->wMapW * nYIndexD)[nXIndexD1].nType == CHIP_TYPE_BLK)
			|| ((lpBg + lpMap->wMapW * nYIndexD)[nXIndexD2].nType == CHIP_TYPE_BLK)) {
			lpChar->nStatus &= ~_STATUS_JUMP;
			nYAdd = 0;
		}
		if (!nXAdd && !nYAdd)
			break;

		nXTmp += nXAdd;
		nXMove += nXAdd;
		nYTmp += nYAdd;
		nYMove += nYAdd;
	}
	lpChar->nXSPD = nXMove;
	lpChar->nYSPD = nYMove;
}
