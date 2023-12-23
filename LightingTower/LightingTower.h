#ifndef LIGHTINGTOWER_H
#define LIGHTINGTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LightingTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    LightingTower(const cocos2d::Vec2& touchlocation);

    //����������������
    cocos2d::Sprite* createBullet();

    //��������
    void tower_upgrade();
};


#endif // LIGHTINGTOWER_H
