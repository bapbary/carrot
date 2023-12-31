#ifndef COVER_H
#define COVER_H

#include "cocos2d.h"
#include"MapChoose.h"
#include "SimpleAudioEngine.h"

class sceneCover : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void touchStart(cocos2d::Ref* pSender);//????¡¤???????
    void menuCloseCallback(cocos2d::Ref* pSender);//???????¨°
    CREATE_FUNC(sceneCover);
};
#endif // COVER_H