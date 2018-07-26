#pragma once
//#ifdef GLOBAL_INSTANCE
//#define GLOBAL
//#else
//#define GLOBAL extern 
//#endif

#define visibleSize_Width 360
#define visibleSize_Height 640

#define InitialCharPositionX 180
#define InitialCharPositionY 200

#define SOUND_KEY "sound_key"
#define	MUSIC_KEY "music_key"
#define	Wudi_KEY "wudi_key"
#define HIGHSCORE_KEY "highscore_key"
#define bg_music_1 "Music/BackMusic.mp3"
#define bg_music_2 "Music/Confirm.wav"
#define sound_1 "Music/Confirm.wav"
#define sound_2 "Music/Confirm.wav"
#define GameSceneBulletVelocity 600 //自机子弹垂直方向速度
/*
	GameScene Tags
*/
#define GameScene_Score 10//积分层
#define GameScene_Game1 11//游戏层
#define GameScene_Game2 12
#define GameSceneNodeTagChar 20//自机
#define GameSceneNodeTagBoss 21//Boss
#define GameSceneNodeBatchTagBullet 30//自机子弹
#define GameSceneNodeBatchTagBulletBoss 31//Boss弹幕
#define GameSceneNodeTagStatusBarCharselfNode 50
#define GameSceneNodeTagStatusBarLifeNode 51
#define GameSceneNodeTagStatusBarScore 52
#define GameSceneNodeTagExplosionParticleSystem 53
#define DecisionPointChar 233//Boss碰撞点
#define GamesceneRunning 77//游戏场景正在运行
#define ContactStatusCadan 90
#define ContactStatusPengzhuang 91

//Char
#define LID 601 //L
#define LNAME "L"
#define YID 602 //Y
#define YNAME "Y"
#define MID 603 //M
#define MNAME "M"
#define CharStatusDead -1
#define CharStatusSpawn 0
#define CharStatusLive 1
//Boss
#define StageOne 1
#define StageTwo 2
#define BossStatusDead -1
#define BossStatusSpawn 0
#define BossStatusLive 1
//Stage
#define Stage1ID 0
#define Stage2ID 1
#define Stage3ID 2
#define Stage4ID 3
#define Stage5ID 4

#define Stage2_2ID 11
#define Stage4_2ID 13
//hp Tag
#define hpSpriteTag 7
#define hpSprite2Tag 8






#define PI 3.1415926535897932385f
#define PI2 (PI * 2)
#define DEG_RAD (PI / 180)
#define RAD_DEG (180 / PI)

#define ABS(A) ((A) < 0? -(A): (A))
#define SIGNUM(A) ((A) < 0? -1: (A) > 0 ? 1 : 0)

#define FMOD(A,B) (float)fmod(A, B)
#define ATAN2(A,B) (float)atan2(A, B)
#define COS(A) (float)cos(A)
#define SIN(A) (float)sin(A)
#define SQRT(A) (float)sqrt(A)
#define ACOS(A) (float)acos(A)

#define SIN_RAD(A) SIN((A) * RAD_DEG)
#define COS_RAD(A) COS((A) * RAD_DEG)
#define SIN_DEG(A) SIN((A) * DEG_RAD)
#define COS_DEG(A) COS((A) * DEG_RAD)
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif
#ifndef Sign
#define Sign(x) ((x) > 0 ? 1 : -1)
#endif