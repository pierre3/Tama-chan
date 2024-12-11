/***directD.h***/
#ifndef DDRAW_H
#define DDRAW_H

//********************************************
//�C���N���[�h
//********************************************
#include "gameMain.h"
//*********************************************
//�}�N��
//********************************************
#define BPP 8//�J���[���[�h�i8bit,256�F�j
#define COLOR_KEY 15//�J���[�L�[(�p���b�g�ԍ�)
//**********************************************
//�\���̒�`
//**********************************************
typedef struct tagDDRAW{
	LPDIRECTDRAW		lpDD;//Direct Draw �I�u�W�F�N�g
	LPDIRECTDRAWSURFACE lpDDPR;//�v���C�}���T�[�t�B�X
	LPDIRECTDRAWSURFACE lpDDBK;//�o�b�N�o�b�t�@
	LPDIRECTDRAWSURFACE lpDDOF[OFFSCRN_COUNT];//�I�t�X�N���[���T�[�t�B�X
	LPDIRECTDRAWPALETTE lpDDPL;//�p���b�g
	LPDIRECTDRAWCLIPPER lpDDCL;//�N���b�p�[
	BOOL				fInitDD;//Direct Draw �̏������ł�����...TRUE�F����OK
	BOOL				fFull;//TRUE�F�t���X�N���[�����[�h���@FALSE�F�E�C���h�E���[�h��
	PALETTEENTRY		ape2[256];
	//DirectDraw�̐ݒ���E�C���h�E���[�h�ōs��
	BOOL	DDCreateWin();
	
	//DirectDraw�̐ݒ���t���X�N���[�����[�h�ōs��
	BOOL	DDCreateFull();
	
	//DirectDraw�֘A�̃I�u�W�F�N�g�̉��
	void	DDReleaseFull();
	void	DDReleaseWin();
	
	//�X�N���[�����[�h�̐؂�ւ�
	BOOL	ChangeScreenMode();
	
	//�I�t�X�N���[���T�[�t�B�X���쐬
	BOOL	DDCreateOffScreen(
				LPDIRECTDRAWSURFACE*,//�쐬�����I�t�X�N���[�����󂯎��|�C���^�̃A�h���X
				DWORD,//�J���[�L�[�ɐݒ肷��F�̃p���b�g�ԍ�
				DWORD,//�쐬����I�t�X�N���[���̕�
				DWORD,//�쐬����I�t�X�N���[���̍���
				DWORD);//�������[�t���O
	
	//�r�b�g�}�b�v�t�@�C�����I�t�X�N���[���T�[�t�B�X�ɓǂݍ���
	BOOL	DDLoadBmp(
				LPDIRECTDRAWSURFACE*,//�摜�f�[�^���i�[����I�t�X�N���[���T�[�t�B�X
				LPSTR,//�t�@�C����
				DWORD,
				DWORD,
				DWORD,
				DWORD,
				DWORD,
				DWORD);
	
	//�I�t�X�N���[���̍쐬�ƃr�b�g�}�b�v�̓ǂݍ���
	BOOL	SetBitmap();
	void	VRAMCheck();
}_DDRAW;

//*********************************************************
//�v���g�^�C�v�錾
//*********************************************************
//��ʃ��[�h�`�F�b�N�p
HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC,LPVOID);

#endif