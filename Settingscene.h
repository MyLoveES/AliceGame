#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
class Settingscene :public BaseLayer {
public:
	CREATE_FUNC(Settingscene);
	static cocos2d::Scene* createScene();
	bool init();
	void menuMusicToggleCallBack(Ref * pSender);
	void menuSoundToggleCallBack(Ref * pSender);
	void menuWudiToggleCallBack(Ref * pSender);
	//添加所需函数即可
};
