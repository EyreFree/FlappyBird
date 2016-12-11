#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "Stdafx.h"

class LoadingScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void runMenuScene(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(LoadingScene);
};

#endif // __HELLOWORLD_SCENE_H__
