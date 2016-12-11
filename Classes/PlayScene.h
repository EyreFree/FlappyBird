#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "StdAfx.h"

class PlayScene : public cocos2d::CCLayer,public b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	// TouchesPerformTest1
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void ccTouchCancelled(CCTouch* touch, CCEvent* event);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(PlayScene);

	virtual void update(float dt);
	void clockBird(float dt);
	void clockGround(float dt);
	virtual void BeginContact(b2Contact* contact);
	void createMenu(float dt);

	b2World *world;

	CCSize screenSize;

	B2Sprite *pFlyingBird;
	CCSprite *pBarContainer;
	CCSprite *pGroundContainer;
	CCSprite *pSpriteTitle;
	CCSprite *pSpritePrompt;
	CCSprite *pSpriteScore;
	CCSprite *pSpriteResultBorder;

	CCArray	*ccaItems;
	CCMenu	*menu;

	CCMenuItemImage *ccmiiItem;

	bool bGameOver;
	bool bRuning;
	bool bLiving;

	CCAction *ccaFlyingBird;

	int iScore;

	static char * NumberPath[20];

private:
	void initWorld();

	void addBackground();
	void addBird();
	void addGroundContainer();
	void addBar(float dt);
	void addBarContainer();
	void addScore();
	void addTitle_GetReady();
	void addPrompt();
	void addTitle_GameOver();
	void addButton();
	void addResultBoard();

	void killBird();

	void stopBar();
	void stopUpdate(float dt);
	void ScoreToPicture(int iNum);
	void ScoreToBorder(int iNum, CCPoint ccpPos);

	void startGame();
	void stopGame();

	int getScore();
};

#endif // __HELLOWORLD_SCENE_H__
