/*ctachCount.cpp*/

#include "catchCount.h"
/////////////////////////////////////
//�O���[�o���ϐ�
/////////////////////////////////////
BYTE nCatchCount = 0;
//////////////////////////////////////////////////
//�B�ɕ߂炦���G�̐��𐔂���
/////////////////////////////////////////////////

//�P�C�߂܂�����
void CatchCountCatch()
{
	nCatchCount++;
}

//�P�C��������
void CatchCountEscape()
{
	nCatchCount--;
}
//0�ɏ�����
void CatchCountZero()
{
	nCatchCount = 0;
}
//nCatchCount���擾����
BYTE GetCatchCount()
{
	return(nCatchCount);
}