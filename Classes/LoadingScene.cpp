#include "Stdafx.h"

USING_NS_CC;

CCScene* LoadingScene::scene()
{
	CCScene *scene = CCScene::create();
	LoadingScene *layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* pSpriteLoading = CCSprite::create(LOADING_IMG);

	CCSize sizeBackground = pSpriteLoading->getContentSize();
	pSpriteLoading->setScaleX(visibleSize.width / sizeBackground.width);
	pSpriteLoading->setScaleY(visibleSize.height / sizeBackground.height);

	pSpriteLoading->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pSpriteLoading, 0);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSIC_LOADING);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSIC_DIE);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSIC_HIT);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSIC_POINT);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSIC_SWOOSHING);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSIC_WING);
#endif

	scheduleOnce(schedule_selector(LoadingScene::runMenuScene), 3);

	return true;
}

void LoadingScene::runMenuScene( float dt )
{
	CCDirector::sharedDirector()->purgeCachedData();

	CCScene * scene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, scene)); 
}
