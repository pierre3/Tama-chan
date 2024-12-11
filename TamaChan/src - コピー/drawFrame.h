/*drawFrame.h*/
#ifndef DFRAME
#define DFRAME
//**********************************
//�C���N���[�h
//*********************************
#include "directD.h"
#include "gameMain.h"
//****************************************
//�Q�[���X�e�[�^�X
#define GSTATE_GAME 0x00//�ʏ펞
#define GSTATE_PAUSE 0x01//�|�[�Y
#define GSTATE_OUT	0x02//�~�X
#define GSTATE_GOVER 0x04//�Q�[���I�[�o�[
#define GSTATE_CLEAR 0x08//�Q�[���N���A�[
#define GSTATE_TITLE 0x10
//
#define GSTATE_MASK 0x1f
//
#define STAGE_MAX 5
//*************************************
//�֐��̃v���g�^�C�v
//************************************
//���C�������A�`����s���֐�//////////////////////////////
extern BOOL	DrawFrame(_DDRAW*,//_DDRAW�\����
				  _CHAR*);//chData[]�̐擪�A�h���X

//�N���b�s���O����//////////////////////////////////////////
extern void Clipping(int*,//�]����摜��X���W�̃A�h���X
			  int*,//�]����摜��Y���W�̃A�h���X
			  RECT*);//�]�����摜��RECT�\���̂̃A�h���X
	/*�]���摜���]����ŃX�N���[������͂ݏo���Ȃ�
			�l�Ɋe�����̒l���C������*/

//�f�o�b�O�p�����̕\��////////////////////////////////////
void	DDTextOut(_DDRAW*);//�����F_DDRAW�\����


//���C������///////////////////////////////////////

//�ʏ펞
BOOL Game(_DDRAW*,
		  _CHAR*,//chData[]�̐擪�A�h���X
		  _BGSCROLL*,//�X�N���[���f�[�^
		  WORD);//�C���v�b�g�f�[�^
		//�߂�l:���s...FALSE/����...TRUE
//�|�[�Y��
BOOL Scroll(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//�~�X��
BOOL MyCharOut(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//�Q�[���I�[�o�[���
BOOL GameOver(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//�Q�[���N���A�[���
BOOL GameClear(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//�^�C�g�����
BOOL Title(_DDRAW*,_CHAR*,_BGSCROLL*,WORD);
//�t���[�����[�g�̒���///////////////////////////////
void FrameWait();

//�X�N���[���f�[�^�̐ݒ�
void SetScrollData(_BGSCROLL*);

//�`�揈��///////////////////////////////////////////
void DrawBg(_DDRAW*,_BGSCROLL*);//BG�`�b�v
void DrawCharctor(_DDRAW*,_CHAR*);//�L�����N�^

//ENTER�@KEY�����������̏���,�Q�[���X�e�[�^�X�̐؂�ւ�
BOOL ToTitle();
BOOL Pause();
BOOL GameStart(_CHAR*);
#endif