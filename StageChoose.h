#pragma once
#include "SystemHeader.h"
#include "Gamescene.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"

class StageChoose : public Layer
{
	MenuItemLabel* Stage1, *Stage2,* Stage3, *Stage4, *Stage5, * SelectedStage, *LastStage;
	int StageCount = 5, SelectedStageID = Stage1ID, LastStageID,menuTag=636;
	EventListenerTouchOneByOne *TouchChar;
	EventListenerTouchOneByOne *TouchStage;
	Sprite * YItem;
	Sprite * LItem;
	Sprite * MItem;
	Vec2 left = Vec2(-90, 45);
	Vec2 middle = Vec2(180, 180);
	Vec2 right = Vec2(-90, 315);
public:
	int ZOrderFirst = 12, ZOrderSecond = 11, ZOrderThird = 11;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void onExit();
	//virtual void onEnterTransitionDidFinish();
	// a selector callback
	void menuItemCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(StageChoose);
	//void setCharsPosition(const cocos2d::Vec2& newPosition);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent);
	void NextNodeAction();
	void PreNodeAction();
	void NextStage(Ref* pSender);
	void PreStage(Ref* pSender);
};

