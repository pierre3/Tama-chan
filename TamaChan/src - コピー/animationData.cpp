/*animationData.cpp...アニメーションパターンのデータ*/
//*********************************
//インクルード
//********************************
#include "animationData.h"
//*********************************************************
//アニメーションパターンの設定
//********************************************************
	//MyChar
	_ACTDATA actMCRight[]={
		{{0*CHAR_W,	0,	0*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{1*CHAR_W,	0,	1*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{2*CHAR_W,	0,	2*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{1*CHAR_W,	0,	1*CHAR_W + CHAR_W,CHAR_H},8,4}
	};
	_ACTDATA actMCLeft[]={
		{{3*CHAR_W,	0,	3*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{4*CHAR_W,	0,	4*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{5*CHAR_W,	0,	5*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{4*CHAR_W,	0,	4*CHAR_W + CHAR_W,CHAR_H},8,4}
	};
	_ACTDATA actMCUp[]={
		{{0*CHAR_W,	3*CHAR_H,0*CHAR_W + CHAR_W,4*CHAR_H},8,4},
		{{1*CHAR_W,	3*CHAR_H,1*CHAR_W + CHAR_W,4*CHAR_H},8,4},
		{{2*CHAR_W,	3*CHAR_H,2*CHAR_W + CHAR_W,4*CHAR_H},8,4},
		{{1*CHAR_W,	3*CHAR_H,1*CHAR_W + CHAR_W,4*CHAR_H},8,4}
	};
	
	_ACTDATA actMCDashR[]={
		{{0*CHAR_W,	0,	0*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{1*CHAR_W,	0,	1*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{2*CHAR_W,	0,	2*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{1*CHAR_W,	0,	1*CHAR_W + CHAR_W,CHAR_H},4,4}
	};
	_ACTDATA actMCDashL[]={
		{{3*CHAR_W,	0,	3*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{4*CHAR_W,	0,	4*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{5*CHAR_W,	0,	5*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{4*CHAR_W,	0,	4*CHAR_W + CHAR_W,CHAR_H},4,4}
	};
	_ACTDATA actMCJumpR[]={
		{{0*CHAR_W,CHAR_H,0*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
		{{1*CHAR_W,CHAR_H,1*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
		{{2*CHAR_W,CHAR_H,2*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
		{{3*CHAR_W,CHAR_H,3*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
	};
	_ACTDATA actMCJumpL[]={
		{{0*CHAR_W,	2*CHAR_H, 
			0*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
		{{1*CHAR_W,2*CHAR_H, 
			1*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
		{{2*CHAR_W,2*CHAR_H, 
			2*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
		{{3*CHAR_W,2*CHAR_H, 
			3*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
	};
	_ACTDATA actMCDashJumpR[]={
		{{0*CHAR_W,CHAR_H, 
			0*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
		{{1*CHAR_W,CHAR_H, 
			1*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
		{{2*CHAR_W,CHAR_H, 
			2*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
		{{3*CHAR_W,CHAR_H, 
			3*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
	};
	_ACTDATA actMCDashJumpL[]={
		{{0*CHAR_W,2*CHAR_H, 
			0*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
		{{1*CHAR_W,2*CHAR_H, 
			1*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
		{{2*CHAR_W,2*CHAR_H, 
			2*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
		{{3*CHAR_W,2*CHAR_H, 
			3*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
	};
	_ACTDATA actMCStopL[]={	
		{{4*CHAR_W,0,4*CHAR_W + CHAR_W,CHAR_H},65535,1}};
	
	_ACTDATA actMCStopR[]={	
		{{1*CHAR_W,0,1*CHAR_W + CHAR_W,CHAR_H},65535,1}};
	
	_ACTDATA actMCStopUp[]={	
		{{1*CHAR_W,3*CHAR_H,1*CHAR_W + CHAR_W,4*CHAR_H},65535,1}};
	
	_ACTDATA actMCPiyo[]={
		{{3*CHAR_W,3*CHAR_H,4*CHAR_W,4*CHAR_H},8,2},
		{{4*CHAR_W,3*CHAR_H,5*CHAR_W,4*CHAR_H},8,2}
	};
	//////////////////////////////////////////////////////////////////
	_ACTDATA actMCRightD[]={
		{{0*CHAR_W,	0,	0*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{0,0,0,0},8,4},
		{{2*CHAR_W,	0,	2*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{0,0,0,0},8,4}
	};
	_ACTDATA actMCLeftD[]={
		{{3*CHAR_W,	0,	3*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{0,0,0,0},8,4},
		{{5*CHAR_W,	0,	5*CHAR_W + CHAR_W,CHAR_H},8,4},
		{{0,0,0,0},8,4}
	};
	_ACTDATA actMCUpD[]={
		{{0*CHAR_W,	3*CHAR_H,0*CHAR_W + CHAR_W,4*CHAR_H},8,4},
		{{0,0,0,0},8,4},
		{{2*CHAR_W,	3*CHAR_H,2*CHAR_W + CHAR_W,4*CHAR_H},8,4},
		{{0,0,0,0},8,4}
	};
	
	_ACTDATA actMCDashRD[]={
		{{0*CHAR_W,	0,	0*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{0,0,0,0},4,4},
		{{2*CHAR_W,	0,	2*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{0,0,0,0},4,4}
	};
	_ACTDATA actMCDashLD[]={
		{{3*CHAR_W,	0,	3*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{0,0,0,0},4,4},
		{{5*CHAR_W,	0,	5*CHAR_W + CHAR_W,CHAR_H},4,4},
		{{0,0,0,0},4,4}
	};
	_ACTDATA actMCJumpRD[]={
		{{0*CHAR_W,CHAR_H,0*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
		{{0,0,0,0},8,4},
		{{2*CHAR_W,CHAR_H,2*CHAR_W + CHAR_W,CHAR_H + CHAR_H},8,4},
		{{0,0,0,0},8,4},
	};
	_ACTDATA actMCJumpLD[]={
		{{0*CHAR_W,	2*CHAR_H, 
			0*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
		{{0,0,0,0},8,4},
		{{2*CHAR_W,2*CHAR_H, 
			2*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},8,4},
		{{0,0,0,0},8,4},
	};
	_ACTDATA actMCDashJumpRD[]={
		{{0*CHAR_W,CHAR_H, 
			0*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
		{{0,0,0,0},4,4},
		{{2*CHAR_W,CHAR_H, 
			2*CHAR_W + CHAR_W,CHAR_H + CHAR_H},4,4},
		{{0,0,0,0},4,4},
	};
	_ACTDATA actMCDashJumpLD[]={
		{{0*CHAR_W,2*CHAR_H, 
			0*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
		{{0,0,0,0},4,4},
		{{2*CHAR_W,2*CHAR_H, 
			2*CHAR_W + CHAR_W,2*CHAR_H + CHAR_H},4,4},
		{{0,0,0,0},4,4},
	};
	_ACTDATA actMCStopLD[]={	
		{{4*CHAR_W,0,4*CHAR_W + CHAR_W,CHAR_H},8,2},
		{{0,0,0,0},8,2}
	};
	
	_ACTDATA actMCStopRD[]={	
		{{1*CHAR_W,0,1*CHAR_W + CHAR_W,CHAR_H},8,2},
		{{0,0,0,0},8,2}
	};
	
	_ACTDATA actMCStopUpD[]={	
		{{1*CHAR_W,3*CHAR_H,1*CHAR_W + CHAR_W,4*CHAR_H},8,2},
		{{0,0,0,0},8,2}
	};
	//////////////////////////////////////////////////////////////////
	//敵キャラ
	 _ACTDATA actE00Left[]={
		{{1*CHAR_W,BMP_EN_Y,2*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y,1*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{2*CHAR_W,BMP_EN_Y,3*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y,1*CHAR_W,BMP_EN_Y + CHAR_H },8,4}
	 };
	
	 _ACTDATA actE00Right[]={
		{{1*CHAR_W,BMP_EN_Y + CHAR_H,2*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y + CHAR_H,1*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{2*CHAR_W,BMP_EN_Y + CHAR_H,3*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y + CHAR_H,1*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4}
	 };
	 _ACTDATA actE00Up[]={
		{{1*CHAR_W,BMP_EN_Y + 2*CHAR_H,2*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y + 2*CHAR_H,1*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{2*CHAR_W,BMP_EN_Y + 2*CHAR_H,3*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{0*CHAR_W,BMP_EN_Y + 2*CHAR_H,1*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4}
	 };
	 _ACTDATA actE00Piyo[]={
		{{0*CHAR_W,BMP_EN_Y + 3*CHAR_H,1*CHAR_W,BMP_EN_Y + 4*CHAR_H},8,2},
		{{1*CHAR_W,BMP_EN_Y + 3*CHAR_H,2*CHAR_W,BMP_EN_Y + 4*CHAR_H},8,2}
	 };
	_ACTDATA actE00CageL[]={
		{{10*CHAR_W,BMP_EN_Y,11*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{9*CHAR_W,BMP_EN_Y,10*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{11*CHAR_W,BMP_EN_Y,12*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{9*CHAR_W,BMP_EN_Y,10*CHAR_W,BMP_EN_Y + CHAR_H },8,4}
	 };
	_ACTDATA actE00CageR[]={
		{{10*CHAR_W,BMP_EN_Y + CHAR_H,11*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{9*CHAR_W,BMP_EN_Y + CHAR_H,10*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{11*CHAR_W,BMP_EN_Y + CHAR_H,12*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{9*CHAR_W,BMP_EN_Y + CHAR_H,10*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4}
	 };
	_ACTDATA actE00EscL[]={
		{{10*CHAR_W,BMP_EN_Y + 2*CHAR_H,11*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{9*CHAR_W,	BMP_EN_Y + 2*CHAR_H,10*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{11*CHAR_W,BMP_EN_Y + 2*CHAR_H,12*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{9*CHAR_W,	BMP_EN_Y + 2*CHAR_H,10*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4}
	};
	_ACTDATA actE00EscR[]={
		{{13*CHAR_W,BMP_EN_Y + 2*CHAR_H,14*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{12*CHAR_W,BMP_EN_Y + 2*CHAR_H,13*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{14*CHAR_W,BMP_EN_Y + 2*CHAR_H,15*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{13*CHAR_W,BMP_EN_Y + 2*CHAR_H,14*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4}
	};
	_ACTDATA actE00CagePiyo[]={
		{{15*CHAR_W,BMP_EN_Y + 2*CHAR_H,16*CHAR_W,BMP_EN_Y + 3*CHAR_H},8,2},
		{{16*CHAR_W,BMP_EN_Y + 2*CHAR_H,17*CHAR_W,BMP_EN_Y + 3*CHAR_H},8,2}
	};
	 //敵０１
	 _ACTDATA actE01Left[]={
		{{4*CHAR_W,BMP_EN_Y,5*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y,4*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{5*CHAR_W,BMP_EN_Y,6*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y,4*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
	 };
	
	 _ACTDATA actE01Right[]={
		{{4*CHAR_W,BMP_EN_Y + CHAR_H,5*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y + CHAR_H,4*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{5*CHAR_W,BMP_EN_Y + CHAR_H,6*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y + CHAR_H,4*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
	 };
	 _ACTDATA actE01Up[]={
		{{4*CHAR_W,BMP_EN_Y + 2*CHAR_H,5*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y + 2*CHAR_H,4*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{5*CHAR_W,BMP_EN_Y + 2*CHAR_H,6*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{3*CHAR_W,BMP_EN_Y + 2*CHAR_H,4*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
	 };
	 _ACTDATA actE01CageL[]={
		{{13*CHAR_W,BMP_EN_Y,14*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{12*CHAR_W,BMP_EN_Y,13*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{14*CHAR_W,BMP_EN_Y,15*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{12*CHAR_W,BMP_EN_Y,13*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
	 };
	_ACTDATA actE01CageR[]={
		{{13*CHAR_W,BMP_EN_Y + CHAR_H,14*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{12*CHAR_W,BMP_EN_Y + CHAR_H,13*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{14*CHAR_W,BMP_EN_Y + CHAR_H,15*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{12*CHAR_W,BMP_EN_Y + CHAR_H,13*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
	 };
	
	 _ACTDATA actE01Piyo[]={
		{{2*CHAR_W,BMP_EN_Y + 3*CHAR_H,3*CHAR_W,BMP_EN_Y + 4*CHAR_H},8,2},
		{{3*CHAR_W,BMP_EN_Y + 3*CHAR_H,4*CHAR_W,BMP_EN_Y + 4*CHAR_H},8,2}
	 };
	 //敵０２
	_ACTDATA actE02Left[]={
		{{7*CHAR_W,BMP_EN_Y,8*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y,7*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{8*CHAR_W,BMP_EN_Y,9*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y,7*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
	 };
	
	 _ACTDATA actE02Right[]={
		{{7*CHAR_W,BMP_EN_Y + CHAR_H,8*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y + CHAR_H,7*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{8*CHAR_W,BMP_EN_Y + CHAR_H,9*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y + CHAR_H,7*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
	 };

	 _ACTDATA actE02Up[]={
		{{7*CHAR_W,BMP_EN_Y + 2*CHAR_H,8*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y + 2*CHAR_H,7*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{8*CHAR_W,BMP_EN_Y + 2*CHAR_H,9*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
		{{6*CHAR_W,BMP_EN_Y + 2*CHAR_H,7*CHAR_W,BMP_EN_Y + 3*CHAR_H },8,4},
	 };
	 
	 _ACTDATA actE02CageL[]={
		{{16*CHAR_W,BMP_EN_Y,17*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{15*CHAR_W,BMP_EN_Y,16*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{17*CHAR_W,BMP_EN_Y,18*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
		{{15*CHAR_W,BMP_EN_Y,16*CHAR_W,BMP_EN_Y + CHAR_H },8,4},
	 };
	_ACTDATA actE02CageR[]={
		{{16*CHAR_W,BMP_EN_Y + CHAR_H,17*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{15*CHAR_W,BMP_EN_Y + CHAR_H,16*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{17*CHAR_W,BMP_EN_Y + CHAR_H,18*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
		{{15*CHAR_W,BMP_EN_Y + CHAR_H,16*CHAR_W,BMP_EN_Y + 2*CHAR_H },8,4},
	 };
	//ブロック
	 _ACTDATA actBlk00Normal[]={
		 {{CHAR_W,	BMP_BL_Y,	2*CHAR_W,	BMP_BL_Y + CHAR_H},65535,1}
	 };
	 _ACTDATA actBlk02Normal[]={
		 {{CHAR_W, BMP_BL_Y + CHAR_H, 2*CHAR_W, BMP_BL_Y + 2*CHAR_H},65535,1}
	 };

	 
	 //アイテム
	 _ACTDATA actItem[]={
		 {{176,32,192,48},8,3},
		 {{176,48,192,64},8,3},
		 {{176,64,192,80},8,3}
	 };
//***********************************************************************
//アニメーションパターンのテーブル
//************************************************************************
	
 _ACTDATA *actData[][128]={
	{//マイキャラ
	actMCStopL,		actMCLeft,		actMCStopR,		actMCRight,
	actMCJumpL,		actMCJumpL,		actMCJumpR,		actMCJumpR,
	actMCStopL,		actMCDashL,		actMCStopR,		actMCDashR,
	actMCDashJumpL,	actMCDashJumpL,	actMCDashJumpR,	actMCDashJumpR,
	
	actMCStopUp,	actMCUp,		actMCStopUp,	actMCUp,
	actMCStopUp,	actMCUp,		actMCStopUp,	actMCUp,
	actMCStopUp,	actMCUp,		actMCStopUp,	actMCUp,
	actMCStopUp,	actMCUp,		actMCStopUp,	actMCUp,
	
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,

	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,

	actMCStopLD,	actMCLeftD,		actMCStopRD,	actMCRightD,
	actMCJumpLD,	actMCJumpLD,	actMCJumpRD,	actMCJumpRD,
	actMCStopLD,	actMCDashLD,	actMCStopRD,	actMCDashRD,
	actMCDashJumpLD,actMCDashJumpLD,actMCDashJumpRD,actMCDashJumpRD,
	
	actMCStopUpD,	actMCUpD,		actMCStopUpD,	actMCUpD,
	actMCStopUpD,	actMCUpD,		actMCStopUpD,	actMCUpD,
	actMCStopUpD,	actMCUpD,		actMCStopUpD,	actMCUpD,
	actMCStopUpD,	actMCUpD,		actMCStopUpD,	actMCUpD,
	
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,

	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo,
	actMCPiyo,		actMCPiyo,		actMCPiyo,		actMCPiyo

	},
	{//Enem00
	actE00Left,		actE00Right,	actE00Left,		actE00Right,
	actE00Left,		actE00Right,	actE00Left,		actE00Right,
	actE00Up,		actE00Up,		actE00Up,		actE00Up,
	actE00Up,		actE00Up,		actE00Up,		actE00Up,
	
	actE00Piyo,		actE00Piyo,		actE00Piyo,		actE00Piyo,
	actE00Piyo,		actE00Piyo,		actE00Piyo,		actE00Piyo,
	actE00Piyo,		actE00Piyo,		actE00Piyo,		actE00Piyo,
	actE00Piyo,		actE00Piyo,		actE00Piyo,		actE00Piyo,
	
	actE00CageL,	actE00CageR,	actE00CageL,	actE00CageR,
	actE00CageL,	actE00CageR,	actE00CageL,	actE00CageR,
	actE00CageL,	actE00CageR,	actE00CageL,	actE00CageR,
	actE00CageL,	actE00CageR,	actE00CageL,	actE00CageR,
	
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,

	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,

	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,
	actE00EscL,		actE00EscR,		actE00EscL,		actE00EscR,

	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,
	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo,	actE00CagePiyo

	

	},
	{//Blk00
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,

	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal,
	actBlk00Normal,actBlk00Normal,actBlk00Normal,actBlk00Normal
	},
	{//Enem01
	actE01Left,		actE01Right,	actE01Left,		actE01Right,
	actE01Left,		actE01Right,	actE01Left,		actE01Right,
	actE01Up,		actE01Up,		actE01Up,		actE01Up,
	actE01Up,		actE01Up,		actE01Up,		actE01Up,
	
	actE01Piyo,		actE01Piyo,		actE01Piyo,		actE01Piyo,
	actE01Piyo,		actE01Piyo,		actE01Piyo,		actE01Piyo,
	actE01Piyo,		actE01Piyo,		actE01Piyo,		actE01Piyo,
	actE01Piyo,		actE01Piyo,		actE01Piyo,		actE01Piyo,
	
	actE01Left,		actE01Right,	actE01Left,		actE01Right,
	actE01Left,		actE01Right,	actE01Left,		actE01Right,
	actE01Up,		actE01Up,		actE01Up,		actE01Up,
	actE01Up,		actE01Up,		actE01Up,		actE01Up,
	
	actE01CageL,	actE01CageR,	actE01CageL,	actE01CageR,
	actE01CageL,	actE01CageR,	actE01CageL,	actE01CageR,
	actE01CageL,	actE01CageR,	actE01CageL,	actE01CageR,
	actE01CageL,	actE01CageR,	actE01CageL,	actE01CageR,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL
	},
	{//Enem02
	actE02Left,		actE02Right,	actE02Left,		actE02Right,
	actE02Left,		actE02Right,	actE02Left,		actE02Right,
	actE02Up,		actE02Up,		actE02Up,		actE02Up,
	actE02Up,		actE02Up,		actE02Up,		actE02Up,
	
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,
	actE02CageL,	actE02CageR,	actE02CageL,	actE02CageR,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,

	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL,
	actE00EscL,		actE00EscL,		actE00EscL,		actE00EscL
	},
	{//Blk02
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,

	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal,
	actBlk02Normal,actBlk02Normal,actBlk02Normal,actBlk02Normal
	},
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,

	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem,
	actItem,actItem,actItem,actItem
};
void PicChange(_CHAR*lpChar){
		
	_ACTDATA		*lpActTmp=NULL;
	
	//ステータスに変化があったらアニメカウントを更新
	if(lpChar->nStatusOld!=lpChar->nStatus){
		lpChar->wAnimeCnt=0;
		lpChar->nAnimeIndex=0;
	}
	//ステータスデータを取っておく
	lpChar->nStatusOld	=lpChar->nStatus;
	//絵の切り替え
	lpActTmp = actData[lpChar->nType & 0x07][lpChar->nStatus & _STATUS_MASK] 
		+ lpChar->nAnimeIndex;
	lpChar->rcSrc=lpActTmp->rcSrc;
	lpChar->wAnimeCnt++;
	if(lpChar->wAnimeCnt==lpActTmp->wAnimeCntMax){
		lpChar->wAnimeCnt=0;
		lpChar->nAnimeIndex++;
		if(lpChar->nAnimeIndex==lpActTmp->nAnimeIndexMax)
			lpChar->nAnimeIndex=0;
	}
}
