
/*dash.h*/
#ifndef DASH_H
#define DASH_H

//***********************
//�}�N����`
//**********************
//B_DASH
#define _ADD_SPD 0xd00
#define _DASH_MAX 0x30000
//*****************************************
//�֐��̃v���g�^�C�v
//******************************************
//�_�b�V�����Ɉړ��ʂ։��Z����l�����߂�֐�
//�����F�}�C�L�����̃A�h���X
extern void DashR(_CHAR*);
extern void DashL(_CHAR*);
extern void DashRBrake(_CHAR*);
extern void DashLBrake(_CHAR*);
extern void DashRBrake2(_CHAR*);
extern void DashLBrake2(_CHAR*);
extern void DashOff(_CHAR*);
extern void NoChange(_CHAR*);

#endif