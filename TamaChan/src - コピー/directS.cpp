/*directS.cpp*/
//****************************************************
//�C���N���[�h
//***************************************************
#include "gameMain.h"
#include "directS.h" 

//************************************************
//�O���[�o���ϐ�
//************************************************
_DSOUND DSound;
//**************************************************
//DirectSound�̐ݒ�
//**************************************************

BOOL _DSOUND::DSCreate() {
	//------------------------------------------
	//���[�J���ϐ�
	//-----------------------------------------
	HRESULT			hResult;//�G���[�`�F�b�N�p
	GUID* guID = NULL;//�T�E���h�f�o�C�XID
	DSBUFFERDESC	dsbd;//�v���C�}���o�b�t�@�̋@�\�ݒ�p
	//-----------------------------------
	//Direct Sound Object �̍쐬
	//------------------------------------
	hResult = DirectSoundCreate(
		guID,
		&lpDS,
		NULL);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "�I�u�W�F�N�g�̍쐬�Ɏ��s",
			"DSound�G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//----------------------------------
	//�������x���̐ݒ�
	//---------------------------------
	hResult = lpDS->SetCooperativeLevel(
		gData.hwnd,
		DSSCL_PRIORITY);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "�������x���̐ݒ�Ɏ��s",
			"DSound�G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//-----------------------------
	//�v���C�}���o�b�t�@�̍쐬
	//----------------------------
	//�o�b�t�@�@�\�̐ݒ�
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER |
		DSBCAPS_CTRLVOLUME;


	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	//�v���C�}���o�b�t�@�̍쐬
	hResult = lpDS->CreateSoundBuffer(
		&dsbd,
		&lpDSPrm,
		NULL);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "�v���C�}���o�b�t�@�̍쐬�Ɏ��s",
			"DSound�G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	if (!LoadWave(const_cast<char*>("waveData\\powan.wav"), &lpDSSec[SOUND_JUMP]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\piko.wav"), &lpDSSec[SOUND_HEAD]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\OH-YEA!.wav"), &lpDSSec[SOUND_OPEN]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\koripon.wav"), &lpDSSec[SOUND_HIT]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\hitBlock.wav"), &lpDSSec[SOUND_BLKBREAK]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\pikopiko.wav"), &lpDSSec[SOUND_PAUSE]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\gossan.wav"), &lpDSSec[SOUND_CAGE]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\ufu1.wav"), &lpDSSec[SOUND_DAMAGE]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\escape.wav"), &lpDSSec[SOUND_ESCAPE]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\warning.wav"), &lpDSSec[SOUND_WARNING]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\nandayo.wav"), &lpDSSec[SOUND_GOVER]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\hartGet.wav"), &lpDSSec[SOUND_ITEM]))
		return(FALSE);
	if (!LoadWave(const_cast<char*>("waveData\\Alien Out.wav"), &lpDSSec[SOUND_HITCAGE]))
		return(FALSE);

	return(TRUE);
}
//***********************************************************************
//WAVE�f�[�^�̓ǂݍ���
//***********************************************************************  
BOOL _DSOUND::LoadWave(LPSTR lpszFileName, LPDIRECTSOUNDBUFFER* lplpDSSec) {
	//-------------------------------------------------------
	//���[�J���ϐ�
	//-------------------------------------------------------
	//�Z�J���_���o�b�t�@�쐬�p
	DSBUFFERDESC	dsbd;//�v���C�}���o�b�t�@�̋@�\�ݒ�p
	//�t�@�C���f�[�^�擾�p
	WAVEFORMATEX waveFormat;//fmt�`�����N�̃f�[�^���i�[
	char* lpWaveData;//WAVE�f�[�^���i�[����̈�ւ̃|�C���^
	DWORD		dwDataSize;//WAVE�f�[�^�̃T�C�Y���i�[
	MMCKINFO	ckWAVE,//�e�`�����N�p
		ckData;//�T�u�`�����N�p
	HMMIO		hFile;//�J�����t�@�C���̃n���h��

	//�G���[�`�F�b�N�p
	MMRESULT	mmResult;
	HRESULT		hResult;
	//�Z�J���_���o�b�t�@�ւ̏������ݗp
	LPVOID		lpLock1, lpLock2;//���b�N�n�_�擾�p
	DWORD		dwLockSize1, dwLockSize2;//���b�N���ꂽ�̈�擾�p
	//--------------------------------------------------------
	//WAVE�t�@�C�����J��
	//--------------------------------------------------------
	hFile = mmioOpen(lpszFileName,
		NULL,
		MMIO_READ);
	if (NULL == hFile) {
		MessageBox(gData.hwnd, "�t�@�C�����J���̂Ɏ��s",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------------
	//WAVE�`�����N�̌���
	//---------------------------------------------------------
	ckWAVE.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmResult = mmioDescend(hFile,
		&ckWAVE,
		NULL,//�e�`�����N�Ȃ�
		MMIO_FINDRIFF);//RIFF���̌���
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "WAVE�t�@�C���ł͂Ȃ�����",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}

	//-----------------------------------------
	//fmt�`�����N���������Đi��
	//----------------------------------------
	ckData.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmResult = mmioDescend(hFile,
		&ckData,
		&ckWAVE,
		MMIO_FINDCHUNK);
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "fmt�`�����N��������Ȃ�����",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//---------------------------------------------
	//�`�����N�f�[�^��WAVEFORMATEX�ɓǂݍ���
	//--------------------------------------------
	mmResult = mmioRead(hFile,
		(char*)&waveFormat,
		sizeof(waveFormat));
	if (mmResult == -1) {
		MessageBox(gData.hwnd, "�t�H�[�}�b�g�ǂݍ��݂Ɏ��s",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//---------------------------------------------
	//fmt��ޏo����
	//--------------------------------------------
	mmResult = mmioAscend(hFile,
		&ckData, 0);
	if (mmResult != MMSYSERR_NOERROR) {
		MessageBox(gData.hwnd, "fmt�`�����N����̑ޏo�Ɏ��s",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//-----------------------------------------------
	//data�`�����N���������Đi��
	//---------------------------------------------
	ckData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = mmioDescend(hFile,
		&ckData,
		&ckWAVE,
		MMIO_FINDCHUNK);
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "data�`�����N��������Ȃ�����",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//-----------------------------------------
	//data�`�����N�T�C�Y���擾����
	//-----------------------------------------
	dwDataSize = ckData.cksize;
	//------------------------------------------
	//�T�E���h�f�[�^���������ɓǂݍ���
	//------------------------------------------
	lpWaveData = (char*)malloc(dwDataSize);
	mmResult = mmioRead(hFile,
		lpWaveData,
		dwDataSize);
	if (mmResult == -1) {
		MessageBox(gData.hwnd, "WAVE�f�[�^�̓ǂݍ��݂Ɏ��s",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	mmioClose(hFile, NULL);
	//--------------------------------------------------
	//�Z�J���_���o�b�t�@�̍쐬
	//-------------------------------------------------
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 |
		DSBCAPS_CTRLPAN |
		DSBCAPS_CTRLVOLUME |
		DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = dwDataSize;
	dsbd.lpwfxFormat = &waveFormat;
	hResult = lpDS->CreateSoundBuffer(&dsbd, lplpDSSec, NULL);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "�Z�J���_���o�b�t�@�̍쐬�Ɏ��s",
			"DirectSound�G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------
	//�擾�f�[�^���Z�J���_���o�b�t�@�֏�������
	//---------------------------------------------------
	//�Z�J���_���o�b�t�@�̃��b�N
	hResult = (*lplpDSSec)->Lock(0,
		dwDataSize,
		&lpLock1, &dwLockSize1,//��ӏ���
		&lpLock2, &dwLockSize2,//��ӏ���
		DSBLOCK_FROMWRITECURSOR);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "�Z�J���_���o�t�@�̃��b�N�Ɏ��s",
			"WAVE�ǂݍ��݃G���[", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//�T�E���h�f�[�^���Z�J���_���o�b�t�@�փR�s�[����
	CopyMemory(lpLock1,
		lpWaveData,
		dwLockSize1);
	if (dwLockSize2 != 0)
		CopyMemory(lpLock2,
			lpWaveData + dwLockSize1,
			dwLockSize2);
	//�A�����b�N
	(*lplpDSSec)->Unlock(lpLock1, dwLockSize1,
		lpLock2, dwLockSize2);

	//�m�ۂ����������̉��
	free(lpWaveData);

	return(TRUE);
}
void DSoundPlay(BYTE nSoundNum) {
	DSound.lpDSSec[nSoundNum]->SetCurrentPosition(0);
	DSound.lpDSSec[nSoundNum]->Play(0, 0, 0);
}

void DSoundClear()
{

	DSound.lpDS = NULL;
	DSound.lpDSPrm = NULL;
	for (BYTE i = 0; i < SOUND_MAX; i++)
		DSound.lpDSSec[i] = NULL;
}

void ReleaseDS()
{
	for (BYTE i = 0; i < SOUND_MAX + 1; i++) {
		RELEASEDX(DSound.lpDSSec[i]);
	}
	RELEASEDX(DSound.lpDSPrm);
	RELEASEDX(DSound.lpDS);
}
BOOL DSoundCreate()
{
	if (!DSound.DSCreate())
		return(FALSE);

	return(TRUE);
}