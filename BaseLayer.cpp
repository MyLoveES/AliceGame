#include "BaseLayer.h"
bool BaseLayer::init() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();


	if (!Layer::init()) {
		return false;
	}
	//ÊÂ¼þ¼àÌý
	auto listener = EventListenerKeyboard::create();//fanhuijian
	listener->onKeyReleased = CC_CALLBACK_2(BaseLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto Base = Sprite::createWithSpriteFrameName("BackGround.jpg");
	Base->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//float scale_Home = (float)size.width / (float)Base->getContentSize().width;
	//Base->setScale(ContentScaleFactor);    //Ëõ·Å  
	this->addChild(Base, 0);

	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BaseLayer::menuBackCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	closeItem->setTag(10);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	return true;
}

//void BaseLayer::menuBackCallback(Ref* pSender)
//{
//	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY, true)) {
//		SimpleAudioEngine::getInstance()->playEffect(sound_1);
//	}
//	Director::getInstance()->popScene();
//}

void BaseLayer::onEnterTransitionDidFinish(){
	Layer::onEnterTransitionDidFinish();
}

void BaseLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->popScene();
}