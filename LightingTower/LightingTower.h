#ifndef LIGHTINGTOWER_H
#define LIGHTINGTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LightingTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    LightingTower(const cocos2d::Vec2& touchLocation);

    //��������
    void towerAttack(const cocos2d::Vec2& targetLocation);

    //�����������Ӳ�����������Ч
    void towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation);

    //��������
    void towerUpgrade();
};


#endif // LIGHTINGTOWER_H
