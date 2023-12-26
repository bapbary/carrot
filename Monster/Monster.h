#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include<vector>
//��һ����ͼ�յ�
const cocos2d::Vec2 DestinationOne = cocos2d::Vec2(702, 156);
//#define MONSTER 200
//#define CARROT 100
class Carrot;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init();
    CREATE_FUNC(GameObject);
    //��һ�ŵ�ͼ·��
    cocos2d::Sequence* MoveWayInMapOne(GameObject *monster);
    //����Ѫ��
    void setHealthBar(cocos2d::Sprite* monster, float current, float initial);
    //��ӹ���
    void addMonster(float dt);
    //����Ѫ��
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
    //�Ӵ�
    //bool onContactBegin(cocos2d::PhysicsContact& contact);
    //���¹�������
    void updateMonsterPositions(float dt);
    //objectλ��
    cocos2d::Vec2 objectPosition;
    //����ֵ
    float objectHealthValue;
    //��ȡ����ڵ�
    cocos2d::Sprite* getSprite();
    cocos2d::Vec2 getCurrentPosition();
    //����λ�ú���
    void update(float dt);
    float speed;
protected:
    Carrot* carrotLayer;
    //����ڵ�
    cocos2d::Sprite* objectSprite;
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//����֡����
};
class MonsterOne :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer);
    static MonsterOne* create(Carrot* carrotLayer);
};

class MonsterTwo :public GameObject
{
public:
    virtual bool init(Carrot* _carrotLayer);
    static MonsterTwo* create(Carrot* carrotLayer);
};
class Carrot : public GameObject
{
public:
    void decreaseHealth();
    virtual bool init();
    CREATE_FUNC(Carrot);
    Carrot();
private:
    cocos2d::Sprite* spriteNum;
    cocos2d::Sprite* spriteCarrot;
};

#endif // __MONSTER_H__
