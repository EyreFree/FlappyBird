#ifndef  __MENU_SCENE_H_
#define  __MENU_SCENE_H_

#include "StdAfx.h"

class MenuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender);

    virtual void update(float dt);
	virtual void clockBird(float dt);

	void addButton();
	void addFlyingBird();

    // implement the "static node()" method manually
    CREATE_FUNC(MenuScene);

private:
	CCSize screenSize;
	CCSprite *pGroundContainer;
	CCSprite *pBirdContainer;
	CCSprite *pFlyingBird;

	CCArray	*ccaItems;
	CCMenu	*menu;

	CCMenuItemImage *ccmiiItem;
};

#endif