/*chaceMyChar.cpp*/
#include "gameMain.h"
#include "chaceMyChar.h"
#include "mapData.h"
//******************************************************
//敵キャラがマイキャラを追いかける処理
//******************************************************

//////////////////////////////////////////////////
//マイキャラが同じ階で、右にいる時
/////////////////////////////////////////////////
void ChaceMc_Right(_CHAR* lpChar) {

	lpChar->nStatus |= _ENEM_RIGHT;

}

////////////////////////////////////////////
//マイキャラが同じ階で、左にいる時
////////////////////////////////////////////
void ChaceMc_Left(_CHAR* lpChar) {
	lpChar->nStatus &= ~_ENEM_RIGHT;
}

//////////////////////////////////////////
//マイキャラが上の階にいる時
//////////////////////////////////////////
void ChaceMc_Up(_CHAR* lpChar) {
	int nLIndex, nRIndex, nBIndex,
		nYIndex, nXIndex,
		nXTmp, nYTmp, nAdd;
	BOOL fEndR = FALSE, fEndL = FALSE;

	_LPMAPDATA lpMap = NULL;
	_LPBGDATA lpBg = NULL;
	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXTmp = (lpChar->nXPos + _HALF) >> 16;
	nYTmp = (lpChar->nYPos + _HALF) >> 16;
	nLIndex = (nXTmp + 1) >> 5;
	nRIndex = (nXTmp + 30) >> 5;
	nBIndex = (nYTmp + 32) >> 5;

	nXIndex = (nXTmp + 15) >> 5;
	nYIndex = (nYTmp + 15) >> 5;
	nAdd = 1;


	if ((lpBg + lpMap->wMapW * nYIndex)[nXIndex].nType == CHIP_TYPE_STP)
	{
		//はしごに重なっていたら
		if (((lpBg + lpMap->wMapW * nYIndex)[nLIndex].nType == CHIP_TYPE_STP)
			&& ((lpBg + lpMap->wMapW * nYIndex)[nRIndex].nType == CHIP_TYPE_STP))
		{
			//はしごを登る
			lpChar->nXPos = (nLIndex << 5) << 16;
			lpChar->nStatus |= _ENEM_UP | _ENEM_UPDOWN;
		}
		return;
	}
	if ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex].nType == CHIP_TYPE_BG)
	{
		return;
	}

	while ((!fEndR) && (!fEndL))
	{
		if (!fEndR)
		{
			if (((nXIndex + nAdd) > (lpMap->wMapW - 1))
				|| ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex + nAdd].nType == CHIP_TYPE_BG))
			{
				lpChar->nStatus &= ~_ENEM_RIGHT;
				fEndR = TRUE;

			}
			else if ((lpBg + lpMap->wMapW * nYIndex)[nXIndex + nAdd].nType == CHIP_TYPE_STP)
			{
				lpChar->nStatus |= _ENEM_RIGHT;
				return;
			}
		}
		if (!fEndL)
		{
			if (((nXIndex - nAdd) < 0)
				|| ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex - nAdd].nType == CHIP_TYPE_BG))
			{
				lpChar->nStatus |= _ENEM_RIGHT;
				fEndL = TRUE;

			}
			else if ((lpBg + lpMap->wMapW * nYIndex)[nXIndex - nAdd].nType == CHIP_TYPE_STP)
			{
				lpChar->nStatus &= ~_ENEM_RIGHT;
				return;
			}
		}
		nAdd++;
	}
}

/////////////////////////////////////////////////
//マイキャラが下の階にいる時
/////////////////////////////////////////////////
void ChaceMc_Lo(_CHAR* lpChar) {
	int nLIndex, nRIndex, nBIndex,
		nXIndex, nYIndex,
		nXTmp, nYTmp, nAdd;
	BOOL fEndR = FALSE, fEndL = FALSE;

	_LPMAPDATA lpMap = NULL;
	_LPBGDATA lpBg = NULL;
	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;

	nXTmp = (lpChar->nXPos + _HALF) >> 16;
	nYTmp = (lpChar->nYPos + _HALF) >> 16;

	//はしごと重なったか調べる
	//(X:キャラの両端)
	nLIndex = (nXTmp + 1) >> 5;
	nRIndex = (nXTmp + 30) >> 5;
	//(Y：キャラの足元)
	nBIndex = (nYTmp + 32) >> 5;
	nXIndex = (nXTmp + 15) >> 5;
	nYIndex = (nYTmp + 15) >> 5;



	if ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex].nType == CHIP_TYPE_STP)
	{
		//足元にはしごがあったら
		if (((lpBg + lpMap->wMapW * nBIndex)[nLIndex].nType == CHIP_TYPE_STP)
			&& ((lpBg + lpMap->wMapW * nBIndex)[nRIndex].nType == CHIP_TYPE_STP))
		{
			//はしごを降りる
			lpChar->nXPos = (nLIndex << 5) << 16;
			lpChar->nStatus |= _ENEM_UPDOWN;
			lpChar->nStatus &= ~_ENEM_UP;
		}

		return;
	}
	if ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex].nType == CHIP_TYPE_BG)
	{
		return;
	}

	//はしごか穴を探して近いほうに移動する	
	nAdd = 1;
	while ((!fEndL) && (!fEndR))
	{
		//右側
		if (!fEndR)
		{
			if ((nXIndex + nAdd) > (lpMap->wMapW - 1))
			{
				lpChar->nStatus &= ~_ENEM_RIGHT;
				fEndR = TRUE;

			}
			else if (((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex + nAdd].nType == CHIP_TYPE_STP)
				|| ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex + nAdd].nType == CHIP_TYPE_BG))
			{
				lpChar->nStatus |= _ENEM_RIGHT;
				return;
			}
		}
		//左側
		if (!fEndL)
		{
			if ((nXIndex - nAdd) < 0)
			{
				lpChar->nStatus |= _ENEM_RIGHT;
				fEndL = TRUE;

			}
			else if (((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex - nAdd].nType == CHIP_TYPE_STP)
				|| ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex - nAdd].nType == CHIP_TYPE_BG))
			{
				lpChar->nStatus &= ~_ENEM_RIGHT;
				return;
			}
		}
		nAdd++;
	}
}
