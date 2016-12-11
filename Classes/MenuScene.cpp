#include "Stdafx.h"

USING_NS_CC;

CCScene* MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	screenSize = CCDirector::sharedDirector()->getVisibleSize();

	//背景图
	srand(time(0));

	CCSprite* pSpriteBackground;
	if(0 == (rand() % 2))
	{
		pSpriteBackground = CCSprite::create(BACKGROUND_IMG_DAY);
	}
	else
	{
		pSpriteBackground = CCSprite::create(BACKGROUND_IMG_EVE);
	}
	CCSize sizeBackground = pSpriteBackground->getContentSize();
	pSpriteBackground->setScaleX(screenSize.width / sizeBackground.width);
	pSpriteBackground->setScaleY(screenSize.height / sizeBackground.height);
	pSpriteBackground->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	addChild(pSpriteBackground);

	//标题
	CCSprite* pSpriteTitle = CCSprite::create(TITLE_IMG_FLAPPYBIRD);
	pSpriteTitle->setPosition(ccp(screenSize.width / 2, screenSize.height / 3 * 2));
	addChild(pSpriteTitle);

	//地板
	pGroundContainer = CCSprite::create();

	CCSprite *pSpriteGround_1 = CCSprite::create(GROUND_IMG);
	CCSize sizeGround = pSpriteGround_1->getContentSize();
	pSpriteGround_1->setPosition(ccp(sizeGround.width / 2, screenSize.height / 12));
	pGroundContainer->addChild(pSpriteGround_1);

	CCSprite *pSpriteGround_2 = CCSprite::create(GROUND_IMG);
	pSpriteGround_2->setPosition(ccp(sizeGround.width / 2 * 3, screenSize.height / 12));
	pGroundContainer->addChild(pSpriteGround_2);
	
	addChild(pGroundContainer);

	//EyreFree
	CCSprite* pSpriteTitleEyreFree = CCSprite::create(TITLE_IMG_EYREFREE);
	pSpriteTitleEyreFree->setPosition(ccp(sizeGround.width / 2, screenSize.height / 7));
	addChild(pSpriteTitleEyreFree);

	addButton();
	addFlyingBird();

	addChild(pBirdContainer);

	scheduleUpdate();
	this->schedule( schedule_selector(MenuScene::clockBird), 0.018);

	return true;
}

void MenuScene::addButton()
{
	ccaItems = CCArray::create();

	ccmiiItem = CCMenuItemImage::create(BUTTON_PLAY_IMG_NORMAL, BUTTON_PLAY_IMG_SELECTED, this, menu_selector(MenuScene::menuCallback));
	ccmiiItem->setPosition(ccp(screenSize.width / 2 - ccmiiItem->getContentSize().width / 3 * 1.9, screenSize.height / 3.85));
	ccmiiItem->setTag(TAG_BUTTON_PLAY);
	ccaItems->addObject(ccmiiItem);

	ccmiiItem = CCMenuItemImage::create(BUTTON_QUIT_IMG_NORMAL, BUTTON_QUIT_IMG_SELECTED, this, menu_selector(MenuScene::menuCallback));
	ccmiiItem->setPosition(ccp(screenSize.width / 2 + ccmiiItem->getContentSize().width / 3 * 1.9, screenSize.height / 3.85));
	ccmiiItem->setTag(TAG_BUTTON_QUIT);
	ccaItems->addObject(ccmiiItem);

	menu = CCMenu::createWithArray(ccaItems);
	menu->setPosition(ccp(0,0));

	this->addChild(menu);
}


void MenuScene::update( float dt )
{
	//地板
	float iPosX = pGroundContainer->getPositionX();
	if(-336 < iPosX)
	{
		iPosX -= 3;
		pGroundContainer->setPosition(ccp(iPosX, 0));
	}
	else
	{
		pGroundContainer->setPosition(ccp(0, 0));
	}
}


void MenuScene::clockBird( float dt )
{
	//鸟
	static int iTurn = 7;
	int iTable[] = {-7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6};
	pBirdContainer->setPosition(ccp(0, iTable[iTurn % 28]));
	++ iTurn;
}


void MenuScene::menuCallback(CCObject* pSender)
{
	PlaySound_Android(MUSIC_SWOOSHING);

	CCMenuItemImage* ccmiiItem = (CCMenuItemImage*)pSender;
	switch(ccmiiItem->getTag())
	{
	case TAG_BUTTON_PLAY:
		{
			CCDirector::sharedDirector()->purgeCachedData();

			CCScene * scene = PlayScene::scene();  
			CCDirector::sharedDirector()->replaceScene((CCTransitionCrossFade::create(0.5, scene)));
		}
		break;
	case TAG_BUTTON_QUIT:
#if		(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
		CCDirector::sharedDirector()->end();
#if		(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
		break;
	}
}

void MenuScene::addFlyingBird()
{
	pBirdContainer = CCSprite::create();
	pFlyingBird = CCSprite::create();
	pFlyingBird->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));

	CCAnimation* pAnimation = CCAnimation::create();

	switch((int)(rand() % 3))
	{
	case 0:
		pAnimation->addSpriteFrameWithFileName(BIRD_YELLOW_IMG_1);
		pAnimation->addSpriteFrameWithFileName(BIRD_YELLOW_IMG_2);
		pAnimation->addSpriteFrameWithFileName(BIRD_YELLOW_IMG_3);
		break;
	case 1:
		pAnimation->addSpriteFrameWithFileName(BIRD_BLUE_IMG_1);
		pAnimation->addSpriteFrameWithFileName(BIRD_BLUE_IMG_2);
		pAnimation->addSpriteFrameWithFileName(BIRD_BLUE_IMG_3);
		break;
	case 2:
		pAnimation->addSpriteFrameWithFileName(BIRD_RED_IMG_1);
		pAnimation->addSpriteFrameWithFileName(BIRD_RED_IMG_2);
		pAnimation->addSpriteFrameWithFileName(BIRD_RED_IMG_3);
		break;
	}

	//每帧停留的时间
	pAnimation->setDelayPerUnit(0.1f);

	//动画播放完成后是否返回到原始帧
	pAnimation->setRestoreOriginalFrame(false);
	CCSequence* seqAction = CCSequence::create(
		CCAnimate::create(pAnimation),
		NULL
		);
	pFlyingBird->runAction(CCRepeatForever::create(seqAction));
	pBirdContainer->addChild(pFlyingBird);
}