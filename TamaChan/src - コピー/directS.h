/***directS.h***/
#ifndef DSOUND
#define DSOUND

//*************************************************
//マクロ
//*************************************************
#define SOUND_MAX	12//読み込むWAVEファイルの最大値

//サウンド番号
#define SOUND_JUMP		0
#define SOUND_HEAD		1
#define SOUND_OPEN		2
#define SOUND_HIT		3
#define SOUND_BLKBREAK	4
#define SOUND_PAUSE		5
#define SOUND_CAGE		6
#define SOUND_DAMAGE	7
#define SOUND_WARNING	8
#define SOUND_ESCAPE	9
#define SOUND_GOVER		10
#define SOUND_ITEM		11
#define SOUND_HITCAGE	12
//***************************************************
//DirectSound構造体
//***************************************************
typedef struct tagDSOUND{
	
	LPDIRECTSOUND		lpDS;
	LPDIRECTSOUNDBUFFER lpDSPrm;
	LPDIRECTSOUNDBUFFER lpDSSec[SOUND_MAX + 1];
	/*ダイレクトサウンド関連の設定、オブジェクトの作成*/
	BOOL DSCreate();
	//セカンダリバッファを作成し、Waveデータを読み込む
	BOOL LoadWave(LPSTR,	/*引数１：読み込むファイル名*/
		LPDIRECTSOUNDBUFFER*);/*引数２：セカンダリバッファへのポインタのアドレス*/
			
}_DSOUND;
extern void DSoundPlay(BYTE);
extern void DSoundClear();
extern void ReleaseDS();
extern BOOL DSoundCreate();
#endif