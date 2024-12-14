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
#define BPP 24 //�J���[���[�h�i24bit�j
#define COLOR_KEY_R 156
#define COLOR_KEY_G 220
#define COLOR_KEY_B 220
//**********************************************
//�\���̒�`
//**********************************************
typedef struct tagDDRAW {
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
		BYTE,//�J���[�L�[�Ƃ���F��R
		BYTE,//�J���[�L�[�Ƃ���F��R
		BYTE,//�J���[�L�[�Ƃ���F��R
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
	DWORD	RgbToDword(LPDIRECTDRAWSURFACE lpDDPR, BYTE r, BYTE g, BYTE b);
}_DDRAW;

//*********************************************************
//�v���g�^�C�v�錾
//*********************************************************
//��ʃ��[�h�`�F�b�N�p
HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC, LPVOID);

#endif