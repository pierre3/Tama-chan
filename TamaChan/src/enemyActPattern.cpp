/*enemyActPattern.cpp*/
//****************************
//�C���N���[�h
//****************************
#include "gameMain.h"
#include "directS.h"
#include "catchCount.h"
#include "enemyActPattern.h"
#include "mapData.h"
///////////////////////////////////////////////
//�G�L�����̃X�e�[�^�X�ʂ̈ړ�����
//////////////////////////////////////////////
//*******************************************
//���ړ�
//******************************************
void EnemyLeft(_CHAR*lpChar){
	register int i;
	int nILeft,nIRight,nIYCent,nIBottom,
		nXTmp,nYTmp,
		nShfXTmp,nShfYTmp,
		nXMove,nLoop;
	
	int nEnemSpd[]={0,
		ENEM_SPD_LO,
		0,
		ENEM_SPD_LO,
		ENEM_SPD_HI
	};
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	nLoop=nEnemSpd[lpChar->nType];
	
	nXMove=0;
	nXTmp=lpChar->nXPos;
	nYTmp=lpChar->nYPos;
	nShfYTmp	=(nYTmp+_HALF)>>16;
	nIYCent		=(nShfYTmp + 15)>>5;
	nIBottom	=(nShfYTmp +32)>>5;
	
	for(i=0;i<nLoop;i++){
		
		nShfXTmp	=(nXTmp+_HALF)>>16;
		nILeft		=nShfXTmp>>5;
		nIRight		=(nShfXTmp+31)>>5;
		if((lpBg + lpMap->wMapW * nIBottom)[nIRight].nType==CHIP_TYPE_BG)
		{
			lpChar->nStatus |=_ENEM_FALL;
			break;
		}else if((lpBg + lpMap->wMapW * nIYCent)[nILeft].nType==CHIP_TYPE_BLK)
		{
			lpChar->nStatus |=_ENEM_RIGHT;
			break;
		}
		
		nXMove -=0x8000;
		nXTmp  -=0x8000;
	}
	lpChar->nXPos +=nXMove;
	
	
}
//************************************************
//�E�ړ�
//************************************************
void EnemyRight(_CHAR*lpChar){
	register int i;
	int nIRight,nILeft,nIYCent,nIBottom,
		nXTmp,nYTmp,
		nShfXTmp,nShfYTmp,
		nXMove,nLoop;
	
	int nEnemSpd[]={0,
		ENEM_SPD_LO,
		0,
		ENEM_SPD_LO,
		ENEM_SPD_HI
	};
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	nLoop=nEnemSpd[lpChar->nType];
	nXMove=0;
	nXTmp=lpChar->nXPos;
	nYTmp=lpChar->nYPos;
	nShfYTmp	=(nYTmp+_HALF)>>16;
	nIYCent=(nShfYTmp + 15)>>5;
	nIBottom=(nShfYTmp + 32)>>5;
	for(i=0;i<nLoop;i++){
		
		nShfXTmp	=(nXTmp+_HALF)>>16;
		nIRight	=(nShfXTmp + 31)>>5;
		nILeft	=nShfXTmp>>5;
		if((lpBg + lpMap->wMapW * nIBottom)[nILeft].nType==CHIP_TYPE_BG)
		{
			lpChar->nStatus |=_ENEM_FALL;
		}else if((lpBg + lpMap->wMapW * nIYCent)[nIRight].nType==CHIP_TYPE_BLK)
		{
			lpChar->nStatus &= ~_ENEM_RIGHT;
			break;
		}
		nXMove +=0x8000;
		nXTmp  +=0x8000;
	}
	lpChar->nXPos +=nXMove;
	
	
	
}
//*******************************************
//�͂��������
//********************************************
void EnemyUp(_CHAR* lpChar)
{
	register int i;
	int nBIndex,nXIndex,
		nXTmp,nYTmp,
		nShfXTmp,nShfYTmp,
		nYMove,nLoop;
	
	int nEnemSpd[]={0,
		ENEM_STEP_LO,
		0,
		ENEM_STEP_LO,
		ENEM_STEP_HI
	};
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	nLoop=nEnemSpd[lpChar->nType];
	nYMove=0;
	nXTmp=lpChar->nXPos;
	nYTmp=lpChar->nYPos;
	nShfXTmp	=(nXTmp+_HALF)>>16;
	nXIndex		=(nShfXTmp + 15)>>5;
	
	for(i=0;i<nLoop;i++){
		
		nShfYTmp	=(nYTmp+_HALF)>>16;
		nBIndex		=(nShfYTmp + 31)>>5;
		
		if((lpBg + lpMap->wMapW * nBIndex)[nXIndex].nType!=CHIP_TYPE_STP){
			lpChar->nStatus &= ~_ENEM_UPDOWN;
			lpChar->nStatus &= ~_ENEM_FALL;
			break;
		}
		nYMove -=_HALF;
		nYTmp  -=_HALF;
	}
	lpChar->nYPos +=nYMove;
	
}
//********************************************
//�͂����������
//********************************************
void EnemyDown(_CHAR* lpChar)
{
	register int i;
	int nBIndex,nXIndex,
		nXTmp,nYTmp,
		nShfXTmp,nShfYTmp,
		nYMove,nLoop;
	
	int nEnemSpd[]={0,
		ENEM_STEP_LO,
		0,
		ENEM_STEP_LO,
		ENEM_STEP_HI
	};	
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	nLoop=nEnemSpd[lpChar->nType];
	
	nYMove=0;
	nXTmp=lpChar->nXPos;
	nYTmp=lpChar->nYPos;
	nShfXTmp	=(nXTmp+_HALF)>>16;
	nXIndex		=(nShfXTmp + 15)>>5;
	
	for(i=0;i<nLoop;i++){
		
		nShfYTmp	=(nYTmp+_HALF)>>16;
		nBIndex		=(nShfYTmp + 32)>>5;
		
		if((lpBg + lpMap->wMapW * nBIndex)[nXIndex].nType==CHIP_TYPE_BLK){
			lpChar->nStatus &= ~_ENEM_UPDOWN;
			break;
		}
		nYMove +=0x8000;
		nYTmp  +=0x8000;
	}
	lpChar->nYPos +=nYMove;
}
//**************************************
//����
//**************************************
void EnemyFall(_CHAR* lpChar)
{
	register int i;
	int nLoopMax,nYMove,
		nXTmp,nYTmp,
		nShfXTmp,nShfYTmp,
		nBIndex,nXIndex;

	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	lpChar->nYSPD +=_G;
	nLoopMax=(lpChar->nYSPD+_HALF)>>15;
	
	nYMove=0;
	nXTmp=lpChar->nXPos;
	nYTmp=lpChar->nYPos;
	nShfXTmp	=(nXTmp+_HALF)>>16;
	nXIndex		=(nShfXTmp + 15)>>5;
	for(i=0;i<nLoopMax;i++){
		nShfYTmp=(nYTmp+_HALF)>>16;
		nBIndex=(nShfYTmp + 32)>>5;
		if((lpBg + lpMap->wMapW * nBIndex)[nXIndex].nType==CHIP_TYPE_BLK){
			lpChar->nYSPD=0;
			lpChar->nStatus &= ~_ENEM_FALL;
			break;
		}
		nYMove +=0x8000;
		nYTmp  +=0x8000;
	}
	lpChar->nYPos +=nYMove;
}
//********************************************************
//�C�⒆
//*******************************************************
void EnemyPiyo(_CHAR*lpChar){
	int nYIndex,nLIndex,nRIndex,nXTmp,nYTmp;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	//�C�⎞�Ԃ��J�E���g
	lpChar->wPiyoCnt++;
	//���t���[�����J�E���g������C�C���Ԃ�����
	if(lpChar->wPiyoCnt==PIYOCNT_MAX)
	{
		lpChar->nStatus &=~_ENEM_PIYO;
		lpChar->wPiyoCnt=0;
	}	
	
	//�����Ȃ��Ƃ��낾�����痎������
	nXTmp=(lpChar->nXPos + _HALF)>>16;
	nYTmp=(lpChar->nYPos + _HALF)>>16;
	nYIndex=(nYTmp +32)>>5;
	nLIndex=(nXTmp + 0)>>5;
	nRIndex=(nXTmp +31)>>5;

	if(((lpBg + lpMap->wMapW * nYIndex)[nLIndex].nType!=CHIP_TYPE_BLK)
		&&((lpBg + lpMap->wMapW * nYIndex)[nRIndex].nType!=CHIP_TYPE_BLK))
	{
		lpChar->nStatus |=_ENEM_FALL;
	}
}
void EnemyPiyoFall(_CHAR* lpChar)
{
	
	//�C�⎞�Ԃ��J�E���g
	lpChar->wPiyoCnt++;
	//���t���[�����J�E���g������C�C���Ԃ�����
	if(lpChar->wPiyoCnt==PIYOCNT_MAX)
	{
		lpChar->nStatus &=~_ENEM_PIYO;
		lpChar->wPiyoCnt=0;
	}	
	//��������
	EnemyFall(lpChar);
}

//////////////////////////////////////////////////////////////
//�B�ɕ߂���Ă��鎞
//////////////////////////////////////////////////////////////
void EnemyCage(_CHAR* lpChar)
{

	int nYIndex,nLIndex,nRIndex,nXTmp,nYTmp;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	//�t���[�������J�E���g	
	lpChar->wCageCnt++;
char str[256];
wsprintf(str,"%d\n",lpChar->wCageCnt);
OutputDebugString(str);
	//��莞�Ԃ������瓦����
	if(lpChar->wCageCnt == ESCAPE_COUNT)
	{
		lpChar->nStatus &=~_ENEM_CAGE;
		lpChar->nStatus &=~_ENEM_ESCAPE;
		(lpBg + lpMap->wMapW * lpChar->nMapY)[lpChar->nMapX].nPartsNum
			=PARTS_BLK02;
		(lpBg + lpMap->wMapW * lpChar->nMapY)[lpChar->nMapX].nPartsOld
			=PARTS_BLK02;
		
		DSoundPlay(SOUND_ESCAPE);
		//�߂܂��Ă���G�̃J�E���g�����炷
		CatchCountEscape();	
	//�����鏭���O�Ɍx������
	}else if(lpChar->wCageCnt == WARNING_COUNT)
	{
		lpChar->nStatus |=_ENEM_ESCAPE;
		DSoundPlay(SOUND_WARNING);

	}
	
	
	//�����Ȃ��Ƃ��낾�����痎������
	nXTmp=(lpChar->nXPos + _HALF)>>16;
	nYTmp=(lpChar->nYPos + _HALF)>>16;
	nYIndex=(nYTmp +32)>>5;
	nLIndex=(nXTmp + 0)>>5;
	nRIndex=(nXTmp +31)>>5;

	if(((lpBg + lpMap->wMapW * nYIndex)[nLIndex].nType!=CHIP_TYPE_BLK)
		&&((lpBg + lpMap->wMapW * nYIndex)[nRIndex].nType!=CHIP_TYPE_BLK))
	{
		lpChar->nStatus |=_ENEM_FALL;
	}
	

}

void EnemyCageFall(_CHAR* lpChar)
{
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	//�t���[�������J�E���g	
	lpChar->wCageCnt++;
	
	//��莞�Ԃ������瓦����
	if(lpChar->wCageCnt == ESCAPE_COUNT)
	{
		lpChar->nStatus &=~_ENEM_CAGE;
		lpChar->nStatus &=~_ENEM_ESCAPE;
		(lpBg + lpMap->wMapW * lpChar->nMapY)[lpChar->nMapX].nPartsNum
			=PARTS_BLK02;
		(lpBg + lpMap->wMapW * lpChar->nMapY)[lpChar->nMapX].nPartsOld
			=PARTS_BLK02;
		DSoundPlay(SOUND_ESCAPE);

		//�߂܂��Ă���G�̃J�E���g�����炷
		CatchCountEscape();

	//�����鏭���O�Ɍx������
	}else if(lpChar->wCageCnt == WARNING_COUNT)
	{
		lpChar->nStatus |=_ENEM_ESCAPE;
		DSoundPlay(SOUND_WARNING);
	}
	//��������
	EnemyFall(lpChar);

	//�n�ʂɗ�������J�E���g���O�ɖ߂�,���΂炭�͓����Ȃ��悤�ɂ���
	if(!(lpChar->nStatus & _ENEM_FALL))
	{
		if(lpChar->nStatus & _ENEM_ESCAPE)
		{
			lpChar->nStatus &=~_ENEM_ESCAPE;
			lpChar->wCageCnt=0;
			DSoundPlay(SOUND_HITCAGE);
		}else{
			lpChar->nStatus |=_ENEM_PIYO;
			DSoundPlay(SOUND_HIT);
		}
	}
}