#include "Obstacles.h"
USING_NS_CC;
Obstacles* Obstacles::create(cocos2d::Vec2 position, float scale, char* filename, float health,float coin)
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
bool Obstacles::init(Vec2 position, float scale, char* filename, float health,float coin)
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

    auto physicsBody = PhysicsBody::createBox(objectSprite->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    objectSprite->setTag(OBSTACLE);//�ϰ����൱�ھ�ֹ�Ĺ���
    objectSprite->setPhysicsBody(physicsBody);
    setHealthBar(objectSprite);
    // ���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ�á�Ѫ��
    this->scheduleUpdate();
    return true;
}