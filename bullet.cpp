#include "bullet.h"
#include "math.h"
Bullet * Bullet::createWithSpriteFrameName(const char * spriteFrameName) {
	Bullet * bullet = new Bullet();
	if (bullet && bullet->initWithSpriteFrameName(spriteFrameName)) {
		bullet->autorelease();
		bullet->setVisible(false);
		auto *body = PhysicsBody::createCircle(7.5);
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);
		bullet->setPhysicsBody(body);
		bullet->unscheduleUpdate();
		//bullet->RotationInited = 0;
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}
void Bullet::setRotation(const float & newRotation, int tag ) {
	switch (tag) {
	case 0:
		Sprite::setRotation(newRotation);
		break;
	case 1:
		Sprite::setRotation(90 - newRotation);
		break;
	}
	//
	//if (this->RotationInited == 0) {
	//	this->RotationInited = 1;
	//	this->setDirectRotation(this->getRotation());
	//}
}
void Bullet::shootBullet() {
	this->setVisible(true);
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void Bullet::update(float dt) {
	Size visiblesize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(this->getPosition() + this->getVelocity()*dt));

	if (UserDefault::getInstance()->getIntegerForKey("Stage") == Stage4ID && this->getTag() == GameSceneNodeBatchTagBulletBoss && this->getName() == "BULLET8") {
		this->setRotation(this->getRotation() + this->getPalstance()*dt);
		if (this->getAccelerate().getLength() != 0) {
			this->setVelocity(this->getVelocity() + this->getAccelerate()*dt);
		}
		else {
			this->setVelocity(Vec2(this->getVelocity().getLength()*SIN_DEG(this->getRotation()), this->getVelocity().getLength()*COS_DEG(this->getRotation())));
		}
	}
	else {
		if (this->getPosition().y > 1.2f * visiblesize.height + this->getContentSize().height || this->getPosition().y < 0 || this->getPosition().x > 1.2f * visiblesize.width + this->getContentSize().width || this->getPosition().x < -0.2*visiblesize.width - this->getContentSize().width) {
			this->setVisible(false);
			this->unscheduleAllCallbacks();
			this->removeFromParentAndCleanup(true);
			return;
		}
		else {
			this->setAccelerate(this->getAAccelerate()*Vec2(SIN_DEG(this->getRotation()),COS_DEG(this->getRotation()))*dt+this->getAccelerate());
			this->setPalstance(this->getPalstance() + this->getPAccelerate()*dt);
			this->setRotation(this->getRotation() + this->getPalstance()*dt);
			if (this->getAccelerate().getLength() != 0) {
				this->setVelocity(this->getVelocity() + this->getAccelerate()*dt);
			}
			else {
				this->Velocity(this->getVelocity().getLength() +this->getAcceleration()*dt);
				this->setVelocity(Vec2(this->getVelocity().getLength()*SIN_DEG(this->getRotation()), this->getVelocity().getLength()*COS_DEG(this->getRotation())));
			}
			return;
		}
	}
	
}


void Bullet::Velocity(const float newVelocity){
	this->setVelocity(Vec2(newVelocity * SIN_DEG(this->getRotation()) , newVelocity * COS_DEG(this->getRotation())));
}
void Bullet::Accelerate(const float newAccelerate) {
	this->setAccelerate(Vec2(newAccelerate * SIN_DEG(this->getRotation()), newAccelerate * COS_DEG(this->getRotation())));
}

void Bullet::BULLET1(float dt, float rotation) {
	this->setVisible(true);
	this->unscheduleAllCallbacks();
	this->runAction(Sequence::create(RotateTo::create(0.5, rotation), CallFunc::create([this] { this->shootBullet(); }), NULL));
}
void Bullet::BULLET3(float dt, Sprite * charself) {
	this->unscheduleUpdate(); 
	this->unscheduleAllCallbacks();
	this->Velocity(200);
	float rotation = atan2(charself->getPositionY() - this->getPositionY(), charself->getPositionX() - this->getPositionX())*RAD_DEG;
	this->runAction(Sequence::create(RotateTo::create(0.5, 90-rotation), CallFunc::create([this] {this->shootBullet(); }), NULL));
}

void Bullet::BULLET4(float dt) {
	this->unscheduleAllCallbacks();
	if (dt == 1) {
		this->scheduleUpdate();
		this->scheduleOnce([this](int) { this->unscheduleUpdate(); this->BULLET4(2); }, 0.3f, "BULLET4_1");
	}
	else {
		this->scheduleOnce([this](int) { this->unscheduleUpdate(); this->setRotation(Utility::getRand(0, 360));  this->Velocity(100); this->shootBullet(); }, 2.0f, "BULLET4_2");
	}
}

void Bullet::BULLET6(float dt) {
	this->unscheduleAllCallbacks();
	if (dt == 1) {
		this->scheduleUpdate();
		this->scheduleOnce([this](int) { this->unscheduleUpdate(); this->BULLET4(2); }, 0.3f, "BULLET6_1");
	}
	else {
		this->scheduleOnce([this](int) { this->unscheduleUpdate(); this->setRotation(Utility::getRand(0, 360)); this->Velocity(100); this->shootBullet(); }, 3.0f, "BULLET6_2");
	}
	//float rotation = atan2(charself->getPositionY() - this->getPositionY(), charself->getPositionX() - this->getPositionX())*RAD_DEG;
}

void Bullet::BULLET7(float dt) {
	this->unscheduleAllCallbacks();
	this->setSpriteFrame("b7_09.png");
	this->scheduleOnce([this](int) { 
		this->unscheduleAllCallbacks();
		this->setRotation(Utility::getRand(0, 360));
		this->Velocity(100);
		this->setAccelerate(10 * Vec2(SIN_DEG(this->getRotation()), COS_DEG(this->getRotation()))); 
		this->scheduleUpdate(); }, 1.0f , "BULLET7_1");
}

void Bullet::BULLET8(float dt) {
	if ( dt == 1 ) {
		this->unscheduleUpdate();
		this->scheduleOnce([this](int) {
		this->Velocity(300);
		this->setAccelerate(-100 * Vec2(SIN_DEG(this->getRotation()), COS_DEG(this->getRotation())));
		this->scheduleUpdate();
		this->BULLET8(2); }, 5.0f, "BULLET8_1");
	}
	else if (dt == 2) {
		this->scheduleOnce([this](int) {
		this->unscheduleUpdate();
		this->Velocity(-300);
		this->setAccelerate(100 * Vec2(SIN_DEG(this->getRotation()), COS_DEG(this->getRotation())));
		 }, 3, "BULLET8_2");
	}
}

void Bullet::BULLET16(float dt, Sprite * charself) {
	this->unscheduleUpdate();
	this->unscheduleAllCallbacks();
	this->Velocity(150);
	float rotation = atan2(charself->getPositionY() - this->getPositionY(), charself->getPositionX() - this->getPositionX())*RAD_DEG;
	this->runAction(Sequence::create(RotateTo::create(0.5, 90 - rotation), CallFunc::create([this] { this->setAcceleration(0); this->shootBullet(); }), NULL));
}

