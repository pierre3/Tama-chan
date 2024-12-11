/*chkCharHit.cpp*/
//************************
//�C���N���[�h
//************************
#include "chkCharHit.h"
#include "enemyWait.h"
#include "directS.h"
#include "setCharData.h"
#include "catchCount.h"
#include "mapData.h"

//****************************
//
//****************************
//************************************************************
//����p���W�̐ݒ�
void SetHitRect(_CHAR*lpChar,
				int nXAdj,	//X�C���l
				int nYAdj){	//Y�C���l
	lpChar->hitChk.rcHit.left  =lpChar->nXPos+nXAdj;
	lpChar->hitChk.rcHit.right =lpChar->hitChk.rcHit.left
								+ lpChar->hitChk.nHitW;
	lpChar->hitChk.rcHit.top=lpChar->nYPos+nYAdj;
	lpChar->hitChk.rcHit.bottom=lpChar->hitChk.rcHit.top 
								+ lpChar->hitChk.nHitH;
}
//����`�F�b�N
BOOL ChkHitRect(_HITCHK hit1,_HITCHK hit2){
	int L1,R1,T1,B1,
		L2,R2,T2,B2;
	if(hit1.nHitW >= hit2.nHitW){
		L1	=hit1.rcHit.left;
		R1	=hit1.rcHit.right;
		L2	=hit2.rcHit.left;
		R2	=hit2.rcHit.right;
	}else{
		L1	=hit2.rcHit.left;
		R1	=hit2.rcHit.right;
		L2	=hit1.rcHit.left;
		R2	=hit1.rcHit.right;
	}

	if(hit1.nHitH >= hit2.nHitH){
		T1	=hit1.rcHit.top;
		B1	=hit1.rcHit.bottom;
		T2	=hit2.rcHit.top;
		B2	=hit2.rcHit.bottom;
	}else{
		T1	=hit2.rcHit.top;
		B1	=hit2.rcHit.bottom;
		T2	=hit1.rcHit.top;
		B2	=hit1.rcHit.bottom;
	}
	if((L2>=L1 && L2<= R1)||(R2>=L1 && R2<=R1 ))
		if((T2>=T1 && T2<=B1)||(B2>=T1 && B2<=B1))
			return TRUE;

	
	return FALSE;		
}



//**********************************************************
//���蔭����̏���
//***********************************************************

////////////////////////////////////////////////////////////
//�_�~�[
void HitActDamy(_CHAR* lpChar1,_CHAR* lpChar2)
{
	return;
}

//////////////////////////////////////////////////////////
//�G�L�������C�₳����
/////////////////////////////////////////////////////////
void PiyoChar1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	//�G�L�����������悤�Ƃ��Ă���
	if((lpChar1->nStatus & _ENEM_CAGE)
		&& (lpChar1->nStatus & _ENEM_ESCAPE))
	{
		lpChar1->nStatus &=~_ENEM_ESCAPE;
		lpChar1->wCageCnt=0;
		DSoundPlay(SOUND_HITCAGE);
	}//����ȊO
	else{
		lpChar1->nStatus |=_ENEM_PIYO;
		DSoundPlay(SOUND_HIT);
	}
	lpChar2->fLive	=FALSE;
	
	
}
void PiyoChar2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar2->nStatus & _ENEM_CAGE)
		&& (lpChar2->nStatus & _ENEM_ESCAPE))
	{
		lpChar2->nStatus &=~_ENEM_ESCAPE;
		lpChar2->wCageCnt=0;
		DSoundPlay(SOUND_HITCAGE);
	}else{
		lpChar1->nStatus |=_ENEM_PIYO;
		DSoundPlay(SOUND_HIT);
	}
	lpChar1->fLive =FALSE;
	
}
////////////////////////////////////////////////////////
//enemy02���C�₳����enemy01�ɕς���
///////////////////////////////////////////////////////
void PiyoEn02_1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar1->nType	=TYPE_ENEM01;
		lpChar1->nStatus |=_ENEM_PIYO;
	}
	lpChar2->fLive =FALSE;
	DSoundPlay(SOUND_HIT);
}
void PiyoEn02_2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar2->nType	=TYPE_ENEM01;
		lpChar2->nStatus |=_ENEM_PIYO;
	}
	lpChar1->fLive =FALSE;
	DSoundPlay(SOUND_HIT);
}
////////////////////////////////////////////////////////////
//enemy01�ƃu���b�N�����������Ƃ��ienemy01��enemy02�ɕς���j
////////////////////////////////////////////////////////////
void HitEn01_Blk(_CHAR *lpChar1,_CHAR *lpChar2)
{
	_CHAR* lpChar00=NULL;
	register int i;
	int nXPos,nYPos;

	if(!(lpChar1->nStatus & _ENEM_CAGE)
		&& (!(lpChar1->nStatus & _ENEM_PIYO)))
	{	
		//�^�C�v�̕ύX
		lpChar1->nType=TYPE_ENEM02;
		
		//�A�C�e��"�n�[�g"���o��������
		lpChar00 =lpChar1 - (lpChar1->wCharNum);
		if(lpChar1->nStatus & _ENEM_RIGHT)
		{
			nXPos	=lpChar1->nXPos + CHAR_W*_ONE;
		}else{
			nXPos	=lpChar1->nXPos;
		}
		nYPos	=lpChar1->nYPos + 8*_ONE;

		for(i=0;i<CHAR_MAX;i++)
		{
			if(!(lpChar00+i)->fLive)	
			{
				SetItem(lpChar00 + i,i,nXPos,nYPos);
				break;
			}
		}
			
	}

	lpChar2->fLive=FALSE;
	DSoundPlay(SOUND_HIT);
	
}
void HitBlk_En01(_CHAR *lpChar1,_CHAR *lpChar2)
{
	_CHAR* lpChar00=NULL;
	int nXPos,nYPos;
	register int i;

	if(!(lpChar2->nStatus & _ENEM_CAGE)
		&& (!(lpChar2->nStatus & _ENEM_PIYO)))
	{	
		//�^�C�v�̕ύX
		lpChar2->nType=TYPE_ENEM02;
		
		//�A�C�e��"�n�[�g"���o��������
		lpChar00	=lpChar2 - (lpChar2->wCharNum);
	
		if(lpChar2->nStatus & _ENEM_RIGHT)
		{
			nXPos	=lpChar2->nXPos + CHAR_W*_ONE;
		}else{
			nXPos	=lpChar2->nXPos;	
		}
		nYPos		=lpChar2->nYPos;
		
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!(lpChar00+i)->fLive)	
			{
				SetItem(lpChar00 + i,i,nXPos,nYPos);
				break;
			}
		}
			
	}

	lpChar1->fLive=FALSE;
	DSoundPlay(SOUND_HIT);
}
////////////////////////////////////////////////////////////////
//�}�C�L�����ƓG�L���������������Ƃ�
///////////////////////////////////////////////////////////////
void HitMy_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar2->nStatus & _ENEM_PIYO)
		&&(!(lpChar2->nStatus & _ENEM_CAGE)))
	{
		if(!(lpChar1->nStatus & _STATUS_DAMAGE))
		{
			lpChar1->nLife--;
			
			if(!lpChar1->nLife)
			{
				lpChar1->fLive=FALSE;
				DSoundPlay(SOUND_HIT);
			}else{
				lpChar1->nStatus |=_STATUS_DAMAGE;
				lpChar1->nStatus &=~_STATUS_PIYO;
				lpChar1->wPiyoCnt =0;
				DSoundPlay(SOUND_DAMAGE);
			}
			
		}

	}
}
void HitEn_My(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(!(lpChar1->nStatus & _ENEM_PIYO)
		&&(!(lpChar1->nStatus & _ENEM_CAGE)))
	{
		if(!(lpChar2->nStatus & _STATUS_DAMAGE))
		{
			lpChar2->nLife--;
			if(lpChar2->nLife==0)
			{
				lpChar2->fLive=FALSE;
				DSoundPlay(SOUND_GOVER);
			}else{
				
				lpChar2->nStatus	|=_STATUS_DAMAGE;
				lpChar2->nStatus	&=~_STATUS_PIYO;
				lpChar2->wPiyoCnt	=0;
				DSoundPlay(SOUND_DAMAGE);
			}
		}
	}
}
/////////////////////////////////////////////////////////////////
//Blk02(�B)�ƓG�L�����ienemy00�j������������(enemy00��߂܂���)
////////////////////////////////////////////////////////////////
void HitBlk02_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	BYTE nCatchCount;
	register int i;
	
	
	//�擪�A�h���X
	_CHAR* lpChar00	=NULL;
	lpChar00=lpChar1+lpChar1->wCharNum;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;
	
	//���������u���b�N�͏���
	lpChar1->fLive=FALSE;

	//���łɟB�ɓ����Ă���ꍇ
	if(lpChar2->nStatus & _ENEM_CAGE)
		return;
	
	//��������u���b�N��Blk00�ɂ���
	(lpBg + lpMap->wMapW * lpChar1->nMapY)[lpChar1->nMapX].nPartsOld =PARTS_BLK00;
	//�G�L�����̃X�e�[�^�X��"�B"�ɂ���
	lpChar2->nStatus |=_ENEM_CAGE;
	lpChar2->nMapX	=lpChar1->nMapX;
	lpChar2->nMapY	=lpChar1->nMapY;
	lpChar2->wCageCnt=0;
	DSoundPlay(SOUND_CAGE);
	
	//�߂܂��Ă���G�̃J�E���g���P���₷
	CatchCountCatch();

	//���ݕ߂܂��Ă���G�̐����󂯎��
	nCatchCount=GetCatchCount();
	
	//�V���ȓG���o��������
	if(nCatchCount==(lpMap->nCageCount - 2))
	{
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!((lpChar00+i)->fLive))
			{
				SetEn01(lpChar00 + i,i,1*CHAR_W*_ONE,(lpMap->wMapH - 3)*CHAR_H*_ONE);
				break;
			}
		}
	}
	
	
	
}

void HitEn_Blk02(_CHAR *lpChar1,_CHAR *lpChar2)
{
	BYTE nCatchCount;
	register int i;
	_CHAR* lpChar00	=NULL;
	lpChar00=lpChar2-lpChar2->wCharNum;
	
	_LPMAPDATA lpMap=NULL;
	_LPBGDATA lpBg=NULL;
	lpMap=GetMapData();
	lpBg=lpMap->lpBgData;

	lpChar2->fLive=FALSE;
	if(lpChar1->nStatus & _ENEM_CAGE)
		return;
	
	(lpBg + lpMap->wMapW * lpChar2->nMapY)[lpChar2->nMapX].nPartsOld =PARTS_BLK00;
	
	lpChar1->nStatus |=_ENEM_CAGE;
	lpChar1->nMapX	=lpChar2->nMapX;
	lpChar1->nMapY	=lpChar2->nMapY;
	lpChar1->wCageCnt=0;
	DSoundPlay(SOUND_CAGE);
	//�߂܂��Ă���G�̃J�E���g���P���₷
	CatchCountCatch();
	//���ݕ߂܂��Ă���G�̐����󂯎��
	nCatchCount=GetCatchCount();
	//�V���ȓG���o��������
	if(nCatchCount==(lpMap->nCageCount - 2))
	{
		for(i=0;i<CHAR_MAX;i++)
		{
			if(!((lpChar00+i)->fLive))
			{
				SetEn01(lpChar00 + i,i,1*CHAR_W*_ONE,(lpMap->wMapH - 2)*CHAR_H*_ONE);
				break;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////
//�}�C�L�����ƃA�C�e���Ƃ̐ڐG�iItem Get!!�j
/////////////////////////////////////////////////////////////////
void HitMy_Hart(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if(lpChar1->nLife< LIFE_MAX)	
	{
		lpChar1->nLife++;
		DSoundPlay(SOUND_ITEM);
	}
	lpChar2->fLive=FALSE;
}
void HitHart_My(_CHAR*lpChar1,_CHAR*lpChar2)
{
	lpChar1->fLive=FALSE;
	if(lpChar2->nLife < LIFE_MAX)
	{
		lpChar2->nLife++;
		DSoundPlay(SOUND_ITEM);
	}
}
/////////////////////////////////////////////////////////////////////
//�}�C�L�������C�₳����
//////////////////////////////////////////////////////////////////////
void PiyoMyChar1(_CHAR *lpChar1,_CHAR *lpChar2)
{
	lpChar1->nStatus |=_STATUS_PIYO;
	lpChar2->fLive	=FALSE;
	DSoundPlay(SOUND_HIT);
}
void PiyoMyChar2(_CHAR *lpChar1,_CHAR *lpChar2)
{
	lpChar2->nStatus |=_STATUS_PIYO;
	lpChar1->fLive	=FALSE;
	DSoundPlay(SOUND_HIT);
}

//////////////////////////////////////////////////////////////
//�G�L�������m���Ԃ�������
/////////////////////////////////////////////////////////////

//enemy02�̈ړ���D�悳����i�ق��̃L������҂�����j
void HitEn02_En(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar1->nStatus &_ENEM_PIYO)
		||(lpChar1->nStatus & _ENEM_CAGE))
	{
		lpChar1->fWait=TRUE;
		lpChar2->fWait=FALSE;
	}else{
		lpChar2->fWait=TRUE;
		lpChar1->fWait=FALSE;
	}
}	
void HitEn_En02(_CHAR *lpChar1,_CHAR *lpChar2)
{
	if((lpChar2->nStatus &_ENEM_PIYO)
		||(lpChar2->nStatus & _ENEM_CAGE))
	{
		lpChar2->fWait=TRUE;
		lpChar1->fWait=FALSE;
	}else{
		lpChar1->fWait=TRUE;
		lpChar2->fWait=FALSE;
	}
}
//
//�G�L�����̈ړ������ɂ���Ăǂ���̃L�������҂�����邩�����߂�
//
//�L������҂�����֐��̃e�[�u��
void (*tblEnemyWait[6][6])(_CHAR*,_CHAR*)={
	//0:��			1:�E			2:����				3:�͂�������		4:�͂������		5:�C��												
	EnemyWait_Right,EnemyWait_Right,EnemyWait_1,		EnemyWait_Lower,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_Right,EnemyWait_Left,	EnemyWait_1,		EnemyWait_Lower,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_2,	EnemyWait_2,	EnemyWait_NoWait,	EnemyWait_2,		EnemyWait_2,		EnemyWait_2,
	EnemyWait_Lower,EnemyWait_Lower,EnemyWait_1,		EnemyWait_Lower,	EnemyWait_NoWait,	EnemyWait_2,
	EnemyWait_Upper,EnemyWait_Upper,EnemyWait_1,		EnemyWait_NoWait,	EnemyWait_Upper,	EnemyWait_2,
	EnemyWait_1,	EnemyWait_1,	EnemyWait_1,		EnemyWait_1,		EnemyWait_1,		EnemyWait_NoWait
};

//�ړ������̃e�[�u��
BYTE tblChkMoveFlag[]={
	0,1,2,2,0,1,2,2,3,3,3,3,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
};
//---------------------------------------------------
void Enem(_CHAR *lpChar1,_CHAR *lpChar2)
{
	WORD wIndex1,wIndex2;
	wIndex1=tblChkMoveFlag[lpChar1->nStatus & _STATUS_MASK];
	wIndex2=tblChkMoveFlag[lpChar2->nStatus & _STATUS_MASK];
	tblEnemyWait[wIndex1][wIndex2](lpChar1,lpChar2);	
	
}	
/////////////////////////////////////////////////////////////////
