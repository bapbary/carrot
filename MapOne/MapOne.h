#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public mapChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;//·��ͼ
    cocos2d::MenuItemImage* fireBottle;//��ƿѡ��ͼ��
    cocos2d::EventListenerTouchOneByOne* touchListener;//��������
    cocos2d::Sprite* loadingBar;//Ѫ������
    cocos2d::ProgressTimer* loadingBarBlood;//Ѫ�����
    cocos2d::Sprite* selectedPos;//��ѡ��
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼ������ʼ��(UI���)
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�����ʼ����֤�����������У�
    void obstacleDispatch();//�ϰ�������
    void fireBottleGenerate(cocos2d::Ref* pSender);//��������
    cocos2d::Vec2 passPos();//��������λ��
    void deleteTower(cocos2d::Ref* pSender);//ɾ������
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H

