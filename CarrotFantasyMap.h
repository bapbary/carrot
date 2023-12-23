/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CARROTFANTASYMAP_SCENE_H__
#define __CARROTFANTASYMAP_SCENE_H__

#include "cocos2d.h"


class sceneCover : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void touchStart(cocos2d::Ref* pSender);//�������ѡ��
    void menuCloseCallback(cocos2d::Ref* pSender);//�˳�����
    CREATE_FUNC(sceneCover);
};

class sceneChoose : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼѡ�񳡾���ʼ��
    void returnLast(cocos2d::Ref* pSender);//�ص���һ����
    void flipToNext(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void flipToLast(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void enterMapOne(cocos2d::Ref* pSender);//�����һ����ͼ��
    CREATE_FUNC(sceneChoose);

};

class mapOne : public sceneChoose
{
    cocos2d::Label* label;
    cocos2d::MenuItemImage* fireBottle;
    cocos2d::EventListenerTouchOneByOne* touchListener;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼ������ʼ��
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    void menuCloseCallback(cocos2d::Ref* pSender);//�˳�����

    CREATE_FUNC(mapOne);

};

//�����������ࣨ����������scene������������ʱ����ѡ�񸲸�ĳЩ�����ͺ�����
//���Ա���ݰ���ÿ�������Ĳ�����״̬���Լ�һ������Ҫ�ľ��鱾��
//���Ա������������ع��ܵ�ʵ��
class BasicDifensiveTower : public cocos2d::Scene {
public:

    //���캯�������������ĳ�ʼ������ʾ
    BasicDifensiveTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation) {
        tower = cocos2d::Sprite::create(filename);
        towerlocation = touchlocation;
        category_code = code;
        tower_level = level;
        //����������ų�ʼ��������������ֵ




        //������������ʾ
        tower->setPosition(touchlocation);
        //����������С
        tower->setScale(10);
        sprite_show(tower);
        //�����龰���ڽ��������֮��һ�䣬�������н��з���
    }

    //��ȡ�������鱾��
    cocos2d::Sprite* BasicDifensiveTower::getTowerSprite() const {
        return tower;
    }

    //ͼ�����ʾ
    void sprite_show(cocos2d::Sprite* sprite) {
        tower->setVisible(true);
    }
    //ͼ�������
    void sprite_hide(cocos2d::Sprite* sprite) {
        tower->setVisible(false);
    }

    //�ж�Ŀ�������ʧ������������



    //�����������ж���
    void tower_targetupdate() {
        // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
        if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
            currenttarget = findTarget();
        }
        //Ŀ��ѡ�����֮����й�������
        tower_attack();
    }

    //���������������
    cocos2d::Sprite* findTarget() {
        //�ڹ���ͼ������������������Ǹ�
        //��returnһ���������return nullptr
    }

    //��������
    void tower_attack() {
        //���ι���Ŀ������һ�������������������������
    }

    //����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
    void tower_spin(const cocos2d::Vec2& targetlocation) {
        //����Ŀ��������Ŀ��->������㣩
        cocos2d::Vec2 direction = towerlocation - targetlocation;
        // ������ת�ĽǶȣ�ʵ�ʵõ����ǻ��ȣ�
        float angle = atan2(direction.y, direction.x);
        // ������ת��Ϊ�Ƕ�
        float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
        // ������ת����
        auto rotateAction = cocos2d::RotateBy::create(0.2f, angleInDegrees);
        // ִ����ת����
        tower->runAction(rotateAction);
    }

    //����������������
    cocos2d::Sprite* createBullet() {
        // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
        cocos2d::Sprite* lightingbullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
        //���ӵ�Ҳ���뵱ǰ������
        this->addChild(lightingbullet);
        //�����ӵ����鱾�����ں����ӵ�������Ч����
        return lightingbullet;
    }

    //�����������Ӳ�����������Ч
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
        //�������Ӳ���ʾ
        bullet->setPosition(towerlocation);
        bullet->setScale(2);
        sprite_show(bullet);
        //Ȼ�������ж���
        auto moveTo = cocos2d::MoveTo::create(2.0f, targetlocation);
        //�����ٶȵ���
        auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
        //ִ�з��в���
        bullet->runAction(moveTo);
        //����Ŀ��λ�ú������������Ч
        tower_hit_target(targetlocation);
        //ɾ���ӵ������������У�
        this->removeChild(bullet);
    }
    //��������ײ��Ŀ��������ݴ����Ч
    void tower_hit_target(const cocos2d::Vec2& targetlocation) {
        // �����������ͽ�����Ӧ�����Ч
        cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
        //�������Ч���볡����
        this->addChild(hit);
        tower->setPosition(targetlocation);
        sprite_show(hit);
        //����sequence�������У���ά�ְ�����Զ�����
        auto delay = cocos2d::DelayTime::create(1.0f); // ��ʱ1��
        auto remove = cocos2d::RemoveSelf::create();
        auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
        //ִ��sequence��������
        hit->runAction(sequence);
    }

    //�ж������Ƿ���Խ�������������
    //�����Ҳ�֪��pzx��������������������

    //��������
    void tower_upgrade() {
        if (tower_level == 1) {
            tower_level++;
            //һϵ����ֵ����

            // ʹ����ͼ���滻��ͼ��
            tower->setTexture("LightingTower_middle.png");
        }
        else if (tower_level == 2) {
            tower_level++;
            //һϵ����ֵ����

            // ʹ����ͼ���滻��ͼ��
            tower->setTexture("LightingTower_big.png");
        }
    }
    //������ɾ��
    void tower_delete() {
        // �Ӹ��ڵ����Ƴ�����
        this->removeChild(tower);
        //���ⲿ���ù�������������ֶ�delete��������ౣ֤��Դ�ͷ�
        // ���ʵ���ʱ��������ɾ������
        /*���磺mytower->tower_delete();
                delete mytower;*/
    }

private:
    //��������ľ����ʾ
    cocos2d::Sprite* tower;
    //����Ŀǰ��������
    cocos2d::Sprite* currenttarget;
    //����λ������
    cocos2d::Vec2 towerlocation;
    //��ǰ��������λ������
    cocos2d::Vec2 currenttargetlocation;
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

//��������������
class Bullet : public cocos2d::Scene {
public:

private:
};

#endif // __CARROTFANTASYMAP_SCENE_H__

