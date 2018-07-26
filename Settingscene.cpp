#include "Settingscene.h"
#include "HelloWorldScene.h"
bool Settingscene::init() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();
	auto ContentScaleFactor = Director::getInstance()->getContentScaleFactor();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();


	if (!BaseLayer::init()) {
		return false;
	}

	auto Title = Label::createWithTTF(Utility::ToUTF8("Option"), "fonts/Chi.ttf", 62.5);
	Title->setColor(Color3B::BLACK);
	Title->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
	this->addChild(Title, 1);
	//Music
	auto Music = Label::createWithTTF(Utility::ToUTF8("Music"), "fonts/Chi.ttf", 50);
	Music->setColor(Color3B::WHITE);
	Music->setPosition(Vec2(origin.x + visibleSize.width / 2 - Music->getContentSize().width / 2, origin.y + visibleSize.height / 2));
	this->addChild(Music, 1);
	//MusicCloud
	auto SettingMusic = Sprite::createWithSpriteFrameName("Cloud.png");
	SettingMusic->setPosition(Vec2(origin.x + visibleSize.width / 2 + Music->getContentSize().width / 2, Music->getPositionY()));
	this->addChild(SettingMusic, 1);
	//Sound
	auto Sound = Label::createWithTTF(Utility::ToUTF8("Sound"), "fonts/Chi.ttf", 50);
	Sound->setColor(Color3B::WHITE);
	Sound->setPosition(Vec2(origin.x + visibleSize.width / 2 - Sound->getContentSize().width / 2, origin.y + visibleSize.height / 2 - 75));
	this->addChild(Sound, 1);
	//SoundCloud
	auto SettingSound = Sprite::createWithSpriteFrameName("Cloud.png");
	SettingSound->setPosition(Vec2(origin.x + visibleSize.width / 2 + Sound->getContentSize().width / 2, Sound->getPositionY()));
	this->addChild(SettingSound, 1);
	//wudi
	auto wudi = Label::createWithTTF(Utility::ToUTF8("Wudi"), "fonts/Chi.ttf", 50);
	wudi->setColor(Color3B::WHITE);
	wudi->setPosition(Vec2(origin.x + visibleSize.width / 2 - Music->getContentSize().width / 2, origin.y + visibleSize.height / 2 - 150));
	this->addChild(wudi, 1);
	//wudiCloud
	auto Settingwudi = Sprite::createWithSpriteFrameName("Cloud.png");
	Settingwudi->setPosition(Vec2(origin.x + visibleSize.width / 2 + wudi->getContentSize().width / 2, wudi->getPositionY()));
	this->addChild(Settingwudi, 1);
	//添加菜单选项MusicON
	auto MusicON = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OnNormal.png"), Sprite::createWithSpriteFrameName("On.png"), Sprite::createWithSpriteFrameName("NoOn.png"));
	//添加菜单选项MusicOFF
	auto MusicOFF = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OffNormal.png"), Sprite::createWithSpriteFrameName("Off.png"), Sprite::createWithSpriteFrameName("NoOff.png"));
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Settingscene::menuMusicToggleCallBack, this), MusicON, MusicOFF, NULL);
	musicToggleMenuItem->setPosition(SettingMusic->getPositionX() + 2.5, SettingMusic->getPositionY() + SettingMusic->getContentSize().height / 3);
	//添加菜单选项SoundON
	auto SoundON = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OnNormal.png"), Sprite::createWithSpriteFrameName("On.png"), Sprite::createWithSpriteFrameName("NoOn.png"));
	//添加菜单选项SoundOFF
	auto SoundOFF = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OffNormal.png"), Sprite::createWithSpriteFrameName("Off.png"), Sprite::createWithSpriteFrameName("NoOff.png"));
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Settingscene::menuSoundToggleCallBack, this), SoundON, SoundOFF, NULL);
	soundToggleMenuItem->setPosition(SettingSound->getPositionX() + 2.5, SettingSound->getPositionY() + SettingMusic->getContentSize().height / 3);
	
	//添加菜单选项wudi
	auto WidiON = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OnNormal.png"), Sprite::createWithSpriteFrameName("On.png"), Sprite::createWithSpriteFrameName("NoOn.png"));
	//添加菜单选项wudi
	auto WidiOFF = MenuItemSprite::create(Sprite::createWithSpriteFrameName("OffNormal.png"), Sprite::createWithSpriteFrameName("Off.png"), Sprite::createWithSpriteFrameName("NoOff.png"));
	auto WidiToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Settingscene::menuWudiToggleCallBack, this), WidiON, WidiOFF, NULL);
	WidiToggleMenuItem->setPosition(Settingwudi->getPositionX() + 2.5, Settingwudi->getPositionY() + SettingMusic->getContentSize().height / 3);
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(soundToggleMenuItem, musicToggleMenuItem, WidiToggleMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	//menu->alignItemsVerticallyWithPadding(20.0f);
	this->addChild(menu, 2);

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
	musicToggleMenuItem->setSelectedIndex(0);
	}
	else {
	musicToggleMenuItem->setSelectedIndex(1);
	}
	if (defaults->getBoolForKey(SOUND_KEY)){
	soundToggleMenuItem->setSelectedIndex(0);
	}
	else {
	soundToggleMenuItem->setSelectedIndex(1);
	}
	if (defaults->getBoolForKey(Wudi_KEY)) {
	WidiToggleMenuItem->setSelectedIndex(0);
	}
	else {
	WidiToggleMenuItem->setSelectedIndex(1);
	}
	return true;
}
Scene *Settingscene::createScene() {
	auto scene = Scene::create();
	auto layer = Settingscene::create();
	scene->addChild(layer);
	return scene;
}
void Settingscene::menuMusicToggleCallBack(Ref * pSender) {

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY, true)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	if (defaults->getBoolForKey(MUSIC_KEY, true)) {
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}
void Settingscene::menuSoundToggleCallBack(Ref * pSender) {
	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY, true)) {
		defaults->setBoolForKey(SOUND_KEY, false);
	}
	else {
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void Settingscene::menuWudiToggleCallBack(Ref * pSender) {
	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY, true)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	if (!(defaults->getBoolForKey(Wudi_KEY, false))) {
		defaults->setBoolForKey(Wudi_KEY, true);
	}
	else {
		defaults->setBoolForKey(Wudi_KEY, false);
	}
}