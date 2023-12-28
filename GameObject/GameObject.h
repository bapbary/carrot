#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "cocos2d.h"
#include<vector>
//地图终点、起点
const cocos2d::Vec2 Destination[2] = { cocos2d::Vec2(736, 180),cocos2d::Vec2(890,269) };
const cocos2d::Vec2 Origin[2] = { cocos2d::Vec2(383, 532),cocos2d::Vec2(994,531) };
#define MONSTER 200
#define CARROT 100
#define LIGHTINGBULLET1 30
#define LIGHTINGBULLET2 35
#define LIGHTINGBULLET3 40
#define FIREBULLET1 41
#define FIREBULLET2 52
#define FIREBULLET3 63
#define LEAF1 20
#define LEAF2 25
#define LEAF3 45
#define OBSTACLE 300
const float MonsterOneHealth = 100.f;
const float MonsterTwoHealth = 200.f;
const float MonsterThreeHealth = 500.0f;
const float MonsterOneValue = 100.0f;
const float MonsterTwoValue = 200.0f;
const float MonsterThreeValue = 500.0f;
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
    //添加障碍物
    void addObstaclesInMapOne();
    void addObstaclesInMapTwo();
    //更新血量
    void updateHealthBar(cocos2d::ProgressTimer* healthBar,float initial,float current);
    //接触
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //object位置
    cocos2d::Vec2 objectPosition;
    //生命值
    float currentHealth;//当前
    float initialHealth;//原始
    //金币值
    float coinValue;
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
    void hitMonster(cocos2d::Node* node, float num, float scale, char* filename);
    void hitObstacle(cocos2d::Node* node, float num, float scale, char* filename);
protected:
    Carrot* carrotLayer;
    //物体节点
    cocos2d::Sprite* objectSprite;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//设置帧动画
};
#endif // __GAME_OBJECT_H__
