#include "char.h"
Char* Char::createWithSpriteFrameName(const char * spriteFrameName) {
	Char * charself = new Char();
	if (charself && charself->initWithSpriteFrameName(spriteFrameName)) {
		charself->autorelease();
		Vec2 verts[] = {
			Vec2(-14,0),
			Vec2(14,0),
			Vec2(0,22),
			Vec2(0,-22)
		};
		auto shape = PhysicsShapeCircle::create(6);
		auto body = PhysicsBody::createPolygon(verts, 4);
		shape->setTag(DecisionPointChar);

		body->addShape(shape);
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);
		charself->setPhysicsBody(body);
		return charself;
	}
	CC_SAFE_DELETE(charself);
	return NULL;
}

void Char::setPosition(const Vec2& newPosition) {
	Size screensize = Director::getInstance()->getVisibleSize();
	float halfWidth = this->getContentSize().width / 2;
	float halfHeight = this->getContentSize().height / 2;
	float pos_x = newPosition.x;
	float pos_y = newPosition.y;
	if (pos_x < halfWidth) {
		pos_x = halfWidth;
	}
	else if (pos_x > screensize.width - halfWidth) {
		pos_x = screensize.width - halfWidth;
	}
	if (pos_y < 160 + halfHeight) {
		pos_y = 160 + halfHeight;
	}
	else if (pos_y > screensize.height - halfHeight) {
		pos_y = screensize.height - halfHeight;
	}

	Sprite::setPosition(Vec2(pos_x, pos_y));
	Sprite::setAnchorPoint(Vec2::ANCHOR_MIDDLE);
}

void Char::Spawn() {
	this->setStatus(CharStatusSpawn) ;
	this->setPosition(Vec2(InitialCharPositionX, InitialCharPositionY));
	this->CharOnAction(1);
	this->runAction(Sequence::create(Blink::create(1, 10), CallFunc::create([this] {this->setStatus(CharStatusLive); }), NULL));
	//Sprite::runAction(Blink::create(1, 10));
}

void Char::CharOnAction(int k) {
	Sprite::stopAllActions();
	Animation * CharAnimation = Animation::create();
	switch (k) {
	case 1:
		for (int i = 1; i <= 4; i = i + 1) {
			__String * frameName = __String::createWithFormat("%s%d.png", UserDefault::getInstance()->getStringForKey("CharName").c_str(), i);
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			CharAnimation->addSpriteFrame(spriteFrame);
		}
		break;
	case 2:
		for (int i = 1; i <= 7; i = i + 1) {
			__String * frameName = __String::createWithFormat("%sR%d.png", UserDefault::getInstance()->getStringForKey("CharName").c_str(), i);
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			CharAnimation->addSpriteFrame(spriteFrame);
		}
		break;
	case 3:
		for (int i = 1; i <= 7; i = i + 1) {
			__String * frameName = __String::createWithFormat("%sL%d.png", UserDefault::getInstance()->getStringForKey("CharName").c_str(), i);
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			CharAnimation->addSpriteFrame(spriteFrame);
		}
		break;
	}
	CharAnimation->setDelayPerUnit(0.1f);
	CharAnimation->setRestoreOriginalFrame(true);
	CharAction = Animate::create(CharAnimation);
	Sprite::runAction(RepeatForever::create(CharAction));
}