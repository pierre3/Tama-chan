/*dash.cpp*/
//***********************
//�C���N���[�h
//***********************
#include "gameMain.h"
#include "dash.h"
//*******************************************************
//�_�b�V���֐�
//******************************************************
//�ړ��ʂɉ��Z����_�b�V���ړ��ʂ�ω�������

//���Ƀ_�b�V��
void DashL(_CHAR* lpMC) {
	lpMC->nStatus |= _STATUS_DASH;//�_�b�V���t���OON
	lpMC->nDashSPD -= _ADD_SPD;//�_�b�V���l��_ADD_SPD�������炷
	if (lpMC->nDashSPD < -_DASH_MAX)//�ŏ��l�ȉ��ɂ͂��Ȃ�
		lpMC->nDashSPD = -_DASH_MAX;

}
//�E�Ƀ_�b�V��
void DashR(_CHAR* lpMC) {
	lpMC->nStatus |= _STATUS_DASH;//�_�b�V���t���OON
	lpMC->nDashSPD += _ADD_SPD;//�_�b�V���l��_ADD_SPD�������Z
	if (lpMC->nDashSPD > _DASH_MAX)//�ő�l�ȏ�ɂ͂��Ȃ�
		lpMC->nDashSPD = _DASH_MAX;

}
//�E�_�b�V�������� 
void DashRBrake(_CHAR* lpMC) {
	lpMC->nDashSPD -= _ADD_SPD;
	if (lpMC->nDashSPD < 0)
		lpMC->nDashSPD = 0;
}
//���_�b�V��������
void DashLBrake(_CHAR* lpMC) {
	lpMC->nDashSPD += _ADD_SPD;
	if (lpMC->nDashSPD > 0)
		lpMC->nDashSPD = 0;
}
//�E�_�b�V���������i2�{�j
void DashRBrake2(_CHAR* lpMC) {
	lpMC->nDashSPD -= _ADD_SPD << 1;
	if (lpMC->nDashSPD < 0)
		lpMC->nDashSPD = 0;
}
//���_�b�V���������i2�{�j
void DashLBrake2(_CHAR* lpMC) {
	lpMC->nDashSPD += _ADD_SPD << 1;
	if (lpMC->nDashSPD > 0)
		lpMC->nDashSPD = 0;
}
//�_�b�V���I��
void DashOff(_CHAR* lpMC) {
	lpMC->nStatus &= ~_STATUS_DASH;
}
//�������Ȃ�
void NoChange(_CHAR* lpMC) {
	return;
}