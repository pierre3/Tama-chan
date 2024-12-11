//************************
//インクルード
//************************
#include "getImputData.h"

BYTE tblXY[]={
		0x00,0x06,0x04,0x06,0x05,0x06,0x05,0x06,
		0x02,0x06,0x06,0x06,0x05,0x06,0x05,0x06,
		0x01,0x06,0x05,0x06,0x05,0x06,0x05,0x06,
		0x02,0x06,0x06,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x08,0x06,0x04,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x06,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x05,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x06,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x09,0x06,0x09,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		0x0a,0x06,0x0a,0x06,0x05,0x06,0x05,0x06,
		};	
void GetKeyInfo(WORD *lpInputData){
	static WORD wKeyOld;
	WORD		wKeyNew=0,
				wKeyChg=0,
				wKeyPrs=0,
				wKeyRls=0,
				wKeyPrsKep=0;
	BYTE		nTenKey=0;
	
	*lpInputData=0;
	
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x61) 
			& 0xff00)>>15);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x62) 
			& 0xff00)>>14);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x63) 
			& 0xff00)>>13);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x64) 
			& 0xff00)>>12);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x66) 
			& 0xff00)>>11);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x67) 
			& 0xff00)>>10);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x68) 
			& 0xff00)>>9);
	nTenKey	|=(BYTE)((GetAsyncKeyState(0x69) 
			& 0xff00)>>8);
	nTenKey	|=(BYTE)((GetAsyncKeyState(VK_DOWN) 
			& 0xff00)>>14);
	nTenKey	|=(BYTE)((GetAsyncKeyState(VK_LEFT) 
			& 0xff00)>>12);
	nTenKey	|=(BYTE)((GetAsyncKeyState(VK_RIGHT) 
			& 0xff00)>>11);
	nTenKey	|=(BYTE)((GetAsyncKeyState(VK_UP) 
			& 0xff00)>>9);
	
	
	wKeyNew	|=(WORD)tblXY[nTenKey];
	*lpInputData	=wKeyNew;//0-3bit
	//z(A):4bit
	wKeyNew |=(WORD)((GetAsyncKeyState(0x5a)	 
			& 0x8000)>>11);					
	//Ctrl(B):5bit
	wKeyNew |=(WORD)((GetAsyncKeyState(0x11)	 
			& 0x8000)>>10);					
	//Esc:6bit
	wKeyNew |=(WORD)((GetAsyncKeyState(0x1B)	
			& 0x8000)>>9);					
	//Enter:7bit
	wKeyNew |=(WORD)((GetAsyncKeyState(0x0d)	
			& 0x8000)>>8);
	//Function Key:8-11bit
	wKeyNew |=(WORD)((GetAsyncKeyState(VK_F1)	 
			& 0x8000)>>7);
	wKeyNew |=(WORD)((GetAsyncKeyState(VK_F2)	 
			& 0x8000)>>6);
	wKeyNew |=(WORD)((GetAsyncKeyState(VK_F3)	 
			& 0x8000)>>5);
	wKeyNew |=(WORD)((GetAsyncKeyState(VK_F4)	 
			& 0x8000)>>4);

	wKeyChg		=wKeyNew ^ wKeyOld;
	wKeyPrs		=wKeyNew & wKeyChg;
	wKeyRls		=wKeyOld & wKeyChg;
	wKeyPrsKep	=wKeyNew & wKeyOld;
	
	*lpInputData	|=((wKeyPrs & _A)//4bit目
						| ((wKeyRls & _A)<<1)//5
						| ((wKeyPrsKep & _A)<<2));//6
	*lpInputData	|=(((wKeyPrs & _B)<<2)//7
						| ((wKeyRls & _B)<<3)//8
						| ((wKeyPrsKep & _B)<<4));//9
	*lpInputData	|=(wKeyPrs & _ESC)<<4;//10
	*lpInputData	|=(wKeyPrs & _ENT)<<4;//11
	*lpInputData	|=(wKeyPrs & _F1)<<4;//12
	*lpInputData	|=(wKeyPrs & _F2)<<4;//13
	*lpInputData	|=(wKeyPrs & _F3)<<4;//14
	*lpInputData	|=(wKeyPrs & _F4)<<4;//15
	
	//-----Oldデータを更新する-----
	wKeyOld		=wKeyNew;	
	
}
BOOL GetJoyInfo(WORD *lpInputData){
	
	JOYINFOEX	joy;
	BYTE		nJoyNew		=0,
				nJoyChg		=0,
				nJoyPrs		=0,
				nJoyRls		=0,
	 			nJoyPrsKep	=0;
	static BYTE nJoyOld;
	
	*lpInputData	=0;
	//----ジョイスティックの情報を取得----
	joy.dwSize		=sizeof(joy);
	joy.dwFlags		=JOY_RETURNBUTTONS | JOY_RETURNX 
		| JOY_RETURNY;
	
	if(joyGetPosEx(JOYSTICKID1,&joy)!=JOYERR_NOERROR)
		return(FALSE);
	//----各ボタンのデータをnJoyNewに納める----
	if(joy.dwXpos < 5000)
		nJoyNew |= _L;
	else if(joy.dwXpos > 60000)
		nJoyNew |= _R;
	
	if(joy.dwYpos < 5000)
		nJoyNew |= _U;
	else if(joy.dwYpos > 60000)
		nJoyNew |= _D;
	
	nJoyNew		|=(BYTE)((joy.dwButtons & 0x03) << 4);
	//-----nJoyNew,nJoyOldから更に細かいデータを
	//							wInputDataに納める-----
	nJoyChg		=nJoyNew ^ nJoyOld;//変化したbitだけが１
	nJoyPrs		=nJoyNew & nJoyChg;//0-->1に変化した
	nJoyRls		=nJoyOld & nJoyChg;//1-->0に変化した
	nJoyPrsKep	=nJoyNew & nJoyOld;//１のまま変化しなかった
	
	
	*lpInputData	|=(WORD)(nJoyNew & _DIR_MASK);
										//bit0-3:方向キー
	*lpInputData	|=(WORD)(nJoyPrs & _A);
										//bit4:A-押した
	*lpInputData	|=(WORD)((nJoyRls & _A)<<1);
										//bit5:A-離した
	*lpInputData	|=(WORD)((nJoyPrsKep & _A)<<2);
										//bit6:A-押されたまま
	*lpInputData	|=(WORD)((nJoyPrs & _B)<<2);
										//bit7:B-押した
	*lpInputData	|=(WORD)((nJoyRls & _B)<<3);
										//bit8:B-離した
	*lpInputData	|=(WORD)((nJoyPrsKep & _B)<<4);
										//bit9:B-押されたまま
	
	
	//-----Oldデータを更新する-----
	nJoyOld			=nJoyNew;
	
	
	return(TRUE);
}

