#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
static int count;//ȫ�ּ�����

class mapChoose : public cocos2d::Scene
{
public:
    cocos2d::Size visibleSize;//��ͼ�Ŀɼ���С
    cocos2d::Vec2 origin;//��ͼ��ʼ��ʱ�Ŀɼ���С
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
    void returnChoose(cocos2d::Ref* pSender);//�ӵ�ͼ���˳�
    virtual bool ifSafe(cocos2d::Vec2 mousePos) { return 1; };//�жϵ�������Ƿ�Ϊ����
    virtual void selectedPosSet(float mouseLocX, float mouseLocY) { return; };//��ѡ��λ�����ã���ͬλ����ϸС���
    virtual void obstacleDispatch() { return; };
    void fireBottleGenerate(cocos2d::Ref* pSender);//���û���ƿ����
    void leafTowerGenerate(cocos2d::Ref* pSender);//���÷�������
    void lightingTowerGenerate(cocos2d::Ref* pSender);//������ƿ����
    void nullCallBack(cocos2d::Ref* pSender);//�ջص�����
    void upgradeFireTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//ɾ������
    void deleteLightTower(cocos2d::Ref* pSender);//ɾ������
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�����ʼ����֤�����������У�
    cocos2d::Vec2 passPos();//��������λ��

    CREATE_FUNC(mapChoose);

};
#endif // MAP_CHOOSE_H
