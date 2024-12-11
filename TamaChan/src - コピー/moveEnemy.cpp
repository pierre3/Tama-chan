/*moveEnemy.cpp*/
//*************************
//�C���N���[�h
//**************************
#include "gameMain.h"
#include "setCharData.h"
#include "changeBlock.h"
#include "chkCharHit.h"
#include "directS.h"
#include "chaceMyChar.h"
#include "enemyActPattern.h"
#include "moveEnemy.h"
#include "sin_data.h"
#include "mapData.h"

/////////////////////////////////////////////////////////
//�L�����N�^�̕\���A��\����؂�ւ���֐�
/////////////////////////////////////////////////////////
void SetDrawFlag(_CHAR *lpChar){
	
	if((lpChar->nYDsp >= -CHAR_H)&&(lpChar->nYDsp <= SCREEN_H))
		lpChar->fDraw=TRUE;
	else
		lpChar->fDraw=FALSE;

	if((lpChar->nYDsp >= -CHAR_W)&&(lpChar->nYDsp <= SCREEN_W))
		lpChar->fDraw=TRUE;
	else
		lpChar->fDraw=FALSE;

}

///////////////////////////////////////////////////////////
//�L�����N�^�̈ړ�����
///////////////////////////////////////////////////////////
//�_�~�[
void DamyMove(_CHAR*,_BGSCROLL*){
	return;
}
//////////////////////////////////////////////////////////
//�u���b�N
void BlkMove(_CHAR*lpChar,_BGSCROLL *lpBgScrl){
	
	WORD wLoopMax,
		wIMidX,wIBottom;
	int nShfXTmp,nShfYTmp;

	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	lpChar->nYSPD +=0x8000;
	
	wLoopMax	=lpChar->nYSPD >>15;
	
	for(WORD i=0;i<wLoopMax;i++){
		
		nShfXTmp	=(lpChar->nXPos+_HALF)>>16;
		nShfYTmp	=(lpChar->nYPos+_HALF)>>16;
		
		wIBottom	=(nShfYTmp +31)>>5;
		wIMidX		=(nShfXTmp + 15)>>5;
	
		
		if((lpBg + lpMap->wMapW * wIBottom)[wIMidX].nType==CHIP_TYPE_BLK){		
			lpChar->fLive=FALSE;
			DSoundPlay(SOUND_BLKBREAK);
			return;
		}
		lpChar->nYPos   +=0x8000;
	}
	
		
	if(lpChar->nYPos > lpMap->wMapW*CHAR_W*_ONE){
		lpChar->fLive=FALSE;
		return;
	}
		
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp = (lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	SetDrawFlag(lpChar);
	
	SetHitRect(lpChar,8*_ONE,0);
}
///////////////////////////////////////////////////////////////////
//�G�L����
//-------------------------------------------------------


//�G�L�����̈ړ������e�[�u���i�X�e�[�^�X�ʂɐU�蕪����j
void (*MoveTblEn00[])(_CHAR*)={
		EnemyLeft,EnemyRight,EnemyFall,EnemyFall,
		EnemyLeft,EnemyRight,EnemyFall,EnemyFall,
		EnemyDown,EnemyDown,EnemyDown,EnemyDown,
		EnemyUp,EnemyUp,EnemyUp,EnemyUp,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,

		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,

		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCage,EnemyCage,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,
		EnemyCageFall,EnemyCageFall,EnemyCageFall,EnemyCageFall,

		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyo,EnemyPiyo,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,
		EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall,EnemyPiyoFall
		
	};
//------------------------------------------------------
void EnemyMove00(_CHAR*lpChar,_BGSCROLL *lpBgScrl){
	
	//���[�J���ϐ�
	_CHAR* lpMyChar=NULL;//�}�C�L�����̃A�h���X���󂯎��
	
	int nXIndex,nYIndex,nXTmp,nYTmp,
		nMyXIndex,nMyYIndex,nMyXTmp,nMyYTmp;
	
	_LPMAPDATA lpMap=NULL;
	BYTE* lpFloorData=NULL;
	lpMap=GetMapData();
	lpFloorData=lpMap->lpFloorData;
	
	//�}�C�L�����̃A�h���X���v�Z
	lpMyChar=lpChar +( CHAR_MAX - lpChar->wCharNum);
	
	//�ړ�����
	//nStatus�ňړ�������U�蕪����
	if(!lpChar->fWait)
		MoveTblEn00[lpChar->nStatus & _STATUS_MASK](lpChar);
	lpChar->fWait=FALSE;
	
	
	//�}�C�L������ǂ�������
	
	//�}�b�v��ł̈ʒu���v�Z
	//�G�L����
	nXTmp=(lpChar->nXPos+_HALF)>>16;
	nYTmp=(lpChar->nYPos+_HALF)>>16;
	nXIndex=(nXTmp+15)>>5;
	nYIndex=(nYTmp+31)>>5;
	//�}�C�L����
	nMyXTmp=(lpMyChar->nXPos+_HALF)>>16;
	nMyYTmp=(lpMyChar->nYPos+_HALF)>>16;
	nMyXIndex=(nMyXTmp+15)>>5;
	nMyYIndex=(nMyYTmp+31)>>5;

	/*�}�C�L�����Ƃ̈ʒu�֌W�𒲂ׂ�
						�}�C�L������ǂ������鏈��*/
	
	//�}�C�L�����������K�ɂ���
	if(lpFloorData[nYIndex]==lpFloorData[nMyYIndex])
	{

		if(lpMyChar->nStatus & _STATUS_UPDOWN)
		{
			if(lpChar->nYPos > lpMyChar->nYPos)
				ChaceMc_Up(lpChar);
			else
				ChaceMc_Lo(lpChar);
		}else if(nXIndex <= nMyXIndex)
			//�����K�Ń}�C�L�������E�ɂ��鎞�̏���
			ChaceMc_Right(lpChar);
		else if(nXIndex > nMyXIndex)
			//�����K�Ń}�C�L���������ɂ��鎞�̏���
			ChaceMc_Left(lpChar);
		
	//�}�C�L��������ɂ���
	}else if(lpFloorData[nYIndex] > lpFloorData[nMyYIndex])
	{
		ChaceMc_Up(lpChar);
	//�}�C�L���������ɂ���
	}else{
		ChaceMc_Lo(lpChar);
	}
	
	
	//�\�����W�̌v�Z//////////////////////////////////////////////////////
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp =(lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	//�\���t���O��on-off
	SetDrawFlag(lpChar);
	/////////////////////////////////////////////////
	//���蔻��pRECT�̍X�V
	SetHitRect(lpChar,1*_ONE,1*_ONE);
}
///////////////////////////////////////////////////////////////////////////////////////
//�A�C�e��
void ItemMove(_CHAR	*lpChar,_BGSCROLL *lpBgScrl)
{
	static WORD wMoveCnt;
	
	lpChar->nXSPD	=(sin_tbl[wMoveCnt & 511]);
	lpChar->nYPos	-=ITEM_MOVE_Y;
	lpChar->nXPos	+=lpChar->nXSPD;
	
	wMoveCnt	+=4;
	if(lpChar->nYPos < 0)
		lpChar->fLive=FALSE;
	
	//�\�����W�̌v�Z//////////////////////////////////////////////////////
	lpChar->nXDsp =(lpChar->nXPos - lpBgScrl->nBgX+_HALF)>>16;
	lpChar->nYDsp =(lpChar->nYPos - lpBgScrl->nBgY+_HALF)>>16;
	//�\���t���O��on-off
	SetDrawFlag(lpChar);
	/////////////////////////////////////////////////
	//���蔻��pRECT�̍X�V
	SetHitRect(lpChar,0*_ONE,0*_ONE);

}