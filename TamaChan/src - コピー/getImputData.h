/*getImputData.h*/

#ifndef IMPUT_H
#define IMPUT_H
//************************
//�C���N���[�h
//************************
#include "gameMain.h"
//***************************
//�}�N��
//***************************
//�{�^��,�L�[�t���O
#define _R		(WORD)0x0001//�E�L�[
#define _L		(WORD)0x0002//���L�[
#define _D		(WORD)0x0004//���L�[
#define _U		(WORD)0x0008//��L�[
#define _A		(WORD)0x0010//A�{�^��
#define _B		(WORD)0x0020//B�{�^��
#define _ESC	(WORD)0x0040//�G�X�P�[�v�L�[
#define _ENT	(WORD)0x0080//�G���^�[�L�[
#define _F1		(WORD)0x0100//�t�@���N�V�����L�[
#define _F2		(WORD)0x0200
#define _F3		(WORD)0x0400
#define _F4		(WORD)0x0800
//*************************************
//�v���g�^�C�v�錾
//*************************************
extern BOOL GetJoyInfo(WORD*);
extern void GetKeyInfo(WORD*);

#endif