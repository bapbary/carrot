#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "cocos2d.h"
#include "BasicDifensiveTower.h"

class FireTower : public BasicDefensiveTower {
public:
    //���캯�������������ĳ�ʼ������ʾ
    FireTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation);
};


#endif // FIRETOWER_H