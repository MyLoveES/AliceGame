#include "GameoverScene.h"
#include "HelloWorldScene.h" 
bool GameoverScene::init() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	if (!Layer::init()) {
		return false;
	}

	auto BackGround = Sprite::createWithSpriteFrameName("BackGround.jpg");
	BackGround->setAnchorPoint(Vec2::ZERO);
	BackGround->setPosition(Vec2(origin.x, origin.y));
	this->addChild(BackGround, 0);

	

	auto CurrentLabel = Label::createWithTTF(Utility::ToUTF8("Current"), "fonts/Chi.ttf", 50);
	CurrentLabel->setPosition(180, 540);
	CurrentLabel->setColor(Color3B::RED);
	CurrentLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(CurrentLabel, 0);

	auto StageLabel = Label::createWithTTF(__String::createWithFormat("Stage%d:%8d", 1+UserDefault::getInstance()->getIntegerForKey("Stage"), UserDefault::getInstance()->getIntegerForKey("CurrentScore", 0))->getCString(), "fonts/Chi.ttf", 50);
	StageLabel->setPosition(180, 480);
	StageLabel->setColor(Color3B::BLACK);
	StageLabel->enableGlow(Color4B::WHITE);
	//StageLabel->enableOutline(Color4B::WHITE, 2);
	this->addChild(StageLabel, 0);

	auto HistoryLabel = Label::createWithTTF(Utility::ToUTF8("History"), "fonts/Chi.ttf", 50);
	HistoryLabel->setPosition(180, 390);
	HistoryLabel->setColor(Color3B::RED);
	HistoryLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(HistoryLabel, 0);

	for (int i = 1; i < 6; i++) {
		auto StageLabel = Label::createWithTTF(__String::createWithFormat("Stage%d:%8d", i, UserDefault::getInstance()->getIntegerForKey(__String::createWithFormat("Stage%dMax", i)->getCString(), 0))->getCString(), "fonts/Chi.ttf", 40);
		StageLabel->setPosition(180, 390-i*60);
		StageLabel->setColor(Color3B::BLACK);
		StageLabel->enableGlow(Color4B::WHITE);
		//StageLabel->enableOutline(Color4B::WHITE, 2);
		this->addChild(StageLabel, 0);
	}


	//°´¼ü¼àÌý
	auto listener = EventListenerKeyboard::create();//fanhuijian
	listener->onKeyReleased = CC_CALLBACK_2(GameoverScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void GameoverScene::onExit() {
	Layer::onExit();
}

void GameoverScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

Scene *GameoverScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameoverScene::create();
	scene->addChild(layer);
	return scene;
}
