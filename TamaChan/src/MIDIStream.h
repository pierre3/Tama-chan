/*MIDIStream.h*/
#ifndef MIDISTRM_H
#define MIDISTRM_H

//***************************
//構造体
//***************************
//MDS読み込み用//////////////

//fmtチャンクデータを格納
typedef struct tagMDSFORMAT{
	DWORD	dwTimeFormat;//時間フォーマット
	DWORD	dwMaxBuffer;//分割されたブロックの最大サイズ
	DWORD	dwFormatFlags;//フォーマットフラグ
}MDSFORMAT,*LPMSDFORMAT;

//dataチャンク
//各ブロックデータ
typedef struct tagMDSBUFFER{
	DWORD	dwBlockStart;
	DWORD	dwBlockLength;
}MDSBUFFER,*LPMDSBUFFER;

typedef struct tagMIDISTREAM{
	MDSFORMAT	mdsFormat;//fmtチャンクデータを格納
	DWORD		dwMaxBlockCount;//分割ブロック数
	MIDIHDR		*lpMidiHdr;//ブロック単位で演奏データを入れる
	HMIDISTRM	hMidiStream;//MIDIデバイスハンドル
	DWORD		dwSetBlockNum;//次にキューに積む番号
	BOOL		fPlay,
				fLoop,
				fPause;
}MIDISTREAM,*LPMIDISTREAM;

///////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////
BOOL mdsLoad(LPSTR);
BOOL mdsOpen(LPSTR);
void CALLBACK StreamProc(HMIDIIN ,UINT,DWORD,DWORD,DWORD);

extern BOOL mdsPlay(LPSTR,BOOL);//再生
extern BOOL mdsStop();//停止
extern void mdsPause();//一時停止
extern void mdsRestert();//一時停止解除
#endif