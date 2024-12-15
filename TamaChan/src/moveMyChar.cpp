/*moveMyChar.cpp*/
//*************************
//�C���N���[�h
//**************************
#include "gameMain.h"
#include "directS.h"
#include "chkBgHit.h"
#include "dash.h"
#include "chkCharHit.h"
#include "moveEnemy.h"
#include "moveMyChar.h"
#include "mapData.h"
//*******************************************
//�_�b�V���X�s�[�h�����߂�֐��̃e�[�u��
//*******************************************

void (*tblDash[][32])(_CHAR*) = {
	{
	DashOff,	DashOff,	DashOff,	DashOff,
	DashOff,	DashR,		DashL,		DashOff,
	DashRBrake,	DashRBrake,	DashRBrake2,DashRBrake,
	DashRBrake,	DashR,		DashRBrake2,DashRBrake,
	DashLBrake,	DashLBrake2,DashLBrake,	DashLBrake,
	DashLBrake,	DashLBrake2,DashL,		DashLBrake,
	DashOff,	DashOff,	DashOff,	DashOff,
	DashOff,	DashOff,	DashOff,	DashOff,
	},
	{
	NoChange,	NoChange,	NoChange,	NoChange,
	NoChange,	NoChange,	NoChange,	NoChange,
	NoChange,	NoChange,	DashRBrake,NoChange,
	NoChange,	NoChange,	DashRBrake,NoChange,
	NoChange,	DashLBrake,NoChange,	NoChange,
	NoChange,	DashLBrake,NoChange,	NoChange,
	NoChange,	NoChange,	NoChange,	NoChange,
	}
};
//*************************************************************
//BG�ɂ߂荞�܂Ȃ��悤�Ɉړ��ʂ��C������֐��̃e�[�u��
//************************************************************
//�ʏ펞(X,Y�����̈ړ��ʂ̕�����Y�����Ƃ���...�������}0�̎���0,�{�̎���1,�|�̎���2)
void (*chkBg_Normal[3][3])(_CHAR*) = {
	{ChkBgHit_Stop,	ChkBgHit_D,		ChkBgHit_U},
	{ChkBgHit_R,	ChkBgHit_DR,	ChkBgHit_UR},
	{ChkBgHit_L,	ChkBgHit_DL,	ChkBgHit_UL}
};
//�͂������ړ����Ă��鎞�i�����L�[�̃C���v�b�g�f�[�^��Y�����ɂ���j
void (*chkBg_Step[])(_CHAR*) = {
	ChkBgHit_Stop,	ChkBgHit_R,		ChkBgHit_L,		ChkBgHit_Stop,
	ChkBgHit_D,		ChkBgHit_D,		ChkBgHit_D,		ChkBgHit_D,
	ChkBgHit_U,		ChkBgHit_U,		ChkBgHit_U,		ChkBgHit_U,
	ChkBgHit_Stop,	ChkBgHit_Stop,	ChkBgHit_Stop,	ChkBgHit_Stop,
};
//----------------------------------
//�ړ��ʃe�[�u��	
//----------------------------------
//�ʏ펞��X�����̈ړ���
int tblXMove[] = {
		0,WALK_SPD,-WALK_SPD,0,
		0,WALK_SPD,-WALK_SPD,0,
		0,WALK_SPD,-WALK_SPD,0,
		0,0,0,0
};
//�͂����ړ�����Y�����̈ړ���
int tblStepYMove[] = {
	0,0,0,0,
	STEP_SPD,STEP_SPD,STEP_SPD,0,
	-STEP_SPD,-STEP_SPD,-STEP_SPD,0,
	0,0,0,0
};
//�͂����ړ�����Y�����̈ړ���
int tblStepXMove[] = {
	0,STEP_SPD,-STEP_SPD,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};
//-------------------------------------
//�t���O�؂�ւ��e�[�u��
//------------------------------------
//�͂�����艺��̃t���O��on-off
BOOL fUpDownKey[] = {
	0,0,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,0
};
/*�L�����X�e�|�^�X�̕��s�t���O��ON-OFF�Ɏg�p*/
BYTE tblWalkFlag[] = {

	  0x00,0x01,0x01,0x00,
	  0x01,0x01,0x01,0x00,
	  0x01,0x01,0x01,0x00,
	  0x00,0x00,0x00,0x00
};
/*LR�t���O�̐؂�ւ��Ɏg�p*/
BYTE tblLRFlag[][16] = {
		{
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02,
		0x00,0x02,0x00,0x02
		},
		{
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02,
		0x00,0x00,0x02,0x02
		}
};
//*************************************************************
//�}�C�L�������ړ�������֐�
//*************************************************************
void MyCharMove(_CHAR* lpMC, _BGSCROLL* lpBgScrl, WORD wInputData)
{
	//------------------------------------------
	//���[�J���ϐ�
	//----------------------------------------
	//�����Ƀu���b�N�����邩�A
	//�͂����ɐG��Ă��邩�𒲂ׂ�
	int nBottomIndex, nLeftIndex, nRightIndex,
		nYIndex1, nYIndex2, nXIndex;

	//�X�N���[��
	int nScrlY0, nScrlY1, nScrlX0, nScrlX1;

	static BOOL fStep = FALSE;

	static WORD wMutekiCnt;
	_LPMAPDATA lpMap = NULL;
	_LPBGDATA lpBg = NULL;
	//�C�⒆�͓��͏����O�ɂ���
	if (lpMC->nStatus & _STATUS_PIYO)
	{
		wInputData = 0;
		lpMC->nStatus &= ~_STATUS_UPDOWN;
		fStep = FALSE;
		lpMC->nStatus |= _STATUS_JUMP;
		lpMC->nDashSPD = 0;
		lpMC->wPiyoCnt++;
		if (lpMC->wPiyoCnt == PIYO_CNT_MC)
		{
			lpMC->wPiyoCnt = 0;
			lpMC->nStatus &= ~_STATUS_PIYO;
		}
	}
	//�_���[�W��̖��G��Ԃ̃J�E���g
	if (lpMC->nStatus & _STATUS_DAMAGE)
	{
		wMutekiCnt++;
		if (wMutekiCnt == MUTEKICOUNT_MAX)
		{
			lpMC->nStatus &= ~_STATUS_DAMAGE;
			wMutekiCnt = 0;
		}
	}
	//------------------------------------------------------------
	//�v�������A�����t���O
	//------------------------------------------------------------
	if (wInputData & _DIR_MASK) {
		lpMC->nStatus
			|= tblWalkFlag[wInputData & _DIR_MASK];
		lpMC->nStatus
			^= tblLRFlag[(lpMC->nStatus & _STATUS_RIGHT) >> 1]
			[wInputData & _DIR_MASK];
	}
	else {
		lpMC->nStatus &= ~_STATUS_WALK;
	}


	if (fStep) {
		lpMC->nStatus |= _STATUS_UPDOWN;
		lpMC->nStatus &= ~_STATUS_JUMP;
		lpMC->nDashSPD = 0;
		lpMC->nYSPD = 0;
	}


	//-------------------------------------------
	//�L�����N�^�̈ړ��ʂ����߂�
	//------------------------------------------
	if (lpMC->nStatus & _STATUS_UPDOWN)
		//�͂����̏�艺��
		MCStepMove(lpMC, wInputData);
	else
		//�ʏ�ړ�
		MCNormalMove(lpMC, wInputData);


	//------------------------------------------
	//�L�����N�^���ړ��A�X�N���[��
	//------------------------------------------
	nScrlX0 = lpBgScrl->nBgX + 6 * CHAR_W * _ONE;
	nScrlX1 = lpBgScrl->nBgX + (SCREEN_W - 7 * CHAR_W) * _ONE;
	nScrlY0 = lpBgScrl->nBgY + 6 * CHAR_H * _ONE;
	nScrlY1 = lpBgScrl->nBgY + (SCREEN_H - 7 * CHAR_H) * _ONE;
	//�ړ��ʂ�������
	lpMC->nYPos += lpMC->nYSPD;
	lpMC->nXPos += lpMC->nXSPD;

	//�X�N���[��
	//Y����//////////
	//�ړ��悪�X�N���[���ʒu�𒴂��Ă�����
	//�i��ʉ��̃X�N���[���ʒu�j
	if (lpMC->nYPos > nScrlY1) {
		//�������������X�N���[������
		lpBgScrl->nBgY += lpMC->nYPos - nScrlY1;

		//�i��ʏ�̃X�N���[���ʒu�j
	}
	else if (lpMC->nYPos < nScrlY0) {
		//�������������X�N���[��
		lpBgScrl->nBgY -= nScrlY0 - lpMC->nYPos;

	}
	//�X�N���[�����W���ő�l(BG�̒[)�𒴂��Ȃ��l�ɂ���
	if (lpBgScrl->nBgY > lpBgScrl->nYMax)
	{
		lpBgScrl->nBgY = lpBgScrl->nYMax;
	}//�X�N���[�����W���ŏ��l��(BG�̒[)�����Ȃ��悤�ɂ���
	else if (lpBgScrl->nBgY < lpBgScrl->nYMin)
	{
		lpBgScrl->nBgY = lpBgScrl->nYMin;
	}


	//X����////////////////////
	//�ړ��悪�X�N���[���ʒu�𒴂��Ă�����
	//�i��ʉE�̃X�N���[���ʒu�j
	if (lpMC->nXPos > nScrlX1) {
		lpBgScrl->nBgX += lpMC->nXPos - nScrlX1;

		//�i��ʍ��̃X�N���[���ʒu�j
	}
	else if (lpMC->nXPos < nScrlX0) {
		lpBgScrl->nBgX -= nScrlX0 - lpMC->nXPos;

	}
	if (lpBgScrl->nBgX > lpBgScrl->nXMax)
	{
		lpBgScrl->nBgX = lpBgScrl->nXMax;
	}
	else if (lpBgScrl->nBgX < lpBgScrl->nXMin)
	{
		lpBgScrl->nBgX = lpBgScrl->nXMin;
	}
	//---------------------------------------------
	//�L�����̑����Ƀu���b�N�����邩�A
	//�L�������͂����ɐG��Ă��邩�𒲂ׂ�
	//----------------------------------------------
	//�u���b�N�pBG���W���v�Z
	nBottomIndex = (((lpMC->nYPos + _HALF) >> 16) + 32) >> 5;
	nLeftIndex = (((lpMC->nXPos + _HALF) >> 16) + 0) >> 5;
	nRightIndex = (((lpMC->nXPos + _HALF) >> 16) + 31) >> 5;

	//�͂����pBG���W���v�Z
	nYIndex1 = (((lpMC->nYPos + _HALF) >> 16) + 0) >> 5;

	//�~��鎞�͑����A����ȊO�͑����̂P�s�N�Z����̍��W�𒲂ׂ�
	if (wInputData & _DOWN)
		nYIndex2 = nBottomIndex;
	else
		nYIndex2 = (((lpMC->nYPos + _HALF) >> 16) + 31) >> 5;

	//�͂����`�F�b�N�pX���W�̓L�����N�^�̒����ɐݒ�
	nXIndex = (((lpMC->nXPos + _HALF) >> 16) + 15) >> 5;

	lpMap = GetMapData();
	lpBg = lpMap->lpBgData;
	//�����Ƀu���b�N���Ȃ���΃W�����v(��)�t���O��ON(����������)
	if ((!(lpBg + lpMap->wMapW * nBottomIndex)[nLeftIndex].nType)
		&& (!(lpBg + lpMap->wMapW * nBottomIndex)[nRightIndex].nType)) {
		lpMC->nStatus |= _STATUS_JUMP;
	}
	//�͂����ɐG��Ă��鎞
	if (((lpBg + lpMap->wMapW * nYIndex1)[nXIndex].nType == CHIP_TYPE_STP)
		|| ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_STP)) {
		//��L�[�����L�[��������Ă�����
		if (fUpDownKey[wInputData & (_DIR_MASK)]) {
			//�͂����t���O��ON�ɂ��A�L�����N�^��X���W���͂����ƍ��킹��
			fStep = TRUE;
			lpMC->nXPos = ((nXIndex << 16) - 15) << 5;
		}
		//�����Ƀu���b�N����������͂����t���O��OFF�i�͂������~��Ēn�ʂ܂ł������j
		if ((lpBg + lpMap->wMapW * nYIndex2)[nXIndex].nType == CHIP_TYPE_BLK) {
			lpMC->nStatus &= ~_STATUS_UPDOWN;
			fStep = FALSE;
		}
		//�͂����ɐG��Ă��Ȃ��Ƃ��́A�͂����t���O��OFF�ɂ���
	}
	else {
		lpMC->nStatus &= ~_STATUS_UPDOWN;
		fStep = FALSE;
	}


	//-----�\���p�̍��W�ɕϊ�-----
	lpMC->nXDsp = (lpMC->nXPos - lpBgScrl->nBgX + _HALF) >> 16;
	lpMC->nYDsp = (lpMC->nYPos - lpBgScrl->nBgY + _HALF) >> 16;
	SetDrawFlag(lpMC);
	SetHitRect(lpMC, 1 * _ONE, 1 * _ONE);

}

//*******************************************************
//�}�C�L�����̈ړ��ʂ����߂�֐�
//*******************************************************
//-----------------------------------------------------------
//�ʏ펞
//-----------------------------------------------------------
void MCNormalMove(_CHAR* lpMC, WORD wInputData) {

	//------------------------------------------
	//���[�J���ϐ�
	//---------------------------------------
	//Dash
	BYTE nDashFlag = 0;//�_�b�V�����̃C���v�b�g�f�[�^�Ȃǂ�����Ă���
	//�_�b�V���֐��e�[�u���̓Y�����Ɏg��
	int nSpdAdj;//DashSPD�̏C���l:0.5��؂�ɂ���

	//BG�Ƃ̐ڐG�𒲂ׂ�
	BYTE nXSign,//�}�C�L�����̈ړ��ʂ̕���������Ă���
		nYSign;//�ړ��ʏC���֐��e�[�u���̓Y����

	//----------------------------------------------
	//X�����̈ړ��ʂ����߂�
	//---------------------------------------------

	//�_�b�V���t���O�ɃC���v�b�g�f�[�^������
		//�iB�{�^���{�E�����Ń_�b�V��ON�j
	nDashFlag |= (wInputData & _B_KEP) >> 7;
	nDashFlag |= wInputData & _LEFT;
	nDashFlag |= wInputData & _RIGHT;

	//���݂̃_�b�V�������̃f�[�^������
	if (lpMC->nDashSPD > 0)//�{�̎��͉E�Ƀ_�b�V�����Ă���
		nDashFlag |= 0x08;
	else if (lpMC->nDashSPD < 0)//�|�̎��͍��Ƀ_�b�V��
		nDashFlag |= 0x10;
	else//0�̎��̓_�b�V�����Ă��Ȃ�				
		nDashFlag &= 0x07;//�C���v�b�g�f�[�^���c����bit_off����

	//�_�b�V�����Z�l�����߂�
	//�i�_�b�V���t���O�ɂ���ď�����U�蕪����j
	tblDash[(lpMC->nStatus & _STATUS_JUMP) >> 2]
		[nDashFlag & 0x1f](lpMC);

	//X�����̈ړ��ʂ����߂�
	nSpdAdj = lpMC->nDashSPD & (0x8000 - 1);//�_�b�V�����Z�l��0.5�P�ʂɊۂ߂�
	lpMC->nXSPD = tblXMove[wInputData & _DIR_MASK]//�����L�[�ɂ����Z�l
		+ lpMC->nDashSPD - nSpdAdj;//�_�b�V�����Z�l

	//------------------------------------------
	//Y�����̈ړ��ʂ����߂�
	//-----------------------------------------

	//�W�����v
	//�L�������󒆂ɋ���Ƃ�
	if (lpMC->nStatus & _STATUS_JUMP) {

		//Y�ړ��ʂɈ��ʂ����Z
		lpMC->nYSPD += _G;
		//�W�����v���{�^���������ꂽ��㏸���~
		if (!(wInputData & _A_KEP) && (lpMC->nYSPD < 0))
			lpMC->nYSPD = 0;
	}
	else {	//���n��

		lpMC->nYSPD = 0;//Y�����̈ړ��ʂ��O�ɂ���
		//�W�����v�{�^���������ꂽ��
		if (wInputData & _A_PRS) {
			//�t���O�𗧂ĂăW�����v
			lpMC->nStatus |= _STATUS_JUMP;
			//�_�b�V���X�s�[�h���W�����v�̍����ɉ�����
			lpMC->nYSPD = -_JUMP_HI
				- (_ABS(lpMC->nDashSPD + nSpdAdj));
			//�W�����v��
			DSoundPlay(SOUND_JUMP);
		}
	}

	//-----------------------------------------
	//BG�ɂ߂荞�܂Ȃ��悤�Ɉړ��ʂ��C������
	//----------------------------------------
	//�ړ��ʂ̕����𒲂ׂ�
	if (!lpMC->nXSPD)	nXSign = 0;
	else if (lpMC->nXSPD > 0)	nXSign = 1;
	else	nXSign = 2;

	if (!lpMC->nYSPD)	nYSign = 0;
	else if (lpMC->nYSPD > 0)	nYSign = 1;
	else	nYSign = 2;
	//�ړ������ɂ���ď�����U�蕪����
	chkBg_Normal[nXSign][nYSign](lpMC);

}
//--------------------------------------------------------
//�͂������ړ�����Ƃ�
//---------------------------------------------------------
void MCStepMove(_CHAR* lpMC, WORD wInputData) {

	lpMC->nYSPD = tblStepYMove[wInputData & _DIR_MASK];
	lpMC->nXSPD = tblStepXMove[wInputData & _DIR_MASK];

	chkBg_Step[wInputData & _DIR_MASK](lpMC);

}
