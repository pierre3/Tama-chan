/*moveEnemy.h*/
#ifndef MOVENEM_H
#define MOVENEM_H



#define ITEM_MOVE_Y 0x8000
//************************************
//�֐��̃v���g�^�C�v
//*************************************
//�L�����̈ړ�����
void EnemyMove00(_CHAR*,_BGSCROLL*);
void BlkMove(_CHAR*,_BGSCROLL*);
void DamyMove(_CHAR*,_BGSCROLL*);
void ItemMove(_CHAR*,_BGSCROLL*);


void SetDrawFlag(_CHAR*);
/***SetDrawFlag�֐�********************************
	�\���t���O��ON-OFF
	
	�L�����N�^����ʂ̊O�ɏo�Ă��邩���ׂāA
	��ʊO�Ȃ炻�̃L�����N�^�̕\���t���O
	(_CHAR�\���̂�fDraw�����o)��FALSE(��\��)�ɂ�,
	��ʓ��Ȃ�TRUE(�\��)�ɂ���
	
	�����F���ׂ�L�����N�^�̃A�h���X
**************************************************/
#endif 