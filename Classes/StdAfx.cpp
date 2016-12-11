#include "StdAfx.h"


void PlaySound_Android(char * szSound)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(szSound);
}
