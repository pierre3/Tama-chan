/*chngeBlock.cpp*/
//**************************
//�C���N���[�h
//*************************
#include "changeBlock.h"
#include "SetCharData.h"
#include "mapData.h"
#include "drawFrame.h"
#include "chkCharHit.h"
//******************************************************
//�}�b�v�f�[�^�̃u���b�N���L�����N�^�f�[�^�ɒu��������֐�
//******************************************************
void ChangeBlock(_CHAR* lpChar,int nXIndex,int nYIndex){
	register int i;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	//�}�b�v�f�[�^����폜
	
	(lpBg + lpMap->wMapW * nYIndex)[nXIndex].nType		=CHIP_TYPE_BG;
	(lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsNum	=PARTS_BG;
	//�}�b�v�f�[�^�̃u���b�N���L�����N�^�̃f�[�^�ɒu��������
	//�z��̋󂫗v�f��T���ău���b�N���L�����N�^�Ƃ��Đݒ�
	for(i=0;i<CHAR_MAX;i++)
	{
		if(!(lpChar + i)->fLive)
		{
			if((lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsOld==PARTS_BLK00)
				SetBlk00(lpChar + i,i,nXIndex,nYIndex);
			else if((lpBg + lpMap->wMapW * nYIndex)[nXIndex].nPartsOld==PARTS_BLK02)
				SetBlk02(lpChar + i,i,nXIndex,nYIndex);
			break;
		}
	}
}
//************************************************************
//�u�������̃^�C�~���O���J�E���g����
//************************************************************
void ChgBlkCount(_DDRAW DDraw,_CHAR* lpChar,_BGSCROLL *lpBgScrl){
	RECT rcSrc={
		0,
		BMP_BL_Y + CHAR_H,
		CHAR_W,
		BMP_BL_Y + 2*CHAR_H
	};//�u���b�N�_�ŗp�摜�f�[�^
	int nXDest,nYDest;//�_�ŉ摜�̓]����
	register int i,j,k;//���[�v�J�E���^
	_HITCHK hitBlk;

	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	for(i=0;i<lpMap->wMapH;i++){
		for(j=0;j<lpMap->wMapW;j++){
			
			//�����J�E���g��
			if((lpBg + lpMap->wMapW * i)[j].fFallCnt){
				//�J�E���g�_�E��
				(lpBg + lpMap->wMapW * i)[j].wFallCnt--;
				
				//�u���b�N�̓_�ŕ`��
				if(!((lpBg + lpMap->wMapW * i)[j].wFallCnt & 0x07)){
					nXDest=(j<<5)-((lpBgScrl->nBgX + _HALF)>>16);
					nYDest=(i<<5)-((lpBgScrl->nBgY + _HALF)>>16);
					Clipping(&nXDest,&nYDest,&rcSrc);
					//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
					DDraw.lpDDBK->BltFast(nXDest,nYDest,
						DDraw.lpDDOF[0],&rcSrc,
						DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
				}
			}
			//�����J�E���g���O�ɂȂ�����
			if(!(lpBg + lpMap->wMapW * i)[j].wFallCnt){
				ChangeBlock(lpChar,j,i);//�}�b�v�f�[�^��BG�`�b�v���L�����N�^�f�[�^�ɒu��������
				(lpBg + lpMap->wMapW * i)[j].wFallCnt=FALL_CNT;//�����J�E���g�����ɖ߂�
				(lpBg + lpMap->wMapW * i)[j].fFallCnt=FALSE;//�����J�E���g�t���O��off�ɂ���
				(lpBg + lpMap->wMapW * i)[j].fResetCnt=TRUE;//���Z�b�g�J�E���g�t���Oon
			}
			//���Z�b�g�J�E���g��
			if((lpBg + lpMap->wMapW * i)[j].fResetCnt)
				//�J�E���g�_�E��
				(lpBg + lpMap->wMapW * i)[j].wResetCnt--;

			//���Z�b�g�J�E���g���O�ɂȂ�����//////////////////////////////
			if(!(lpBg + lpMap->wMapW * i)[j].wResetCnt){
				//�}�b�v�f�[�^�����ɖ߂�
				(lpBg + lpMap->wMapW * i)[j].nPartsNum	
					=(lpBg + lpMap->wMapW * i)[j].nPartsOld;
				(lpBg + lpMap->wMapW * i)[j].nType	=CHIP_TYPE_BLK;
				(lpBg + lpMap->wMapW * i)[j].wResetCnt=RESET_CNT;//���Z�b�g�J�E���g��߂�
				(lpBg + lpMap->wMapW * i)[j].fResetCnt=FALSE;//���Z�b�g�J�E���g�t���Ooff
				
				//��������ꏊ�ɃL���������Ȃ������ׂ�
				hitBlk.rcHit.left	=(j<<5)<<16;
				hitBlk.rcHit.top	=(i<<5)<<16;
				hitBlk.rcHit.right	=hitBlk.rcHit.left + (CHAR_W<<16);
				hitBlk.rcHit.bottom=hitBlk.rcHit.top + (CHAR_H<<16);
				hitBlk.nHitW		=CHAR_W<<16;
				hitBlk.nHitH		=CHAR_H<<16;
				for(k=0;k<(CHAR_MAX + 1);k++)
				{
					if((lpChar + k)->fLive)
					{
						if(ChkHitRect((lpChar+k)->hitChk,hitBlk))
						{
							if((lpChar+k)->nYPos >= hitBlk.rcHit.top)
								(lpChar+k)->nYPos	=hitBlk.rcHit.bottom;
							else
								(lpChar+k)->nYPos	=hitBlk.rcHit.top - (CHAR_H<<16);
						}	
					}
				}
			}
			/////////////////////////////////////////////////////////////
		}
	}

}
