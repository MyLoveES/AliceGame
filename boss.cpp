#include "boss.h"
Boss* Boss::createWithSpriteFrameName(const char * spriteFrameName) {
	Boss * boss = new Boss();
	if (boss && boss->initWithSpriteFrameName(spriteFrameName)) {
		boss->autorelease();
		Vec2 verts[] = {
			Vec2(-23,0),//120
			Vec2(23,0),
			Vec2(0,38),
			Vec2(0,-38)
		};
		auto body = PhysicsBody::createPolygon(verts,4);
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);
		boss->setPhysicsBody(body);
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return NULL;
}

//void Boss::setPosition(const Vec2& newPosition) {
//	Size screensize = Director::getInstance()->getVisibleSize();
//	float halfWidth = this->getContentSize().width / 2;
//	float halfHeight = this->getContentSize().height / 2;
//	float pos_x = newPosition.x;
//	float pos_y = newPosition.y;
//
//	if (pos_x<halfWidth) {
//		pos_x = halfWidth;
//	}
//	else if (pos_x>screensize.width-halfWidth) {
//		pos_x = screensize.width - halfWidth;
//	}
//	if (pos_y<halfHeight) {
//		pos_x = halfHeight;
//	}
//	else if (pos_y>screensize.height - halfHeight) {
//		pos_x = screensize.height - halfHeight;
//	}
//
//	this->setPosition(Vec2(pos_x,pos_y));
//	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//}

void Boss::Spawn() {
	this->setStatus(BossStatusSpawn);
	this->setInitialHitPoints(400);
	this->setHitPoints(this->getInitialHitPoints());
	if (this->getStage()== StageOne) {
		this->setPosition(Vec2(visibleSize_Width / 2, visibleSize_Height + this->getContentSize().height));
	}
	this->runAction(Sequence::create(MoveTo::create(1, Vec2(visibleSize_Width / 2, visibleSize_Height - 150)), CallFunc::create([this] {this->setStatus(BossStatusLive); this->setSpawnTime(-1); }), NULL));
}
