/*MIDIStream.cpp*/
#include "gameMain.h"
#include "MIDIStream.h"
//***************************
//グローバル
//**************************
MIDISTREAM midiStream;

//文字表示用データ
DWORD	g_dwTempo;
WORD	g_wLVol,g_wRVol;
BOOL	g_fTempo=TRUE;

//***********************************************************
//mdsファイルを読み込みMIDIHDRに読み出す
//***********************************************************
BOOL mdsLoad(LPSTR lpszFileName){
	//---------------------------------------------------
	//ローカル変数
	//---------------------------------------------------
	HMMIO		hFile;			//ファイルハンドル
	MMCKINFO	ckMIDS,ckSub;	//チャンク情報
	DWORD		dwDataSize;		//dataチャンクサイズ取得用
	BYTE		*lpMDSData;//dataチャンクを読み込む
	MMRESULT	mmResult;		//エラーチェック用
	//-----------------------------------------------
	//MDSファイルを開く
	//----------------------------------------------
	hFile=mmioOpen(lpszFileName,
				NULL,MMIO_READ);
	if(NULL==hFile){
		MessageBox(gData.hwnd,"MDSファイルを開くのに失敗",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);
	}
	//----------------------------------------------
	//MIDSチャンクに進入
	//---------------------------------------------
	ckMIDS.fccType	=mmioFOURCC('M','I','D','S');
	mmResult		=mmioDescend(hFile,
						&ckMIDS,
						NULL,
						MMIO_FINDRIFF);
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"MDSファイルではない",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);		
		return(FALSE);
	}
	//-----------------------------------------------------
	//fmtチャンクに進入
	//------------------------------------------------------
	ckSub.ckid	=mmioFOURCC('f','m','t',' ');
	mmResult	=mmioDescend(hFile,
					&ckSub,
					&ckMIDS,
					MMIO_FINDCHUNK);
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"fmtチャンクが見つからない",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//----------------------------------------------------------
	//fmtチャンクデータ読み込み
	//-------------------------------------------------------
	mmResult	=mmioRead(hFile,
					(char*)&midiStream.mdsFormat,
					sizeof(midiStream.mdsFormat));
	if(mmResult==-1){
		MessageBox(gData.hwnd,"fmtチャンク読み取りエラー",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//------------------------------------------------------------
	//チャンクから退出
	//------------------------------------------------------------
	mmResult	=mmioAscend(hFile,&ckSub,0);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"fmtチャンクからの退出に失敗",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//-------------------------------------------------------------
	//dataチャンクへ進入
	//-------------------------------------------------------------
	ckSub.ckid	=mmioFOURCC('d','a','t','a');
	mmResult	=mmioDescend(hFile,
					&ckSub,
					&ckMIDS,
					MMIO_FINDCHUNK);
	
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"dataチャンクが見つからなかった",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//-----------------------------------------------------------
	//dataチャンクサイズを控える
	//-----------------------------------------------------------
	dwDataSize	=ckSub.cksize;
	//-----------------------------------------------------------
	//分割読み取り
	//-----------------------------------------------------------
	mmResult	=mmioRead(hFile,
				(char*)&midiStream.dwMaxBlockCount,//ここに分割数が入る
				sizeof(DWORD));
	if(mmResult	==	-1){
		MessageBox(gData.hwnd,"分割読み取りエラー",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);		
	}
	//--------------------------------------------------------
	//ブロック数分のメモリ確保
	//--------------------------------------------------------
	lpMDSData=(BYTE*)GlobalAlloc(
					GPTR,
					dwDataSize);
	//----------------------------------------------------------
	//ブロックデータをメモリに書き込む
	//----------------------------------------------------------
	mmResult	=mmioRead(hFile,
					(char*)lpMDSData,//ここに各ブロックデータが入る
					dwDataSize);
	if(mmResult	==	-1){
		MessageBox(gData.hwnd,"ブロックデータ読み取りエラー",
			"MIDIストリーム読み込みエラー",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//MDSファイルを閉じる
	mmioClose(hFile,NULL);
	//-----------------------------------------------------------
	//ブロック数分MIDIHDR構造体を用意
	//-----------------------------------------------------------
	midiStream.lpMidiHdr	=(MIDIHDR*)GlobalAlloc(
							GPTR,
							sizeof(MIDIHDR) * midiStream.dwMaxBlockCount);
	
	BYTE *lpTmpAddr;
	//
	lpTmpAddr	=lpMDSData;
	for(DWORD i=0;	i < midiStream.dwMaxBlockCount;	i++){
		//lpDataメンバにブロックサイズ分のメモリを確保
		midiStream.lpMidiHdr[i].lpData=
				(LPSTR)GlobalAlloc(GPTR,
				midiStream.mdsFormat.dwMaxBuffer);
		//dwBuffreLengthメンバにブロックサイズを代入
		midiStream.lpMidiHdr[i].dwBufferLength=
				midiStream.mdsFormat.dwMaxBuffer;
		//dwBytesRecordedメンバに演奏データのサイズを入れる
		midiStream.lpMidiHdr[i].dwBytesRecorded=
				((LPMDSBUFFER)lpMDSData)->dwBlockLength;
		//ブロック番号
		midiStream.lpMidiHdr[i].dwUser		=i;
		//その他
		midiStream.lpMidiHdr[i].reserved	=0;
		midiStream.lpMidiHdr[i].dwFlags		=0;
		midiStream.lpMidiHdr[i].lpNext		=NULL;
		
		//演奏データが入っている地点までアドレスを進める
		lpMDSData +=sizeof(MDSBUFFER);
		
		//lpDataメンバに演奏データをコピーする
		CopyMemory(midiStream.lpMidiHdr[i].lpData,
				lpMDSData,
				midiStream.lpMidiHdr[i].dwBytesRecorded);
		
		//次の演奏ブロックまでアドレスを進める
		lpMDSData +=midiStream.lpMidiHdr[i].dwBytesRecorded;
	}
	//
	GlobalFree(lpTmpAddr);
	return(TRUE);
}
//*************************************************************************
//MIDIストリームの準備
//************************************************************************
BOOL mdsOpen(LPSTR lpszFileName){
	//--------------------------------
	//ローカル変数
	//-------------------------------
	UINT			uiID;//使用デバイスID
	MMRESULT		mmResult;//エラーチェック用
	MIDIPROPTIMEDIV	midiProp;//MIDI時間設定用
	
	//デバイスのハンドル、IDを初期化
	midiStream.hMidiStream		=0;
	uiID			=MIDI_MAPPER;
	//----------------------------------------------------------
	//MDSの読み込み
	//----------------------------------------------------------
	if(!mdsLoad(lpszFileName)){
		return(FALSE);
	}
	//------------------------------------------------------------
	//デバイスオープン
	//------------------------------------------------------------
	mmResult	=midiStreamOpen(
				&midiStream.hMidiStream,//デバイスハンドルの取得
				&uiID,				//デバイスIDの指定
				1,					//１に予約
				(DWORD)StreamProc,//ストリーム用プロシージャ
				0,
				CALLBACK_FUNCTION);//コールバック関数としてストリーム用プロシージャを使用
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDIデバイスのオープンに失敗",
			"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	//-----------------------------------------------
	//MIDIタイムプロパティの設定
	//----------------------------------------------
	midiProp.cbStruct	=sizeof(midiProp);
	midiProp.dwTimeDiv	=midiStream.mdsFormat.dwTimeFormat;
	mmResult	=midiStreamProperty(
				midiStream.hMidiStream,
				(BYTE*)&midiProp,
				MIDIPROP_SET | MIDIPROP_TIMEDIV);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDIタイムプロパティの設定に失敗",
			"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	return(TRUE);
}
//*****************************************************************
//MIDIストリームの演奏
//*****************************************************************
BOOL mdsPlay(LPSTR lpszFileName,BOOL fLoopFlag){
	
	//-----------------------------------------
	//デバイスの二重オープン禁止
	//----------------------------------------
	if(midiStream.fPlay)	return (TRUE);
	//--------------------------------------------
	//MIDIストリームの準備
	//--------------------------------------------
	if(!mdsOpen(lpszFileName)){
		return (FALSE);
	}
	
	//----------------------------------------
	//ループフラグセット
	//--------------------------------------
	midiStream.fLoop	=fLoopFlag;
	//----------------------------------------
	//ローカル変数
	//---------------------------------------
	MMRESULT	mmResult;//エラーチェック用
	
	//-----------------------------------------------------------
	//ブロックDataの転送
	//-----------------------------------------------------------
	
	midiStream.dwSetBlockNum	=0;//ブロック番号を０に初期化
	
	for(DWORD i=0;i<16;i++){//最大16まで積める
		
		if(i>=midiStream.dwMaxBlockCount)//全ブロック数が16個以下の時
			break;
		
		//転送準備
		mmResult=midiOutPrepareHeader(
			(HMIDIOUT)midiStream.hMidiStream,//デバイスハンドル
			&midiStream.lpMidiHdr[i],//転送ブロックデータ
			sizeof(MIDIHDR));//サイズ
		if(mmResult!=MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"MIDIブロックデータの転送準備に失敗",
				"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
			return(FALSE);
		}
		//転送
		mmResult=midiStreamOut(
			midiStream.hMidiStream,
			&midiStream.lpMidiHdr[i],
			sizeof(MIDIHDR));
		if(mmResult!=MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"MIDIブロックデータの転送に失敗",
				"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
			return(FALSE);
		}
		//次のブロックに番号を進める
		midiStream.dwSetBlockNum++;
	}
	//--------------------------------------------------------
	//演奏を開始する
	//--------------------------------------------------------
	mmResult=midiStreamRestart(midiStream.hMidiStream);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"演奏失敗",
			"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);
	}
	//再生中フラグON
	midiStream.fPlay	=TRUE;
	
	return(TRUE);
}
//*************************************************************
//演奏終了、MIDIストリームの終了処理
//*************************************************************
BOOL mdsStop(){
	
	MMRESULT	mmResult;//エラーチェック用変数
	
	//再生中でなければ何もしない
	if(!midiStream.fPlay)	return(TRUE);
	
	//再生中フラグをFALSEにする
	midiStream.fPlay	=FALSE;
	
	//演奏停止
	mmResult=midiStreamStop(midiStream.hMidiStream);
	if(mmResult != MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDIストリームデバイスのクローズに失敗",
			"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	
	//全ブロックの出力停止
	midiOutReset((HMIDIOUT)midiStream.hMidiStream);
	
	//全ブロック(ストリームバッファ)の解除
	for(DWORD i=0;i<midiStream.dwMaxBlockCount;i++)
	{
		mmResult=midiOutUnprepareHeader(
				(HMIDIOUT)midiStream.hMidiStream,
				&midiStream.lpMidiHdr[i],
				sizeof(MIDIHDR));
		if(mmResult != MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"ストリームバッファの解除に失敗",
				"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
			return(FALSE);	
		}
	}
	
	//ブロックデータ用メモリの解放
	for(i=0;i<midiStream.dwMaxBlockCount;i++)
	{
		GlobalFree(midiStream.lpMidiHdr[i].lpData);
	}
	GlobalFree(midiStream.lpMidiHdr);
	
	//MIDIストリームデバイスを閉じる
	mmResult=midiStreamClose(midiStream.hMidiStream);
	if(mmResult != MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDIストリームデバイスのクローズに失敗",
			"MIDIストリームエラー",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	
	return(TRUE);
}
//****************************************************************
//MIDIストリームプロシージャ
//****************************************************************
void CALLBACK StreamProc(HMIDIIN hMidiIn,UINT msg,
						 DWORD hInst,DWORD wParam,DWORD lParam)
{
	//演奏中でなければ抜ける
	if(!midiStream.fPlay){
		return;
	}

	//1ブロックの演奏が終了したら次ブロックを演奏キューにセット
	if(msg==MOM_DONE){
		if(midiStream.fLoop){
			if(midiStream.dwSetBlockNum
				==midiStream.dwMaxBlockCount)
				midiStream.dwSetBlockNum  =0;
		}
		//セットするブロック番号がブロック最大数未満ならブロックを転送
		if(midiStream.dwSetBlockNum!=midiStream.dwMaxBlockCount){
			//転送準備
			midiOutPrepareHeader(
				(HMIDIOUT)midiStream.hMidiStream,
				&midiStream.lpMidiHdr[midiStream.dwSetBlockNum],
				sizeof(MIDIHDR));
			
			//転送
			midiStreamOut(
				midiStream.hMidiStream,
				&midiStream.lpMidiHdr[midiStream.dwSetBlockNum],
				sizeof(MIDIHDR));
			
			char st[256];
			wsprintf(st, "%d %d %d %d\n",midiStream.dwMaxBlockCount,midiStream.dwSetBlockNum,((MIDIHDR*)wParam)->dwUser, lParam);
			OutputDebugString(st);
			midiOutUnprepareHeader((HMIDIOUT)midiStream.hMidiStream,
				(MIDIHDR*)wParam,
				sizeof(MIDIHDR));

			
			//次のブロックに番号を進める
			midiStream.dwSetBlockNum++;		
		}
	}
	//ループの指定があれば
	//ブロック番号がブロック最大数になった時に
	//ブロック番号を０番に戻す
	if(midiStream.fLoop){
		if(midiStream.dwSetBlockNum
			==midiStream.dwMaxBlockCount)
			midiStream.dwSetBlockNum  =0;
	}
}
/*
//**************************************************************************
//各種コントロールのテスト用関数
//**************************************************************************
void mdsTest(){
	
	//停止*******************************
	if(GetAsyncKeyState(0x74) & 0xff00){//F5
		mdsStop();
	}else if(GetAsyncKeyState(0x75) & 0xff00){//F6
		mdsPlay("testSong1.mds",TRUE);
	}else if(GetAsyncKeyState(0x76) & 0xff00){//F7
		mdsPlay("testSong2.mds",TRUE);
	}else if(GetAsyncKeyState(0x77) & 0xff00){//F8
		mdsPlay("testSong4.mds",TRUE);
	}
	//一時停止******************************
	if(midiStream.fPause){
		if(GetAsyncKeyState(0x78) & 0xff00){//F9
			midiStream.fPause=FALSE;
			midiStreamRestart(midiStream.hMidiStream);
		}
	}else{
		if(GetAsyncKeyState(0x79) & 0xff00){//F10
			midiStream.fPause=TRUE;
			midiStreamPause(midiStream.hMidiStream);
		}
	}
	//ボリューム、テンポ*********************************
	
	

	if(GetAsyncKeyState(VK_LEFT) & 0xff00)
		g_fTempo=TRUE;
	else if(GetAsyncKeyState(VK_RIGHT) & 0xff00)
		g_fTempo=FALSE;

	if(g_fTempo){	
		//テンポチェンジ
		if(GetAsyncKeyState(VK_UP) & 0xff00)
			mdsChgTempo(-1000,TRUE);
		else if(GetAsyncKeyState(VK_DOWN) & 0xff00)
			mdsChgTempo(1000,TRUE);
	}else{
		//ボリュームチェンジ
		if(GetAsyncKeyState(VK_UP) & 0xff00)
			mdsChgVolume(100,100,TRUE);
		else if(GetAsyncKeyState(VK_DOWN) & 0xff00)
			mdsChgVolume(-100,-100,TRUE);
	}
}
//***************************************************
//MIDIストリームテンポチェンジ
//***************************************************
void mdsChgTempo(int nVal,BOOL fAdd){
	
	if(!midiStream.fPlay)	return;

	MIDIPROPTEMPO	midiProp;

	midiProp.cbStruct	=sizeof(midiProp);
	midiProp.dwTempo	=0;

	//現在のテンポの値を取得
	midiStreamProperty(midiStream.hMidiStream,
		(BYTE*)&midiProp,
		MIDIPROP_GET | MIDIPROP_TEMPO);
	
	//テンポの値を変える
	if(fAdd)	
		midiProp.dwTempo	+=nVal;
	else
		midiProp.dwTempo	=nVal;
	
	g_dwTempo	=midiProp.dwTempo;

	//修正後のテンポの値をセットする
	midiStreamProperty(midiStream.hMidiStream,
		(BYTE*)&midiProp,
		MIDIPROP_SET | MIDIPROP_TEMPO);

}
//**********************************************************
//MIDIストリームボリュームチェンジ
//**********************************************************
void mdsChgVolume(short nLeftVal,short nRightVal,BOOL fAdd){
	
	if(!midiStream.fPlay)	return;

	DWORD	dwVolume;
	WORD	wVolumeL,wVolumeR;

	midiOutGetVolume(
		(HMIDIOUT)midiStream.hMidiStream,
		&dwVolume);
	
	wVolumeL	=LOWORD(dwVolume);
	wVolumeR	=HIWORD(dwVolume);
	
	if(fAdd){
		wVolumeL	+=nLeftVal;
		wVolumeR	+=nRightVal;
	}else{
		wVolumeL	=nLeftVal;
		wVolumeR	=nRightVal;
	}
	
	g_wLVol	=wVolumeL;
	g_wRVol	=wVolumeR;

	midiOutSetVolume(
		(HMIDIOUT)midiStream.hMidiStream,
		MAKELONG(wVolumeL,wVolumeR));
}
*/

void mdsPause()
{
	if(midiStream.fPause)
		return;
	else
		midiStream.fPause=TRUE;
	midiStreamPause(midiStream.hMidiStream);
	
}
void mdsRestert()
{	
	if(midiStream.fPause)
		midiStream.fPause=FALSE;
	else
		return;

	midiStreamRestart(midiStream.hMidiStream);
}