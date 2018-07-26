#include "StageChoose.h"
#include "cmath"
USING_NS_CC;

Scene* StageChoose::createScene()
{
	auto scene = Scene::create();
	auto layer = StageChoose::create();
	scene->addChild(layer);
	return scene;
}
bool StageChoose::init()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//°´¼ü¼àÌý
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(StageChoose::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//Chars
	auto layer3D = Layer::create();
	this->addChild(layer3D);
	auto DiBan = Sprite::createWithSpriteFrameName("DiBan.png");
	DiBan->setScale(0.8f);
	DiBan->setPosition3D(Vec3(380,180,-80));
	DiBan->setCameraMask(2);

	LItem = Sprite::createWithSpriteFrameName("LingMeng.png"); LItem->setTag(LID);
	YItem = Sprite::createWithSpriteFrameName("YouMeng.png");  YItem->setTag(YID);
	MItem = Sprite::createWithSpriteFrameName("MoLiSha.png");  MItem->setTag(MID);
	YItem->setCameraMask(2);
	LItem->setCameraMask(2);
	MItem->setCameraMask(2);
	YItem->setPosition3D(Vec3(-90, 315, 0));
	LItem->setPosition3D(Vec3(180, 180, 0));
	MItem->setPosition3D(Vec3(-90, 45, 0));
	UserDefault::getInstance()->setIntegerForKey("CharID", LID);
	UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(LNAME));
	LItem->setRotation3D(Vec3(90, 0, -90));
	MItem->setRotation3D(Vec3(90, 0, -90));
	YItem->setRotation3D(Vec3(90, 0, -90));
	Camera* cameraExample = Camera::createPerspective(50, (GLfloat)size.width / size.height, 1, 1000);
	cameraExample->setCameraFlag(CameraFlag::USER1);
	cameraExample->setPosition3D(Vec3(800, 180, 0));
	cameraExample->lookAt(Vec3(180, 180, -80),Vec3(0,0,1));
	layer3D->addChild(DiBan, 0);
	layer3D->addChild(YItem, ZOrderSecond);
	layer3D->addChild(LItem, ZOrderFirst);
	layer3D->addChild(MItem, ZOrderThird);
	layer3D->addChild(cameraExample);

	//Stage
	auto StageLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("StageLeft.png"), Sprite::createWithSpriteFrameName("StageLeftSelected.png"), Sprite::createWithSpriteFrameName("LeftDisable.png"),CC_CALLBACK_1(StageChoose::PreStage,this));
	auto StageRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("StageRight.png"), Sprite::createWithSpriteFrameName("StageRightSelected.png"), Sprite::createWithSpriteFrameName("RightDisable.png"), CC_CALLBACK_1(StageChoose::NextStage, this));
	StageRight->setPosition(origin.x+visibleSize.width- StageRight->getContentSize().width/2,120);
	StageLeft->setPosition(origin.x + StageRight->getContentSize().width / 2, 120);
	Stage1 = MenuItemLabel::create(Label::createWithTTF("Stage1", "fonts/Chi.ttf", 60), CC_CALLBACK_1(StageChoose::menuItemCallback, this));
	Stage2 = MenuItemLabel::create(Label::createWithTTF("Stage2", "fonts/Chi.ttf", 60), CC_CALLBACK_1(StageChoose::menuItemCallback, this));
	Stage3 = MenuItemLabel::create(Label::createWithTTF("Stage3", "fonts/Chi.ttf", 60), CC_CALLBACK_1(StageChoose::menuItemCallback, this));
	Stage4 = MenuItemLabel::create(Label::createWithTTF("Stage4", "fonts/Chi.ttf", 60), CC_CALLBACK_1(StageChoose::menuItemCallback, this));
	Stage5 = MenuItemLabel::create(Label::createWithTTF("Stage5", "fonts/Chi.ttf", 60), CC_CALLBACK_1(StageChoose::menuItemCallback, this));
	Stage1->setPosition(Vec2(visibleSize.width / 2, 120));
	Stage2->setPosition(Vec2(visibleSize.width / 2, 120));
	Stage3->setPosition(Vec2(visibleSize.width / 2, 120));
	Stage4->setPosition(Vec2(visibleSize.width / 2, 120));
	Stage5->setPosition(Vec2(visibleSize.width / 2, 120));
	Stage1->setTag(Stage1ID);
	Stage2->setTag(Stage2ID);
	Stage3->setTag(Stage3ID);
	Stage4->setTag(Stage4ID);
	Stage5->setTag(Stage5ID);
	Stage1->setVisible(true);
	Stage2->setVisible(false);
	Stage3->setVisible(false);
	Stage4->setVisible(false);
	Stage5->setVisible(false);
	auto menu = Menu::create(StageLeft, StageRight, Stage1, Stage2, Stage3, Stage4, Stage5, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(menuTag);
	this->addChild(menu, 1);

	//×¢²á´¥ÃþÊÂ¼þ¼àÌýÆ÷
	TouchChar = EventListenerTouchOneByOne::create();
	TouchChar->setSwallowTouches(true);
	//´¥ÃþÒÆ¶¯
	TouchChar->onTouchBegan = [](Touch *touch, Event *unused_event) {
		return true;
	};
	TouchChar->onTouchMoved = [this](Touch *touch, Event *unused_event) {
		return true;
	};
	TouchChar->onTouchEnded = [this](Touch *touch, Event *unused_event) {
		if (touch->getStartLocation().x>touch->getLocation().x) {
			this->PreNodeAction();
		}else if (touch->getStartLocation().x<touch->getLocation().x) {
			this->NextNodeAction();
		}
		return true;
	};
	//Ìí¼Ó´¥ÃþÊÂ¼þ¼àÌýÆ÷
	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchChar, this);
	return true;
}

void StageChoose::NextNodeAction() {
	TouchChar->setEnabled(false);
	if (MItem->getPositionY()==left.y) {
		UserDefault::getInstance()->setIntegerForKey("CharID",MID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(MNAME));
		MItem->setLocalZOrder(ZOrderFirst);
		LItem->setLocalZOrder(ZOrderSecond);
		YItem->setLocalZOrder(ZOrderThird);
		MItem->runAction(MoveTo::create(0.3f, middle));
		LItem->runAction(MoveTo::create(0.3f, right));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, left), CallFunc::create([this](void) {TouchChar->setEnabled(true); }), NULL));
	}else if (MItem->getPositionY() == middle.y) {
		UserDefault::getInstance()->setIntegerForKey("CharID", YID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(YNAME));
		MItem->setLocalZOrder(ZOrderSecond);
		LItem->setLocalZOrder(ZOrderThird);
		YItem->setLocalZOrder(ZOrderFirst);
		MItem->runAction(MoveTo::create(0.3f, right));
		LItem->runAction(MoveTo::create(0.3f, left));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, middle), CallFunc::create([this](void) {TouchChar->setEnabled(true); }), NULL));
	}else {
		UserDefault::getInstance()->setIntegerForKey("CharID", LID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(LNAME));
		MItem->setLocalZOrder(ZOrderThird);
		LItem->setLocalZOrder(ZOrderFirst);
		YItem->setLocalZOrder(ZOrderSecond);
		MItem->runAction(MoveTo::create(0.3f, left));
		LItem->runAction(MoveTo::create(0.3f, middle));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, right), CallFunc::create([this](void) {TouchChar->setEnabled(true); }), NULL));
	}
}
void StageChoose::PreNodeAction() {
	TouchChar->setEnabled(false);
	if (MItem->getPositionY() == left.y) {
		UserDefault::getInstance()->setIntegerForKey("CharID", YID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(YNAME));
		MItem->setLocalZOrder(ZOrderThird);
		LItem->setLocalZOrder(ZOrderSecond);
		YItem->setLocalZOrder(ZOrderFirst);
		MItem->runAction(MoveTo::create(0.3f, right));
		LItem->runAction(MoveTo::create(0.3f, left));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, middle), CallFunc::create([this](void) {TouchChar->setEnabled(true); }), NULL));
	}
	else if (MItem->getPositionY() == middle.y) {
		UserDefault::getInstance()->setIntegerForKey("CharID", LID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(LNAME));
		MItem->setLocalZOrder(ZOrderSecond);
		LItem->setLocalZOrder(ZOrderFirst);
		YItem->setLocalZOrder(ZOrderThird);
		MItem->runAction(MoveTo::create(0.3f, left));
		LItem->runAction(MoveTo::create(0.3f, middle));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, right), CallFunc::create([this](void) {TouchChar->setEnabled(true); }), NULL));
	}
	else {
		UserDefault::getInstance()->setIntegerForKey("CharID", MID);
		UserDefault::getInstance()->setStringForKey("CharName", Utility::to_string(MNAME));
		MItem->setLocalZOrder(ZOrderFirst);
		LItem->setLocalZOrder(ZOrderSecond);
		YItem->setLocalZOrder(ZOrderThird);
		MItem->runAction(MoveTo::create(0.3f, middle));
		LItem->runAction(MoveTo::create(0.3f, right));
		YItem->runAction(Sequence::create(MoveTo::create(0.3f, left), CallFunc::create([this](void){TouchChar->setEnabled(true); }), NULL));
	}
}
void StageChoose::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, HelloWorld::createScene()));
}

void StageChoose::NextStage(Ref* pSender){

	LastStageID = SelectedStageID;
	LastStage = (MenuItemLabel*)this->getChildByTag(menuTag)->getChildByTag(LastStageID);
	LastStage->setVisible(false);

	SelectedStageID = (SelectedStageID + 1) % StageCount;
	SelectedStage = (MenuItemLabel*)this->getChildByTag(menuTag)->getChildByTag(SelectedStageID);
	SelectedStage->setVisible(true);
}
void StageChoose::PreStage(Ref* pSender) {

	LastStageID = SelectedStageID;
	LastStage = (MenuItemLabel*)this->getChildByTag(menuTag)->getChildByTag(LastStageID);
	LastStage->setVisible(false);

	SelectedStageID = (SelectedStageID +4) % StageCount;
	SelectedStage = (MenuItemLabel*)this->getChildByTag(menuTag)->getChildByTag(SelectedStageID);
	SelectedStage->setVisible(true);
}
void StageChoose::menuItemCallback(Ref* pSender) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY, true)) {
		UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	MenuItem* newItem = (MenuItem *)pSender;
	switch (newItem->getTag()) {
	case 0:
		UserDefault::getInstance()->setIntegerForKey("Stage", Stage1ID);
		break;
	case 1:
		UserDefault::getInstance()->setIntegerForKey("Stage", Stage2ID);
		break;
	case 2:
		UserDefault::getInstance()->setIntegerForKey("Stage", Stage3ID);
		break;
	case 3:
		UserDefault::getInstance()->setIntegerForKey("Stage", Stage4ID);
		break;
	case 4:
		UserDefault::getInstance()->setIntegerForKey("Stage", Stage5ID);
		break;
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, Gamescene::createScene()));//¶¯»­Ð§¹û µ­³ö
}

void StageChoose::onExit() {
	Layer::onExit();
	this->unscheduleAllCallbacks();
	auto nodes = this->getChildren();
	for (const auto & node : nodes) {
		this->removeChild(node);
	}
}