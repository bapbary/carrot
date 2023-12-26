#ifndef BASICDEFENSIVETOWER_H
#define BASICDEFENSIVETOWER_H

#include "cocos2d.h"
#include "Monster.h"
#include "MapChoose.h"

//�����������ࣨ����������scene������������ʱ����ѡ�񸲸�ĳЩ�����ͺ�����
//���Ա���ݰ���ÿ�������Ĳ�����״̬���Լ�һ������Ҫ�ľ��鱾��
//���Ա������������ع��ܵ�ʵ��
class BasicDefensiveTower : public mapChoose {
public:

    //��ȡ�������鱾��
    cocos2d::Sprite* getTowerSprite();

    //��ȡ��������
    std::string getTowerName();

    //��ȡ����λ������
    cocos2d::Vec2 getTowerLocation();

    //ͼ�����ʾ
    void sprite_show(cocos2d::Sprite* sprite);
    //ͼ�������
    void sprite_hide(cocos2d::Sprite* sprite);

    //�����������ж���
    void tower_targetupdate(float dt);

    //���������������
    GameObject* findTarget();

    //��������
    void tower_attack();

    //����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
    void tower_spin(const cocos2d::Vec2& targetlocation);

    //����������������
    virtual cocos2d::Sprite* createBullet();

    //�����������Ӳ�����������Ч
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation);

    //������virtual��ײ��Ŀ��������ݴ����Ч
    void tower_hit_target(const cocos2d::Vec2& targetlocation);

    //�ж������Ƿ���Խ�������������
    //�����Ҳ�֪��pzx��������������������

    //��������
    virtual void towerUpgrade();
protected:
    //���������ľ����ʾ
    cocos2d::Sprite* tower;
    //����Ŀǰ��������(�Զ�/����)
    GameObject* currenttarget;
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
    //������������  �������趨�Ǵ�1 ħ�����������
    int tower_attack_number;
    //����������Χ
    int tower_attack_range;
    //���������˺�
    int tower_attack_power;
    //���������ٶ�
    int tower_attack_speed;
    //������������ʱ�䣨��Ի���ƿ�Ƿ�ӹ���
    int tower_sustained_attack_time;

    //�������ȹ�������
    //���˸о�������ó�ȫ�ֻ��һЩ��
    //��������������������������������
};

#endif // BASICDEFENSIVETOWER_H