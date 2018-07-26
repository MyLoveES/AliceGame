#pragma once
#include "cocos2d.h"
#include "define.h"
#include "char.h"
#include "boss.h"
#include "Utility.h"
class Bullet : public cocos2d::Sprite {
	//int RotationInited;
	//CC_SYNTHESIZE(float, v, V);//速度大小
	CC_SYNTHESIZE(Vec2, velocity, Velocity);//速度
	CC_SYNTHESIZE(Vec2, accelerate, Accelerate);//加速度
	CC_SYNTHESIZE(float, acceleration, Acceleration);//加速度值
	CC_SYNTHESIZE(float, aAccelerate, AAccelerate);//加加速度
	CC_SYNTHESIZE(float, directRotation, DirectRotation);//方向角度
	CC_SYNTHESIZE(float, palstance, Palstance);//角速度
	CC_SYNTHESIZE(float, pAccelerate, PAccelerate);//角加速度
public :
	void shootBullet();
	void update(float dt);
	void update2(float dt);
	static Bullet * createWithSpriteFrameName(const char * spriteFrameName);
	void shootBulletFromBoss_BULLET1_1(float dt);

	//void setPosition(const cocos2d::Vec2& newPosition);
	void setRotation(const float & newRotation, int tag = 0);
	void Velocity(const float newVelocity);
	void Accelerate(const float newAccelerate);


	void BULLET1(float dt, float rotation);
	void BULLET3(float dt, Sprite * charself);
	void BULLET4(float dt);
	void BULLET6(float dt);
	void BULLET7(float dt);
	void BULLET8(float dt);
	void BULLET16(float dt, Sprite * charself);
};