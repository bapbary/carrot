#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class FireTower : public BasicDefensiveTower {
public:
    //构造函数：炮塔参数的初始化并显示
    FireTower(const cocos2d::Vec2& touchlocation);

    //炮塔产生攻击粒子
    cocos2d::Sprite* createBullet();

    //炮塔升级
    void towerUpgrade();
};


#endif // FIRETOWER_H