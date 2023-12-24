#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
static int count;//ȫ�ּ�����

class mapChoose : public cocos2d::Scene
{
public:
    cocos2d::Vec2 towerPos;//����λ��
    cocos2d::Sprite* obstacleTree;//�ϰ���
    cocos2d::Label* goldCoinDisplay;
    int goldCoin = 10000;//���
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼѡ�񳡾���ʼ��
    void returnLast(cocos2d::Ref* pSender);//�ص���һ����
    void flipToNext(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void flipToLast(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void enterMapOne(cocos2d::Ref* pSender);//�����һ����ͼ��
    void enterMapTwo(cocos2d::Ref* pSender);//����ڶ�����ͼ��

    CREATE_FUNC(mapChoose);

};
#endif // MAP_CHOOSE_H
