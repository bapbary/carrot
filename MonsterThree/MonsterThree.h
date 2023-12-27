#ifndef __MONSTERTHREE_H__
#define __MONSTERTHREE_H__
#include "cocos2d.h"
#include"GameObject.h"
class MonsterThree :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer, int mapCatalog);
    static MonsterThree* create(Carrot* carrotLayer, int mapCatalog);
};

#endif // __MONSTERTHREE_H__
