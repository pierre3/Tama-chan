/*MIDIStream.cpp*/
#include "gameMain.h"
#include "MIDIStream.h"
//***************************
//�O���[�o��
//**************************
MIDISTREAM midiStream;

//�����\���p�f�[�^
DWORD	g_dwTempo;
WORD	g_wLVol,g_wRVol;
BOOL	g_fTempo=TRUE;

//***********************************************************
//mds�t�@�C����ǂݍ���MIDIHDR�ɓǂݏo��
//***********************************************************
BOOL mdsLoad(LPSTR lpszFileName){
	//---------------------------------------------------
	//���[�J���ϐ�
	//---------------------------------------------------
	HMMIO		hFile;			//�t�@�C���n���h��
	MMCKINFO	ckMIDS,ckSub;	//�`�����N���
	DWORD		dwDataSize;		//data�`�����N�T�C�Y�擾�p
	BYTE		*lpMDSData;//data�`�����N��ǂݍ���
	MMRESULT	mmResult;		//�G���[�`�F�b�N�p
	//-----------------------------------------------
	//MDS�t�@�C�����J��
	//----------------------------------------------
	hFile=mmioOpen(lpszFileName,
				NULL,MMIO_READ);
	if(NULL==hFile){
		MessageBox(gData.hwnd,"MDS�t�@�C�����J���̂Ɏ��s",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);
	}
	//----------------------------------------------
	//MIDS�`�����N�ɐi��
	//---------------------------------------------
	ckMIDS.fccType	=mmioFOURCC('M','I','D','S');
	mmResult		=mmioDescend(hFile,
						&ckMIDS,
						NULL,
						MMIO_FINDRIFF);
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"MDS�t�@�C���ł͂Ȃ�",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);		
		return(FALSE);
	}
	//-----------------------------------------------------
	//fmt�`�����N�ɐi��
	//------------------------------------------------------
	ckSub.ckid	=mmioFOURCC('f','m','t',' ');
	mmResult	=mmioDescend(hFile,
					&ckSub,
					&ckMIDS,
					MMIO_FINDCHUNK);
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"fmt�`�����N��������Ȃ�",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//----------------------------------------------------------
	//fmt�`�����N�f�[�^�ǂݍ���
	//-------------------------------------------------------
	mmResult	=mmioRead(hFile,
					(char*)&midiStream.mdsFormat,
					sizeof(midiStream.mdsFormat));
	if(mmResult==-1){
		MessageBox(gData.hwnd,"fmt�`�����N�ǂݎ��G���[",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//------------------------------------------------------------
	//�`�����N����ޏo
	//------------------------------------------------------------
	mmResult	=mmioAscend(hFile,&ckSub,0);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"fmt�`�����N����̑ޏo�Ɏ��s",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//-------------------------------------------------------------
	//data�`�����N�֐i��
	//-------------------------------------------------------------
	ckSub.ckid	=mmioFOURCC('d','a','t','a');
	mmResult	=mmioDescend(hFile,
					&ckSub,
					&ckMIDS,
					MMIO_FINDCHUNK);
	
	if(mmResult==MMIOERR_CHUNKNOTFOUND){
		MessageBox(gData.hwnd,"data�`�����N��������Ȃ�����",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//-----------------------------------------------------------
	//data�`�����N�T�C�Y���T����
	//-----------------------------------------------------------
	dwDataSize	=ckSub.cksize;
	//-----------------------------------------------------------
	//�����ǂݎ��
	//-----------------------------------------------------------
	mmResult	=mmioRead(hFile,
				(char*)&midiStream.dwMaxBlockCount,//�����ɕ�����������
				sizeof(DWORD));
	if(mmResult	==	-1){
		MessageBox(gData.hwnd,"�����ǂݎ��G���[",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);		
	}
	//--------------------------------------------------------
	//�u���b�N�����̃������m��
	//--------------------------------------------------------
	lpMDSData=(BYTE*)GlobalAlloc(
					GPTR,
					dwDataSize);
	//----------------------------------------------------------
	//�u���b�N�f�[�^���������ɏ�������
	//----------------------------------------------------------
	mmResult	=mmioRead(hFile,
					(char*)lpMDSData,//�����Ɋe�u���b�N�f�[�^������
					dwDataSize);
	if(mmResult	==	-1){
		MessageBox(gData.hwnd,"�u���b�N�f�[�^�ǂݎ��G���[",
			"MIDI�X�g���[���ǂݍ��݃G���[",MB_OK|MB_ICONSTOP);
		mmioClose(hFile,NULL);
		return(FALSE);
	}
	//MDS�t�@�C�������
	mmioClose(hFile,NULL);
	//-----------------------------------------------------------
	//�u���b�N����MIDIHDR�\���̂�p��
	//-----------------------------------------------------------
	midiStream.lpMidiHdr	=(MIDIHDR*)GlobalAlloc(
							GPTR,
							sizeof(MIDIHDR) * midiStream.dwMaxBlockCount);
	
	BYTE *lpTmpAddr;
	//
	lpTmpAddr	=lpMDSData;
	for(DWORD i=0;	i < midiStream.dwMaxBlockCount;	i++){
		//lpData�����o�Ƀu���b�N�T�C�Y���̃��������m��
		midiStream.lpMidiHdr[i].lpData=
				(LPSTR)GlobalAlloc(GPTR,
				midiStream.mdsFormat.dwMaxBuffer);
		//dwBuffreLength�����o�Ƀu���b�N�T�C�Y����
		midiStream.lpMidiHdr[i].dwBufferLength=
				midiStream.mdsFormat.dwMaxBuffer;
		//dwBytesRecorded�����o�ɉ��t�f�[�^�̃T�C�Y������
		midiStream.lpMidiHdr[i].dwBytesRecorded=
				((LPMDSBUFFER)lpMDSData)->dwBlockLength;
		//�u���b�N�ԍ�
		midiStream.lpMidiHdr[i].dwUser		=i;
		//���̑�
		midiStream.lpMidiHdr[i].reserved	=0;
		midiStream.lpMidiHdr[i].dwFlags		=0;
		midiStream.lpMidiHdr[i].lpNext		=NULL;
		
		//���t�f�[�^�������Ă���n�_�܂ŃA�h���X��i�߂�
		lpMDSData +=sizeof(MDSBUFFER);
		
		//lpData�����o�ɉ��t�f�[�^���R�s�[����
		CopyMemory(midiStream.lpMidiHdr[i].lpData,
				lpMDSData,
				midiStream.lpMidiHdr[i].dwBytesRecorded);
		
		//���̉��t�u���b�N�܂ŃA�h���X��i�߂�
		lpMDSData +=midiStream.lpMidiHdr[i].dwBytesRecorded;
	}
	//
	GlobalFree(lpTmpAddr);
	return(TRUE);
}
//*************************************************************************
//MIDI�X�g���[���̏���
//************************************************************************
BOOL mdsOpen(LPSTR lpszFileName){
	//--------------------------------
	//���[�J���ϐ�
	//-------------------------------
	UINT			uiID;//�g�p�f�o�C�XID
	MMRESULT		mmResult;//�G���[�`�F�b�N�p
	MIDIPROPTIMEDIV	midiProp;//MIDI���Ԑݒ�p
	
	//�f�o�C�X�̃n���h���AID��������
	midiStream.hMidiStream		=0;
	uiID			=MIDI_MAPPER;
	//----------------------------------------------------------
	//MDS�̓ǂݍ���
	//----------------------------------------------------------
	if(!mdsLoad(lpszFileName)){
		return(FALSE);
	}
	//------------------------------------------------------------
	//�f�o�C�X�I�[�v��
	//------------------------------------------------------------
	mmResult	=midiStreamOpen(
				&midiStream.hMidiStream,//�f�o�C�X�n���h���̎擾
				&uiID,				//�f�o�C�XID�̎w��
				1,					//�P�ɗ\��
				(DWORD)StreamProc,//�X�g���[���p�v���V�[�W��
				0,
				CALLBACK_FUNCTION);//�R�[���o�b�N�֐��Ƃ��ăX�g���[���p�v���V�[�W�����g�p
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDI�f�o�C�X�̃I�[�v���Ɏ��s",
			"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	//-----------------------------------------------
	//MIDI�^�C���v���p�e�B�̐ݒ�
	//----------------------------------------------
	midiProp.cbStruct	=sizeof(midiProp);
	midiProp.dwTimeDiv	=midiStream.mdsFormat.dwTimeFormat;
	mmResult	=midiStreamProperty(
				midiStream.hMidiStream,
				(BYTE*)&midiProp,
				MIDIPROP_SET | MIDIPROP_TIMEDIV);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDI�^�C���v���p�e�B�̐ݒ�Ɏ��s",
			"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	return(TRUE);
}
//*****************************************************************
//MIDI�X�g���[���̉��t
//*****************************************************************
BOOL mdsPlay(LPSTR lpszFileName,BOOL fLoopFlag){
	
	//-----------------------------------------
	//�f�o�C�X�̓�d�I�[�v���֎~
	//----------------------------------------
	if(midiStream.fPlay)	return (TRUE);
	//--------------------------------------------
	//MIDI�X�g���[���̏���
	//--------------------------------------------
	if(!mdsOpen(lpszFileName)){
		return (FALSE);
	}
	
	//----------------------------------------
	//���[�v�t���O�Z�b�g
	//--------------------------------------
	midiStream.fLoop	=fLoopFlag;
	//----------------------------------------
	//���[�J���ϐ�
	//---------------------------------------
	MMRESULT	mmResult;//�G���[�`�F�b�N�p
	
	//-----------------------------------------------------------
	//�u���b�NData�̓]��
	//-----------------------------------------------------------
	
	midiStream.dwSetBlockNum	=0;//�u���b�N�ԍ����O�ɏ�����
	
	for(DWORD i=0;i<16;i++){//�ő�16�܂Őς߂�
		
		if(i>=midiStream.dwMaxBlockCount)//�S�u���b�N����16�ȉ��̎�
			break;
		
		//�]������
		mmResult=midiOutPrepareHeader(
			(HMIDIOUT)midiStream.hMidiStream,//�f�o�C�X�n���h��
			&midiStream.lpMidiHdr[i],//�]���u���b�N�f�[�^
			sizeof(MIDIHDR));//�T�C�Y
		if(mmResult!=MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"MIDI�u���b�N�f�[�^�̓]�������Ɏ��s",
				"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
			return(FALSE);
		}
		//�]��
		mmResult=midiStreamOut(
			midiStream.hMidiStream,
			&midiStream.lpMidiHdr[i],
			sizeof(MIDIHDR));
		if(mmResult!=MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"MIDI�u���b�N�f�[�^�̓]���Ɏ��s",
				"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
			return(FALSE);
		}
		//���̃u���b�N�ɔԍ���i�߂�
		midiStream.dwSetBlockNum++;
	}
	//--------------------------------------------------------
	//���t���J�n����
	//--------------------------------------------------------
	mmResult=midiStreamRestart(midiStream.hMidiStream);
	if(mmResult!=MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"���t���s",
			"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);
	}
	//�Đ����t���OON
	midiStream.fPlay	=TRUE;
	
	return(TRUE);
}
//*************************************************************
//���t�I���AMIDI�X�g���[���̏I������
//*************************************************************
BOOL mdsStop(){
	
	MMRESULT	mmResult;//�G���[�`�F�b�N�p�ϐ�
	
	//�Đ����łȂ���Ή������Ȃ�
	if(!midiStream.fPlay)	return(TRUE);
	
	//�Đ����t���O��FALSE�ɂ���
	midiStream.fPlay	=FALSE;
	
	//���t��~
	mmResult=midiStreamStop(midiStream.hMidiStream);
	if(mmResult != MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDI�X�g���[���f�o�C�X�̃N���[�Y�Ɏ��s",
			"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	
	//�S�u���b�N�̏o�͒�~
	midiOutReset((HMIDIOUT)midiStream.hMidiStream);
	
	//�S�u���b�N(�X�g���[���o�b�t�@)�̉���
	for(DWORD i=0;i<midiStream.dwMaxBlockCount;i++)
	{
		mmResult=midiOutUnprepareHeader(
				(HMIDIOUT)midiStream.hMidiStream,
				&midiStream.lpMidiHdr[i],
				sizeof(MIDIHDR));
		if(mmResult != MMSYSERR_NOERROR){
			MessageBox(gData.hwnd,"�X�g���[���o�b�t�@�̉����Ɏ��s",
				"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
			return(FALSE);	
		}
	}
	
	//�u���b�N�f�[�^�p�������̉��
	for(i=0;i<midiStream.dwMaxBlockCount;i++)
	{
		GlobalFree(midiStream.lpMidiHdr[i].lpData);
	}
	GlobalFree(midiStream.lpMidiHdr);
	
	//MIDI�X�g���[���f�o�C�X�����
	mmResult=midiStreamClose(midiStream.hMidiStream);
	if(mmResult != MMSYSERR_NOERROR){
		MessageBox(gData.hwnd,"MIDI�X�g���[���f�o�C�X�̃N���[�Y�Ɏ��s",
			"MIDI�X�g���[���G���[",MB_OK|MB_ICONSTOP);
		return(FALSE);	
	}
	
	return(TRUE);
}
//****************************************************************
//MIDI�X�g���[���v���V�[�W��
//****************************************************************
void CALLBACK StreamProc(HMIDIIN hMidiIn,UINT msg,
						 DWORD hInst,DWORD wParam,DWORD lParam)
{
	//���t���łȂ���Δ�����
	if(!midiStream.fPlay){
		return;
	}

	//1�u���b�N�̉��t���I�������玟�u���b�N�����t�L���[�ɃZ�b�g
	if(msg==MOM_DONE){
		if(midiStream.fLoop){
			if(midiStream.dwSetBlockNum
				==midiStream.dwMaxBlockCount)
				midiStream.dwSetBlockNum  =0;
		}
		//�Z�b�g����u���b�N�ԍ����u���b�N�ő吔�����Ȃ�u���b�N��]��
		if(midiStream.dwSetBlockNum!=midiStream.dwMaxBlockCount){
			//�]������
			midiOutPrepareHeader(
				(HMIDIOUT)midiStream.hMidiStream,
				&midiStream.lpMidiHdr[midiStream.dwSetBlockNum],
				sizeof(MIDIHDR));
			
			//�]��
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

			
			//���̃u���b�N�ɔԍ���i�߂�
			midiStream.dwSetBlockNum++;		
		}
	}
	//���[�v�̎w�肪�����
	//�u���b�N�ԍ����u���b�N�ő吔�ɂȂ�������
	//�u���b�N�ԍ����O�Ԃɖ߂�
	if(midiStream.fLoop){
		if(midiStream.dwSetBlockNum
			==midiStream.dwMaxBlockCount)
			midiStream.dwSetBlockNum  =0;
	}
}
/*
//**************************************************************************
//�e��R���g���[���̃e�X�g�p�֐�
//**************************************************************************
void mdsTest(){
	
	//��~*******************************
	if(GetAsyncKeyState(0x74) & 0xff00){//F5
		mdsStop();
	}else if(GetAsyncKeyState(0x75) & 0xff00){//F6
		mdsPlay("testSong1.mds",TRUE);
	}else if(GetAsyncKeyState(0x76) & 0xff00){//F7
		mdsPlay("testSong2.mds",TRUE);
	}else if(GetAsyncKeyState(0x77) & 0xff00){//F8
		mdsPlay("testSong4.mds",TRUE);
	}
	//�ꎞ��~******************************
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
	//�{�����[���A�e���|*********************************
	
	

	if(GetAsyncKeyState(VK_LEFT) & 0xff00)
		g_fTempo=TRUE;
	else if(GetAsyncKeyState(VK_RIGHT) & 0xff00)
		g_fTempo=FALSE;

	if(g_fTempo){	
		//�e���|�`�F���W
		if(GetAsyncKeyState(VK_UP) & 0xff00)
			mdsChgTempo(-1000,TRUE);
		else if(GetAsyncKeyState(VK_DOWN) & 0xff00)
			mdsChgTempo(1000,TRUE);
	}else{
		//�{�����[���`�F���W
		if(GetAsyncKeyState(VK_UP) & 0xff00)
			mdsChgVolume(100,100,TRUE);
		else if(GetAsyncKeyState(VK_DOWN) & 0xff00)
			mdsChgVolume(-100,-100,TRUE);
	}
}
//***************************************************
//MIDI�X�g���[���e���|�`�F���W
//***************************************************
void mdsChgTempo(int nVal,BOOL fAdd){
	
	if(!midiStream.fPlay)	return;

	MIDIPROPTEMPO	midiProp;

	midiProp.cbStruct	=sizeof(midiProp);
	midiProp.dwTempo	=0;

	//���݂̃e���|�̒l���擾
	midiStreamProperty(midiStream.hMidiStream,
		(BYTE*)&midiProp,
		MIDIPROP_GET | MIDIPROP_TEMPO);
	
	//�e���|�̒l��ς���
	if(fAdd)	
		midiProp.dwTempo	+=nVal;
	else
		midiProp.dwTempo	=nVal;
	
	g_dwTempo	=midiProp.dwTempo;

	//�C����̃e���|�̒l���Z�b�g����
	midiStreamProperty(midiStream.hMidiStream,
		(BYTE*)&midiProp,
		MIDIPROP_SET | MIDIPROP_TEMPO);

}
//**********************************************************
//MIDI�X�g���[���{�����[���`�F���W
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