#ifndef BASICDEFENSIVETOWER_H
#define BASICDEFENSIVETOWER_H

#include "cocos2d.h"
#include "GameObject.h"
#include "MapChoose.h"

//�����������ࣨ����������scene������������ʱ����ѡ�񸲸�ĳЩ�����ͺ�����
//���Ա���ݰ���ÿ�������Ĳ�����״̬���Լ�һ������Ҫ�ľ��鱾��
//���Ա������������ع��ܵ�ʵ��
class BasicDefensiveTower : public cocos2d::Scene {
public:
    virtual bool init();
    //��ȡ�������鱾��
    cocos2d::Sprite* getTowerSprite();

    //��ȡ�����������鱾��
    cocos2d::Sprite* getBaseSprite();

    //��ȡ��������
    std::string getTowerName();

    //��ȡ����λ������
    cocos2d::Vec2 getTowerLocation();

    //��ȡ�����ȼ�
    int getTowerLevel();

    //ͼ�����ʾ
    void spriteShow(cocos2d::Sprite* sprite);
    //ͼ�������
    void spriteHide(cocos2d::Sprite* sprite);

    //�����������ж���̫������
    void towerTargetUpdate1(float dt);

    //�����������ж�������ƿ��
    void towerTargetUpdate2(float dt);

    //�����������ж���Ҷ������
    void towerTargetUpdate3(float dt);

    //���������������
    GameObject* findTarget();

    //��������
    virtual void towerAttack(const cocos2d::Vec2& targetlocation);

    //����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
    void towerSpin(const cocos2d::Vec2& targetlocation);

    //�����������Ӳ�����������Ч
    virtual void towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //��������
    virtual void towerUpgrade();

    //�������庯��
    void BasicDefensiveTower::setPhysicsBody(cocos2d::Sprite* Bullet, float value);
    void BasicDefensiveTower::setSunFlowerPhysicsBody(cocos2d::Sprite* Bullet, float value);
protected:
    //��������ľ����ʾ
    cocos2d::Sprite* tower;
    //�������������ʾ
    cocos2d::Sprite* base;
    //����Ŀǰ��������(�Զ�/����)
    GameObject* currentTarget = nullptr;
    //����λ������
    cocos2d::Vec2 towerLocation;
    //��ǰ��������λ������
    cocos2d::Vec2 currentTargetLocation;
    //��������
    std::string towerName;
    //�����������
    int categoryCode;
    //�����ȼ�
    int towerLevel;
    //������������
    int towerAttackNumber;
    //����������Χ
    int towerAttackRange;
    //���������˺�
    int towerAttackPower;
    //���������ٶ�
    float towerAttackSpeed;
};

#endif // BASICDEFENSIVETOWER_H