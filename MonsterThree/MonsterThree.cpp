#include "MonsterThree.h"
USING_NS_CC;
//����3��ʼ��
bool MonsterThree::init(Carrot* _carrotLayer, int mapCatalog)
{
    if (!Node::init())
    {
        return false;
    }
    carrotLayer = _carrotLayer;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ����ֵ
    initialHealth = MonsterThreeHealth;
    currentHealth = initialHealth;
    coinValue = MonsterThreeValue;
    //����Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterOne = getAnimation("monster3/%04d.png", 2);
    objectSprite = Sprite::createWithSpriteFrame(framesMonsterOne.front());
    //�����ٶ�
    this->speed = 200.0f;
    auto physicsBody = PhysicsBody::createBox(objectSprite->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    physicsBody->setCollisionBitmask(0x03);   // 0011
    objectSprite->setTag(MONSTER);
    objectSprite->setPhysicsBody(physicsBody);

    this->addChild(objectSprite, 2);
    //����
    objectSprite->setScale(1.9, 1.9);
    objectSprite->setOpacity(0);
    objectPosition = Origin[mapCatalog - 1];
    objectSprite->setPosition(objectPosition);

    //����Ѫ��
    setHealthBar(objectSprite);
    //֡����
    auto animationMonsterOne = Animation::createWithSpriteFrames(framesMonsterOne, 1.0f / 3);
    objectSprite->runAction(RepeatForever::create(Animate::create(animationMonsterOne)));
    Sequence* moveAction;
    if (mapCatalog == 1)
        moveAction = MoveWayInMapOne(this); // ���ƶ�������������
    else
        moveAction = MoveWayInMapTwo(this);
    objectSprite->runAction(moveAction);

    //���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ��
    this->scheduleUpdate();
    return true;
}
MonsterThree* MonsterThree::create(Carrot* carrotLayer, int mapCatalog)
{
    MonsterThree* monsterthree = new MonsterThree();
    if (monsterthree && monsterthree->init(carrotLayer, mapCatalog))
    {
        monsterthree->autorelease();
        return monsterthree;
    }
    else
    {
        delete monsterthree;
        return nullptr;
    }
}

