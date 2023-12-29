#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class FireTower : public BasicDefensiveTower {
public:
    //构造函数：炮塔参数的初始化并显示
    FireTower(const cocos2d::Vec2& touchlocation);

    //炮塔攻击
    void tower_attack(const cocos2d::Vec2& targetlocation);

    //炮塔发射粒子并产生飞行特效
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //炮塔升级
    void towerUpgrade();
};


#endif // FIRETOWER_H