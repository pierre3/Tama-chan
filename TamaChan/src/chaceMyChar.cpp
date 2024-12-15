/*chaceMyChar.cpp*/
#include "gameMain.h"
#include "chaceMyChar.h"
#include "mapData.h"
//******************************************************
//�G�L�������}�C�L������ǂ������鏈��
//******************************************************

//////////////////////////////////////////////////
//�}�C�L�����������K�ŁA�E�ɂ��鎞
/////////////////////////////////////////////////
void ChaceMc_Right(_CHAR* lpChar) {

	lpChar->nStatus |= _ENEM_RIGHT;

}

////////////////////////////////////////////
//�}�C�L�����������K�ŁA���ɂ��鎞
////////////////////////////////////////////
void ChaceMc_Left(_CHAR* lpChar) {
	lpChar->nStatus &= ~_ENEM_RIGHT;
}

//////////////////////////////////////////
//�}�C�L��������̊K�ɂ��鎞
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
		//�͂����ɏd�Ȃ��Ă�����
		if (((lpBg + lpMap->wMapW * nYIndex)[nLIndex].nType == CHIP_TYPE_STP)
			&& ((lpBg + lpMap->wMapW * nYIndex)[nRIndex].nType == CHIP_TYPE_STP))
		{
			//�͂�����o��
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
//�}�C�L���������̊K�ɂ��鎞
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

	//�͂����Əd�Ȃ��������ׂ�
	//(X:�L�����̗��[)
	nLIndex = (nXTmp + 1) >> 5;
	nRIndex = (nXTmp + 30) >> 5;
	//(Y�F�L�����̑���)
	nBIndex = (nYTmp + 32) >> 5;
	nXIndex = (nXTmp + 15) >> 5;
	nYIndex = (nYTmp + 15) >> 5;



	if ((lpBg + lpMap->wMapW * (nYIndex + 1))[nXIndex].nType == CHIP_TYPE_STP)
	{
		//�����ɂ͂�������������
		if (((lpBg + lpMap->wMapW * nBIndex)[nLIndex].nType == CHIP_TYPE_STP)
			&& ((lpBg + lpMap->wMapW * nBIndex)[nRIndex].nType == CHIP_TYPE_STP))
		{
			//�͂������~���
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

	//�͂���������T���ċ߂��ق��Ɉړ�����	
	nAdd = 1;
	while ((!fEndL) && (!fEndR))
	{
		//�E��
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
		//����
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
