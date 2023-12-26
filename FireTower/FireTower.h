#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class FireTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    FireTower(const cocos2d::Vec2& touchlocation);

    //����������������
    cocos2d::Sprite* createBullet();

    //��������
    void towerUpgrade();
};


#endif // FIRETOWER_H