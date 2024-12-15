//****************************************
//�C���N���[�h
//****************************************
#include "gameMain.h"
#include "directD.h"
#include "directS.h"
#include "SetCharData.h"
#include "midiStream.h"
#include "drawFrame.h"
#include "mapData.h"
//*************************************
//�O���[�o���ϐ�
//*************************************
_GAMEDATA		gData;
_DDRAW			DDraw;
_CHAR			chData[CHAR_MAX + 1];/*�L�����N�^�̊Ǘ�*/;


char szClassName[] = "TamaChan";

//*********************************************************
//�v���g�^�C�v�錾
//*********************************************************
/*�E�C���h�E�v���V�[�W��*/
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//�ύX�����J���[���[�h�����ɖ߂�
void ResetColorMode(BOOL, DWORD);


//*******************************************************************
//WinMain �֐�
//******************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance,
	LPSTR lpszArgs, int nWinMode)
{
	//--------------------------
	//���[�J���ϐ��̐錾
	//---------------------------
	//�E�C���h�E�f�[�^
	MSG				msg;
	WNDCLASS		wcls;
	RECT			rcAdj;//�E�C���h�E�T�C�Y�C���l
	//�J���[���[�h�`�F�b�N�A�C���p
	HDC				hDeviceDC;//�f�o�C�XDC�̃n���h��
	DEVMODE			dm;//�f�o�C�X�ݒ�p
	DWORD			dwColor;//������ݒ肵�Ă���J���[���[�h���擾����
	BOOL			fChgColor = FALSE;//�J���[���[�h��ύX������TRUE�C���Ȃ�������FALSE
	//�C���X�^���X�n���h���̎擾
	gData.hInst = hInstance;

	register int i;
	//------------------------------------------
	//�\���̂̏�����
	//------------------------------------------
	/*�e�I�u�W�F�N�g�ւ̃|�C���^��NULL�ŏ�����*/
	DDraw.lpDD = NULL;
	DDraw.lpDDPR = NULL;
	DDraw.lpDDBK = NULL;
	DDraw.lpDDPL = NULL;
	DDraw.lpDDCL = NULL;
	for (i = 0; i < OFFSCRN_COUNT; i++)
	{
		DDraw.lpDDOF[i] = NULL;
	}

	DSoundClear();

	//---------------------------------------------------------------
	//�E�C���h�E�X�P���g���쐬
	//---------------------------------------------------------------
	//�E�C���h�E�E�N���X��`��_______________________________________
	wcls.hInstance = hInstance;
	wcls.lpszClassName = szClassName;
	wcls.lpfnWndProc = WinProc;
	wcls.style = CS_DBLCLKS
		| CS_BYTEALIGNCLIENT
		| CS_BYTEALIGNWINDOW;
	wcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.lpszMenuName = NULL;
	wcls.cbClsExtra = 0;
	wcls.cbWndExtra = 0;
	//�쐬�E�C���h�E�E�o�b�N�O���E���h�J���[�ݒ蕔______________________
	wcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);


	//�E�C���h�E�E�N���X�쐬��________________________________________
	if (!RegisterClass(&wcls))	return 0;


	//�E�C���h�E�T�C�Y�̏C��_______________________
	SetRect(&rcAdj, 0, 0, SCREEN_W, SCREEN_H);
	AdjustWindowRect(&rcAdj,
		WS_POPUP | WS_BORDER | WS_CAPTION, FALSE);

	//�\���E�C���h�E�E�X�^�C���ݒ蕔_________________
	gData.hwnd = CreateWindowEx(NULL,
		szClassName,
		"���b�n���^�[TaMa_Chan",
		WS_POPUP | WS_BORDER | WS_CAPTION,
		0, 0,
		rcAdj.right - rcAdj.left,
		rcAdj.bottom - rcAdj.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//�f�B�X�v���C��DC�擾�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
	hDeviceDC = CreateDC("DISPLAY", NULL, NULL, NULL);

	//�J���[���[�h�̕ύX
	dwColor = GetDeviceCaps(hDeviceDC, BITSPIXEL);
	DeleteDC(hDeviceDC);
	if (dwColor != BPP) {
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = BPP;
		dm.dmFields = DM_BITSPERPEL;
		if (SUCCEEDED(ChangeDisplaySettings(&dm, CDS_TEST)))//��x�e�X�g����
		{
			ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);//�؂�ւ��p�Ƃ��ĕۑ�
			fChgColor = TRUE;
		}
		else {
			MessageBox(gData.hwnd, "�J���[���[�h�̕ύX�Ɏ��s���܂���",
				"Direct Draw", MB_OK | MB_ICONSTOP);
			return(FALSE);
		}
	}
	//�E�C���h�E�`�敔____________________
	ShowWindow(gData.hwnd, nWinMode);
	UpdateWindow(gData.hwnd);

	//--------------------------------------------------------
	//DirectDraw�̐ݒ�
	//--------------------------------------------------------
	if (!DDraw.DDCreateWin()) {
		//DDRaw�I�u�W�F�N�g�̉��
		DDraw.DDReleaseWin();
		//�J���[���[�h�����ɖ߂�
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}
	//�I�t�X�N���[���̍쐬����уr�b�g�}�b�v�̓ǂݍ���
	if (!DDraw.SetBitmap()) {
		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}

	DDraw.fInitDD = TRUE;
	//------------------------------------------------------------
	//DirectSound�̐ݒ�
	//------------------------------------------------------------
	if (!DSoundCreate()) {
		ReleaseDS();

		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}


	if (!mdsPlay(const_cast<char*>("mds\\ryuu.mds"), TRUE))
	{
		ReleaseDS();

		for (i = 0; i < OFFSCRN_COUNT; i++)
		{
			RELEASEDX(DDraw.lpDDOF[i]);
		}
		DDraw.DDReleaseWin();
		ResetColorMode(fChgColor, dwColor);
		return(FALSE);
	}

	//----------------------------------------
	srand(time(NULL));
	//-----------------------------------------------
	//���b�Z�[�W���[�v
	//-----------------------------------------------
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (gData.fActive)
			{

				/*��ʃ��[�h�̐؂�ւ�*/

				if (!DDraw.ChangeScreenMode())
				{
					//���s������I�u�W�F�N�g�̉��
					//DDraw
					for (i = 0; i < OFFSCRN_COUNT; i++)
					{
						RELEASEDX(DDraw.lpDDOF[i]);
					}
					if (DDraw.fFull)
						DDraw.DDReleaseFull();
					else
						DDraw.DDReleaseWin();
					FreeMap();
					//DSound
					ReleaseDS();
					mdsStop();
					ResetColorMode(fChgColor, dwColor);
					return(FALSE);
				}
				/*********���C������**************/


				if (!DrawFrame(&DDraw, chData))
				{
					//�I�u�W�F�N�g���
					//DDraw
					for (i = 0; i < OFFSCRN_COUNT; i++)
					{
						RELEASEDX(DDraw.lpDDOF[i]);
					}
					if (DDraw.fFull)
						DDraw.DDReleaseFull();
					else
						DDraw.DDReleaseWin();
					FreeMap();
					//DSound
					ReleaseDS();
					mdsStop();
					ResetColorMode(fChgColor, dwColor);
					return(FALSE);
				}
				/*********************************/
			}
			else
				WaitMessage();
		}
	}//while(1)

	//*******************************************
	//�I������
	//*******************************************
	FreeMap();
	//---------------------------
	//MIDI�X�g���[�����t��~
	//---------------------------
	mdsStop();
	//-------------------------------
	//�I�u�W�F�N�g�̉���i����I�����j
	//-------------------------------
	//DirectDraw
	for (i = 0; i < OFFSCRN_COUNT; i++)
	{
		RELEASEDX(DDraw.lpDDOF[i]);
	}
	if (DDraw.fFull)
		DDraw.DDReleaseFull();
	else
		DDraw.DDReleaseWin();

	//DirectSound
	ReleaseDS();

	//�J���[���[�h�����ɖ߂�
	ResetColorMode(fChgColor, dwColor);
	return msg.wParam;
}

//---------------------------------------------------------------------------
//�E�C���h�E�v���V�[�W��
//----------------------------------------------------------------------------
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_PAINT: {
		PAINTSTRUCT	ps;
		BeginPaint(hwnd, &ps);
		if (DDraw.fInitDD)
			if (!DrawFrame(&DDraw, chData))
				DestroyWindow(hwnd);

		EndPaint(hwnd, &ps);

	}break;

	case WM_ACTIVATEAPP:
		gData.fActive = (BOOL)wParam;
		break;

	case WM_PALETTECHANGED:
		if (wParam == (DWORD)hwnd)	break;
	case WM_QUERYNEWPALETTE:
		if (DDraw.lpDDPR) {
			DDraw.lpDDPR->SetPalette(DDraw.lpDDPL);
		}break;

	case WM_CREATE:
	case WM_MOVE:
		//---GET CLIENT RECT----
		GetClientRect(hwnd, &gData.rcClient);
		ClientToScreen(hwnd, (LPPOINT)&gData.rcClient);
		ClientToScreen(hwnd, (LPPOINT)&gData.rcClient + 1);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
//�J���[���[�h�����ɖ߂�
void ResetColorMode(BOOL fChgColor, DWORD dwColor)
{
	DEVMODE dm;
	if (fChgColor)
	{
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = dwColor;
		dm.dmFields = DM_BITSPERPEL;
		if (SUCCEEDED(ChangeDisplaySettings(&dm, CDS_TEST)))//��x�e�X�g����
			ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);//�؂�ւ��p�Ƃ��ĕۑ�
	}
}