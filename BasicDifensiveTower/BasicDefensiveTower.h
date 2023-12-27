#ifndef BASICDEFENSIVETOWER_H
#define BASICDEFENSIVETOWER_H

#include "cocos2d.h"
#include "Monster.h"
#include "MapChoose.h"

//定义炮塔基类（本身派生于scene）【后续派生时根据选择覆盖某些参数和函数】
//类成员数据包含每个炮塔的参数和状态，以及一个最重要的精灵本体
//类成员函数是炮塔相关功能的实现
class BasicDefensiveTower : public cocos2d::Scene {
public:
    virtual bool init();
    //获取炮塔精灵本身
    cocos2d::Sprite* getTowerSprite();

    //获取炮塔名字
    std::string getTowerName();

    //获取炮塔位置坐标
    cocos2d::Vec2 getTowerLocation();

    //图标的显示
    void sprite_show(cocos2d::Sprite* sprite);
    //图标的隐藏
    void sprite_hide(cocos2d::Sprite* sprite);

    //炮塔更新索敌对象
    void tower_targetupdate(float dt);

    //炮塔最近距离索敌
    GameObject* findTarget();

    //炮塔攻击
    void tower_attack(const cocos2d::Vec2& targetlocation);

    //炮塔转动（参数为当前攻击目标的所处的位置）
    void tower_spin(const cocos2d::Vec2& targetlocation);

    //炮塔产生攻击粒子
    virtual cocos2d::Sprite* createBullet();

    //炮塔发射粒子并产生飞行特效
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //炮塔粒virtual子撞击目标产生短暂打击特效
    void tower_hit_target(const cocos2d::Vec2& targetlocation);

    //判断炮塔是否可以进行升级并产生
    //（？我不知道pzx这个函数可以做这个不）

    //炮塔升级
    virtual void towerUpgrade();
protected:
    //炮塔本身的精灵表示
    cocos2d::Sprite* tower;
    //炮塔目前攻击对象(自动/怪物)
    GameObject* currenttarget = nullptr;
    //炮塔位置坐标
    cocos2d::Vec2 towerlocation;
    //当前攻击对象位置坐标
    cocos2d::Vec2 currenttargetlocation;
    //炮塔名字
    std::string towername;
    //炮塔种类代号
    int category_code;
    //炮塔等级
    int tower_level;
    //炮塔攻击数量  （风扇设定是打1 魔法球会增长）
    int tower_attack_number;
    //炮塔攻击范围
    int tower_attack_range;
    //炮塔攻击伤害
    int tower_attack_power;
    //炮塔攻击速度
    float tower_attack_speed;
    //炮塔持续攻击时间（针对火焰瓶是否加攻）
    int tower_sustained_attack_time;

    //炮塔优先攻击对象
    //个人感觉这个设置成全局会好一些？
    //。。。。。。。。。。。。。。。。
};

#endif // BASICDEFENSIVETOWER_H
