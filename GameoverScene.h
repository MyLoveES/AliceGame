#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"
using namespace cocos2d;
class GameoverScene : public Layer {
public :
	CREATE_FUNC(GameoverScene);
	static cocos2d::Scene* createScene();
	int score;
	bool init();
	void onExit();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent);
};