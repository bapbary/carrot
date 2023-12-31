#ifndef LIGHTINGTOWER_H
#define LIGHTINGTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LightingTower : public BasicDefensiveTower {
public:
    //构造函数：炮塔参数的初始化并显示
    LightingTower(const cocos2d::Vec2& touchLocation);

    //炮塔攻击
    void towerAttack(const cocos2d::Vec2& targetLocation);

    //炮塔发射粒子并产生飞行特效
    void towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation);

    //炮塔升级
    void towerUpgrade();
};


#endif // LIGHTINGTOWER_H