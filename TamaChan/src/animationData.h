/*animationData.h*/
#ifndef ANIMEDATA_H
#define ANIMEDATA_H
//**********************
//�C���N���[�h
//********************
#include "gameMain.h"
//*****************************
//�\���̂̒�`
//*****************************
//�A�j���[�V�����f�[�^
typedef struct tagACTDATA{
	RECT	rcSrc;//�摜�f�[�^
	WORD	wAnimeCntMax;//�摜�𑱂��ĕ\������t���[����
	BYTE	nAnimeIndexMax;//1�p�^�[���̃A�j���[�V�����Ŏg�p����摜�̖���
}_ACTDATA;
//************************************
//�֐��̃v���g�^�C�v
//***********************************
/*�\������G��؂�ւ���֐�
	�����F�A�j���[�V����������L�����N�^�̃A�h���X*/
void PicChange(_CHAR*);


#endif 