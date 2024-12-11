/*enemyActPattern.h*/

#ifndef ENEM_ACT_H
#define ENEM_ACT_H


//*************************
//É}ÉNÉç
//*************************
#define PIYOCNT_MAX 512
#define ENEM_SPD_LO 3
#define ENEM_SPD_HI 4
#define ENEM_STEP_HI 3
#define ENEM_STEP_LO 2

#define ESCAPE_COUNT	4500 
#define WARNING_COUNT	2500

extern void EnemyLeft(_CHAR*);
extern void EnemyRight(_CHAR*);
extern void EnemyUp(_CHAR*);
extern void EnemyDown(_CHAR*);
extern void EnemyFall(_CHAR*);
extern void EnemyPiyo(_CHAR*);
extern void EnemyPiyoFall(_CHAR*);
extern void EnemyCage(_CHAR*);
extern void EnemyCageFall(_CHAR*);
#endif