#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public sceneChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;
    cocos2d::MenuItemImage* fireBottle;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::Sprite* loadingBar;
    cocos2d::ProgressTimer* loadingBarBlood;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图场景初始化
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//点击结束
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//点击开始（保证监听正常进行）
    void obstacleDispatch();//障碍物设置
    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序
    void towerGenerate(cocos2d::Ref* pSender);//放置炮塔
    cocos2d::Vec2 passPos();
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H

