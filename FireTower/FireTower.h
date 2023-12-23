#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "cocos2d.h"
#include "BasicDifensiveTower.h"

class FireTower : public BasicDefensiveTower {
public:
    //构造函数：炮塔参数的初始化并显示
    FireTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation);
};


#endif // FIRETOWER_H