/*moveChar.h*/
#ifndef MOVECHR_H
#define MOVECHR_H

//********************************************
//�}�N��
//******************************************
#define WALK_SPD 0x20000
#define STEP_SPD 0x18000
//JUMP
#define _JUMP_HI 0xa0000

#define PIYO_CNT_MC 128
#define MUTEKICOUNT_MAX 96
//************************************************
//�v���g�^�C�v�錾
//************************************************
//�}�C�L�����𓮂����֐�
void MyCharMove(_CHAR*, _BGSCROLL*, WORD);

//�ړ��ʂ����߂�֐�
void MCNormalMove(_CHAR*, WORD);
void MCStepMove(_CHAR*, WORD);





#endif