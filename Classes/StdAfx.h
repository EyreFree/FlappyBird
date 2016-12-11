#ifndef  _STDAFX_H_
#define  _STDAFX_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <E:\cocos2d-x\cocos2d-x-2.2.2\external\Box2D\Box2D.h>
#include "B2Sprite.h"
#include "AppDelegate.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "LoadingScene.h"

#define LOADING_IMG					"Loading.png"

#define GROUND_IMG					"Ground.png"
#define BUTTON_PLAY_IMG_NORMAL		"Button_Play.png"
#define BUTTON_PLAY_IMG_SELECTED	"Button_Play_Push.png"
#define BUTTON_QUIT_IMG_NORMAL		"Button_Quit.png"
#define BUTTON_QUIT_IMG_SELECTED	"Button_Quit_Push.png"
#define TITLE_IMG_FLAPPYBIRD		"Title_FlappyBird.png"
#define TITLE_IMG_EYREFREE			"Title_EyreFree.png"
#define BACKGROUND_IMG_DAY			"Background_1.png"
#define BACKGROUND_IMG_EVE			"Background_2.png"
#define	BIRD_YELLOW_IMG_1			"Bird_1_1.png"
#define	BIRD_YELLOW_IMG_2			"Bird_1_2.png"
#define	BIRD_YELLOW_IMG_3			"Bird_1_3.png"
#define	BIRD_BLUE_IMG_1				"Bird_2_1.png"
#define	BIRD_BLUE_IMG_2				"Bird_2_2.png"
#define	BIRD_BLUE_IMG_3				"Bird_2_3.png"
#define	BIRD_RED_IMG_1				"Bird_3_1.png"
#define	BIRD_RED_IMG_2				"Bird_3_2.png"
#define	BIRD_RED_IMG_3				"Bird_3_3.png"

#define TITLE_IMG_GETREADY			"Title_GetReady.png"
#define TITLE_IMG_GAMEOVER			"Title_GameOver.png"
#define TITLE_IMG_NEW				"New_Record.png"
#define PROMPT_IMG					"Prompt.png"
#define NUMBER_IMG_0				"Num_0.png"
#define NUMBER_IMG_1				"Num_1.png"
#define NUMBER_IMG_2				"Num_2.png"
#define NUMBER_IMG_3				"Num_3.png"
#define NUMBER_IMG_4				"Num_4.png"
#define NUMBER_IMG_5				"Num_5.png"
#define NUMBER_IMG_6				"Num_6.png"
#define NUMBER_IMG_7				"Num_7.png"
#define NUMBER_IMG_8				"Num_8.png"
#define NUMBER_IMG_9				"Num_9.png"
#define BAR_IMG_DOWN				"DownBar.png"
#define BAR_IMG_UP					"UpBar.png"
#define RESULT_BORDER_IMG			"ResultBorder.png"
#define NUMBER_IMG_MINI_0			"Num_Mini_0.png"
#define NUMBER_IMG_MINI_1			"Num_Mini_1.png"
#define NUMBER_IMG_MINI_2			"Num_Mini_2.png"
#define NUMBER_IMG_MINI_3			"Num_Mini_3.png"
#define NUMBER_IMG_MINI_4			"Num_Mini_4.png"
#define NUMBER_IMG_MINI_5			"Num_Mini_5.png"
#define NUMBER_IMG_MINI_6			"Num_Mini_6.png"
#define NUMBER_IMG_MINI_7			"Num_Mini_7.png"
#define NUMBER_IMG_MINI_8			"Num_Mini_8.png"
#define NUMBER_IMG_MINI_9			"Num_Mini_9.png"
#define MEDAL_GOLD_IMG				"GoldMedal.png"

#define MEDAL_SLIVER_IMG			"SliverMedal.png"
#define MUSIC_LOADING				"sfx_welcome.mp3"
#define MUSIC_DIE					"sfx_die.ogg"
#define MUSIC_HIT					"sfx_hit.ogg"
#define MUSIC_POINT					"sfx_point.ogg"
#define MUSIC_SWOOSHING				"sfx_swooshing.ogg"
#define MUSIC_WING					"sfx_wing.ogg"

void PlaySound_Android(char * szSound);

#define	SPEED_BIRD_UP	6.0F		//上升速度
#define SPEED_BAR		1.9F		//管道速度
#define SPEED_GROUND	3.0F

#define	TIME_BIRD		0.018F		//鸟的时间
#define	TIME_GROUND		0.0171F		//地板的时间
#define TIME_BAR		2.2F		//管道出现时间

#define RATIO			48.0F		//比例系数
#define	GRAVITY_WORLD	20.0F		//系统重力
#define	CHANNEL_OFFSET	4			//管道offset_5
#define	CHANNEL_WIDTH	2			//管道width_2
#define PI				3.141592654F

#define TAG_BUTTON_PLAY	1
#define TAG_BUTTON_QUIT	2
#define TAG_BAR_LEFT	3
#define	TAG_BAR_RIGHT	4
#define TAG_GROUND		5

#define userDefault CCUserDefault::sharedUserDefault()

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#define TEST
#endif

#ifdef TEST
#include <atlstr.h>
#endif

#endif