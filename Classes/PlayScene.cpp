#include "PlayScene.h"

USING_NS_CC;

char * PlayScene::NumberPath[20] = {
		NUMBER_IMG_0, 
		NUMBER_IMG_1, 
		NUMBER_IMG_2, 
		NUMBER_IMG_3, 
		NUMBER_IMG_4, 
		NUMBER_IMG_5, 
		NUMBER_IMG_6, 
		NUMBER_IMG_7, 
		NUMBER_IMG_8, 
		NUMBER_IMG_9,
		NUMBER_IMG_MINI_0,
		NUMBER_IMG_MINI_1,
		NUMBER_IMG_MINI_2,
		NUMBER_IMG_MINI_3,
		NUMBER_IMG_MINI_4,
		NUMBER_IMG_MINI_5,
		NUMBER_IMG_MINI_6,
		NUMBER_IMG_MINI_7,
		NUMBER_IMG_MINI_8,
		NUMBER_IMG_MINI_9
};

CCScene* PlayScene::scene()
{
	CCScene *scene = CCScene::create();
	PlayScene *layer = PlayScene::create();

	scene->addChild(layer);

	return scene;
}

bool PlayScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	bRuning = false;
	bGameOver = false;
	bLiving = true;
	iScore = 0;

	screenSize = CCDirector::sharedDirector()->getVisibleSize();

	initWorld();

	addBackground();
	addBarContainer();
	addBird();

	addGroundContainer();

	addScore();
	addTitle_GetReady();
	addPrompt();

	this->schedule( schedule_selector(PlayScene::clockBird), TIME_BIRD);
	this->schedule( schedule_selector(PlayScene::clockGround), TIME_GROUND);

	setTouchEnabled(true);
	return true;
}


void PlayScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void PlayScene::addBird()
{
	//鸟
	pFlyingBird = B2Sprite::create();
	CCSprite *pBirdTemp = CCSprite::create(BIRD_RED_IMG_2);
	CCSize size = pBirdTemp->getContentSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(screenSize.width / 3 / RATIO, screenSize.height / 2 / RATIO);
	b2Body *birdBody = world->CreateBody(&bodyDef);

	b2PolygonShape birdShape;
	birdShape.SetAsBox(size.width / 2 / RATIO, size.height / 2 / RATIO);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdBody->CreateFixture(&birdFixtureDef);

	pFlyingBird->setPTMRatio(RATIO);
	pFlyingBird->setB2Body(birdBody);

	//动作
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

	ccaFlyingBird = CCRepeatForever::create(seqAction);
	pFlyingBird->runAction(ccaFlyingBird);

	addChild(pFlyingBird);
	removeChild(pBirdTemp);
}

void PlayScene::addBackground()
{
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
}

void PlayScene::addScore()
{
	pSpriteScore = CCSprite::create();
	ScoreToPicture(getScore());
	addChild(pSpriteScore);
}

void PlayScene::ScoreToPicture(int iNum)
{
	pSpriteScore->removeAllChildren();
	
	//计算位数
	int iCount = 0, i = iNum;
	do
	{
		++ iCount;
		i /= 10;
	}
	while(i > 0);
	
	//匹配精灵类
	for(int j = iCount; j > 0; --j)
	{
		int iTarget = iNum % 10;
		iNum /= 10;

		CCSprite * ccsTemp = CCSprite::create(NumberPath[iTarget]);
		CCSize size = ccsTemp->getContentSize();

		if(iCount % 2 == 0)
		{
			ccsTemp->setPosition(ccp(screenSize.width / 2 + (j - (int)(iCount / 2) - 0.5) * size.width, screenSize.height / 6 * 5));
		}
		else
		{
			ccsTemp->setPosition(ccp(screenSize.width / 2 + (j - (int)(iCount / 2) - 1.0) * size.width, screenSize.height / 6 * 5));
		}

		pSpriteScore->addChild(ccsTemp);
	}
}

void PlayScene::addTitle_GetReady()
{
	pSpriteTitle = CCSprite::create(TITLE_IMG_GETREADY);
	pSpriteTitle->setPosition(ccp(screenSize.width / 2, screenSize.height / 3 * 2  + 10));
	addChild(pSpriteTitle);
}

void PlayScene::addPrompt()
{
	pSpritePrompt = CCSprite::create(PROMPT_IMG);
	pSpritePrompt->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - 12));
	addChild(pSpritePrompt);
}

void PlayScene::initWorld()
{
	world = new b2World(b2Vec2(0, -GRAVITY_WORLD));
	world->SetContactListener(this);
}

void PlayScene::update(float dt)
{
	world->Step(dt, 8, 3);
	CCSprite * s;
	for(b2Body *b = world->GetBodyList(); b != NULL; b = b->GetNext())
	{
		
		if(b->GetPosition().x < pFlyingBird->getPositionX() / RATIO)
		{
			if(b->GetPosition().x < -3)
			{
				s = (CCSprite *)b->GetUserData();
				{
					s->removeFromParent();
				}
				world->DestroyBody(b);
			}
			else if(((B2Sprite *)(b->GetUserData()))->getTag() == TAG_BAR_RIGHT)
			{
				((B2Sprite *)(b->GetUserData()))->setTag(TAG_BAR_LEFT);
				++ iScore;
#ifdef TEST
				char strTemp[64] = "";
				itoa(iScore,strTemp,10);
				CString cstrTemp = strTemp;
				OutputDebugString(cstrTemp);
#endif
				if(iScore % 2 == 0)
				{
					ScoreToPicture(getScore());
					PlaySound_Android(MUSIC_POINT);
				}
			}
		}
	}

	CCPoint ccpBird = pFlyingBird->getPosition();
	if(bLiving)
	{
		b2Vec2 fSpeed = pFlyingBird->getB2Body()->GetLinearVelocity();
		pFlyingBird->getB2Body()->SetTransform(b2Vec2(ccpBird.x / RATIO, ccpBird.y / RATIO), fSpeed.y / 5 / 2);
	}
	else
	{
		pFlyingBird->getB2Body()->SetTransform(b2Vec2(ccpBird.x / RATIO, (ccpBird.y - 5) / RATIO), -PI / 2);
	}
}

void PlayScene::clockBird( float dt )
{
	//鸟
	static int iTurn = 7;
	int iTable[] = {-7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6};
	pFlyingBird->setPosition(ccp(screenSize.width / 3, screenSize.height / 2 + iTable[iTurn % 28] + 2));
	++ iTurn;
}

void PlayScene::clockGround( float dt )
{
	//地板
	float iPosX = pGroundContainer->getPositionX();
	if(-336 < iPosX)
	{
		iPosX -= SPEED_GROUND;
		pGroundContainer->setPosition(ccp(iPosX, 0));
	}
	else
	{
		pGroundContainer->setPosition(ccp(0, 0));
	}
}

void PlayScene::addGroundContainer()
{
	pGroundContainer = CCSprite::create();

	//1
	B2Sprite *ground_1 = B2Sprite::create(GROUND_IMG);
	CCSize size = ground_1->getContentSize();

	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position = b2Vec2(size.width / 2 / RATIO, size.height / 3 / RATIO + 0.0416);
	b2Body *groundBody = world->CreateBody(&bDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(size.width / 2 / RATIO, size.height / 2 / RATIO);
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	groundBody->CreateFixture(&groundFixtureDef);

	ground_1->setB2Body(groundBody);
	ground_1->setPTMRatio(RATIO);
	ground_1->setTag(TAG_GROUND);

	pGroundContainer->addChild(ground_1);

	//2
	B2Sprite *ground_2 = B2Sprite::create(GROUND_IMG);

	b2BodyDef bDef_2;
	bDef_2.type = b2_staticBody;
	bDef_2.position = b2Vec2(size.width / 2 / RATIO * 3, size.height / 3 / RATIO + 0.0416);
	b2Body *groundBody_2 = world->CreateBody(&bDef_2);

	b2PolygonShape groundShape_2;
	groundShape_2.SetAsBox(size.width / 2 / RATIO, size.height / 2 / RATIO);
	b2FixtureDef groundFixtureDef_2;
	groundFixtureDef_2.shape = &groundShape_2;
	groundBody_2->CreateFixture(&groundFixtureDef_2);

	ground_2->setB2Body(groundBody_2);
	ground_2->setPTMRatio(RATIO);
	ground_2->setTag(TAG_GROUND);

	pGroundContainer->addChild(ground_2);

	addChild(pGroundContainer);
}


void PlayScene::addBar( float dt )
{
	float offset = -rand() % CHANNEL_OFFSET;

	//down bar
	B2Sprite * down_bar = B2Sprite::create(BAR_IMG_DOWN);
	CCSize down_bar_size = down_bar->getContentSize();

	b2BodyDef down_bar_body_def;
	down_bar_body_def.type = b2_kinematicBody;
	down_bar_body_def.position = b2Vec2(screenSize.width/RATIO+2, down_bar_size.height/RATIO/2+offset);
	down_bar_body_def.linearVelocity = b2Vec2(-SPEED_BAR, 0);
	b2Body * down_bar_body = world->CreateBody(&down_bar_body_def);

	b2PolygonShape down_bar_shape;
	down_bar_shape.SetAsBox(down_bar_size.width/2/RATIO, down_bar_size.height/2/RATIO);
	b2FixtureDef down_bar_fixture_def;

	down_bar_fixture_def.shape = &down_bar_shape;
	down_bar_body->CreateFixture(&down_bar_fixture_def);

	down_bar->setB2Body(down_bar_body);
	down_bar->setPTMRatio(RATIO);
	down_bar->setTag(TAG_BAR_RIGHT);

	pBarContainer->addChild(down_bar);

	//up bar
	B2Sprite * up_bar = B2Sprite::create(BAR_IMG_UP);
	CCSize up_bar_size = up_bar->getContentSize();

	b2BodyDef up_bar_body_def;
	up_bar_body_def.type = b2_kinematicBody;
	up_bar_body_def.position = b2Vec2(screenSize.width/RATIO+2, down_bar_size.height/RATIO+offset+CHANNEL_WIDTH+up_bar_size.height/2/RATIO);
	up_bar_body_def.linearVelocity = b2Vec2(-SPEED_BAR, 0);
	b2Body * up_bar_body = world->CreateBody(&up_bar_body_def);

	b2PolygonShape up_bar_shape;
	up_bar_shape.SetAsBox(up_bar_size.width/2/RATIO, up_bar_size.height/2/RATIO);
	b2FixtureDef up_bar_fixture_def;
	up_bar_fixture_def.shape = &up_bar_shape;
	up_bar_body->CreateFixture(&up_bar_fixture_def);

	up_bar->setB2Body(up_bar_body);
	up_bar->setPTMRatio(RATIO);
	up_bar->setTag(TAG_BAR_RIGHT);

	pBarContainer->addChild(up_bar);
}

////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////

void PlayScene::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool PlayScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!bGameOver)
	{
		PlaySound_Android(MUSIC_WING);
		if(bRuning)
		{
			pFlyingBird->getB2Body()->SetLinearVelocity(b2Vec2(0, SPEED_BIRD_UP));
		}
		else
		{
			startGame();
			pFlyingBird->getB2Body()->SetLinearVelocity(b2Vec2(0, SPEED_BIRD_UP));
			bRuning = true;
		}
	}
	return true;
}

void PlayScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void PlayScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
}

void PlayScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

void PlayScene::addBarContainer()
{
	pBarContainer = CCSprite::create();
	addChild(pBarContainer);
}

void PlayScene::BeginContact( b2Contact* contact )
{
	if(contact->GetFixtureA()->GetBody()->GetUserData() == pFlyingBird || contact->GetFixtureB()->GetBody()->GetUserData() == pFlyingBird)
	{
		stopGame();
		if(((B2Sprite *)(contact->GetFixtureA()->GetBody()->GetUserData()))->getTag() == TAG_GROUND || 
			((B2Sprite *)(contact->GetFixtureB()->GetBody()->GetUserData()))->getTag() == TAG_GROUND)
		{
			PlaySound_Android(MUSIC_HIT);
			killBird();
		}
		else
		{
			PlaySound_Android(MUSIC_HIT);
			PlaySound_Android(MUSIC_DIE);
		}
	}
}

void PlayScene::startGame()
{
	scheduleUpdate();
	schedule(schedule_selector(PlayScene::addBar), TIME_BAR);

	unschedule(schedule_selector(PlayScene::clockBird));

	removeChild(pSpriteTitle);
	removeChild(pSpritePrompt);
}

void PlayScene::stopGame()
{
	if(!bGameOver)
	{
		bGameOver = true;

		unschedule(schedule_selector(PlayScene::addBar));
		unschedule(schedule_selector(PlayScene::clockGround));

		stopBar();

		addTitle_GameOver();

		scheduleOnce(schedule_selector(PlayScene::createMenu), 2);
		scheduleOnce(schedule_selector(PlayScene::stopUpdate), 2);
	}
}

void PlayScene::addTitle_GameOver()
{
	pSpriteTitle = CCSprite::create(TITLE_IMG_GAMEOVER);
	pSpriteTitle->setPosition(ccp(screenSize.width / 2, screenSize.height / 3 * 2 + 10));
	pSpriteScore->removeAllChildren();
	addChild(pSpriteTitle);
}

void PlayScene::addButton()
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

void PlayScene::addResultBoard()
{
	pSpriteResultBorder = CCSprite::create();

	//板子
	CCSprite * pResultBoardImg = CCSprite::create(RESULT_BORDER_IMG);
	pResultBoardImg->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	pSpriteResultBorder->addChild(pResultBoardImg);

	//获取记录
	int iRecord = userDefault->getIntegerForKey("record",0);
	if(iRecord < getScore())
	{
		userDefault->setIntegerForKey("record", getScore());

		CCSprite * pNewImg = CCSprite::create(TITLE_IMG_NEW);
		pNewImg->setPosition(ccp(screenSize.width / 2 + 5, screenSize.height / 2 - 28));
		pSpriteResultBorder->addChild(pNewImg);
	}

	if(getScore() >= iRecord)
	{
		CCSprite * pMedalImg = CCSprite::create(MEDAL_GOLD_IMG);
		pMedalImg->setPosition(ccp(screenSize.width / 2 - 65, screenSize.height / 2 - 7));
		pSpriteResultBorder->addChild(pMedalImg);
	}
	else if(getScore() >= (float)(iRecord / 2.0))
	{
		CCSprite * pMedalImg = CCSprite::create(MEDAL_SLIVER_IMG);
		pMedalImg->setPosition(ccp(screenSize.width / 2 - 65, screenSize.height / 2 - 7));
		pSpriteResultBorder->addChild(pMedalImg);
	}

	//新分数
	ScoreToBorder(getScore(), ccp(screenSize.width / 4 * 3 - 10, screenSize.height / 2 + 13));

	//记录分数
	ScoreToBorder(iRecord, ccp(screenSize.width / 4 * 3 - 10, screenSize.height / 2 - 28));

	PlaySound_Android(MUSIC_SWOOSHING);

	//板子的移动
	pSpriteResultBorder->setPosition(ccp(0, -screenSize.height / 2 - pResultBoardImg->getContentSize().height));
	CCSequence* seqAction = CCSequence::create(
		CCMoveTo::create(0.3,ccp(0, 0)),
		NULL
		);
	pSpriteResultBorder->runAction(seqAction);

	addChild(pSpriteResultBorder);
}

void PlayScene::ScoreToBorder( int iNum, CCPoint ccpPos )
{
	//计算位数
	int iCount = 0, i = iNum;
	do
	{
		++ iCount;
		i /= 10;
	}
	while(i > 0);
	
	//匹配精灵类
	for(int j = iCount; j > 0; --j)
	{
		int iTarget = iNum % 10;
		iNum /= 10;

		CCSprite * ccsTemp = CCSprite::create(NumberPath[iTarget + 10]);
		CCSize size = ccsTemp->getContentSize();

		if(iCount % 2 == 0)
		{
			ccsTemp->setPosition(ccp(ccpPos.x + (j - (int)(iCount / 2) - 0.5) * size.width, ccpPos.y));
		}
		else
		{
			ccsTemp->setPosition(ccp(ccpPos.x + (j - (int)(iCount / 2) - 1.0) * size.width, ccpPos.y));
		}

		pSpriteResultBorder->addChild(ccsTemp);
	}
}

void PlayScene::createMenu( float dt )
{
	addButton();
	addResultBoard();
}

void PlayScene::killBird()
{
	if(bLiving)
	{
		bLiving = false;
		pFlyingBird->stopAction(ccaFlyingBird);
	}
}

void PlayScene::stopBar()
{
	CCSprite * s;
	for(b2Body *b = world->GetBodyList(); b != NULL; b = b->GetNext())
	{
		s = (CCSprite *)b->GetUserData();
		if(TAG_BAR_RIGHT == s->getTag() || TAG_BAR_LEFT == s->getTag())
		{
			b->SetLinearVelocity(b2Vec2(0, 0));
			b->SetActive(false);
		}
	}
}

void PlayScene::stopUpdate( float dt )
{
	unscheduleUpdate();
}

int PlayScene::getScore()
{
	return (iScore / 2);
}
