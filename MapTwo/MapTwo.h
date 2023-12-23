#ifndef MAP_TWO_H
#define MAP_TWO_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapTwo : public mapChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;//·��ͼ
    cocos2d::MenuItemImage* fireBottle;//��ƿѡ��ͼ��
    cocos2d::EventListenerTouchOneByOne* touchListener;//��������
    cocos2d::Sprite* loadingBar;//Ѫ������
    cocos2d::ProgressTimer* loadingBarBlood;//Ѫ�����
    cocos2d::Sprite* selectedPos;//��ѡ��
    cocos2d::Menu* towerMenu = nullptr;//���������˵�
    bool fireBottleClicked = false;
    std::string towerName;//�����λ�����������ɽ��������֣���û����Ϊ�մ�
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼ������ʼ��(UI���)
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; };//�����ʼ����֤�����������У�
    void fireBottleGenerate(cocos2d::Ref* pSender) ;//��������
    cocos2d::Vec2 passPos() {
        return towerPos;
    }//��������λ��
    void upgradeTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//ɾ������
    bool isTouchTower() { return 1; };
    CREATE_FUNC(mapTwo);

};

#endif // MAP_TWO_H


