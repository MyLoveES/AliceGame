#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
using namespace cocos2d;
class Helpscene :public BaseLayer {
public:
	CREATE_FUNC(Helpscene);
	static cocos2d::Scene* createScene();
	bool init();
	//添加所需函数即可
};
