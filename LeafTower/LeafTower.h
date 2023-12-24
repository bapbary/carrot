#ifndef LEAFTOWER_H
#define LEAFTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LeafTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    LeafTower(const cocos2d::Vec2& touchlocation);

    //����������������
    cocos2d::Sprite* createBullet();

    //��������
    void towerUpgrade();
};


#endif // LEAFTOWER_H

