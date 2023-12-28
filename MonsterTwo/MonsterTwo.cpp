#include "MonsterTwo.h"
USING_NS_CC;
MonsterTwo* MonsterTwo::create(Carrot* carrotLayer, int mapCatalog)
{
    MonsterTwo* monsterTwo = new MonsterTwo();
    if (monsterTwo && monsterTwo->init(carrotLayer, mapCatalog))
    {
        monsterTwo->autorelease();
        return monsterTwo;
    }
    else
    {
        delete monsterTwo;
        return nullptr;
    }
}
bool MonsterTwo::init(Carrot* _carrotLayer, int mapCatalog)
{
    if (!Node::init())
    {
        return false;
    }
    carrotLayer = _carrotLayer;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ����ֵ
    initialHealth= MonsterTwoHealth;
    currentHealth = initialHealth;
    coinValue = MonsterTwoValue;
    //����2�Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterTwo = getAnimation("monster2/%04d.png", 3);
    objectSprite = Sprite::createWithSpriteFrame(framesMonsterTwo.front());
    this->addChild(objectSprite, 2);
    //�����ٶ�
    this->speed = 400.0f;

    //����
    objectSprite->setScale(1.9, 1.9);
    objectSprite->setOpacity(100);
    objectPosition = Origin[mapCatalog - 1];
    objectSprite->setPosition(objectPosition);

    auto physicsBody = PhysicsBody::createBox(objectSprite->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    objectSprite->setTag(MONSTER);
    objectSprite->setPhysicsBody(physicsBody);

    setHealthBar(objectSprite);
    //֡����
    auto animationMonsterTwo = Animation::createWithSpriteFrames(framesMonsterTwo, 1.0f / 3);
    objectSprite->runAction(RepeatForever::create(Animate::create(animationMonsterTwo)));
    Sequence* moveAction;
    if (mapCatalog == 1)
        moveAction = MoveWayInMapOne(this); // ���ƶ�������������
    else
        moveAction = MoveWayInMapTwo(this);
    objectSprite->runAction(moveAction);
    // ���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ��
    this->scheduleUpdate();
    return true;
}
