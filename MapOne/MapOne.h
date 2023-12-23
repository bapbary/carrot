#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public sceneChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;
    cocos2d::MenuItemImage* fireBottle;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::Sprite* loadingBar;
    cocos2d::ProgressTimer* loadingBarBlood;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼ������ʼ��
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�����ʼ����֤�����������У�
    void obstacleDispatch();//�ϰ�������
    void menuCloseCallback(cocos2d::Ref* pSender);//�˳�����
    void towerGenerate(cocos2d::Ref* pSender);//��������
    cocos2d::Vec2 passPos();
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H

