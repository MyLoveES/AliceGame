#include "Home.h"
#include "HelloWorldScene.h"

bool Home::init() {
	if (!Scene::init()) {
		return false;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F1.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F2.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F3.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F4.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F5.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/F6.plist");

	auto LoadingAction = Sprite::createWithSpriteFrameName("F (1).jpg");
	this->addChild(LoadingAction);
	LoadingAction->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	//动画开始
	Animation *animation = Animation::create();
	for (int i = 2; i <= 11;i++) {
		__String * frameName = __String::createWithFormat("F (%d).jpg",i);
		SpriteFrame * spriteframe = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteframe);
	}
	animation->setDelayPerUnit(0.015f);
	animation->setRestoreOriginalFrame(true);
	//缩放
	float scale_Home = (float)size.width / (float)LoadingAction->getContentSize().width;
	LoadingAction->setScale(scale_Home);

	Animate * action = Animate::create(animation);
	LoadingAction->runAction(RepeatForever::create(action));
	//异步加载纹理缓存
	m_nNumberOfLoaded = 0;
	Director::getInstance()->getTextureCache()->addImageAsync("back/Back.png",CC_CALLBACK_1(Home::loadingTextureCallBack,this));
	Director::getInstance()->getTextureCache()->addImageAsync("bullet/bullet.png", CC_CALLBACK_1(Home::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("char/char.png", CC_CALLBACK_1(Home::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("boss/boss.png", CC_CALLBACK_1(Home::loadingTextureCallBack, this));
	_loadingAudioThread = new std::thread(&Home::loadingAudio, this);
	return true;

}

Scene *Home::createScene() {
	return Home::create();
}

void Home::loadingTextureCallBack(cocos2d::Texture2D * texture) {
	switch (m_nNumberOfLoaded++) {
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("back/Back.plist", texture); 
		CCLOG("Back OK");
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet/bullet.plist", texture);
		CCLOG("bullet OK");
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("char/char.plist", texture);
		CCLOG("char OK");
		break;
	case 3:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss/boss.plist", texture);
		CCLOG("boss OK");
		this->schedule(schedule_selector(Home::delayCall), 1.0f, 1.0f, 1.0f);
		break;
	}
}
void Home::delayCall(float dt) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, HelloWorld::createScene()));//动画效果 淡出break;
}

void Home::loadingAudio() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/BackMusic.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Confirm.wav");
	CCLOG("loadingAudio OK");
}

void Home::onExit() {
	Scene::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F1.plist");
	/*SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F2.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F3.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F4.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F5.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Loading/F6.plist");*/
	Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F1.png");
	/*Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F2.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F3.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F4.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F5.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("Loading/F6.png");*/
	this->unschedule(schedule_selector(Home::delayCall));
	CCLOG("Exist OK");
}