#ifndef __MONSTER_SCENE_H__
#define __MONSTER_SCENE_H__

#include "cocos2d.h"
#include<vector>
//class basic : public cocos2d::Scene
//{
//public:
//    static cocos2d::Scene* createScene();
//    virtual bool init();
//    void menuCloseCallback(cocos2d::Ref* pSender);
//    CREATE_FUNC(basic);
//    void onMouseMove(cocos2d::Event* event);
//};
class Monster : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init();
    CREATE_FUNC(Monster);
    void setHealthBar(cocos2d::Node* monster,float current,float initial);
    cocos2d::Sequence* MoveWayInMapOne();
    void addMonster(float dt);
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
protected:
    cocos2d::Sprite* carrot;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//…Ë÷√÷°∂Øª≠
};
class Carrot : public Monster
{
public:
    float healthValue;
    void decreaseHealth();
    virtual bool init();
    CREATE_FUNC(Carrot);
    //Carrot();
private:
    cocos2d::Sprite* spriteNum;
    cocos2d::Sprite* spriteCarrot;
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
//class MonsterManager
//{
//public:
//    static MonsterManager* getInstance();
//    void addMonster(Monster* monster);
//    std::vector<Monster*> getMonsters();
//private:
//    MonsterManager() {}
//    std::vector<Monster*> monsters;
//};
//MonsterManager* MonsterManager::getInstance()
//{
//    static MonsterManager instance;
//    return&instance;
//}
//void MonsterManager::addMonster(Monster* monster)
//{
//    monsters.push_back(monster);
//}
//std::vector<Monster*> MonsterManager::getMonsters()
//{
//    return monsters;
//}
#endif // __MONSTER_SCENE_H__
