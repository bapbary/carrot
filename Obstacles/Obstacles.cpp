#include "Obstacles.h"
USING_NS_CC;
Obstacles* Obstacles::create(cocos2d::Vec2 position, float scale, char* filename, int health,int coin)
{
    Obstacles* obstacle = new Obstacles();
    if (obstacle && obstacle->init(position, scale, filename, health,coin))
    {
        obstacle->autorelease();
        return obstacle;
    }
    else
    {
        delete obstacle;
        return nullptr;
    }
}
bool Obstacles::init(Vec2 position, float scale, char* filename, int health,int coin)
{
    if (!Node::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ����ֵ
    initialHealth = health;
    currentHealth = initialHealth;
    //���ֵ
    coinValue = coin;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
    objectSprite = Sprite::createWithSpriteFrame(spriteFrame);
    this->addChild(objectSprite, 2);
    //����
    objectSprite->setScale(scale);
    objectPosition = position;
    objectSprite->setPosition(objectPosition);
    cocos2d::Size smallerSize(objectSprite->getContentSize().width * 0.2f, objectSprite->getContentSize().height * 0.2f);
    auto physicsBody = PhysicsBody::createBox(smallerSize, PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    objectSprite->setTag(OBSTACLE);
    objectSprite->setPhysicsBody(physicsBody);
    setHealthBar(objectSprite);
    // ���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ�á�Ѫ��
    this->scheduleUpdate();
    return true;
}

