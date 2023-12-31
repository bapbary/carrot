#ifndef SUNFLOWERTOWER_H
#define SUNFLOWERTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class SunFlowerTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    SunFlowerTower(const cocos2d::Vec2& touchLocation);

    //��������
    void towerAttack(const cocos2d::Vec2& targetLocation);

    //�����������Ӳ�����������Ч
    void towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation);

    //��������
    void towerUpgrade();
};

#endif // SUNFLOWERTOWER_H