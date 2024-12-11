/*directD.cpp*/
#include "directD.h"
#include "directS.h"
//****************************************************
//		DirectDraw�̐ݒ�(Window Mode)
//****************************************************
BOOL _DDRAW::DDCreateWin() {
	//�O���[�o���ϐ�
	HRESULT			err;
	DDSURFACEDESC	ddsd;
	PALETTEENTRY	ape[256];
	HDC				hdc;
	//---------------------------------------
	//DD_Object
	//---------------------------------------
	//DD�I�u�W�F�N�g�̍쐬
	err = DirectDrawCreate(NULL, &lpDD, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "DD�I�u�W�F�N�g�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�������x���̐ݒ�
	err = lpDD->SetCooperativeLevel(gData.hwnd,
		DDSCL_NORMAL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�������x���̐ݒ�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------
	//Primary_Surface
	//---------------------------------------------
	//�v���C���T�[�t�B�X�̐ݒ�
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE
		| DDSCAPS_VIDEOMEMORY;

	//�v���C�}���T�[�t�B�X�̍쐬
	err = lpDD->CreateSurface(&ddsd, &lpDDPR, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�v���C�}���T�[�t�B�X�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//-----------------------------------------------------
	//Palette_Object
	//---------------------------------------------------
	//�V�X�e���p���b�g�̐ݒ�
	//hdc = GetDC(gData.hwnd);
	//SetSystemPaletteUse(hdc, SYSPAL_STATIC);
	//GetSystemPaletteEntries(hdc, 0, 256, ape);
	//ReleaseDC(gData.hwnd, hdc);

	////�p���b�g�I�u�W�F�N�g�̍쐬
	//err = lpDD->CreatePalette(
	//	DDPCAPS_8BIT,
	//	ape, &lpDDPL, NULL);
	//if (err != DD_OK) {
	//	MessageBox(gData.hwnd, "�p���b�g�I�u�W�F�N�g�̍쐬�Ɏ��s",
	//		"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
	//	return(FALSE);
	//}

	////�v���C�}���T�[�t�B�X�Ƀp���b�g��ݒ肷��
	//err = lpDDPR->SetPalette(lpDDPL);
	//if (err != DD_OK) {
	//	MessageBox(gData.hwnd, "�p���b�g�̐ݒ�Ɏ��s",
	//		"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
	//	return(FALSE);
	//}
	//-------------------------------------------------------
	//Clipper_Object
	//-------------------------------------------------------
	//�N���b�p�[�I�u�W�F�N�g�̍쐬
	err = lpDD->CreateClipper(0, &lpDDCL, NULL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�N���b�p�[�I�u�W�F�N�g�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�N���b�p�[�I�u�W�F�N�g���E�C���h�E�֐ݒ�
	err = lpDDCL->SetHWnd(0, gData.hwnd);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�E�C���h�E�ւ̃N���b�p�[�̐ݒ�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�N���b�p�[�I�u�W�F�N�g���v���C�}���[�T�[�t�B�X�֐ݒ�
	err = lpDDPR->SetClipper(lpDDCL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�v���C�}���T�[�t�B�X�ւ̃N���b�p�[�̐ݒ�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//---------------------------------------------------
	//BackBuffer
	//---------------------------------------------------
	//�o�b�N�o�b�t�@�̍쐬
	if (!DDCreateOffScreen(&lpDDBK, 238, SCREEN_W, SCREEN_H,
		DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}

	return(TRUE);
}
//******************************************************************
//			DirectDraw�̐ݒ�(Full Screen Mode)
//******************************************************************
BOOL _DDRAW::DDCreateFull() {

	HRESULT			err;
	DDSURFACEDESC	ddsd;
	DDSCAPS			caps;
	PALETTEENTRY    ape[256];
	HDC				hdc;
	DWORD			dwResult = 0;
	//---------------------------------------------------
	//DD_Object
	//---------------------------------------------------
	//DD�I�u�W�F�N�g�̍쐬
	err = DirectDrawCreate(NULL, &lpDD, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "DD�I�u�W�F�N�g�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�������x���̐ݒ�
	err = lpDD->SetCooperativeLevel(gData.hwnd,
		DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN
		| DDSCL_ALLOWREBOOT);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�������x���̐ݒ�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�f�B�X�v���C���[�h�̐ݒ�
	lpDD->EnumDisplayModes(
		DDEDM_REFRESHRATES,
		NULL,
		(LPVOID)&dwResult,
		EnumModesCallback);

	if (dwResult) {

		err = lpDD->SetDisplayMode(SCREEN_W, SCREEN_H, BPP);

		if (err != DD_OK) {
			MessageBox(gData.hwnd, "�f�B�X�v���C���[�h�̐ݒ�Ɏ��s",
				"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
			return(FALSE);
		}

	}
	else {
		MessageBox(gData.hwnd, "�w�肳�ꂽ�𑜓x�͎g�p�ł��܂���",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//--------------------------------------------------------
	//Primary_Surface
	//--------------------------------------------------------
	//�v���C���T�[�t�B�X�̐ݒ�
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.dwBackBufferCount = 1;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE
		| DDSCAPS_FLIP
		| DDSCAPS_COMPLEX
		| DDSCAPS_VIDEOMEMORY;

	//�v���C�}���T�[�t�B�X�̍쐬
	err = lpDD->CreateSurface(&ddsd, &lpDDPR, NULL);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�v���C�}���T�[�t�B�X�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�o�b�N�o�b�t�@���v���C�}���T�[�t�B�X�Ƒg�ݍ��킹��
	caps.dwCaps = DDSCAPS_BACKBUFFER;

	err = lpDDPR->GetAttachedSurface(&caps, &lpDDBK);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�T�[�t�B�X�̑g�ݍ��킹�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	//--------------------------------------------------------
	//Palette_Object
	//--------------------------------------------------------
	//�V�X�e���p���b�g�̐ݒ�
	//hdc = GetDC(gData.hwnd);
	//SetSystemPaletteUse(hdc, SYSPAL_STATIC);
	//GetSystemPaletteEntries(hdc, 0, 256, ape);
	//ReleaseDC(gData.hwnd, hdc);

	////�p���b�g�I�u�W�F�N�g�̍쐬
	//err = lpDD->CreatePalette(
	//	DDPCAPS_8BIT | DDPCAPS_ALLOW256,
	//	ape, &lpDDPL, NULL);
	//if (err != DD_OK) {
	//	MessageBox(gData.hwnd, "�p���b�g�I�u�W�F�N�g�̍쐬�Ɏ��s",
	//		"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
	//	return(FALSE);
	//}

	////�v���C�}���T�[�t�B�X�Ƀp���b�g��ݒ肷��
	//err = lpDDPR->SetPalette(lpDDPL);
	//if (err != DD_OK) {
	//	MessageBox(gData.hwnd, "�p���b�g�̐ݒ�Ɏ��s",
	//		"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
	//	return(FALSE);
	//}

	return(TRUE);
}
//*************************************************
//		DirectDraw�֘A�I�u�W�F�N�g�̉��
//*************************************************
void _DDRAW::DDReleaseWin() {
	RELEASEDX((lpDDBK));
	RELEASEDX((lpDDCL));
	RELEASEDX((lpDDPL));
	RELEASEDX((lpDDPR));
	RELEASEDX((lpDD));
}
void _DDRAW::DDReleaseFull() {
	RELEASEDX((lpDDPL));
	RELEASEDX((lpDDPR));
	RELEASEDX((lpDD));
}
//********************************************************************
//�I�t�X�N���[���T�[�t�B�X�̍쐬
//********************************************************************
BOOL _DDRAW::DDCreateOffScreen(LPDIRECTDRAWSURFACE* lplpDDOF,
	DWORD dwColorKey,
	DWORD dwWidth,
	DWORD dwHeight,
	DWORD dwMemoryFlag)
{

	HRESULT			err;
	DDSURFACEDESC	ddsd;
	DDCOLORKEY		ddck;

	//�I�t�X�N���[���T�[�t�B�X�̐ݒ�
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = dwWidth;
	ddsd.dwHeight = dwHeight;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN
		| dwMemoryFlag;

	//�I�t�X�N���[���T�[�t�B�X�̍쐬
	err = lpDD->CreateSurface(&ddsd, lplpDDOF, NULL);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�I�t�X�N���[���T�[�t�B�X�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}

	//�I�t�X�N���[���T�[�t�B�X�ɃJ���[�L�[��ݒ�
	ddck.dwColorSpaceLowValue = dwColorKey;
	ddck.dwColorSpaceHighValue = dwColorKey;
	err = (*lplpDDOF)->SetColorKey(DDCKEY_SRCBLT, &ddck);
	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�J���[�L�[�̐ݒ�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}
	return(TRUE);
}

//**********************************************************************
//�r�b�g�}�b�v��ǂݍ��݁A�I�t�X�N���[���T�[�t�B�X�ɓ]��
//**********************************************************************
BOOL _DDRAW::DDLoadBmp(LPDIRECTDRAWSURFACE* lplpDDOF,
	LPSTR lpszFileName,
	DWORD dwStartingEntry,
	DWORD dwCount,
	DWORD dwXDest,
	DWORD dwYDest,
	DWORD dwWidth,
	DWORD dwHeight)
{

	HDC	hdc, hMemDC;
	HBITMAP	hBitmap;
	RGBQUAD rgb[256];
	PALETTEENTRY ape[256];
	HRESULT err;
	register DWORD i;

	//�r�b�g�}�b�v��ǂݍ���
	hdc = GetDC(gData.hwnd);
	hBitmap = (HBITMAP)LoadImage(gData.hInst, lpszFileName,
		IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(gData.hwnd, hdc);

	////�r�b�g�}�b�v�̃p���b�g�f�[�^��
	//	//�p���b�g�I�u�W�F�N�g�ɔ��f������
	//GetDIBColorTable(hMemDC,
	//	dwStartingEntry,
	//	dwCount,
	//	&rgb[dwStartingEntry]
	//);

	//for (i = dwStartingEntry; i < (dwStartingEntry + dwCount); i++) {
	//	ape[i].peRed = rgb[i].rgbRed;
	//	ape[i].peGreen = rgb[i].rgbGreen;
	//	ape[i].peBlue = rgb[i].rgbBlue;
	//	ape[i].peFlags = PC_RESERVED | PC_NOCOLLAPSE;
	//}
	//�r�b�g�}�b�v����̃p���b�g�f�[�^��o�^
	/*err = lpDDPL->SetEntries(
		0,
		dwStartingEntry,
		dwCount,
		&ape[dwStartingEntry]
	);

	if (err != DD_OK) {
		MessageBox(gData.hwnd, "�p���b�g�f�[�^�̓o�^�Ɏ��s",
			"�G���[���b�Z�[�W", MB_OK | MB_ICONSTOP);
		return(FALSE);
	}*/

	//�r�b�g�}�b�v���I�t�X�N���[���T�[�t�B�X�ɓ]��
	(*lplpDDOF)->GetDC(&hdc);
	BitBlt(hdc, dwXDest, dwYDest, dwWidth, dwHeight,
		hMemDC, 0, 0, SRCCOPY);

	(*lplpDDOF)->ReleaseDC(hdc);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	memcpy(ape2, ape, sizeof(PALETTEENTRY) * 256);
	return(TRUE);
}

//*************************************************************************
//��CALLBACK�֐�(�g�p�\�ȃX�N���[�����[�h�𒲂ׂ�)
//*************************************************************************
HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC lpDdsd,
	LPVOID lpContext) {
	if (lpDdsd->dwWidth == SCREEN_W
		&& lpDdsd->dwHeight == SCREEN_H
		&& lpDdsd->ddpfPixelFormat.dwRGBBitCount == BPP) {
		*(DWORD*)lpContext = TRUE;
		return(DDENUMRET_CANCEL);
	}
	return(DDENUMRET_OK);
}

//******************************************************************
//�X�N���[�����[�h�̐؂�ւ�
//******************************************************************
BOOL _DDRAW::ChangeScreenMode()
{
	RECT rcAdj;

	if (GetAsyncKeyState(VK_F1) & 0xff00) {

		DSoundPlay(SOUND_OPEN);
		fInitDD = FALSE;
		fFull ^= TRUE;
		RELEASEDX(lpDDOF[0]);
		RELEASEDX(lpDDOF[1]);
		RELEASEDX(lpDDOF[2]);
		if (!fFull) {
			//--------------------------------------
			//�t���X�N���[�����[�h�̃I�u�W�F�N�g�����
			//--------------------------------------
			DDReleaseFull();
			//--------------------------------------
			//�E�C���h�E���E�C���h�E���[�h�p�ɕύX
			//--------------------------------------
			//�E�C���h�E�̕�,���������߂�
			SetRect(&rcAdj, 0, 0, SCREEN_W, SCREEN_H);
			AdjustWindowRect(&rcAdj,
				WS_POPUP | WS_BORDER | WS_CAPTION
				| WS_VISIBLE, FALSE);
			//�E�C���h�E�X�^�C����ύX����
			SetWindowLong(gData.hwnd, GWL_STYLE,
				WS_POPUP | WS_CAPTION
				| WS_BORDER | WS_VISIBLE);
			//�E�C���h�E�̕��A������ύX����
			SetWindowPos(gData.hwnd, HWND_NOTOPMOST, 0, 0,
				rcAdj.right - rcAdj.left,
				rcAdj.bottom - rcAdj.top, SWP_DRAWFRAME);
			//---------------------------------------
			//DirectDraw�̏���(Window Mode)
			//---------------------------------------
			if (!DDCreateWin())		return(FALSE);
		}
		else {
			//------------------------------------------
			//�E�C���h�E���[�h�̃I�u�W�F�N�g�����
			//------------------------------------------
			DDReleaseWin();
			//-------------------------------------------
			//�E�C���h�E���t���X�N���[���p�ɕύX
			//-------------------------------------------
			//�E�C���h�E�X�^�C���̕ύX
			SetWindowLong(gData.hwnd, GWL_STYLE, WS_POPUP);
			SetWindowLong(gData.hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
			//---------------------------------------
			//DirectDraw�̏���(Full Screen Mode)
			//---------------------------------------
			if (!DDCreateFull())		return(FALSE);

		}
		if (!SetBitmap())
			return(FALSE);

	}
	static int count;
	if (fFull)
	{
		if (count <= 16)
			lpDDPL->SetEntries(0, 10, 236, &ape2[10]);
		count++;
	}
	else
		count = 0;


	return(fInitDD = TRUE);
}
//--------------------------------------------
//�I�t�X�N���[���̍쐬�A�r�b�g�}�b�v�̓ǂݍ���
//--------------------------------------------
BOOL _DDRAW::SetBitmap()
{
	//�I�t�X�N���[���T�[�t�B�X�̍쐬____________
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_CHAR], COLOR_KEY, OFFSCREEN_W,
		OFFSCREEN_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_GOVER], COLOR_KEY, OFF_GOVER_W,
		OFF_GOVER_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	if (!DDCreateOffScreen(&lpDDOF[OFFSCRN_TITLE], COLOR_KEY, OFF_TITLE_W,
		OFF_TITLE_H, DDSCAPS_VIDEOMEMORY)) {
		return(FALSE);
	}
	//�r�b�g�}�b�v�̓ǂݍ���___________________
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\MyChar.bmp"),
		10, 236, BMP_X, BMP_MC_Y, BMP_MC_W, BMP_MC_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\Block.bmp"),
		10, 236, BMP_X, BMP_BL_Y, BMP_BL_W, BMP_BL_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_CHAR], const_cast<char*>("bitmap\\Enemy.bmp"),
		10, 236, BMP_X, BMP_EN_Y, BMP_EN_W, BMP_EN_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_GOVER], const_cast<char*>("bitmap\\gover.bmp"),
		10, 236, 0, 0, OFF_GOVER_W, OFF_GOVER_H)) {
		return(FALSE);
	}
	if (!DDLoadBmp(&lpDDOF[OFFSCRN_TITLE], const_cast<char*>("bitmap\\title.bmp"),
		10, 236, 0, 0, OFF_TITLE_W, OFF_TITLE_H)) {
		return(FALSE);
	}
	return(TRUE);
}

//---------------------------------------------------------------------
//VRAM�̊J���̈�𒲂ׂ�
//--------------------------------------------------------------------
void _DDRAW::VRAMCheck() {

	DDCAPS hwCaps, swCaps;
	HDC hdc;
	char str[64];

	ZeroMemory(&hwCaps, sizeof(hwCaps));
	hwCaps.dwSize = sizeof(hwCaps);
	ZeroMemory(&swCaps, sizeof(swCaps));
	swCaps.dwSize = sizeof(swCaps);

	lpDD->GetCaps(&hwCaps, &swCaps);

	lpDDBK->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);
	wsprintf(str, "VRAM�S�̗̂e��:%08d",
		hwCaps.dwVidMemTotal);
	TextOut(hdc, 0, 60, str, lstrlen(str));

	wsprintf(str, "VRAM�̎c��e��:%08d",
		hwCaps.dwVidMemFree);
	TextOut(hdc, 0, 80, str, lstrlen(str));

	wsprintf(str, "�����VRAM  :%08d",
		hwCaps.dwVidMemTotal - hwCaps.dwVidMemFree);
	TextOut(hdc, 0, 100, str, lstrlen(str));

	lpDDBK->ReleaseDC(hdc);


}