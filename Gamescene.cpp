#include "Gamescene.h"
#include "HelloWorldScene.h"
#include "GameoverScene.h"


bool Gamescene::init() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	if (!Scene::init()) {
		return false;
	}

	this->setTime(3660);
	TimeLabel = Label::createWithTTF("60" , "fonts/Chi.ttf", 70);
	TimeLabel->setPosition(290, 80);
	TimeLabel->setColor(Color3B::YELLOW);
	TimeLabel->enableGlow(Color4B::WHITE);
	//StageLabel->enableOutline(Color4B::WHITE, 2);
	this->addChild(TimeLabel, GameScene_Score+1);

	//Score
	auto Score = Sprite::createWithSpriteFrameName("Score.png");
	Score->setAnchorPoint(Vec2::ZERO);
	Score->setPosition(Vec2(origin.x, origin.y));
	Score->setTag(GameScene_Score);
	this->addChild(Score, ScoreZOrder);

	//Game1
	auto Game1 = Sprite::createWithSpriteFrameName("bg.png");
	Game1->setAnchorPoint(Vec2::ZERO);
	Game1->setPosition(Vec2(origin.x, origin.y + Score->getContentSize().height));
	Game1->setTag(GameScene_Game1);
	this->addChild(Game1, GameZOrder);

	//Game2
	auto Game2 = Sprite::createWithSpriteFrameName("bg.png");
	Game2->setAnchorPoint(Vec2::ZERO);
	Game2->setPosition(Vec2(origin.x, Game1->getPositionY() + Game1->getContentSize().height));
	Game2->setTag(GameScene_Game2);
	this->addChild(Game2, GameZOrder);

	//自机生命、擦弹、分数
	CharHpX1 = Sprite::createWithSpriteFrameName("CharHp.png");
	CharHpX2 = Sprite::createWithSpriteFrameName("CharHp.png");
	CharHpX1->setTag(1);
	CharHpX2->setTag(2);
	CharHpX1->setPosition( Vec2(121, 128));
	CharHpX2->setPosition(CharHpX1->getPosition() + Vec2(30, 0));
	this->addChild(CharHpX1, ScoreZOrder);
	this->addChild(CharHpX2, ScoreZOrder);
	/*
	test
	*/
	this->Score = 0;
	this->Graze = 0;
	GrazeLabel = LabelAtlas::create(Utility::to_string(this->Graze), "fonts/2.png", 20, 23, '0');
	ScoreLabel = LabelAtlas::create(Utility::to_string(this->Score), "fonts/2.png", 20, 23, '0');
	GrazeLabel->setPosition(Vec2(110, 76));
	ScoreLabel->setPosition(Vec2(110, 39));
	this->addChild(GrazeLabel, ScoreZOrder);
	this->addChild(ScoreLabel, ScoreZOrder);

	//Boss血条
	auto hpSprite = Sprite::createWithSpriteFrameName("hp.png");
	auto hpSprite2 = Sprite::createWithSpriteFrameName("hp2.png");
	progressTimer = ProgressTimer::create(hpSprite);
	progressTimer2 = ProgressTimer::create(hpSprite2);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer2->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0, 0.5));
	progressTimer->setBarChangeRate(Vec2(1, 0));
	progressTimer2->setMidpoint(Vec2(0, 0.5));
	progressTimer2->setBarChangeRate(Vec2(1, 0));
	progressTimer->setPercentage(100);
	progressTimer2->setPercentage(100);
	progressTimer->setAnchorPoint(Vec2(0, 0.5));
	progressTimer2->setAnchorPoint(Vec2(0, 0.5));
	progressTimer2->setPosition(origin.x + 20, origin.y + visibleSize.height - hpSprite2->getContentSize().height);
	progressTimer->setPosition(origin.x + 60, origin.y + visibleSize.height - hpSprite->getContentSize().height);
	this->addChild(progressTimer, HpZOrder, hpSpriteTag);
	this->addChild(progressTimer2, HpZOrder, hpSprite2Tag);


	//按键监听
	auto listener = EventListenerKeyboard::create();//fanhuijian
	listener->onKeyReleased = CC_CALLBACK_2(Gamescene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(Gamescene::moveBackground));//背景滚动
	return true;
}

Scene *Gamescene::createScene() {
	auto scene = Scene::createWithPhysics();
	PhysicsWorld * physicsworld = scene->getPhysicsWorld();
	physicsworld->setGravity(Vect(0, 0));
	auto layer = Gamescene::create();
	scene->addChild(layer);
	scene->setTag(GamesceneRunning);
	return scene;
}
//背景滚动
void Gamescene::moveBackground(float t) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	auto Score = this->getChildByTag(GameScene_Score);
	auto Game1 = this->getChildByTag(GameScene_Game1);
	auto Game2 = this->getChildByTag(GameScene_Game2);
	Game1->setPositionY(Game1->getPositionY() - 1);
	if (Game1->getPositionY() < Score->getContentSize().height - Game1->getContentSize().height) {
		Game1->setPositionY(Score->getContentSize().height);
	}
	Game2->setPositionY(Game1->getPositionY() + Game1->getContentSize().height);
}

void Gamescene::onExit() {
	Scene::onExit();
	this->unschedule(schedule_selector(Gamescene::shootBulletFromChar));
	this->unschedule(schedule_selector(Gamescene::TimerSelect));
	this->unscheduleAllCallbacks();
	Director::getInstance()->getEventDispatcher()->removeEventListener(TouchCharself);
	Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);
	auto nodes = this->getChildren();
	for (const auto & node : nodes) {
		if (node->getTag() != GameScene_Game1 && node->getTag() != GameScene_Game2 && node->getTag() != GameScene_Score) {
			this->unscheduleAllCallbacks(); 
			this->removeChild(node);
		}
	}
}

void Gamescene::onEnter() {
	Scene::onEnter();
	Size visiblesize = Director::getInstance()->getVisibleSize();
	//计时器
	this->setTimer(0);
	this->schedule(schedule_selector(Gamescene::TimerSelect));

	gettimeofday(&psv, NULL);
	unsigned long int seed = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(seed);

	//添加boss
	switch (UserDefault::getInstance()->getIntegerForKey("Stage")) {
	case 0:
		this->boss = Boss::createWithSpriteFrameName("Stage1.png"); break;
	case 1:
		this->boss = Boss::createWithSpriteFrameName("Stage2.png"); break;
	case 2:
		this->boss = Boss::createWithSpriteFrameName("Stage3.png"); break;
	case 3:
		this->boss = Boss::createWithSpriteFrameName("Stage4.png"); break;
	case 4:
		this->boss = Boss::createWithSpriteFrameName("Stage5.png"); break;
	}
	boss->setStage(StageOne);
	this->boss->Spawn();
	this->boss->setSpawnTime(0);
	this->addChild(this->boss, BossZOrder, GameSceneNodeTagBoss);
	//添加自机
	CharAcionIsPlaying = 0;
	__String * CharName = __String::createWithFormat("%s1.png", UserDefault::getInstance()->getStringForKey("CharName").c_str());
	this->charself = Char::createWithSpriteFrameName(CharName->getCString());
	this->charself->setHitPoints(3);//生命
	this->charself->setSpawnTime(0);//登陆时间
	this->charself->Spawn();
	this->addChild(this->charself, CharZOrder, GameSceneNodeTagChar);

	//注册触摸事件监听器
	TouchCharself = EventListenerTouchOneByOne::create();
	TouchCharself->setSwallowTouches(true);
	TouchCharself->setEnabled(false);
	//触摸移动
	TouchCharself->onTouchBegan = [this](Touch *touch, Event *unused_event) {
		return true;
	};
	TouchCharself->onTouchMoved = [this](Touch *touch, Event *unused_event) {
		int i = 1;
		bool changingdirection = false;
		auto target = unused_event->getCurrentTarget();
		if (CharAcionIsPlaying != -1 && touch->getDelta().x < 0) {
			i = 3;
			CharAcionIsPlaying = -1;
			changingdirection = true;
		}
		else if (CharAcionIsPlaying != 1 && touch->getDelta().x > 0) {
			i = 2;
			CharAcionIsPlaying = 1;
			changingdirection = true;
		}
		else if (CharAcionIsPlaying != 0 && touch->getDelta().x == 0) {
			i = 1;
			CharAcionIsPlaying = 0;
			changingdirection = true;
		}
		if (changingdirection == true) {
			this->charself->CharOnAction(i);
		}
		target->setPosition(target->getPosition() + touch->getDelta());
		return true;
	};
	TouchCharself->onTouchEnded = [this](Touch *touch, Event *unused_event) {
		CharAcionIsPlaying = 0;
		this->charself->CharOnAction(1);
		return true;
	};
	//添加触摸飞机事件监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchCharself, this->charself);

	//事件监听器
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact) {
		auto SpriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
		auto SpriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		if (SpriteA != nullptr && SpriteB != nullptr) {
			//danmu与ziji碰撞
			Node * charself2 = nullptr;
			if (SpriteA->getTag() == GameSceneNodeBatchTagBulletBoss&&
				SpriteB->getTag() == GameSceneNodeTagChar&&
				SpriteB->isVisible()) {
				this->Graze += 1;
				this->Score += 111;
				if (!SpriteA->isVisible()) {
					return false;
				}
				if (contact.getShapeB()->getTag() == DecisionPointChar) {
					SpriteA->getPhysicsBody()->setEnabled(false);
					SpriteA->setVisible(false);
					charself2 = SpriteB;
				}
			}
			else if (SpriteB->getTag() == GameSceneNodeBatchTagBulletBoss&&
				SpriteA->getTag() == GameSceneNodeTagChar&&
				SpriteA->isVisible()) {
				this->Graze += 1;
				this->Score += 111;
				if (!SpriteB->isVisible()) {
					return false;
				}
				if (contact.getShapeA()->getTag() == DecisionPointChar) {
					SpriteB->getPhysicsBody()->setEnabled(false);
					SpriteB->setVisible(false);
					charself2 = SpriteA;
				}
			}
			if (charself2 != nullptr && !UserDefault::getInstance()->getBoolForKey(Wudi_KEY, false)) {
				this->handleBulletCollidingWithChar((Char *)charself2);
				return false;
			}

			//炮弹与敌人碰撞
			Node * boss2 = nullptr;
			if (SpriteA->getTag() == GameSceneNodeBatchTagBullet&&
				SpriteB->getTag() == GameSceneNodeTagBoss&&
				SpriteB->isVisible()) {
				this->Score += 1;
				if (!SpriteA->isVisible()) {
					return false;
				}
				SpriteA->setVisible(false);
				boss2 = SpriteB;
			}
			else if (SpriteB->getTag() == GameSceneNodeBatchTagBullet&&
				SpriteA->getTag() == GameSceneNodeTagBoss&&
				SpriteA->isVisible()) {
				this->Score += 1;
				if (!SpriteB->isVisible()) {
					return false;
				}
				SpriteB->setVisible(false);
				boss2 = SpriteA;
			}
			if (boss2 != nullptr) {
				this->handleBulletCollidingWithBoss((Boss *)boss2);
				return false;
			}
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//0.2s 调用 发射子弹
}

void Gamescene::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();
	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY, true)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}

void Gamescene::menuBackCallBack(Ref * pSender) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void Gamescene::menuResumeCallBack(Ref * pSender) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	this->resume();
	this->removeChildByName("PauseItem");
	for (const auto&node : this->getChildren()) {
		node->resume();
	}
	this->removeChild(menu);
}

void Gamescene::shootBulletFromChar(float dt) {
	if (charself && charself->isVisible()) {
		/*for (float i = -1; i <= 1; i++) {
			Bullet *bullet = Bullet::createWithSpriteFrameName("bulletchar.png");
			bullet->setPosition(charself->getPosition() + Vec2(bullet->getContentSize().width*i, charself->getContentSize().height / 2));
			bullet->Velocity(GameSceneBulletVelocity);
			this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBullet);
			this->setLocalZOrder(BulletZOrder);
			bullet->shootBullet();
		}*/
		Bullet *bullet1 = Bullet::createWithSpriteFrameName("bulletchar.png");
		Bullet *bullet2 = Bullet::createWithSpriteFrameName("bulletchar.png");
		Bullet *bullet3 = Bullet::createWithSpriteFrameName("bulletchar.png");
		bullet1->setPosition(charself->getPosition() + Vec2(-bullet1->getContentSize().width*1, charself->getContentSize().height / 2));
		bullet2->setPosition(charself->getPosition() + Vec2(0, charself->getContentSize().height / 2));
		bullet3->setPosition(charself->getPosition() + Vec2(bullet1->getContentSize().width*1, charself->getContentSize().height / 2));
		bullet1->setVelocity(Vec2(0, GameSceneBulletVelocity));
		bullet2->setVelocity(Vec2(0, GameSceneBulletVelocity));
		bullet3->setVelocity(Vec2(0, GameSceneBulletVelocity));
		this->addChild(bullet1, 10, GameSceneNodeBatchTagBullet);
		this->addChild(bullet2, 10, GameSceneNodeBatchTagBullet);
		this->addChild(bullet3, 10, GameSceneNodeBatchTagBullet);
		bullet1->shootBullet();
		bullet2->shootBullet();
		bullet3->shootBullet();
	}
}

void Gamescene::handleBulletCollidingWithBoss(Boss * boss) {
	boss->setHitPoints(boss->getHitPoints() - 1);
	if (boss->getStage() == StageOne) {
		progressTimer->setPercentage(boss->getHitPoints() * 100 / boss->getInitialHitPoints());
		if (boss->getHitPoints() <= 0) {
			this->setTime(3660);
			auto nodes = this->getChildren();
			for (const auto & node : nodes) {
				if (node->getTag() == GameSceneNodeBatchTagBulletBoss) {
					//node->runAction(Sequence::create(FadeOut::create(0.6), CallFunc::create([node] { node->removeFromParentAndCleanup(true); }), NULL));
					node->setVisible(false);
					node->unscheduleAllCallbacks();
					node->removeFromParentAndCleanup(true);
				}
			}
			boss->setStatus(BossStatusDead);
			boss->setStage(StageTwo);
			this->boss->stopAllActions();
			this->boss->setSpawnTime(-1);
			this->setTimer(-1);
			boss->Spawn();
		}
	}
	else if (boss->getStage() == StageTwo) {
		progressTimer2->setPercentage(boss->getHitPoints() * 100 / boss->getInitialHitPoints());
		if (boss->getHitPoints() <= 0) {
			boss->setStatus(BossStatusDead);
			//爆炸和音效
			Node *node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
			if (node) {
				this->removeChild(node);
			}
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(sound_2);
			}
			this->boss->setVisible(false);
			this->Gameover();
			//死亡后继续
			Director::getInstance()->replaceScene(TransitionFade::create(0.1f, GameoverScene::createScene()));
		}
	}
}

void Gamescene::handleCharCollidingWithBoss(Boss * boss) {
	//Size visiblesize = Director::getInstance()->getVisibleSize();
	///*Node *node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
	//if (node) {
	//	this->removeChild(node);
	//}*/
	//if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
	//	SimpleAudioEngine::getInstance()->playEffect(sound_2);
	//}
	//TouchCharself->setEnabled(false);
	//this->charself->setStatus(CharStatusDead);
	//this->charself->setHitPoints(charself->getHitPoints() - 1);
	////this->updateStatusBarFighter();
	//if (charself->getHitPoints() <= 0) {
	//	auto gameOverLayer = GameoverScene::createWithScore(score);
	//	auto gameOverScene = Scene::create();
	//	gameOverScene->addChild(gameOverLayer);
	//	Director::getInstance()->replaceScene(TransitionFade::create(0.1, gameOverScene));
	//}
	//else {
	//	if (this->getChildByTag(this->charself->getHitPoints()) && this->getChildByTag(this->charself->getHitPoints())->isVisible()) {
	//		this->getChildByTag(this->charself->getHitPoints())->setVisible(false);
	//	}
	//	this->charself->setSpawnTime(this->getTimer());
	//	this->charself->Spawn();
	//}
}

void Gamescene::handleBulletCollidingWithChar(Char *charself) {
	TouchCharself->setEnabled(false);
	this->charself->setStatus(CharStatusDead);
	this->charself->setHitPoints(charself->getHitPoints() - 1);
	auto nodes = this->getChildren();
	for (const auto & node : nodes) {
		if (node->getTag() == GameSceneNodeBatchTagBulletBoss) {
			//node->runAction(Sequence::create(FadeOut::create(0.2f), CallFunc::create([node] {  node->removeFromParentAndCleanup(true); }), NULL));
			node->setVisible(false);
			node->unscheduleAllCallbacks();
			node->removeFromParentAndCleanup(true);
		}
	}
	if (charself->getHitPoints() <= 0) {
		this->Gameover();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, GameoverScene::createScene()));
	}
	else {
		if (this->getChildByTag(this->charself->getHitPoints()) && this->getChildByTag(this->charself->getHitPoints())->isVisible()) {
			this->getChildByTag(this->charself->getHitPoints())->setVisible(false);
		}
		this->charself->setSpawnTime(this->getTimer());
		this->charself->stopAllActions();
		this->charself->Spawn();
		this->boss->stopAllActions();
	}
	this->unschedule(schedule_selector(Gamescene::shootBulletFromChar));
}

void Gamescene::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	//暂停node
	this->pause();
	for (const auto&node : this->getChildren()) {
		node->pause();
	}

	auto PauseItem = Sprite::createWithSpriteFrameName("Pause.png");
	PauseItem->setPosition(180,320);
	PauseItem->setName("PauseItem");
	this->addChild(PauseItem, 20, 1000);

	//返回主菜单
	auto backNormal = Sprite::createWithSpriteFrameName("Quit.png");
	auto backMenuItem = MenuItemSprite::create(backNormal, backNormal, CC_CALLBACK_1(Gamescene::menuBackCallBack, this));
	//继续游戏菜单
	auto resumeNormal = Sprite::createWithSpriteFrameName("Continue.png");
	auto resumeMenuItem = MenuItemSprite::create(resumeNormal, resumeNormal, CC_CALLBACK_1(Gamescene::menuResumeCallBack, this));

	menu = Menu::create(backMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize_Width / 2, visibleSize_Height / 2));
	this->addChild(menu, 20, 1000);
}

void Gamescene::TimerSelect(float dt) {
	Score += 11;
	ScoreLabel->setString(Utility::to_string(Score));
	GrazeLabel->setString(Utility::to_string(Graze));
	TimeLabel->setString(__String::createWithFormat("%ld",this->getTime()/60)->getCString());
	this->setTime(this->getTime()-1);
	if (this->getTime()==0) {
		this->boss->setHitPoints(0);
		this->handleBulletCollidingWithBoss(boss);
	}
	if (this->boss->getSpawnTime() == -1 && this->boss->getStatus() == BossStatusLive) {
		this->boss->setSpawnTime(0);
		this->setTimer(0);
	}
	if (!TouchCharself->isEnabled() && this->charself->getStatus() == CharStatusLive) {
		TouchCharself->setEnabled(true);
		this->setTimer(0);
		this->schedule(schedule_selector(Gamescene::shootBulletFromChar), 0.1f);
	}
	if (this->boss->isVisible() && boss->getStatus() == BossStatusLive && charself->getStatus() == CharStatusLive) {
		switch (UserDefault::getInstance()->getIntegerForKey("Stage")) {
		case 0:
			this->Stage1_BossBullet();
			break;
		case 1:
			this->Stage2_BossBullet();
			break;
		case 2:
			this->Stage3_BossBullet();
			break;
		case 3:
			this->Stage4_BossBullet();
			break;
		case 4:
			this->Stage5_BossBullet();
			break;
		}
	}
	if (this->boss->getStatus() == BossStatusLive) {
		this->setTimer(this->getTimer() + 1);
	}
	
}

void Gamescene::Gameover() {
	int MaxScore = 0;
	UserDefault::getInstance()->setIntegerForKey("CurrentScore", this->Score);
	switch (UserDefault::getInstance()->getIntegerForKey("Stage", 0)) {
	case 0:
		if (this->Score>UserDefault::getInstance()->getIntegerForKey("Stage1Max", 0)) {
			UserDefault::getInstance()->setIntegerForKey("Stage1Max", this->Score);
		}
		break;
	case 1:
		if (this->Score>UserDefault::getInstance()->getIntegerForKey("Stage2Max", 0)) {
			UserDefault::getInstance()->setIntegerForKey("Stage2Max", this->Score);
		}
		break;
	case 2:
		if (this->Score>UserDefault::getInstance()->getIntegerForKey("Stage3Max", 0)) {
			UserDefault::getInstance()->setIntegerForKey("Stage3Max", this->Score);
		}
		break;
	case 3:
		if (this->Score>UserDefault::getInstance()->getIntegerForKey("Stage4Max", 0)) {
			UserDefault::getInstance()->setIntegerForKey("Stage4Max", this->Score);
		}
		break;
	case 4:
		if (this->Score>UserDefault::getInstance()->getIntegerForKey("Stage5Max", 0)) {
			UserDefault::getInstance()->setIntegerForKey("Stage5Max", this->Score);
		}
		break;
	}
}


void Gamescene::BULLET1() {
	__String * BulletName = __String::createWithFormat("b13_0%d.png", (int)(Utility::getRand(1, 9)));
	Bullet * bullet = Bullet::createWithSpriteFrameName(BulletName->getCString());
	bullet->setPosition(Vec2(Utility::getRand(0, 360), Utility::getRand(500, 640)));
	bullet->setRotation(180); 
	bullet->Velocity(Utility::getRand(100, 200));
	if (this->boss->getStage() == StageOne) {
		bullet->scheduleOnce([bullet, this](float dt) { bullet->BULLET1(dt, bullet->getRotation()); }, 0, "BULLET1");	
	}else {
		float rotation = atan2(charself->getPositionY() - bullet->getPositionY(), charself->getPositionX() - bullet->getPositionX())*RAD_DEG;
		//bullet->setRotation(Utility::getRand(rotation-10, rotation+10), 1);
		bullet->scheduleOnce([bullet, rotation](float dt) { bullet->BULLET1(dt, 90 - Utility::getRand(rotation - 10, rotation + 10)); }, 0, "BULLET1");
	}
	//std::function<void(float)> dr = [bullet, this](float dt) { bullet->BULLET1(dt, this->charself); };
	this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	//bullet->shootBullet();
}
void Gamescene::BULLET2() {
	for (int i = -2; i <= 2; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b5_03.png");
		bullet->setRotation(i * 10 + atan2(charself->getPositionY() - boss->getPositionY(), charself->getPositionX() - boss->getPositionX())*RAD_DEG, 1);
		bullet->setAcceleration(-40);
		bullet->setPosition(boss->getPosition());
		bullet->Velocity(300);
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
		bullet->shootBullet();
	}
}
void Gamescene::BULLET3() {
	for (int i = -180; i < 180; i = i + 15) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b2 (5).png");
		bullet->setRotation(i);
		bullet->setPosition(boss->getPosition());
		bullet->Velocity(150);
		//bullet->Accelerate(Vec2(0, -100));
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
		bullet->shootBullet();
		float rotation = atan2(charself->getPositionY() - bullet->getPositionY(), charself->getPositionX() - bullet->getPositionX())*RAD_DEG;
		bullet->scheduleOnce([bullet, this](float dt) { bullet->BULLET3(dt, charself); },1, "BULLET3");
	}
}
void Gamescene::BULLET4(){
	float rotation = this->getTimer() % 1200 * 6.0f;
	//float t = this->getTimer() / 600;
	for (int i = 0; i < 4; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b3 (3).png");
		bullet->setVisible(true);
		//bullet->setRotation(t * 45 + i * 90);
		bullet->setRotation(i * 90);
		bullet->Velocity(300);
		bullet->setPosition(boss->getPosition() + 50 * Vec2(SIN_DEG(rotation), COS_DEG(rotation)));
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
		bullet->scheduleOnce([bullet](float dt) { bullet->BULLET4(1); }, 0 , "BULLET4");
	}
}
void Gamescene::BULLET5(Vec2 rand) {
	float rotation = this->getTimer() % 120 * 6.0f;
	__String * BulletName = __String::createWithFormat("b10_0%d.png", 7);
	Bullet * bullet = Bullet::createWithSpriteFrameName(BulletName->getCString());
	bullet->setVisible(true);
	bullet->setRotation(rotation);
	bullet->Velocity(200);
	bullet->setPosition(rand + 20 * Vec2(SIN_DEG(rotation), COS_DEG(rotation)));
	this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	//bullet->Accelerate(Vec2(0, -100));
	//bullet->shootBullet();
	//float rotation = atan2(charself->getPositionY() - bullet->getPositionY(), charself->getPositionX() - bullet->getPositionX())*RAD_DEG;
	bullet->scheduleOnce([bullet](float dt) { bullet->scheduleUpdate(); }, (120.0f - this->getTimer() % 120) / 60, "BULLET5");
}

void Gamescene::BULLET6() {
	Vec2 bulletPosition = this->BULLET6_StageTwo_Tri_Position + 28 * Vec2(SIN_DEG(BULLET6_StageTwo_Tri_Rotation), COS_DEG(BULLET6_StageTwo_Tri_Rotation));
	for (int i = 0; i < 3; i++) {
		//__String * BulletName = __String::createWithFormat("b3 (%d).png", i+1);
		Bullet * bullet = Bullet::createWithSpriteFrameName("b3 (6).png");
		bullet->setVisible(true);
		bullet->setRotation(i*120);
		bullet->Velocity(300);
		bullet->setPosition(bulletPosition);
		this->BULLET6_StageTwo_Tri_Position = bullet->getPosition();
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
		bullet->scheduleOnce([bullet](float dt) { bullet->BULLET6(1); }, 0, "BULLET6");
	}
}

void Gamescene::BULLET7() {
	float Rotation = Utility::getRand(-12,12) + 20 * this->getTimer() ;
	__String * BulletName = __String::createWithFormat("b7_0%d.png", (int)Utility::getRand(1, 7));
	Bullet * bullet = Bullet::createWithSpriteFrameName(BulletName->getCString());
	//bullet->setVisible(true);
	bullet->setRotation(Rotation);
	bullet->Velocity(Utility::getRand(150, 300));
	bullet->setPosition(boss->getPosition());
	this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	bullet->shootBullet();
	bullet->scheduleOnce([bullet](float dt) {bullet->unscheduleUpdate();  bullet->BULLET7(1); }, (180.0f - this->getTimer() % 480) / 60, "BULLET7");
}

void Gamescene::BULLET8() {
	float x, y, Rotation;
	for (float i = -2; i <= 2; i = i + 0.1) {
		x = 16 * (sin(i*1.5)) * (sin(i*1.5)) * (sin(i*1.5));
		y = 13 * cos(i*1.5) - 5 * cos(2 * i*1.5) - 2 * cos(3 * i*1.5) - cos(4 * i*1.5);
		Rotation = atan2(y, x)*RAD_DEG;
		Bullet * bullet = Bullet::createWithSpriteFrameName("b11_03.png");
		bullet->setRotation(Rotation, 1);
		bullet->setAccelerate(-20 * Vec2(x, y) * (1.2f - this->getTimer() % 1200 / 300.0f));
		//bullet->setPosition(this->boss->getPosition() + Vec2(10 * x, 10 * y));
		bullet->setPosition(this->boss->getPosition());
		bullet->Velocity( 20 * Vec2(x,y).getLength() * (1.2f - this->getTimer() % 1200 / 300.0f));
		bullet->setVisible(true);
		bullet->setName("BULLET8");
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss); 
		bullet->scheduleUpdate();
		bullet->scheduleOnce([bullet](float dt) {bullet->BULLET8(1); }, 1, "BULLET8");
	}
	//bullet->Velocity(Utility::getRand(150, 300));
	//bullet->shootBullet();
	//bullet->scheduleOnce([bullet](float dt) {CCLOG("NO"); bullet->unscheduleUpdate();  bullet->BULLET7(1); }, (360.0f - this->getTimer() % 800) / 100, "BULLET6");
}

void Gamescene::BULLET9() {
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 24; i++) {
			Bullet * bullet = Bullet::createWithSpriteFrameName("b11_07.png");
			bullet->setVisible(true);
			bullet->setRotation(i * 15 + 90);
			bullet->Velocity(20);
			bullet->setAcceleration(17);
			bullet->setPalstance(150/PI);
			bullet->setPosition(Vec2(k / 2 * 180 + 90, k % 2 * 240 + 280) +  Vec2(SIN_DEG(bullet->getRotation() - 90), COS_DEG(bullet->getRotation() - 90)));
			bullet->shootBullet();
			this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			bullet->scheduleOnce([bullet](float dt) {bullet->setPalstance(0);}, 7.5, "BULLET9");
		}
	}
		//bullet->scheduleOnce([bullet](float dt) { bullet->scheduleUpdate(); }, (200.0f - this->getTimer() % 200) / 100, "BULLET5");
}

void Gamescene::BULLET10() {
	BULLET4_StageTwo_Rotation += 6;
	for (int i = 0; i < 5; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b2 (5).png");
		bullet->setRotation(BULLET4_StageTwo_Rotation+72*i);
		bullet->Velocity(200);
		bullet->setPosition(this->boss->getPosition());
		bullet->setAcceleration(-20);
		bullet->setPalstance(10);
		bullet->shootBullet();
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}

void Gamescene::BULLET11() {
	BULLET3_StageTwo_Rotation += 6;
	for (int i = 0; i < 30; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b11_07.png");
		bullet->setRotation(BULLET3_StageTwo_Rotation + 12 * i);
		bullet->Velocity(100);
		bullet->setPosition(this->boss->getPosition());
		bullet->setAcceleration(-10);
		bullet->setPalstance(30);
		bullet->shootBullet();
		bullet->scheduleOnce([bullet](float dt) {bullet->setPalstance(0); bullet->setAcceleration(0); }, 2, "BULLET11");
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}

void Gamescene::BULLET12() {
	BULLET3_StageTwo_Rotation += 36;
	for (int i = 0; i < 5; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b0 (1).png");
		bullet->setRotation(BULLET3_StageTwo_Rotation + 72 * i);
		bullet->Velocity(100);
		bullet->setPosition(this->boss->getPosition());
		bullet->setAcceleration(-10);
		bullet->shootBullet();
		bullet->scheduleOnce([bullet](float dt) {bullet->setAcceleration(0); }, 2, "BULLET12");
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}

void Gamescene::BULLET13(){ 
	BULLET2_StageTwo_RotationAc += 0.75f;
	BULLET2_StageTwo_Rotation += BULLET2_StageTwo_RotationAc;
	for (int i = 0; i < 4; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b2 (3).png");
		bullet->setRotation(BULLET2_StageTwo_Rotation + 90 * i);
		bullet->Velocity(150);
		bullet->setPosition(this->boss->getPosition());
		bullet->setAcceleration(-10);
		bullet->shootBullet();
		//bullet->scheduleOnce([bullet](float dt) {bullet->setAcceleration(0); }, 2, "BULLET8");
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}

void Gamescene::BULLET14() {
	float Rotation = 30*SIN_DEG(this->getTimer());
	for (int i = -2; i <= 2; i++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b4_01.png");
		bullet->setRotation(Rotation + 45 * i);
		bullet->Velocity(100);
		bullet->setPosition(this->boss->getPosition());
		bullet->setAccelerate(Vec2(0,-25*COS_DEG(bullet->getRotation())));
		bullet->shootBullet();
		CCLOG("%f,%f", bullet->getVelocity().x, bullet->getAccelerate().x);
		bullet->scheduleOnce([bullet](float dt) {bullet->setVelocity(Vec2(0,bullet->getVelocity().y)); bullet->setAccelerate(Vec2(0, -50)); }, 3, "BULLET14");
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}
void Gamescene::BULLET15() {
	for (int k = 1; k <= 4; k++) {
		for (int i = -3; i <= 3; i++) {
			Bullet * bullet = Bullet::createWithSpriteFrameName("b11_07.png");
			bullet->setRotation(180 + 50 * i);
			bullet->Velocity(k * 150);
			bullet->setPosition(this->boss->getPosition());
			bullet->setAcceleration(-k * 150);
			bullet->shootBullet();
			bullet->scheduleOnce([bullet](float dt) {bullet->setRotation(bullet->getRotation() - 120); bullet->Velocity(25);  bullet->setPalstance(160 / PI); bullet->setAcceleration(0); bullet->setAccelerate(Vec2(0, 0)); bullet->scheduleOnce([bullet](float) {bullet->setPalstance(0); bullet->setAcceleration(50); }, 3, "BULLET15_BULLET_2"); }, 1, "BULLET15_BULLET");
			this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			Bullet * bullet2 = Bullet::createWithSpriteFrameName("b11_07.png");
			bullet2->setRotation(180 + 50 * i);
			bullet2->Velocity(k * 150);
			bullet2->setPosition(this->boss->getPosition());
			bullet2->setAcceleration(-k * 150);
			bullet2->shootBullet();
			bullet2->scheduleOnce([bullet2](float dt) {bullet2->setRotation(bullet2->getRotation() + 0); bullet2->Velocity(25); bullet2->setPalstance(160 / PI); bullet2->setAcceleration(0); bullet2->setAccelerate(Vec2(0,0)); bullet2->scheduleOnce([bullet2](float) {bullet2->setPalstance(0); bullet2->setAcceleration(50); }, 3, "BULLET15_BULLET2_2"); }, 1, "BULLET15_BULLET2");
			this->addChild(bullet2, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			Bullet * bullet3 = Bullet::createWithSpriteFrameName("b11_07.png");
			bullet3->setRotation(180 + 50 * i);
			bullet3->Velocity(k * 150);
			bullet3->setPosition(this->boss->getPosition());
			bullet3->setAcceleration(-k * 150);
			bullet3->shootBullet();
			bullet3->scheduleOnce([bullet3](float dt) {bullet3->setRotation(bullet3->getRotation() + 120); bullet3->Velocity(50); bullet3->setPalstance(320 / PI); bullet3->setAcceleration(0); bullet3->setAccelerate(Vec2(0, 0)); bullet3->scheduleOnce([bullet3](float) {bullet3->setPalstance(0); bullet3->setAcceleration(50); }, 3, "BULLET15_BULLET3_2"); }, 1, "BULLET15_BULLET3");
			this->addChild(bullet3, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
		}
	}
}

void Gamescene::BULLET16() {
	for (int k = -2; k <= 2;k++) {
		Vec2 position = boss->getPosition() + Vec2(k*50,0);
		__String * BulletName = __String::createWithFormat("b2 (%d).png", k + 4);
		for (int i = -180; i < 180; i = i + 15) {
			Bullet * bullet = Bullet::createWithSpriteFrameName(BulletName->getCString());
			bullet->setRotation(i);
			bullet->setPosition(position);
			bullet->Velocity(200);
			bullet->setAcceleration(-50);
			this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			bullet->shootBullet();
			bullet->scheduleOnce([bullet, this](float dt) { bullet->BULLET16(dt, charself); }, 2.0f, "BULLET16");
		}
	}
}

void Gamescene::BULLET17() {
	float rotation = Utility::getRand(-60,60);
	for (int k = -1; k <= 1; k++) {
		Bullet * bullet = Bullet::createWithSpriteFrameName("b4_01.png");
		bullet->setRotation(rotation + k * 120);
		bullet->setPosition(boss->getPosition());
		bullet->Velocity(100);
		bullet->shootBullet();
		this->addChild(bullet, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
	}
}

void Gamescene::Stage1_BossBullet() {
	if (this->getTimer() == 0) {
		this->boss->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(75, 520)), DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(285, 520)), DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(180, 490)), NULL)));
	}
	if (this->getTimer() % 15 == 0 && boss->getStage() == StageTwo) {
		this->BULLET1();
	}
	if (this->getTimer() % 600 <= 300 && this->getTimer() % 120 <= 21 && this->getTimer() % 7 == 0) {
		this->BULLET2();
	}
	else if (this->getTimer() % 600 > 300 && this->getTimer() % 120 == 0) {
		this->BULLET3();
	}
}

void Gamescene::Stage2_BossBullet() {
	if (this->getTimer() == 0) {
		this->boss->runAction(MoveTo::create(0.5f, Vec2(180, 400)));
		this->setTimer(-80);
		return;
	}
	else if (this->getTimer() == -29) {
		this->setTimer(0);
	}
	if (this->getTimer() >= 0) {
		if (boss->getStage() == StageOne) {
			//if (this->getTimer() % 800 < 60 && this->getTimer() % 4 == 0) {
			//	this->BULLET4();
			//}//六秒一个圆
			//if (this->getTimer() % 800 >= 400 && this->getTimer() % 800 < 520 && this->getTimer() % 4 == 0) {
			//	if (this->getTimer() % 400 == 0) {
			//		BULLET6_StageTwo_Tri_Rotation = 198;
			//		BULLET6_StageTwo_Tri_Position = this->boss->getPosition() ;
			//	}
			//	if (this->getTimer() % 400 != 0 && this->getTimer() % 24 == 0) {
			//		BULLET6_StageTwo_Tri_Rotation -= 144;
			//	}
			//	this->BULLET6();
			//}//十秒一个五角星
			if (this->getTimer() % 600 == 0) {
				this->BULLET16();
			}
			if (this->getTimer() % 600 >= 240 && this->getTimer() % 10 == 0) {
				this->BULLET17();
			}
		}
		else{
			if ((this->getTimer()) % 5 == 0) {
				this->BULLET13();
			}
		}
		 //if (boss->getStage() == StageTwo && this->getTimer() % 200 <= 100 && this->getTimer() % 5 == 0) {
		 //	if (this->getTimer() % 200 == 0) {
		 //		this->BULLET5_StageTwo_Rotation = Vec2(Utility::getRand(60, 300), Utility::getRand(240, 560));
		 //	}
		 //	this->BULLET5(BULLET5_StageTwo_Rotation);
		 //}//划小圈
	}
}

void Gamescene::Stage3_BossBullet() {
	if (this->boss->getStage() == StageOne) {
		if (this->getTimer() == 0) {
			this->boss->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(75, 520)), DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(285, 520)), DelayTime::create(0.5f), MoveTo::create(1.5f, Vec2(180, 490)), NULL)));
		}
		if (this->getTimer() % 480 <= 180 && this->getTimer() % 1 == 0) {
			this->BULLET7();
		}
		if (this->getTimer() % 480 > 180 && this->getTimer() % 480 <= 300 && (this->getTimer() - 240) % 60 == 0) {
			this->BULLET3();
		}
	}else{
		if (this->getTimer() == 0) {
			BULLET3_StageTwo_Rotation = 0;
		}
		if (this->getTimer() % 60 == 1) {
			this->BULLET11();
		}
		if (this->getTimer() % 90 == 1) {
			this->BULLET12();
		}
	}
		
}

void Gamescene::Stage4_BossBullet() {
	Bullet* Jian = nullptr;
	//心
	if (this->boss->getStage() == StageOne) {
		if (this->getTimer() % 1200 >= 60 && this->getTimer() % 1200 <= 240 && this->getTimer() % 60 == 0) {
			this->BULLET8();
		}
		switch (this->getTimer() % 1200) {
		case 360:
			Jian = Bullet::createWithSpriteFrameName("Jian.png");
			Jian->setPosition(-Jian->getContentSize().height / 2, 300);
			Jian->setVisible(true);
			Jian->setRotation(atan2(boss->getPositionY() - Jian->getPositionY(), boss->getPositionX() - Jian->getPositionX())*RAD_DEG , 1);
			Jian->Velocity(475);
			Jian->setAccelerate(-475 * Vec2(SIN_DEG(Jian->getRotation()), COS_DEG(Jian->getRotation())));
			Jian->setName("Jian");
			Jian->scheduleUpdate();
			this->addChild(Jian, BulletZOrder, GameSceneNodeBatchTagBulletBoss+1); 
			break;
		case 420:
			Jian = (Bullet *)this->getChildByName("Jian");
			if (Jian!=nullptr) {
				Jian->setAccelerate(450 * Vec2(SIN_DEG(Jian->getRotation()), COS_DEG(Jian->getRotation())));
			}
			break;
		case 450:
			Jian = (Bullet *)this->getChildByName("Jian");
			if (Jian != nullptr) {
				Jian->setLocalZOrder(BulletZOrder - 1);
			}
			break;
		case 840:
			auto nodes = this->getChildren();
			for (auto & node : nodes) {
				if (node->getTag() == GameSceneNodeBatchTagBulletBoss) {
					((Bullet *)node)->scheduleUpdate();
					node->scheduleOnce([this, node](int) { ((Bullet *)node)->unscheduleUpdate(); node->runAction(Sequence::create(DelayTime::create(1.0f), FadeOut::create(2.0f), CallFunc::create([this,node] {node->removeFromParentAndCleanup(true);;}), NULL));  }, 3, "BULLET8_3");
				}
			}
			break;
		}
	}
	else {
		if (this->getTimer() == 0) {
			BULLET4_StageTwo_Rotation = 0;
			this->boss->runAction(MoveTo::create(0.5f, Vec2(180, 400)));
			for (int k = 0; k < 4; k++) {
				Sprite *BulletPoint = Sprite::createWithSpriteFrameName("b4_05.png");
				BulletPoint->setPosition(Vec2(k / 2 * 180 + 90, k % 2 * 240 + 280));
				BulletPoint->setTag(GameScene_Game2);
				BulletPoint->runAction(FadeIn::create(0.5f));
				this->addChild(BulletPoint, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			}
			/*Sprite *BulletPoint2 = Sprite::createWithSpriteFrameName("b4_05.png");
			BulletPoint2->setPosition(Vec2((i % 2 + 1) * 90, Game1->getPositionY() + Game1->getContentSize().height));
			BulletPoint2->setTag(GameScene_Game2);
			this->addChild(BulletPoint2, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			Sprite *BulletPoint3 = Sprite::createWithSpriteFrameName("b4_05.png");
			BulletPoint3->setPosition(Vec2((i % 2 + 1) * 90, Game1->getPositionY() + Game1->getContentSize().height));
			BulletPoint3->setTag(GameScene_Game2);
			this->addChild(BulletPoint3, BulletZOrder, GameSceneNodeBatchTagBulletBoss);
			Sprite *BulletPoint4 = Sprite::createWithSpriteFrameName("b4_05.png");
			BulletPoint4->setPosition(Vec2((i % 2 + 1) * 90, Game1->getPositionY() + Game1->getContentSize().height));
			BulletPoint4->setTag(GameScene_Game2);
			this->addChild(BulletPoint4, BulletZOrder, GameSceneNodeBatchTagBulletBoss);*/
		}
		if (this->getTimer() % 600  == 0) {
			this->BULLET9();
		}
		if (this->getTimer() >= 50 && this->getTimer() % 9 == 0) {
			this->BULLET10();
		}
	}
}

void Gamescene::Stage5_BossBullet() {
	if (this->boss->getStage()==StageOne) {
		if ((this->getTimer()) % 15 == 0) {
			this->BULLET14();
		}
		if (this->getTimer() % 120 == 1) {
			this->BULLET12();
		}
	}
	else {
		if (this->getTimer() % 480 == 0) {
			this->BULLET15();
		}
		if (this->getTimer() % 480 > 360 && this->getTimer() % 60 == 1) {
			this->BULLET12();
		}
	}
}