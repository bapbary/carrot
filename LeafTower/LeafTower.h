#ifndef LEAFTOWER_H
#define LEAFTOWER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"

class LeafTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    LeafTower(const cocos2d::Vec2& touchlocation);

    //��������
    void tower_attack(const cocos2d::Vec2& targetlocation);

    //�����������Ӳ�����������Ч
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //��������
    void towerUpgrade();
};


#endif // LEAFTOWER_H

