#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
class sceneChoose : public cocos2d::Scene
{
public:
    cocos2d::Sprite* selectedPos;
    cocos2d::Vec2 towerPos;
    cocos2d::Sprite* obstacleTree;
    cocos2d::Label* goldCoin;
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼѡ�񳡾���ʼ��
    void returnLast(cocos2d::Ref* pSender);//�ص���һ����
    void flipToNext(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void flipToLast(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void enterMapOne(cocos2d::Ref* pSender);//�����һ����ͼ��
    CREATE_FUNC(sceneChoose);

};
#endif // MAP_CHOOSE_H
