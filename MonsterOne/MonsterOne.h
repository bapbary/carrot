#ifndef __MONSTERONE_H__
#define __MONSTERONE_H__
#include "cocos2d.h"
#include"GameObject.h"
class MonsterOne :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer, int mapCatalog);
    static MonsterOne* create(Carrot* carrotLayer, int mapCatalog);
};

#endif // __MONSTERONE_H__
