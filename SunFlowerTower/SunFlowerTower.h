#ifndef SUNFLOWERTOWER_H
#define SUNFLOWERTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class SunFlowerTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    SunFlowerTower(const cocos2d::Vec2& touchlocation);

    //��������
    void tower_attack(const cocos2d::Vec2& targetlocation);

    //�����������Ӳ�����������Ч
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //��������
    void towerUpgrade();
};

#endif // SUNFLOWERTOWER_H