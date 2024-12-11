/*drawFrame.cpp*/
//************************
//�C���N���[�h
//************************
#include "drawFrame.h"
#include "directS.h"
#include "getImputData.h"
#include "moveMyChar.h"
#include "moveEnemy.h"
#include "animationData.h"
#include "midiStream.h"
#include "chkCharHit.h"
#include "setCharData.h"
#include "catchCount.h"
#include "mapData.h"
#include "changeBlock.h"
//**************************************************
//�O���[�o���ϐ�
//**************************************************
//�Q�[���̏�Ԃ�����Ă����A���C�������̃t���O
BYTE nGameStatus=GSTATE_TITLE;
//���݂̃X�e�[�W�ԍ�
BYTE nStageNum;
//���C�t�Q�[�W(�n�[�g)�̕\���p���W
RECT rcLife[]={
	{128,80,176,96},
	{128,64,176,80},
	{128,48,176,64},
	{128,32,176,48}
};

//���C�������̃e�[�u��
BOOL (*PlayGame[])(_DDRAW*,_CHAR*,_BGSCROLL*,WORD)={
		Game,		Scroll,		MyCharOut,	MyCharOut,
		GameOver,	GameOver,	GameOver,	GameOver,
		GameClear,	GameClear,	GameClear,	GameClear,
		GameClear,	GameClear,	GameClear,	GameClear,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title,
		Title,		Title,		Title,		Title
};

//****************************************************
//		���C������,�r�b�g�}�b�v�̕`��
//****************************************************
BOOL DrawFrame(_DDRAW *lpDDraw,_CHAR*lpChar)
{
	//------------------------------------------
	//���[�J���ϐ�
	//------------------------------------------
	//�摜�f�[�^�]��
	DDBLTFX				ddblt;//Blt�֐��̐ݒ�p
	RECT				rcBK;//�]�������W(�o�b�N�o�b�t�@-->�N���C�A���g�̈�)
	
	//BG Scroll�f�[�^
	static _BGSCROLL	bgScrl;
	
	//�C���v�b�g�f�[�^
	WORD				wInputData,//�C���v�b�g�f�[�^���i�[
						wKeyInput,//�L�[�{�[�h�̏����󂯎��
						wJoyInput;//�W���C�X�e�B�N�̏����󂯎��
	static BOOL			fJoyFlag,/*GetJoyInfo�̖߂�l���󂯎��
								TRUE�F�W���C�X�e�B�N�g�p�\*/	
						fInput=TRUE;//�W���C�X�e�B�b�N�ƃL�[�{�[�h��
							/*�ǂ�����g����
								TRUE--->JOY,FALSE--->KEY*/
	
	////////////////////////////////////////////////////////
	//*******���̓f�[�^�̎擾*********
	fJoyFlag=GetJoyInfo(&wJoyInput);
	GetKeyInfo(&wKeyInput);
	
	//---Esc Key �ŏI��----
	if(wKeyInput & _ESC_PRS)
		DestroyWindow(gData.hwnd);
	
	//---�W���C�X�e�B�N<-->�L�[�{�[�h�̐؂�ւ�
	if(fJoyFlag){
		if(wKeyInput & _F2_PRS)
			fInput ^= 1;
	}else
		fInput = FALSE;
	
	if(fInput)
		wInputData=wJoyInput | (wKeyInput & _FUNC_KEY);
	else
		wInputData=wKeyInput;
	
	//*********�v���C�}���T�[�t�B�X��h��Ԃ�*******
	ddblt.dwSize=sizeof(ddblt);
	ddblt.dwFillColor=0;
	lpDDraw->lpDDBK->Blt(NULL,NULL,NULL,
		DDBLT_WAIT | DDBLT_COLORFILL,&ddblt);
	//**********************************************************
	//���C���̏���
	//**********************************************************
	if(!PlayGame[nGameStatus & GSTATE_MASK](lpDDraw,lpChar,&bgScrl,wInputData))
		return(FALSE);
	//*******************************************************

//*************************************************************

#if(0)
	lpDDraw->VRAMCheck();
	DDTextOut(*lpDDraw);
#endif
	

	if(lpDDraw->fFull)
	{
		//********�t���b�v����******************
		lpDDraw->lpDDPR->Flip(NULL,DDFLIP_WAIT);
	}else{
		//********�N���C�A���g�̈�ɓ]��********
		SetRect(&rcBK,0,0,SCREEN_W,SCREEN_H);
		lpDDraw->lpDDPR->Blt(&gData.rcClient,lpDDraw->lpDDBK,&rcBK,
			DDBLT_WAIT,NULL);
	}
	
	//�t���[�����[�g�̒���
	FrameWait();

	return(TRUE);
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//�Q�[�����̎�ȏ���
//�L�����N�^�̔����A�ړ��A���蔻��Ȃ�
/////////////////////////////////////////////////////////////////////////////

//�L�����N�^�̈ړ��֐��̃e�[�u��
void (*tblEnemyMove[])(_CHAR*,_BGSCROLL*)={
	DamyMove,EnemyMove00,BlkMove,EnemyMove00,
	EnemyMove00,BlkMove,ItemMove,DamyMove
};

//���蔻���̏����̃e�[�u��(�L�����^�C�v��)
void (*tblHitAct[][7])(_CHAR*,_CHAR*)={
//	My			En00		Blk			En01		En02		Blk02		Item
	HitActDamy,	HitMy_En,	PiyoMyChar1,HitMy_En,	HitMy_En,	PiyoMyChar1,HitMy_Hart,//My
	HitEn_My,	Enem,		PiyoChar1,	Enem,		HitEn_En02,	HitEn_Blk02,HitActDamy,//En00
	PiyoMyChar2,PiyoChar2,	HitActDamy,	HitBlk_En01,PiyoEn02_2,	HitActDamy,	HitActDamy,//Blk
	HitEn_My,	Enem,		HitEn01_Blk,Enem,		HitEn_En02,	HitEn01_Blk,HitActDamy,//En01
	HitEn_My,	HitEn02_En,	PiyoEn02_1,	HitEn02_En,	Enem,		PiyoEn02_1,	HitActDamy,//En02
	PiyoMyChar2,HitBlk02_En,HitActDamy,	HitBlk_En01,PiyoEn02_2,	HitActDamy,	HitActDamy,//Blk02
	HitHart_My,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy,	HitActDamy //Item
};

BOOL Game(_DDRAW *lpDDraw,_CHAR* lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	register int i,j;
	RECT rcSrc;

	BYTE nCatchCount;
	_LPMAPDATA lpMap=NULL;
	
	
	
	//BGM�ꎞ��~����
	mdsRestert();
	
	//********Char�̈ړ�*********************
	MyCharMove(lpChar + CHAR_MAX,lpBgScrl,wInputData);
	
	for(i=0;i<CHAR_MAX;i++)
	{
		if((lpChar + i)->fLive)
			tblEnemyMove[((lpChar+i)->nType) & 0x07](lpChar+i,lpBgScrl);
	}
	
	//�����蔻��*****************************************
	for(i=0;i<CHAR_MAX;i++)
	{
		for(j=i+1;j<CHAR_MAX+1;j++)
		{
			if(((lpChar + i)->fLive)&&((lpChar + j)->fLive))
			{
				if(ChkHitRect((lpChar+i)->hitChk,(lpChar+j)->hitChk))
				{
					tblHitAct[((lpChar + i)->nType) & 0x07]
						[((lpChar + j)->nType) & 0x07]
					(lpChar+i,lpChar+j);	
				}
			}
		}
	}
	
	//********�L�����N�^�̃A�j���[�V����**********
	//�\������G��؂�ւ���
	//�}�C�L����
	//�~�X�������̏���
	if(!((lpChar + CHAR_MAX)->fLive)){
		
		nGameStatus |=GSTATE_OUT;
		//�~�X���̃}�C�L�����摜
		(lpChar+CHAR_MAX)->rcSrc.left	=5*CHAR_W;
		(lpChar+CHAR_MAX)->rcSrc.top	=3*CHAR_H;
		(lpChar+CHAR_MAX)->rcSrc.right	=6*CHAR_W;
		(lpChar+CHAR_MAX)->rcSrc.bottom	=4*CHAR_H;
	}else//�ʏ펞�̉摜�؂�ւ�
		PicChange(lpChar+CHAR_MAX);
	
	//�}�C�L�����ȊO
	for(i=0;i<CHAR_MAX;i++)
	{
		if((lpChar + i)->fLive)	PicChange(lpChar+i);
	}
	//*************************************************
	//�r�b�g�}�b�v�̕\��
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);//�X�N���[�����W�̍X�V	
	DrawBg(lpDDraw,lpBgScrl);//Bg�\��
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//���C�t(�n�[�g)�̕\��
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//�u���b�N�𗎂Ƃ�����
	ChgBlkCount(*lpDDraw,lpChar,lpBgScrl);
	/////////////////////////////////////////////////////
	//�N���A����
	nCatchCount=GetCatchCount();
	lpMap=GetMapData();
	if(nCatchCount==lpMap->nCageCount)
	{
		nGameStatus |=GSTATE_CLEAR;
		CatchCountZero();
		mdsStop();
	}

	//�ꎞ��~
	if(wInputData & _ENT_PRS)
		return(Pause());
	
	return(TRUE);	
}


//////////////////////////////////////////////////////////////////////////////////
//�|�[�Y���̏���
/////////////////////////////////////////////////////////////////////////////////
//�X�N���[���ړ��ʃe�[�u��
int nXScrl[]={
	0,5*_ONE,-5*_ONE,0,
	0,5*_ONE,-5*_ONE,0,
	0,5*_ONE,-5*_ONE,0,
	0,0,0,0
};
int nYScrl[]={
	0,0,0,0,
	5*_ONE,5*_ONE,5*_ONE,0,
	-5*_ONE,-5*_ONE,-5*_ONE,0,
	0,0,0,0
};

//*************************************************************
BOOL Scroll(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	register int i;
	RECT rcSrc;
	mdsPause();
	
	//��ʃX�N���[��
	lpBgScrl->nBgX +=nXScrl[wInputData & _DIR_MASK];
	lpBgScrl->nBgY +=nYScrl[wInputData & _DIR_MASK];
	
	if(lpBgScrl->nBgX < lpBgScrl->nXMin)
		lpBgScrl->nBgX=lpBgScrl->nXMin;
	else if(lpBgScrl->nBgX > lpBgScrl->nXMax)
		lpBgScrl->nBgX = lpBgScrl->nXMax;

	if(lpBgScrl->nBgY < lpBgScrl->nYMin)
		lpBgScrl->nBgY=lpBgScrl->nYMin;
	else if(lpBgScrl->nBgY > lpBgScrl->nYMax)
		lpBgScrl->nBgY = lpBgScrl->nYMax;
	
	for(i=0;i<CHAR_MAX+1;i++)
	{
		(lpChar+i)->nXDsp =((lpChar+i)->nXPos-lpBgScrl->nBgX+_HALF)>>16;
		(lpChar+i)->nYDsp =((lpChar+i)->nYPos-lpBgScrl->nBgY+_HALF)>>16;
		SetDrawFlag(lpChar+i);
	}
	//*************************************************
	//�r�b�g�}�b�v�̕\��
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//���C�t(�n�[�g)�̕\��
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	
	//�ꎞ��~����
	if(wInputData & _ENT_PRS)
		return(Pause());
	
	return(TRUE);		
}
///////////////////////////////////////////////////////////////////////////////


//*************************************************************
//�~�X���̏���
//*************************************************************
BOOL MyCharOut(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
		
	_CHAR* lpMyChar=NULL;
	static int nYSpd =-0x98000;
	RECT rcSrc;
	lpMyChar=lpChar + CHAR_MAX;
	
	lpMyChar->nYPos +=nYSpd;
	nYSpd +=_G;
	lpMyChar->nXDsp =(lpMyChar->nXPos-lpBgScrl->nBgX+_HALF)>>16;
	lpMyChar->nYDsp =(lpMyChar->nYPos-lpBgScrl->nBgY+_HALF)>>16;
	
	if(lpMyChar->nYDsp > SCREEN_H)
	{
		nYSpd =-0x98000;
		nGameStatus |=GSTATE_GOVER;
		CatchCountZero();
		mdsStop();
	}
	//*************************************************
	//�r�b�g�}�b�v�̕\��
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//���C�t(�n�[�g)�̕\��
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	return (TRUE);
}
///////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
//�Q�[���I�[�o�[���̏���
/////////////////////////////////////////////////////////////
BOOL GameOver(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT	rcGover={0,0,388,52},
			rcContinue={271,103,406,164},
			rcCurSor={406,103,420,131},
			rcSrc;
	int nYDest;
	static WORD wCount;
	static BOOL fCurSor=TRUE,fContinue=TRUE;
	/////////////////////////////////////////////////////////
	if(wInputData & _UP)
		fContinue=TRUE;
	else if(wInputData & _DOWN)
		fContinue=FALSE;

	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS))
	{
		if(fContinue)
		{
			return(GameStart(lpChar));
		}else
		{
			nStageNum=0;
			return(ToTitle());
		}
	}
	//////////////////////////////////////////////////////
	if(!mdsPlay(const_cast<char*>("mds\\gover.mds"),FALSE))
				return(FALSE);
	//*************************************************
	//�r�b�g�}�b�v�̕\��
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//���C�t(�n�[�g)�̕\��
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//GAME OVER ���b�Z�[�W�\��
	//***********************************************
	lpDDraw->lpDDBK->BltFast(120,96,
		lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcGover,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	lpDDraw->lpDDBK->BltFast(252,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcContinue,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fCurSor)
	{
		if(fContinue)
			nYDest=288;
		else
			nYDest=316;

		lpDDraw->lpDDBK->BltFast(224,nYDest,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcCurSor,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	if(!(++wCount & 0x07))
		fCurSor ^=TRUE;
	
	return(TRUE);
}
/////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////
//�Q�[���N���A�[���̏���
/////////////////////////////////////////////////////////////
BOOL GameClear(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT rcClear={0,52,473,103};
	RECT rcEndKey={0,103,271,164};
	RECT rcSrc;
	static WORD wCount;
	static BOOL fEndKey;
	
	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS)){
		nStageNum++;
		if(nStageNum < STAGE_MAX)
			return(GameStart(lpChar));
		else{
			nStageNum=0;
			return(ToTitle());
		}
	}
	if(!mdsPlay(const_cast<char*>("mds\\gclear.mds"),FALSE))
				return(FALSE);
	//*************************************************
	//�r�b�g�}�b�v�̕\��
	//***************************************************
	//BG
	SetScrollData(lpBgScrl);	
	DrawBg(lpDDraw,lpBgScrl);
	//-------------------------------------------------------
	//************************************************************
	//CHAR
	DrawCharctor(lpDDraw,lpChar);
	//----------------------------------------------------------
	//************************************************
	//���C�t(�n�[�g)�̕\��
	rcSrc=rcLife[(lpChar + CHAR_MAX)->nLife];
	lpDDraw->lpDDBK->BltFast(0,0,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//***********************************************
	//GAME CLEAR ���b�Z�[�W�\��
	//***********************************************
	lpDDraw->lpDDBK->BltFast(74,96,
		lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcClear,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fEndKey)
	{
		lpDDraw->lpDDBK->BltFast(176,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcEndKey,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	if(!(++wCount & 0x3f))
		fEndKey ^=TRUE;


	return(TRUE);
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//�^�C�g�����
////////////////////////////////////////////////////////////////////////////////
BOOL Title(_DDRAW *lpDDraw,_CHAR *lpChar,_BGSCROLL*lpBgScrl,WORD wInputData)
{
	RECT rcTitle={0,0,OFF_TITLE_W,OFF_TITLE_H};
	RECT rcEndKey={0,103,271,164};
	static BOOL fEndKey=TRUE;
	static WORD wCount=0;

	if((wInputData & _A_PRS)||(wInputData & _ENT_PRS))
		return(GameStart(lpChar));

	lpDDraw->lpDDBK->BltFast(0,0,
		lpDDraw->lpDDOF[OFFSCRN_TITLE],&rcTitle,
		DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	if(fEndKey)
	{
		lpDDraw->lpDDBK->BltFast(176,288,
			lpDDraw->lpDDOF[OFFSCRN_GOVER],&rcEndKey,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	
	if(!(++wCount & 0x3f))
		fEndKey ^=TRUE;
	
	return(TRUE);
}
////////////////////////////////////////////////////////////////////////////


//*****************************************************************************
///////////////////////////////////////////////////////////////////////////////
//ENTER KEY �����������̏���
///////////////////////////////////////////////////////////////////////////////
//�^�C�g���ɖ߂�
BOOL ToTitle()
{
	DSoundPlay(SOUND_PAUSE);
	nGameStatus |=GSTATE_TITLE;
	mdsStop();
	if(!mdsPlay(const_cast<char*>("mds\\opning.mds"),TRUE))
		return(FALSE);
	
	return(TRUE);
}
//�|�[�Y<-->�Đ��̐؂�ւ�
BOOL Pause()
{
	nGameStatus ^=GSTATE_PAUSE;
	DSoundPlay(SOUND_PAUSE);
	return(TRUE);
}
//�Q�[���X�^�[�g
BOOL GameStart(_CHAR* lpChar)
{
	
	DSoundPlay(SOUND_PAUSE);
	LPCSTR lpszFilePath[]={
		"mapData\\stage0.map",
		"mapData\\stage1.map",
		"mapData\\stage2.map",
		"mapData\\stage3.map",
		"mapData\\stage4.map"
	};

	//�}�b�v�t�@�C���̓ǂݍ���
	if(!LoadMapData(lpszFilePath[nStageNum]))
		return(FALSE);
	
	//�L�����N�^�̔z�u
	SetUpChar(lpChar);
	
	//BGM�Đ�
	mdsStop();
	if(!mdsPlay(const_cast<char*>("mds\\q2.mds"),TRUE))
		return(FALSE);

	//�Q�[���X�e�[�^�X�t���O�؂�ւ�
	nGameStatus =GSTATE_GAME;

	return(TRUE);
}
//******************************************************************************
//---------------------------------------------------------
//		�N���b�s���O����
//---------------------------------------------------------
void Clipping(int* lpXDsp,int* lpYDsp,RECT *lprcDsp)
{
	int nWidth,nHeight;
	nWidth	=lprcDsp->right - lprcDsp->left;
	nHeight	=lprcDsp->bottom - lprcDsp->top;
	if(*lpXDsp < 0){
		lprcDsp->left +=(~(*lpXDsp) + 1);
		*lpXDsp = 0;
	}else if(*lpXDsp >(SCREEN_W - nWidth)){
		lprcDsp->right -= *lpXDsp-(SCREEN_W - nWidth);
	}
	
	if(*lpYDsp < 0){
		lprcDsp->top +=~(*lpYDsp) + 1;
		*lpYDsp = 0;
	}else if(*lpYDsp >(SCREEN_H - nHeight)){
		lprcDsp->bottom -= *lpYDsp -(SCREEN_H - nHeight);
	}
}
////////////////////////////////////////////////////////////
//		�����̕\��
////////////////////////////////////////////////////////////
void DDTextOut(_DDRAW *lpDDraw)
{
	HDC			hdc;
	char		str[256];	
	BYTE	nCatchCount;

	nCatchCount	=GetCatchCount();
	
	lpDDraw->lpDDBK->GetDC(&hdc);
	wsprintf(str,"�߂܂��Ă���G:%d�C",nCatchCount);
	TextOut(hdc,200,0,str,lstrlen(str));
	lpDDraw->lpDDBK->ReleaseDC(hdc);
	
}

/////////////////////////////////////////////////////////
//�X�N���[���f�[�^�̐ݒ�
///////////////////////////////////////////////////////
void SetScrollData(_BGSCROLL *lpBgScrl)
{
	_LPMAPDATA lpMapData=NULL;

	lpMapData=GetMapData();

	lpBgScrl->nXMin	=0;//X���W��:0�`�}�b�v�E�[�����ʕ���
	lpBgScrl->nXMax	=((lpMapData->wMapW - 20)<<5)*_ONE;
	lpBgScrl->nYMin	=0;//Y���W��:0�`�}�b�v�̉��̒[���P��ʕ���
	lpBgScrl->nYMax	=((lpMapData->wMapH - 15)<<5)*_ONE;
	if(lpBgScrl->nXMax<0)
		lpBgScrl->nXMax=0;
	if(lpBgScrl->nYMax<0)
		lpBgScrl->nYMax=0;
	//�u���b�N�P�ʂł̃X�N���[�����W
	//�X�N���[�����W������[���牽�Ԗڂ̃u���b�N���w���Ă��邩
	lpBgScrl->wXIndex	=((lpBgScrl->nBgX +_HALF)>>16)>>5;
	lpBgScrl->wYIndex	=((lpBgScrl->nBgY + _HALF)>>16)>>5;
	//
	lpBgScrl->nXAdj	=((lpBgScrl->nBgX + _HALF)>>16) & 31;
	lpBgScrl->nYAdj	=((lpBgScrl->nBgY + _HALF)>>16) & 31;
}
//////////////////////////////////////////////////////////////////////////////
//BG�}�b�v�̕\��
////////////////////////////////////////////////////////////////////////////
/*BG�`�b�v�摜�f�[�^*/
RECT rcBgSrc[]={
	{0,			BMP_BL_Y,		CHAR_W,		BMP_BL_Y + CHAR_H},
	{CHAR_W,	BMP_BL_Y,		2*CHAR_W,	BMP_BL_Y + CHAR_H},
	{2*CHAR_W,	BMP_BL_Y,		3*CHAR_W,	BMP_BL_Y + CHAR_H},
	{3*CHAR_W,	BMP_BL_Y,		4*CHAR_W,	BMP_BL_Y + CHAR_H},
	{2*CHAR_W,	BMP_BL_Y+CHAR_H,3*CHAR_W,	BMP_BL_Y + 2*CHAR_H}
};
void DrawBg(_DDRAW *lpDDraw,_BGSCROLL *lpBgScrl){	
	
	register int i,j;
	RECT rcSrc;
		
	int nXDest,nYDest;
	WORD X,Y;
	_LPBGDATA lpBgTmp=NULL;
	_LPMAPDATA lpMapData=NULL;
	
	lpMapData=GetMapData();
	WORD loopX,loopY;
	loopX=(lpMapData->wMapW < 21)? lpMapData->wMapW : 21;
	loopY=(lpMapData->wMapH < 16)? lpMapData->wMapH : 16;
	//---------------------------------------------------------------------------------
	//��ʒ[�A�P�ԏ�̂P��
	for(j=0;j<loopX;j++)
	{
		Y=lpBgScrl->wYIndex + 0;
		X=lpBgScrl->wXIndex + j;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;
		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=(j<<5)- lpBgScrl->nXAdj;
		nYDest	= 0 - lpBgScrl->nYAdj;
		//----�N���b�s���O����------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	//----------------------------------------------------------------------------------
	//�㉺�̒[�ȊO
	for(i=1;i<(loopY - 1);i++)
	{
		//------------------------------------------------------
		//���[�̏c�P��
		Y=lpBgScrl->wYIndex + i;
		X=lpBgScrl->wXIndex + 0;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=0 - lpBgScrl->nXAdj;
		nYDest	=(i<<5)-lpBgScrl->nYAdj;;
		//----�N���b�s���O����------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		
		//--------------------------------------------------------
		//���E�̒[�ȊO�i�^���̃p�[�c�̓N���b�s���O�s�v�j
		for(j=1;j<(loopX - 1);j++)
		{
			Y=lpBgScrl->wYIndex + i;
			X=lpBgScrl->wXIndex + j;
			X %=lpMapData->wMapW;
			Y %=lpMapData->wMapH;
			lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

			rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
			nXDest	=(j<<5) - lpBgScrl->nXAdj;
			nYDest	=(i<<5) - lpBgScrl->nYAdj;
			//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
			lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
				lpDDraw->lpDDOF[0],&rcSrc,
				DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}

		//-------------------------------------------------------------------
		//�E�[�̏c�P��
		Y=lpBgScrl->wYIndex + i;
		X=lpBgScrl->wXIndex + (loopX - 1);
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=((loopX-1)<<5)-lpBgScrl->nXAdj;
		nYDest	=(i<<5)- lpBgScrl->nYAdj;
		//----�N���b�s���O����------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	
	}
	//--------------------------------------------------------------------------------
	//��ʒ[�A�P�ԉ��̂P��
	for(j=0;j<loopX;j++)
	{
		Y=lpBgScrl->wYIndex + (loopY-1);
		X=lpBgScrl->wXIndex + j;
		X %=lpMapData->wMapW;
		Y %=lpMapData->wMapH;
		lpBgTmp=(lpMapData->lpBgData) + (Y * lpMapData->wMapW) + X;

		rcSrc	=rcBgSrc[lpBgTmp->nPartsNum];
		nXDest	=(j<<5)-lpBgScrl->nXAdj;
		nYDest	=((loopY-1)<<5) - lpBgScrl->nYAdj;
		//----�N���b�s���O����------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[0],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	
}
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//�L�����N�^�̕\��
/////////////////////////////////////////////////////////////////////////////////
void DrawCharctor(_DDRAW *lpDDraw,_CHAR* lpChar)
{
	RECT rcSrc;
	int nXDest,nYDest;
	register int i;
	for(i=0;i < CHAR_MAX ;i++)
	{	
		if(((lpChar + i)->fLive)&&((lpChar + i)->fDraw))
		{
			//--------------------------------
			rcSrc	=(lpChar + i)->rcSrc;
			nXDest	=(lpChar + i)->nXDsp;
			nYDest	=(lpChar + i)->nYDsp;
			//----�N���b�s���O����------------
			Clipping(&nXDest,&nYDest,&rcSrc);
			//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
			lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
				lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
				DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
			//------------------------------------
		}
	}
	if((lpChar + CHAR_MAX)->fDraw)
	{
		//--------------------------------
		rcSrc	=(lpChar + i)->rcSrc;
		nXDest	=(lpChar + i)->nXDsp;
		nYDest	=(lpChar + i)->nYDsp;
		//----�N���b�s���O����------------
		Clipping(&nXDest,&nYDest,&rcSrc);
		//----�I�t�X�N���[������o�b�N�o�t�@�ɓ]��---------
		lpDDraw->lpDDBK->BltFast(nXDest,nYDest,
			lpDDraw->lpDDOF[OFFSCRN_CHAR],&rcSrc,
			DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		//------------------------------------
	}
}

////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//�t���[�����[�g�̒���
//-------------------------------------------------------------------------------
void FrameWait(){
	static DWORD dwTimeNew,dwTimeOld;
	
	do{
		dwTimeNew=timeGetTime();
	}while(dwTimeNew-dwTimeOld<17);
	dwTimeOld=dwTimeNew;
}
/////////////////////////////////////////////////////////////////////////////////
