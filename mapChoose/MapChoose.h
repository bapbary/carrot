#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameObject;
class Obstacles;
USING_NS_CC;
extern int goldCoin;
static int count;//ȫ�ּ�����

class mapChoose : public cocos2d::Layer
{
public:
    cocos2d::Size visibleSize;//��ͼ�Ŀɼ���С
    cocos2d::Vec2 origin;//��ͼ��ʼ��ʱ�Ŀɼ���С
    cocos2d::Label* label;
    cocos2d::Sprite* route;//·��ͼ
    cocos2d::MenuItemImage* sunFlower;//��ƿѡ��ͼ��
    cocos2d::MenuItemImage* leafTower;//����ѡ��ͼ��
    cocos2d::MenuItemImage* lightingTower;//����ƿѡ��ͼ��
    cocos2d::EventListenerTouchOneByOne* touchListener;//��������
    cocos2d::Sprite* selectedPos;//��ѡ��
    cocos2d::Menu* towerMenu = nullptr;//���������˵�
    bool sunFlowerClicked = false;
    std::string towerName;//�����λ�����������ɽ��������֣���û����Ϊ�մ�
    cocos2d::Vec2 towerPos;//����λ��
    cocos2d::Label* goldCoinDisplay;
    Sprite* priorAttackLogo = nullptr;
    Sprite* lastPrior = nullptr;
    static cocos2d::Scene* createScene();
    virtual bool init();//��һ����ͼѡ�񳡾���ʼ��
    void returnLast(cocos2d::Ref* pSender);//�ص���һ����
    void flipToNext(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void flipToLast(cocos2d::Ref* pSender);//��������һ����ͼѡ�񳡾�
    void enterMapOne(cocos2d::Ref* pSender);//�����һ����ͼ��
    void enterMapTwo(cocos2d::Ref* pSender);//����ڶ�����ͼ��
    Scene* mapOneChoose();
    void returnChoose(cocos2d::Ref* pSender);//�ӵ�ͼ���˳�
    void suspend(cocos2d::Ref* pSender);//����Ϸ����ͣ
    virtual void tryAgain(cocos2d::Ref* pSender);//���¿�ʼ��Ϸ
    virtual bool ifSafe(cocos2d::Vec2 mousePos) { return 1; };//�жϵ�������Ƿ�Ϊ����
    virtual void selectedPosSet(float mouseLocX, float mouseLocY) { return; };//��ѡ��λ�����ã���ͬλ����ϸС���
    virtual void obstacleDispatch() { return; };
    void sunFlowerGenerate(cocos2d::Ref* pSender);//���û���ƿ����
    void leafTowerGenerate(cocos2d::Ref* pSender);//���÷�������
    void lightingTowerGenerate(cocos2d::Ref* pSender);//������ƿ����
    void nullCallBack(cocos2d::Ref* pSender);//�ջص�����
    void upgradeSunFlowerTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//ɾ������
    void deleteLightTower(cocos2d::Ref* pSender);//ɾ������
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�����ʼ����֤�����������У�
    GameObject* ifClickedMonster(std::vector<GameObject*> monsters, Vec2 mousePos);
    Obstacles* ifClickedObstacle(std::vector<Obstacles*> obstacles, Vec2 mousePos);
    void tryAgainOne(cocos2d::Ref*);
    void tryAgainTwo(cocos2d::Ref*);
    void gameOverOne();
    void gameOverTwo();
    void gameWinOne();
    void gameWinTwo();
    CREATE_FUNC(mapChoose);
};
#endif // MAP_CHOOSE_H
