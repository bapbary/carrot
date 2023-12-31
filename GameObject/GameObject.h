#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "cocos2d.h"
#include "D:\carrot\cocos2d\cocos\editor-support\cocostudio\SimpleAudioEngine.h"
#include<vector>
//��ͼ�յ㡢���
const cocos2d::Vec2 Destination[2] = { cocos2d::Vec2(736, 180),cocos2d::Vec2(890,269) };
const cocos2d::Vec2 Origin[2] = { cocos2d::Vec2(383, 532),cocos2d::Vec2(994,531) };
#define MONSTER 200
#define CARROT 100
#define LIGHTINGBULLET1 3
#define LIGHTINGBULLET2 6
#define LIGHTINGBULLET3 9
#define FIREBULLET1 41
#define FIREBULLET2 52
#define FIREBULLET3 63
#define LEAFBULLET1 20
#define LEAFBULLET2 25
#define LEAFBULLET3 45
#define OBSTACLE 300
const float MonsterOneHealth = 100.f;
const float MonsterTwoHealth = 200.f;
const float MonsterThreeHealth = 500.0f;
const float MonsterOneValue = 100.0f;
const float MonsterTwoValue = 200.0f;
const float MonsterThreeValue = 500.0f;
const float MonsterOneSpeed = 500.0f;
const float MonsterTwoSpeed = 80.0f;
const float MonsterThreeSpeed = 55.f;
class Carrot;
class MonsterManager;
class Obstacles;
class GameObject : public cocos2d::Node
{
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onMouseMove(cocos2d::Event* event);
    virtual bool init(int mapCatalog);
    static GameObject* create(int mapCatalog);
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
    void updateHealthBar(cocos2d::ProgressTimer* healthBar,float initial,float current);
    //�Ӵ�
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //objectλ��
    cocos2d::Vec2 objectPosition;
    //����ֵ
    float currentHealth;//��ǰ
    float initialHealth;//ԭʼ
    //���ֵ
    float coinValue;
    //Ѫ��
    cocos2d::ProgressTimer* healthBar;
    cocos2d::Sprite* healthBarBG;
    //��ȡ����ڵ�
    cocos2d::Sprite* getSprite();
    cocos2d::Vec2 getCurrentPosition();
    //����λ�ú���
    void update(float dt);
    float speed;
    MonsterManager* monstermanager;
    void hitMonster(cocos2d::Node* node, float num, float scale, char* filename);
    void hitObstacle(cocos2d::Node* node, float num, float scale, char* filename);
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
