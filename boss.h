#pragma once
#include "cocos2d.h"
#include "define.h"
using namespace cocos2d;

class Boss : public cocos2d::Sprite {
	CC_SYNTHESIZE(int, stage, Stage);
	CC_SYNTHESIZE(int, status, Status);
	CC_SYNTHESIZE(int, initialHitPoints, InitialHitPoints);
	CC_SYNTHESIZE(long int, spawnTime, SpawnTime);
	CC_SYNTHESIZE(int, hitPoints, HitPoints);
	CC_SYNTHESIZE(Vec2, velocity, Velocity);
public :
	//void setPosition(const cocos2d::Vec2& newPosition);
	static Boss *createWithSpriteFrameName(const char * spriteFrameName);
	void Spawn();
};