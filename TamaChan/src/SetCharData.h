/*setCharData.h*/

#ifndef SETCHR_H
#define SETCHR_H
//**************************************
//�C���N���[�h
//**************************************
#include "gameMain.h"

//------------------------------------

#define LIFE_MAX 3
//**************************************
//�L�����f�[�^�̏����ݒ���s���֐�
//**************************************
//�}�C�L�����̐ݒ�
extern void SetMyChar(_CHAR*,int,int);//�}�C�L�����̃A�h���X


//�}�C�L�����ȊO
extern void SetEn00(_CHAR*,//�Z�b�g����L�����N�^�̃A�h���X
			 WORD,//�z��ichData[]�j�̉��Ԗڂ̗v�f�ɐݒ肷�邩���w��
			 int,int);//�L�����̏������W
extern void SetEn01(_CHAR*,WORD,int,int);
extern void SetEn02(_CHAR*,WORD,int,int);
extern void SetBlk00(_CHAR*,WORD,int,int);
extern void SetBlk02(_CHAR*,WORD,int,int);
extern void SetItem(_CHAR*,WORD,int,int);


//�L�����f�[�^�C�}�b�v�f�[�^�̏����ݒ�
extern void SetUpChar(_CHAR*);
#endif