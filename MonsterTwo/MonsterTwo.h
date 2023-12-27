#ifndef __MONSTERTWO_H__
#define __MONSTERTWO_H__
#include "cocos2d.h"
#include"GameObject.h"
class MonsterTwo :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer, int mapCatalog);
    static MonsterTwo* create(Carrot* carrotLayer, int mapCatalog);
};
#endif // __MONSTERTWO_H__
