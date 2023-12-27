#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "cocos2d.h"
#include<vector>
//第一个地图终点
const cocos2d::Vec2 Destination[2] = { cocos2d::Vec2(685, 180),cocos2d::Vec2(80, 416) };
const cocos2d::Vec2 Origin[2] = { cocos2d::Vec2(383, 532),cocos2d::Vec2(928, 473) };
#define MONSTER 200
#define CARROT 100
#define LIGHTINGBULLET 30
class Carrot;
class MonsterManager;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init(int mapCatalog);
    static GameObject* create(int mapCatalog);
    //地图选择
    int mapChoose;
    //第一张地图路径
    cocos2d::Sequence* MoveWayInMapOne(GameObject* monster);
    //第二张地图路径
    cocos2d::Sequence* MoveWayInMapTwo(GameObject* monster);

    //设置血量
    void setHealthBar(cocos2d::Sprite* monster);
    //添加怪物
    void addMonsterInMapOne();
    void addMonsterInMapTwo();
    void addMonsterOne(float dt);
    void addMonsterTwo(float dt);
    void addMonsterThree(float dt);

    //更新血量
    void updateHealthBar(cocos2d::ProgressTimer* healthBar,float initial,float current);
    //接触
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //object位置
    cocos2d::Vec2 objectPosition;
    //生命值
    float currentHealthValue;//当前
    float initialHealthValue;//原始
    //血条
    cocos2d::ProgressTimer* healthBar;
    cocos2d::Sprite* healthBarBG;
    //获取物体节点
    cocos2d::Sprite* getSprite();
    cocos2d::Vec2 getCurrentPosition();
    //更新位置函数
    void update(float dt);
    float speed;
    MonsterManager* monstermanager;
protected:
    Carrot* carrotLayer;
    //物体节点
    cocos2d::Sprite* objectSprite;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//设置帧动画
};
#endif // __GAME_OBJECT_H__
