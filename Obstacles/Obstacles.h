#ifndef __OBSTACALES_H__
#define __OBSTACALES_H__
#include "cocos2d.h"
#include"GameObject.h"
class Obstacles :public GameObject
{
public:
    virtual bool init(cocos2d::Vec2 position,float scale, char* filename,int health,int coin);
    static Obstacles* create(cocos2d::Vec2 position, float scale, char* filename, int health,int coin);
};

#endif // __OBSTACALES_H__
