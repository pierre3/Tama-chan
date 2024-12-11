/*enemyWait.h*/


//第一引数のキャラが待つ
extern void EnemyWait_1(_CHAR *,_CHAR *);

//第二引数のキャラが待つ
extern void EnemyWait_2(_CHAR *,_CHAR *);
//左にいるキャラが待つ
extern void EnemyWait_Left(_CHAR *,_CHAR *);

//右にいるキャラが待つ
extern void EnemyWait_Right(_CHAR *,_CHAR *);

//上にいるキャラが待つ
extern void EnemyWait_Upper(_CHAR *,_CHAR *);

//下にいるキャラが待つ
extern void EnemyWait_Lower(_CHAR *,_CHAR *);

//ダミー
extern void EnemyWait_NoWait(_CHAR *,_CHAR *);
