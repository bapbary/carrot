#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public mapChoose
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//��ͼ������ʼ��(UI���)
    virtual bool ifSafe(cocos2d::Vec2 mousePos);//�жϵ�������Ƿ�Ϊ����
    virtual void selectedPosSet(float mouseLocX, float mouseLocY);//��ѡ��λ�����ã���ͬλ����ϸС���
    virtual void tryAgain(cocos2d::Ref* pSender) override;
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H