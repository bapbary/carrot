#pragma once
#ifndef __GAMEOBJECT_SCENE_H__
#define __GAMEOBJECT_SCENE_H__

#include "cocos2d.h"
#include<vector>
class Carrot;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init();
    CREATE_FUNC(GameObject);
    void setHealthBar(cocos2d::Node* monster, float current, float initial);
    cocos2d::Sequence* MoveWayInMapOne();
    void addMonster(float dt);
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void updateMonsterPositions(float dt);
    cocos2d::Vector<cocos2d::Sprite*> monster;
    cocos2d::Vec2 objectPosition;
    float objectHealthValue;
    cocos2d::Sprite* objectSprite;
    cocos2d::Sprite* getSprite();
    //获取炮塔位置坐标
    cocos2d::Vec2 getCurrentPosition();
protected:
    Carrot* carrotLayer;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//设置帧动画
};

class Carrot : public GameObject
{
public:
    void decreaseHealth();
    virtual bool init();
    CREATE_FUNC(Carrot);
    Carrot();
private:
    cocos2d::Sprite* spriteNum;
    cocos2d::Sprite* spriteCarrot;
};

class MonsterOne :public GameObject
{
public:
    void update(float dt);
    float speed;
    virtual bool init();
    CREATE_FUNC(MonsterOne);
};
class MonsterTwo :public GameObject
{
public:
    virtual bool init();
    CREATE_FUNC(MonsterTwo);
};

#endif // __GAMEOBJECT_SCENE_H__
