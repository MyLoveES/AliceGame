#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class Home :public cocos2d::Scene {
private:
	std::thread * _loadingAudioThread;
public:
	static cocos2d::Scene* createScene();
	int m_nNumberOfLoaded;
	bool init();
	void moveBackground( float t );
	void loadingTextureCallBack(cocos2d::Texture2D * texture);
	void delayCall( float dt );
	void loadingAudio();
	void onExit();
	CREATE_FUNC(Home);
};
