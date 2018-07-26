#pragma once
#include "cocos2d.h"
#include "define.h"
using namespace cocos2d;

class Char : public cocos2d::Sprite {
	Animate * CharAction;
	CC_SYNTHESIZE(int, stage, Stage);
	CC_SYNTHESIZE(int, status, Status); 
	CC_SYNTHESIZE(long int, spawnTime, SpawnTime);
	CC_SYNTHESIZE(int, initialHitPoints, InitialHitPoints);
	CC_SYNTHESIZE(int, hitPoints, HitPoints);
public:
	void setPosition(const cocos2d::Vec2& newPosition);
	void setPositionForStage(const cocos2d::Vec2& newPosition);
	static Char *createWithSpriteFrameName(const char * spriteFrameName);
	void CharOnAction(int i);
	void Spawn();
};