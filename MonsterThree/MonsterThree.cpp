#include "MonsterThree.h"
USING_NS_CC;
//怪物3初始化
bool MonsterThree::init(Carrot* _carrotLayer, int mapCatalog)
{
    if (!Node::init())
    {
        return false;
    }
    carrotLayer = _carrotLayer;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //初始生命值
    initialHealth = MonsterThreeHealth;
    currentHealth = initialHealth;
    coinValue = MonsterThreeValue;
    //怪物的动画帧
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterOne = getAnimation("monster3/%04d.png", 2);
    objectSprite = Sprite::createWithSpriteFrame(framesMonsterOne.front());
    //设置速度
    this->speed = MonsterThreeSpeed;
    //物理引擎
    setMonsterPhysicsBody();

    this->addChild(objectSprite, 2);
    //缩放
    objectSprite->setScale(1.9, 1.9);
    objectSprite->setOpacity(0);
    objectPosition = Origin[mapCatalog - 1];
    objectSprite->setPosition(objectPosition);

    //设置血条
    setHealthBar(objectSprite);
    //帧速率
    auto animationMonsterOne = Animation::createWithSpriteFrames(framesMonsterOne, 1.0f / 3);
    objectSprite->runAction(RepeatForever::create(Animate::create(animationMonsterOne)));
    Sequence* moveAction;
    if (mapCatalog == 1)
        moveAction = MoveWayInMapOne(this); // 将移动动作保存起来
    else
        moveAction = MoveWayInMapTwo(this);
    objectSprite->runAction(moveAction);

    //调用 scheduleUpdate()，使得 update 函数被调用,每一帧更新位置
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

