/*ctachCount.cpp*/

#include "catchCount.h"
/////////////////////////////////////
//ƒOƒ[ƒoƒ‹•Ï”
/////////////////////////////////////
BYTE nCatchCount = 0;
//////////////////////////////////////////////////
//ŸB‚É•ß‚ç‚¦‚½“G‚Ì”‚ğ”‚¦‚é
/////////////////////////////////////////////////

//‚P•C•ß‚Ü‚¦‚½
void CatchCountCatch()
{
	nCatchCount++;
}

//‚P•C“¦‚°‚½
void CatchCountEscape()
{
	nCatchCount--;
}
//0‚É‰Šú‰»
void CatchCountZero()
{
	nCatchCount = 0;
}
//nCatchCount‚ğæ“¾‚·‚é
BYTE GetCatchCount()
{
	return(nCatchCount);
}