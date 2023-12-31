#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MapChoose.h"
#include<vector>
//��ͼ�յ㡢���
const cocos2d::Vec2 Destination[2] = { cocos2d::Vec2(736, 180),cocos2d::Vec2(890,269) };
const cocos2d::Vec2 Origin[2] = { cocos2d::Vec2(383, 532),cocos2d::Vec2(994,531) };
const int  MONSTER = 200;
const int  CARROT = 100;
const int  LIGHTINGBULLET1 = 3;
const int  LIGHTINGBULLET2 = 6;
const int  LIGHTINGBULLET3 = 9;
const int  SUNFLOWERBULLET1 = 10;
const int  SUNFLOWERBULLET2 = 15;
const int  SUNFLOWERBULLET3 = 20;
const int  LEAFBULLET1 = 4;
const int  LEAFBULLET2 = 8;
const int  LEAFBULLET3 = 12;
const int  OBSTACLE = 300;
const int MonsterOneHealth = 100;
const int MonsterTwoHealth = 200;
const int MonsterThreeHealth = 300;
const int MonsterOneValue = 50;
const int MonsterTwoValue = 80;
const int MonsterThreeValue = 120;
const int MonsterOneSpeed = 50;
const int MonsterTwoSpeed = 65;
const int MonsterThreeSpeed = 55;
class Carrot;
class MonsterManager;
class Obstacles;
class GameObject : public mapChoose
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init(int mapCatalog, cocos2d::Label* _goldCoinDisplay);
    static GameObject* create(int mapCatalog, cocos2d::Label* _goldCoinDisplay);
    //��ͼѡ��
    int mapChoose;
    //��һ�ŵ�ͼ·��
    cocos2d::Sequence* MoveWayInMapOne(GameObject* monster);
    //�ڶ��ŵ�ͼ·��
    cocos2d::Sequence* MoveWayInMapTwo(GameObject* monster);

    //����Ѫ��
    void setHealthBar(cocos2d::Sprite* monster);
    //��ӹ���
    void addMonsterInMapOne();
    void addMonsterInMapTwo();
    void addMonsterOne(float dt);
    void addMonsterTwo(float dt);
    void addMonsterThree(float dt);
    //����ϰ���
    void addObstaclesInMapOne();
    void addObstaclesInMapTwo();
    //����Ѫ��
    void updateHealthBar(cocos2d::ProgressTimer* healthBar,int initial,int current);
    //�Ӵ�
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //objectλ��
    cocos2d::Vec2 objectPosition;
    //����ֵ
    int currentHealth;//��ǰ
    int initialHealth;//ԭʼ
    //���ֵ
    int coinValue;
    //Ѫ��
    cocos2d::ProgressTimer* healthBar;
    cocos2d::Sprite* healthBarBG;
    //��ȡ����ڵ�
    cocos2d::Sprite* getSprite();
    cocos2d::Vec2 getCurrentPosition();
    //����λ�ú���
    void update(float dt);
    int speed;
    MonsterManager* monstermanager;
    void hitMonster(cocos2d::Node* node, int num, float scale, char* filename);
    void hitObstacle(cocos2d::Node* node, int num, float scale, char* filename);
    static GameObject* instance;
    static GameObject* getInstance();
    std::vector<Obstacles*> getObstacles();
    std::vector<Obstacles*> obstacles;
    void removeObstacle(GameObject* obstacle);
    cocos2d::Sprite* objectSprite;
    void setMonsterPhysicsBody();
    void setLabel(char* str, cocos2d:: Vec2 origin, cocos2d::Size visibleSize);
    void clear();
protected:
    Carrot* carrotLayer;
    //����ڵ�
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);//����֡����
};
#endif // __GAME_OBJECT_H__

