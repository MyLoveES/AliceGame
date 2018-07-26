#include "HelloWorldScene.h"
#include "Gamescene.h"
#include "Helpscene.h"
#include "StageChoose.h"
#include "Settingscene.h"
#include "GameoverScene.h"
#include "cmath"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();


	auto Title = Label::createWithTTF(Utility::ToUTF8("Title"), "fonts/Chi.ttf", 62);
	Title->setColor(Color3B::BLACK);
	Title->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 200));
	this->addChild(Title, 1);

	//事件监听
	auto listener = EventListenerKeyboard::create();//fanhuijian
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto gl = Label::createWithTTF(Utility::ToUTF8("GameStart"), "fonts/Chi.ttf", 40);
	//gl->enableGlow(Color4B::BLACK);
	gl->enableOutline(Color4B::RED, 1);
	auto GamestartItem = MenuItemLabel::create( gl , CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	GamestartItem->setColor(Color3B::WHITE);
	GamestartItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 68));
	GamestartItem->setTag(11);
	auto hl = Label::createWithTTF(Utility::ToUTF8("Help"), "fonts/Chi.ttf", 40);
	//hl->enableGlow(Color4B::BLACK);
	hl->enableOutline(Color4B::RED, 1);
	auto HelpItem = MenuItemLabel::create(hl, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	HelpItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + -17.5));
	HelpItem->setColor(Color3B::WHITE);
	HelpItem->setTag(12);
	auto sl = Label::createWithTTF(Utility::ToUTF8("Option"), "fonts/Chi.ttf", 40);
	//sl->enableGlow(Color4B::BLACK);
	sl->enableOutline(Color4B::RED, 1);
	auto SettingItem = MenuItemLabel::create(sl, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	SettingItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 102.5));
	SettingItem->setColor(Color3B::WHITE);
	SettingItem->setTag(13);
	auto rl = Label::createWithTTF(Utility::ToUTF8("Result"), "fonts/Chi.ttf", 40);
	//rl->enableGlow(Color4B::BLACK); 
	rl->enableOutline(Color4B::RED, 1);
	auto ResultItem = MenuItemLabel::create(rl, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	ResultItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 187.5));
	ResultItem->setColor(Color3B::WHITE);
	ResultItem->setTag(14);
	// create menu, it's an autorelease object
	auto menu = Menu::create(GamestartItem, HelpItem, SettingItem, ResultItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto back1 = Sprite::createWithSpriteFrameName("BackGround.jpg");
	back1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	float scale_Home = (float)size.width / (float)back1->getContentSize().width;
	//back1->setScale(ContentScaleFactor);    //缩放  
	this->addChild(back1, 0);

	//添加图层

	return true;
}

void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	CCLOG("onEnterTransitionDidFinishHelloworld OK");
	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY, true) && !SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}

void HelloWorld::menuItemCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY, true)) {
		UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	MenuItem* newItem = (MenuItem *)pSender;
	switch (newItem->getTag()) {
	case 11:
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, StageChoose::createScene())); break;//动画效果 淡出
	case 12:
		Director::getInstance()->pushScene(Helpscene::createScene()); break;//动画效果 淡出
	case 13:
		Director::getInstance()->pushScene(Settingscene::createScene()); break;//动画效果 淡出
	case 14:
		Director::getInstance()->replaceScene(GameoverScene::createScene()); break;//动画效果 淡出
	}
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		//EventCustom customEndEvent("game_scene_close_event");
		//_eventDispatcher->dispatchEvent(&customEndEvent);
}
