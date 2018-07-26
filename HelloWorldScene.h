#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "SystemHeader.h"
typedef enum {
	GamestartItem, HelpItem, SettingItem
}ActionType;

class HelloWorld : Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    // a selector callback
    void menuItemCallback(cocos2d::Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
