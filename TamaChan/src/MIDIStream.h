/*MIDIStream.h*/
#ifndef MIDISTRM_H
#define MIDISTRM_H

//***************************
//�\����
//***************************
//MDS�ǂݍ��ݗp//////////////

//fmt�`�����N�f�[�^���i�[
typedef struct tagMDSFORMAT{
	DWORD	dwTimeFormat;//���ԃt�H�[�}�b�g
	DWORD	dwMaxBuffer;//�������ꂽ�u���b�N�̍ő�T�C�Y
	DWORD	dwFormatFlags;//�t�H�[�}�b�g�t���O
}MDSFORMAT,*LPMSDFORMAT;

//data�`�����N
//�e�u���b�N�f�[�^
typedef struct tagMDSBUFFER{
	DWORD	dwBlockStart;
	DWORD	dwBlockLength;
}MDSBUFFER,*LPMDSBUFFER;

typedef struct tagMIDISTREAM{
	MDSFORMAT	mdsFormat;//fmt�`�����N�f�[�^���i�[
	DWORD		dwMaxBlockCount;//�����u���b�N��
	MIDIHDR		*lpMidiHdr;//�u���b�N�P�ʂŉ��t�f�[�^������
	HMIDISTRM	hMidiStream;//MIDI�f�o�C�X�n���h��
	DWORD		dwSetBlockNum;//���ɃL���[�ɐςޔԍ�
	BOOL		fPlay,
				fLoop,
				fPause;
}MIDISTREAM,*LPMIDISTREAM;

///////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////
BOOL mdsLoad(LPSTR);
BOOL mdsOpen(LPSTR);
void CALLBACK StreamProc(HMIDIIN ,UINT,DWORD,DWORD,DWORD);

extern BOOL mdsPlay(LPSTR,BOOL);//�Đ�
extern BOOL mdsStop();//��~
extern void mdsPause();//�ꎞ��~
extern void mdsRestert();//�ꎞ��~����
#endif