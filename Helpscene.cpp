#include "Helpscene.h"
#include "HelloWorldScene.h"
bool Helpscene::init() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	if (!BaseLayer::init()) {
		return false;
	}

	auto Title = Label::createWithTTF(Utility::ToUTF8("Help"), "fonts/Chi.ttf", 62.5);
	Title->setColor(Color3B::BLACK);
	Title->setPosition(Vec2(origin.x + visibleSize.width / 2, 500));
	this->addChild(Title, 1);


	auto HelpLabel1 = Label::createWithTTF(Utility::ToUTF8("Help1"), "fonts/Chi.ttf", 25);
	HelpLabel1->setPosition(15,380);
	HelpLabel1->setAnchorPoint(Vec2(0, 1));
	HelpLabel1->enableOutline(Color4B::RED, 1);
	this->addChild(HelpLabel1, 1);
	auto HelpLabel2 = Label::createWithTTF(Utility::ToUTF8("Help2"), "fonts/Chi.ttf", 25);
	HelpLabel2->setPosition(15, 300);
	HelpLabel2->setAnchorPoint(Vec2(0, 1));
	HelpLabel2->enableOutline(Color4B::RED, 1); 
	this->addChild(HelpLabel2, 1);
	auto HelpLabel3 = Label::createWithTTF(Utility::ToUTF8("Help3"), "fonts/Chi.ttf", 25);
	HelpLabel3->setPosition(15, 200);
	HelpLabel3->setAnchorPoint(Vec2(0, 1));
	HelpLabel3->enableOutline(Color4B::RED, 1);
	this->addChild(HelpLabel3, 1);

	return true;
}

Scene *Helpscene::createScene() {
	auto scene = Scene::create();
	auto layer = Helpscene::create();
	scene->addChild(layer);
	return scene;
}
