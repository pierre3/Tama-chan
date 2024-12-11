/***directS.h***/
#ifndef DSOUND
#define DSOUND

//*************************************************
//�}�N��
//*************************************************
#define SOUND_MAX	12//�ǂݍ���WAVE�t�@�C���̍ő�l

//�T�E���h�ԍ�
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
//DirectSound�\����
//***************************************************
typedef struct tagDSOUND{
	
	LPDIRECTSOUND		lpDS;
	LPDIRECTSOUNDBUFFER lpDSPrm;
	LPDIRECTSOUNDBUFFER lpDSSec[SOUND_MAX + 1];
	/*�_�C���N�g�T�E���h�֘A�̐ݒ�A�I�u�W�F�N�g�̍쐬*/
	BOOL DSCreate();
	//�Z�J���_���o�b�t�@���쐬���AWave�f�[�^��ǂݍ���
	BOOL LoadWave(LPSTR,	/*�����P�F�ǂݍ��ރt�@�C����*/
		LPDIRECTSOUNDBUFFER*);/*�����Q�F�Z�J���_���o�b�t�@�ւ̃|�C���^�̃A�h���X*/
			
}_DSOUND;
extern void DSoundPlay(BYTE);
extern void DSoundClear();
extern void ReleaseDS();
extern BOOL DSoundCreate();
#endif