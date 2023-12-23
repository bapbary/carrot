#ifndef LIGHTINGTOWER_H
#define LIGHTINGTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LightingTower : public BasicDefensiveTower {
public:
    //构造函数：炮塔参数的初始化并显示
    LightingTower(const cocos2d::Vec2& touchlocation);

    //炮塔产生攻击粒子
    cocos2d::Sprite* createBullet();

    //炮塔升级
    void tower_upgrade();
};


#endif // LIGHTINGTOWER_H
