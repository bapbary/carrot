#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public mapChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;//·��ͼ
    cocos2d::MenuItemImage* fireBottle;//��ƿѡ��ͼ��
    cocos2d::MenuItemImage* leafTower;//����ѡ��ͼ��
    cocos2d::MenuItemImage* lightingTower;//����ƿѡ��ͼ��
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
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�����ʼ����֤�����������У�
    void obstacleDispatch();//�ϰ�������
    void fireBottleGenerate(cocos2d::Ref* pSender);//���û���ƿ����
    void leafTowerGenerate(cocos2d::Ref* pSender);//���÷�������
    void lightingTowerGenerate(cocos2d::Ref* pSender);//������ƿ����
    void fireBottleCannotGenerate(cocos2d::Ref* pSender);//���û���ƿ����
    void leafTowerCannotGenerate(cocos2d::Ref* pSender);//���÷�������
    void lightingTowerCannotGenerate(cocos2d::Ref* pSender);//������ƿ����
    cocos2d::Vec2 passPos(){
        return towerPos;
    }//��������λ��
    void upgradeFireTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//ɾ������
    void deleteLightTower(cocos2d::Ref* pSender);//ɾ������

    bool isTouchTower();
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H

