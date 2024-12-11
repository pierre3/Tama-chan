/*directS.cpp*/
//****************************************************
//インクルード
//***************************************************
#include "gameMain.h"
#include "directS.h" 

//************************************************
//グローバル変数
//************************************************
_DSOUND DSound;
//**************************************************
//DirectSoundの設定
//**************************************************

BOOL _DSOUND::DSCreate() {
	//------------------------------------------
	//ローカル変数
	//-----------------------------------------
	HRESULT			hResult;//エラーチェック用
	GUID* guID = NULL;//サウンドデバイスID
	DSBUFFERDESC	dsbd;//プライマリバッファの機能設定用
	//-----------------------------------
	//Direct Sound Object の作成
	//------------------------------------
	hResult = DirectSoundCreate(
		guID,
		&lpDS,
		NULL);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "オブジェクトの作成に失敗",
			"DSoundエラー", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//----------------------------------
	//協調レベルの設定
	//---------------------------------
	hResult = lpDS->SetCooperativeLevel(
		gData.hwnd,
		DSSCL_PRIORITY);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "協調レベルの設定に失敗",
			"DSoundエラー", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//-----------------------------
	//プライマリバッファの作成
	//----------------------------
	//バッファ機能の設定
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER |
		DSBCAPS_CTRLVOLUME;


	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	//プライマリバッファの作成
	hResult = lpDS->CreateSoundBuffer(
		&dsbd,
		&lpDSPrm,
		NULL);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "プライマリバッファの作成に失敗",
			"DSoundエラー", MB_OK | MB_ICONSTOP);
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
//WAVEデータの読み込み
//***********************************************************************  
BOOL _DSOUND::LoadWave(LPSTR lpszFileName, LPDIRECTSOUNDBUFFER* lplpDSSec) {
	//-------------------------------------------------------
	//ローカル変数
	//-------------------------------------------------------
	//セカンダリバッファ作成用
	DSBUFFERDESC	dsbd;//プライマリバッファの機能設定用
	//ファイルデータ取得用
	WAVEFORMATEX waveFormat;//fmtチャンクのデータを格納
	char* lpWaveData;//WAVEデータを格納する領域へのポインタ
	DWORD		dwDataSize;//WAVEデータのサイズを格納
	MMCKINFO	ckWAVE,//親チャンク用
		ckData;//サブチャンク用
	HMMIO		hFile;//開いたファイルのハンドル

	//エラーチェック用
	MMRESULT	mmResult;
	HRESULT		hResult;
	//セカンダリバッファへの書き込み用
	LPVOID		lpLock1, lpLock2;//ロック地点取得用
	DWORD		dwLockSize1, dwLockSize2;//ロックされた領域取得用
	//--------------------------------------------------------
	//WAVEファイルを開く
	//--------------------------------------------------------
	hFile = mmioOpen(lpszFileName,
		NULL,
		MMIO_READ);
	if (NULL == hFile) {
		MessageBox(gData.hwnd, "ファイルを開くのに失敗",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------------
	//WAVEチャンクの検索
	//---------------------------------------------------------
	ckWAVE.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmResult = mmioDescend(hFile,
		&ckWAVE,
		NULL,//親チャンクなし
		MMIO_FINDRIFF);//RIFF内の検索
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "WAVEファイルではなかった",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}

	//-----------------------------------------
	//fmtチャンクを検索して進入
	//----------------------------------------
	ckData.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmResult = mmioDescend(hFile,
		&ckData,
		&ckWAVE,
		MMIO_FINDCHUNK);
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "fmtチャンクが見つからなかった",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//---------------------------------------------
	//チャンクデータをWAVEFORMATEXに読み込む
	//--------------------------------------------
	mmResult = mmioRead(hFile,
		(char*)&waveFormat,
		sizeof(waveFormat));
	if (mmResult == -1) {
		MessageBox(gData.hwnd, "フォーマット読み込みに失敗",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//---------------------------------------------
	//fmtを退出する
	//--------------------------------------------
	mmResult = mmioAscend(hFile,
		&ckData, 0);
	if (mmResult != MMSYSERR_NOERROR) {
		MessageBox(gData.hwnd, "fmtチャンクからの退出に失敗",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//-----------------------------------------------
	//dataチャンクを検索して進入
	//---------------------------------------------
	ckData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = mmioDescend(hFile,
		&ckData,
		&ckWAVE,
		MMIO_FINDCHUNK);
	if (mmResult == MMIOERR_CHUNKNOTFOUND) {
		MessageBox(gData.hwnd, "dataチャンクが見つからなかった",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	//-----------------------------------------
	//dataチャンクサイズを取得する
	//-----------------------------------------
	dwDataSize = ckData.cksize;
	//------------------------------------------
	//サウンドデータをメモリに読み込む
	//------------------------------------------
	lpWaveData = (char*)malloc(dwDataSize);
	mmResult = mmioRead(hFile,
		lpWaveData,
		dwDataSize);
	if (mmResult == -1) {
		MessageBox(gData.hwnd, "WAVEデータの読み込みに失敗",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		mmioClose(hFile, NULL);
		return(FALSE);
	}
	mmioClose(hFile, NULL);
	//--------------------------------------------------
	//セカンダリバッファの作成
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
		MessageBox(gData.hwnd, "セカンダリバッファの作成に失敗",
			"DirectSoundエラー", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------
	//取得データをセカンダリバッファへ書き込む
	//---------------------------------------------------
	//セカンダリバッファのロック
	hResult = (*lplpDSSec)->Lock(0,
		dwDataSize,
		&lpLock1, &dwLockSize1,//一箇所目
		&lpLock2, &dwLockSize2,//二箇所目
		DSBLOCK_FROMWRITECURSOR);
	if (FAILED(hResult)) {
		MessageBox(gData.hwnd, "セカンダリバファのロックに失敗",
			"WAVE読み込みエラー", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//サウンドデータをセカンダリバッファへコピーする
	CopyMemory(lpLock1,
		lpWaveData,
		dwLockSize1);
	if (dwLockSize2 != 0)
		CopyMemory(lpLock2,
			lpWaveData + dwLockSize1,
			dwLockSize2);
	//アンロック
	(*lplpDSSec)->Unlock(lpLock1, dwLockSize1,
		lpLock2, dwLockSize2);

	//確保したメモリの解放
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