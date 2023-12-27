#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "cocos2d.h"
#include<vector>
//��һ����ͼ�յ�
const cocos2d::Vec2 Destination[2] = { cocos2d::Vec2(685, 180),cocos2d::Vec2(80, 416) };
const cocos2d::Vec2 Origin[2] = { cocos2d::Vec2(383, 532),cocos2d::Vec2(928, 473) };
#define MONSTER 200
#define CARROT 100
class Carrot;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init(int mapCatalog);
    static GameObject* create(int mapCatalog);
    int mapChoose;
    //��һ�ŵ�ͼ·��
    cocos2d::Sequence* MoveWayInMapOne(GameObject* monster);
    //�ڶ��ŵ�ͼ·��
    cocos2d::Sequence* MoveWayInMapTwo(GameObject* monster);

    //����Ѫ��
    void setHealthBar(cocos2d::Sprite* monster, float current, float initial);
    //��ӹ���
    void addMonsterInMapOne();
    void addMonsterInMapTwo();
    void addMonsterOne(float dt);
    void addMonsterTwo(float dt);
    void addMonsterThree(float dt);

    //����Ѫ��
    void updateHealthBar(cocos2d::ProgressTimer* healthBar, float percentage);
    //�Ӵ�
    bool onContactBegin(cocos2d::PhysicsContact& contact);
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
#endif // __GAME_OBJECT_H__
