/*mapData.h*/

#ifndef MAPDATA_H
#define MAPDATA_H

#include "gameMain.h"
//BG�}�b�v�f�[�^
typedef struct tag_BGDATA {
	BYTE	nPartsNum,//�p�[�c�ԍ�
		nPartsOld,//���̃p�[�c�ԍ�
		nType;//�p�[�c�̃^�C�v
	WORD	wFallCnt,//��������^�C�~���O���J�E���g�i0�ɂȂ����痎���j
		wResetCnt;//�����ʒu�ɍĔz�u����^�C�~���O���J�E���g(0�ɂȂ�����z�u)
	BOOL	fFallCnt,//TRUE�FwFallCnt���J�E���g�_�E��������
		fResetCnt;//TRUE�FwResetCnt���J�E���g�_�E��������
}_BGDATA, * _LPBGDATA;
typedef struct tag_CHARPOS {
	WORD	wX,
		wY;
}_CHARPOS, * _LPCHARPOS;
typedef struct tag_MAPDATA {
	_LPBGDATA	lpBgData;
	WORD		wMapW, wMapH;
	BYTE* lpFloorData;
	BYTE		nCageCount;
	_CHARPOS	myCharPos;
	_LPCHARPOS	lpEnemyPos;
}_MAPDATA, * _LPMAPDATA;

extern void FreeMap();
extern BOOL LoadMapData(LPCSTR);
extern _LPMAPDATA GetMapData();

#endif