#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"
using namespace cocos2d;
class BaseLayer :public Layer {
public:
	virtual bool init();
	void  menuBackCallback(cocos2d::Ref* pSender);
	void  onEnterTransitionDidFinish();
	void  onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent);
	CREATE_FUNC(BaseLayer);
};
