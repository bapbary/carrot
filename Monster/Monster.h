#ifndef __BASIC_SCENE_H__
#define __BASIC_SCENE_H__

#include "cocos2d.h"

class basic : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(basic);
    void onMouseMove(cocos2d::Event* event);
};
class Monster : public cocos2d::Node
{
public:
    virtual bool init();
    CREATE_FUNC(Monster);
    void setHealthBar(cocos2d::Node* monster,float current,float initial);
    cocos2d::Sequence* MoveWayInMapOne();
    void addMonster(float dt);
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
protected:
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//…Ë÷√÷°∂Øª≠
};
class Carrot : public Monster
{
public:
    float InitialHealthValue = 10.0f;
    virtual bool init();
    CREATE_FUNC(Carrot);
};

class MonsterOne :public Monster
{
public:
    float InitialHealthValue = 100.0f;
    virtual bool init();
    CREATE_FUNC(MonsterOne);
};
class MonsterTwo :public Monster
{
public:
    float InitialHealthValue = 200.0f;
    virtual bool init();
    CREATE_FUNC(MonsterTwo);
};
#endif // __BASIC_SCENE_H__
