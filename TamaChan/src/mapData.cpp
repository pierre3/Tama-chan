
#include "mapData.h"
////////////////////////////////////
//�O���[�o���ϐ�
_MAPDATA mapData = { 0 };
//////////////////////////////////////
//�}�b�v�f�[�^������Ă���
_LPMAPDATA GetMapData()
{
	return(&mapData);
}

//���������
void FreeMap()
{
	if (NULL != mapData.lpBgData)
	{
		GlobalFree(mapData.lpBgData);
		mapData.lpBgData = NULL;
	}
	if (NULL != mapData.lpFloorData)
	{
		GlobalFree(mapData.lpFloorData);
		mapData.lpFloorData = NULL;
	}
}

//�}�b�v�f�[�^�̃��[�h
BOOL LoadMapData(LPCSTR lpPathName)
{
	HFILE hFile;
	UINT err;

	FreeMap();
	ZeroMemory(&mapData, sizeof(_MAPDATA));
	//�t�@�C���I�[�v��
	hFile = _lopen(lpPathName, OF_READ);
	if (hFile == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE OPEN EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�t�@�C���ǂݍ���////////////////////////////////////////////////////////

	//�}�b�v�T�C�Y//////////////////////////////////////////////////////
	err = _lread(hFile, (WORD*)&mapData.wMapW, sizeof(WORD) * 2);
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�B�̐�//////////////////////////////////////////////////////
	err = _lread(hFile, (BYTE*)&mapData.nCageCount, sizeof(BYTE));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�t���A�f�[�^//////////////////////////////////////////////////////////
	//�������m��
	mapData.lpFloorData = (BYTE*)GlobalAlloc(GPTR,
		sizeof(BYTE) * (mapData.wMapH));
	if (NULL == mapData.lpFloorData)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��sF",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//�ǂݍ���
	err = _lread(hFile, (BYTE*)mapData.lpFloorData, sizeof(BYTE) * (mapData.wMapH));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//MycharPos//////////////////////////////////////////////////
	err = _lread(hFile, (_LPCHARPOS)&mapData.myCharPos,
		sizeof(_CHARPOS));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//EnemyPos////////////////////////////////////////////////
	//�������m��
	mapData.lpEnemyPos = (_LPCHARPOS)GlobalAlloc(GPTR,
		sizeof(_CHARPOS) * mapData.nCageCount);
	if (NULL == mapData.lpEnemyPos)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��sB",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//�ǂݍ���
	err = _lread(hFile, (_LPCHARPOS)mapData.lpEnemyPos,
		sizeof(_CHARPOS) * mapData.nCageCount);
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//BG�f�[�^///////////////////////////////////////////////
	//�������m��
	mapData.lpBgData = (_LPBGDATA)GlobalAlloc(GPTR,
		sizeof(_BGDATA) * (mapData.wMapW) * (mapData.wMapH));
	if (NULL == mapData.lpBgData)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��sB",
			"MEMORY EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//�ǂݍ���
	err = _lread(hFile, (_LPBGDATA)mapData.lpBgData,
		sizeof(_BGDATA) * (mapData.wMapW) * (mapData.wMapH));
	if (err == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE READ EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	////////////////////////////////////////////////////////////////
	//�t�@�C���N���[�Y
	if (_lclose(hFile) == HFILE_ERROR)
	{
		MessageBox(gData.hwnd, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s",
			"FILE CLOSE EROOR", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	return(TRUE);
}

