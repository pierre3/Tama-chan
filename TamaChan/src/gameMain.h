#ifndef MACRO
#define MACRO
//************************************
//�C���N���[�h
//*********************************** 
#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>
//***********************************
//�}�N����`
//***********************************

//�E�C���h�E�̃T�C�Y(�s�N�Z��)
#define SCREEN_W 640
#define SCREEN_H 480
//----------------------
//�r�b�g�}�b�v
//---------------------
//�e�r�b�g�}�b�v�̕��A����
#define BMP_MC_W	192	/*�}�C�L����*/
#define BMP_MC_H	128

#define BMP_BL_W	128	/*�u���b�N*/
#define BMP_BL_H	64

#define BMP_EN_W	576	/*�G�L����*/
#define BMP_EN_H	128



//�e�r�b�g�}�b�v�̃I�t�X�N���[����ł̔z�u�ʒu
//X���W
#define BMP_X		0	/*X���W��0*/
//Y���W
#define BMP_MC_Y	0	/*�}�C�L����*/
#define BMP_BL_Y	BMP_MC_H	/*�u���b�N*/
#define BMP_EN_Y	BMP_BL_Y + BMP_BL_H	/*�G�L����*/

//�I�t�X�N���[���̕�����///////////////////////
/*�L�����N�^*/
#define OFFSCREEN_W BMP_EN_W
#define OFFSCREEN_H BMP_EN_Y + BMP_EN_H 
/*GAME OVER*/
#define OFF_GOVER_W	473
#define OFF_GOVER_H 164
/*�^�C�g�����*/
#define OFF_TITLE_W 640
#define OFF_TITLE_H 480
//////////////////////////////////////////////////////////////
//�I�t�X�N���[���ԍ�
#define OFFSCRN_CHAR 0//�L�����N�^�p
#define OFFSCRN_GOVER 1//GameOver���b�Z�[�W
#define OFFSCRN_TITLE 2//�^�C�g�����
//�I�t�X�N���[���̐�
#define OFFSCRN_COUNT 3
//---------------------------------
//�L�����N�^�f�[�^
//----------------------------------
//�L�����N�^���̍ő�l
#define CHAR_MAX 32	

//�L�����N�^�̕�����
#define CHAR_W 32
#define CHAR_H 32

//�L�����^�C�v
#define TYPE_MC 0
#define TYPE_ENEM00 1
#define TYPE_BLK00 2
#define TYPE_ENEM01 3
#define TYPE_ENEM02 4
#define TYPE_BLK02 5
#define TYPE_HART	6
//-----------------------------
////Map�f�[�^
//----------------------------
//�p�[�c�ԍ�
#define PARTS_BG	0
#define PARTS_BLK00	1
#define PARTS_STP	2
#define PARTS_BLK01	3
#define PARTS_BLK02	4
//BG�`�b�v�^�C�v
#define CHIP_TYPE_BG	0/*�w�i*/
#define CHIP_TYPE_BLK	1/*�u���b�N*/
#define CHIP_TYPE_STP	2/*�͂���*/

//�u���b�N�̗�������
#define FALL_CNT		32//�_�ł��n�߂Ă��痎�����͂��߂�܂ł̃t���[����
#define RESET_CNT		256//�������I����Ă��猳�̈ʒu�ɕ�������܂ł̃t���[����




//-----------------------------------
//�Œ菬���v�Z
//-----------------------------------
#define _ONE 0x10000	//�Œ菬���ł̂P
#define _HALF 0x8000	//�Œ菬���ł̂P/�Q

//�d�͉����x
#define _G 0x8000
//---------------------------------
//�C���v�b�g�f�[�^�擾�t���O
//--------------------------------
//A�{�^��
#define _A_MASK		(WORD)0x0070
#define _A_PRS		(WORD)0x0010
#define _A_RLS		(WORD)0x0020
#define _A_KEP		(WORD)0x0040
//B�{�^��.
#define _B_MASK		(WORD)0x0380
#define _B_PRS		(WORD)0x0080
#define _B_RLS		(WORD)0x0100
#define _B_KEP		(WORD)0x0200
//�G�X�P�[�v�L�[
#define _ESC_PRS	(WORD)0x0400
//ENTER�L�[
#define _ENT_PRS	(WORD)0x0800
//Function�L�|
#define _F1_PRS		(WORD)0x1000		
#define _F2_PRS		(WORD)0x2000
#define _F3_PRS		(WORD)0x4000
#define _F4_PRS		(WORD)0x8000
//�{�^���S��
#define _BTN_MASK	(WORD)0x03f0
//�����L�[
#define _DIR_MASK	(WORD)0x000f
#define _RIGHT		(WORD)0x01
#define _LEFT		(WORD)0x02
#define _DOWN		(WORD)0x04
#define _UP			(WORD)0x08
//Func,Enter,Esc Key �r�b�g�}�X�N
#define _FUNC_KEY	(WORD)0xfc00
//-----------------------------------
//�L�����N�^�X�e�[�^�X�t���O
//----------------------------------
#define _STATUS_WALK	0x01	//���s(on-bit:����)
#define _STATUS_RIGHT	0x02	//���E(on-bit:�E)
#define _STATUS_JUMP	0x04	//�W�����v(on-bit:�W�����v�����͗�����)
#define _STATUS_DASH	0x08	//�_�b�V����
#define _STATUS_UPDOWN	0x10	//�͂����̏�艺��
#define _STATUS_PIYO	0x20	//�C��
#define _STATUS_DAMAGE	0x40	//�_���[�W��̖��G���

#define _ENEM_RIGHT		0x01
#define _ENEM_FALL		0x02
#define _ENEM_UP		0x04
#define _ENEM_UPDOWN	0x08
#define _ENEM_PIYO		0x10
#define _ENEM_CAGE		0x20
#define _ENEM_ESCAPE	0x40

#define _STATUS_MASK 0x7f


//----------------------------
//�}�N���֐�
//---------------------------
//�I�u�W�F�N�g�̉��
#define RELEASEDX(x)	\
	if(x){				\
		x->Release();	\
		x=NULL;			\
	}
//��Βl�����߂�
#define _ABS(x) ((x >=0)? x : -x)



//***************************************
//�\���̂̒�`
//***************************************

//�L�����N�^

typedef struct tagHITCHK {
	int nHitW, nHitH;
	RECT rcHit, rcHitOld;
}_HITCHK;

typedef struct tagCHAR {
	int		nXDsp, nYDsp,//�\���p���W
		nXPos, nYPos,//�v�Z�p���W
		nDashSPD,//�_�b�V���ړ��ʁi�}�C�L�����̂ݎg�p�j
		nXSPD, nYSPD,//�ړ���
		nMapX, nMapY;//bgData�Ƃ��čĔz�u���鎞�̔z�u�ʒu�i�u���b�N�̂ݎg�p�j
	RECT	rcSrc;//�I�t�X�N���[����̃r�b�g�}�b�v���W
	_HITCHK	hitChk;//���蔻��p
	BOOL	fLive,//���݂��Ă��邩
		fDraw,//�\�����邩
		fWait;//�ړ������̈ꎞ��~
	BYTE	nType,//�L�����̃^�C�v
		nStatus, nStatusOld,//�L�����̏��
		nLife;
	WORD	wAnimeCnt,//�\���G�̃t���[�������J�E���g
		wPiyoCnt,//�s�����t���[�������J�E���g
		wCageCnt;
	BYTE	nAnimeIndex;//�\������G�̎w��
	WORD	wCharNum;//chData�̉��Ԗڂ̗v�f���A�v�f�ԍ������Ă���
}_CHAR;


//�Q�[���f�[�^
typedef struct tagGAMEDATA {

	HWND				hwnd;/*�E�C���h�E�̃n���h��*/
	HINSTANCE			hInst;/*�C���X�^���X�n���h��*/
	RECT				rcClient;/*�N���C�A���g�̈�̋�`���W*/
	BOOL				fActive;/*�E�C���h�E���A�N�e�B�u��*/
}_GAMEDATA;



//�X�N���[���f�[�^
typedef struct tagBGSCROLL {

	int		nBgX, nBgY,//�X�N���[�����W
		nXAdj, nYAdj,//�X�N���[�����W�̏C���l
		/*(�X�N���[�����W)/(BG�`�b�v�̃T�C�Y)�̏�]*/
		nXMin, nYMin,//�X�N���[�����W�̍ŏ��l
		nXMax, nYMax;//�X�N���[�����W�̍ő�l
	WORD	wXIndex, wYIndex;//bgData�z��ł̗v�f�ԍ�
	/*(�X�N���[�����W)/(BG�`�b�v�̃T�C�Y)�̐������i.�ȉ��؂�̂āj*/
}_BGSCROLL;



//******************************************
//�O���[�o���ϐ�
//******************************************
extern _GAMEDATA gData;




#endif


