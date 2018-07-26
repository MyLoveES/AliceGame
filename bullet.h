#pragma once
#include "cocos2d.h"
#include "define.h"
#include "char.h"
#include "boss.h"
#include "Utility.h"
class Bullet : public cocos2d::Sprite {
	//int RotationInited;
	//CC_SYNTHESIZE(float, v, V);//�ٶȴ�С
	CC_SYNTHESIZE(Vec2, velocity, Velocity);//�ٶ�
	CC_SYNTHESIZE(Vec2, accelerate, Accelerate);//���ٶ�
	CC_SYNTHESIZE(float, acceleration, Acceleration);//���ٶ�ֵ
	CC_SYNTHESIZE(float, aAccelerate, AAccelerate);//�Ӽ��ٶ�
	CC_SYNTHESIZE(float, directRotation, DirectRotation);//����Ƕ�
	CC_SYNTHESIZE(float, palstance, Palstance);//���ٶ�
	CC_SYNTHESIZE(float, pAccelerate, PAccelerate);//�Ǽ��ٶ�
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