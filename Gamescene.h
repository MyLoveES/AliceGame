#pragma once
#include "cocos2d.h"
#include "bullet.h"
#include "SystemHeader.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class Gamescene :public cocos2d::Scene {
public:
	CC_SYNTHESIZE(long long int, time, Time);
	CC_SYNTHESIZE(long long int, timer , Timer);
	int GameZOrder = 7, ScoreZOrder = 10, HpZOrder = 10, CharZOrder = 9, BossZOrder = 8, BulletZOrder = 9;
	Boss *boss;
	Char *charself;
	int Score,Graze;
	int CharAcionIsPlaying;
	Menu *menu;
	EventListenerTouchOneByOne *TouchCharself;
	EventListenerPhysicsContact *contactListener;
	ProgressTimer * progressTimer;
	ProgressTimer * progressTimer2;
	Sprite * CharHpX1;
	Sprite * CharHpX2;
	LabelAtlas * GrazeLabel;
	LabelAtlas * ScoreLabel;
	Label *TimeLabel;
	timeval psv;

	float BULLET2_StageTwo_RotationAc;//BULLET3_StageTwo µ¯Ä»½Ç¶È+
	float BULLET2_StageTwo_Rotation;//BULLET3_StageTwo µ¯Ä»½Ç¶È
	float BULLET3_StageTwo_Rotation;//BULLET3_StageTwo µ¯Ä»½Ç¶È
	float BULLET4_StageTwo_Rotation;//BULLET4_StageTwo µ¯Ä»½Ç¶È
	Vec2 BULLET5_StageTwo_Rotation;//BULLET5_StageTwo µ¯Ä»Ëæ»ú²úÉúµã
	Vec2 BULLET6_StageTwo_Tri_Position;//BULLET5_StageTwo_tri Îå½Çµ¯Ä»µã
	float BULLET6_StageTwo_Tri_Rotation ;//BULLET5_StageTwo_tri Îå½Çµ¯Ä»½Ç


	CREATE_FUNC(Gamescene);
	static cocos2d::Scene* createScene();
	bool init();
	void onExit();
	void onEnter();
	void onEnterTransitionDidFinish();
	void menuBackCallBack(Ref * pSender);
	void menuResumeCallBack(Ref * pSender);
	void shootBulletFromChar(float dt);
	void handleBulletCollidingWithBoss(Boss * boss);
	void handleBulletCollidingWithChar(Char *charself);
	void handleCharCollidingWithBoss(Boss * boss);
	void moveBackground(float t);
	void TimerSelect(float dt);
	void onKeyReleased(EventKeyboard::KeyCode keycode , Event * pEvent);
	void Gameover();


	void Stage1_BossBullet();
	void Stage2_BossBullet();
	void Stage3_BossBullet();
	void Stage4_BossBullet();
	void Stage5_BossBullet();

	void BULLET1();
	void BULLET2();
	void BULLET3();
	void BULLET4();
	void BULLET5(Vec2 rand);
	void BULLET6();
	void BULLET7();
	void BULLET8();
	void BULLET9();
	void BULLET10();
	void BULLET11();
	void BULLET12();
	void BULLET13();
	void BULLET14();
	void BULLET15();
	void BULLET16();
	void BULLET17();
};