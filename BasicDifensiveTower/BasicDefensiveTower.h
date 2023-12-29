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
    void sprite_show(cocos2d::Sprite* sprite);
    //ͼ�������
    void sprite_hide(cocos2d::Sprite* sprite);

    //�����������ж���
    void tower_targetupdate(float dt);

    //���������������
    GameObject* findTarget();

    //��������
    virtual void tower_attack(const cocos2d::Vec2& targetlocation);

    //����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
    void tower_spin(const cocos2d::Vec2& targetlocation);

    //�����������Ӳ�����������Ч
    virtual void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //��������
    virtual void towerUpgrade();

    //�������庯��
    void BasicDefensiveTower::setPhysicsBody(cocos2d::Sprite* Bullet, float value);
protected:
    //��������ľ����ʾ
    cocos2d::Sprite* tower;
    //�������������ʾ
    cocos2d::Sprite* base;
    //����Ŀǰ��������(�Զ�/����)
    GameObject* currenttarget = nullptr;
    //����λ������
    cocos2d::Vec2 towerlocation;
    //��ǰ��������λ������
    cocos2d::Vec2 currenttargetlocation;
    //��������
    std::string towername;
    //�����������
    int category_code;
    //�����ȼ�
    int tower_level;
    //������������
    int tower_attack_number;
    //����������Χ
    int tower_attack_range;
    //���������˺�
    int tower_attack_power;
    //���������ٶ�
    float tower_attack_speed;
    //������������ʱ�䣨��Ի���ƿ�Ƿ�ӹ���
    int tower_sustained_attack_time;
};

#endif // BASICDEFENSIVETOWER_H
