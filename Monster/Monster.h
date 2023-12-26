#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include<vector>
//第一个地图终点
const cocos2d::Vec2 DestinationOne = cocos2d::Vec2(702, 156);
//#define MONSTER 200
//#define CARROT 100
class Carrot;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init();
    CREATE_FUNC(GameObject);
    //第一张地图路径
    cocos2d::Sequence* MoveWayInMapOne(GameObject *monster);
    //设置血量
    void setHealthBar(cocos2d::Sprite* monster, float current, float initial);
    //添加怪物
    void addMonster(float dt);
    //更新血量
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
    //接触
    //bool onContactBegin(cocos2d::PhysicsContact& contact);
    //更新怪物坐标
    void updateMonsterPositions(float dt);
    //object位置
    cocos2d::Vec2 objectPosition;
    //生命值
    float objectHealthValue;
    //获取物体节点
    cocos2d::Sprite* getSprite();
    cocos2d::Vec2 getCurrentPosition();
    //更新位置函数
    void update(float dt);
    float speed;
protected:
    Carrot* carrotLayer;
    //物体节点
    cocos2d::Sprite* objectSprite;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//设置帧动画
};
class MonsterOne :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer);
    static MonsterOne* create(Carrot* carrotLayer);
};

class MonsterTwo :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer);
    static MonsterTwo* create(Carrot* carrotLayer);
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

#endif // __MONSTER_H__
