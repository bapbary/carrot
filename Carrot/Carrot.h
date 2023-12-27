#ifndef __CARROT_H__
#define __CARROT_H__
#include "cocos2d.h"
#include"GameObject.h"
class Carrot : public GameObject
{
public:
    void decreaseHealth();
    virtual bool init(int mapCatalog);
    static Carrot* create(int mapCatalog);
    Carrot();
private:
    cocos2d::Sprite* spriteNum;
    cocos2d::Sprite* spriteCarrot;
};

#endif // __CARROT_H__
