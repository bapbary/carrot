//#define MONSTER 200
//#define CARROT 100
#include "Monster.h"
#include "MonsterManager.h"
USING_NS_CC;

bool GameObject::init()
{
    if (!Node::init())
    {
        return false;
    }
    //�����������Ҫɾ
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(GameObject::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //��ʼ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����ܲ�
    carrotLayer = Carrot::create();
    this->addChild(carrotLayer, 2);

    //���ýӴ�
    //auto physicsBody = PhysicsBody::createBox(carrotLayer->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    //physicsBody->setDynamic(false);
    //physicsBody->setCategoryBitmask(0x04);    // 0100
    //physicsBody->setContactTestBitmask(0x01); // 0001
    //physicsBody->setCollisionBitmask(0x06);   // 0110
    //carrotLayer->setTag(CARROT);
    //carrotLayer->setPhysicsBody(physicsBody);

    // ÿ��1.5������һ������
    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonster), 2,10,0);

    //�Ӵ�����
    //auto contactListener = EventListenerPhysicsContact::create();
    //contactListener->onContactBegin = CC_CALLBACK_1(GameObject::onContactBegin, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}
//��ȡ����
cocos2d::Sprite* GameObject::getSprite()
{
    return objectSprite;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
//��ȡ��ǰλ��
cocos2d::Vec2 GameObject::getCurrentPosition()
{
    objectPosition = objectSprite->getPosition();
    return objectPosition;
}
//����λ��
void GameObject::update(float dt)
{
    getCurrentPosition();
    if (objectPosition.distance(DestinationOne) <0.1f)  // ���赽��Ŀ��λ�õľ�����ֵΪ0.1f
    {
        this->unscheduleUpdate();
        MonsterManager::getInstance()->removeMonster(this);
    }
}
//��ӹ���
void GameObject::addMonster(float dt)
{
    MonsterOne* MonsterOneLayer = MonsterOne::create(carrotLayer);
    this->addChild(MonsterOneLayer, 2);
    MonsterManager::getInstance()->addMonster(MonsterOneLayer);
    auto delayAction = DelayTime::create(2.0f);
    auto addMonsterTwoAction = CallFunc::create([this]() {
        MonsterTwo* MonsterTwoLayer = MonsterTwo::create(carrotLayer);
        this->addChild(MonsterTwoLayer, 2);
        MonsterManager::getInstance()->addMonster(MonsterTwoLayer);
    });
    // ���������������һ��
    auto sequence = Sequence::create(delayAction, addMonsterTwoAction, nullptr);

    // ���� Sequence
    this->runAction(sequence);
}

void GameObject::setHealthBar(Sprite* monster, float currentHealthValue, float InitialHealthValue)
{
    auto healthBarBG = Sprite::create("loadingBar.png");
    healthBarBG->setScale(0.7);
    healthBarBG->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // ����Ѫ��������λ��
    monster->addChild(healthBarBG, 1);
    auto healthBar = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setScale(0.7);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // ����Ѫ����λ��
    monster->addChild(healthBar, 2);
    float healthPercentage = (currentHealthValue / InitialHealthValue) * 100.0f;
    updateHealthBar(healthBar, healthPercentage);
}

void GameObject::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
//����֡����
Vector<SpriteFrame*> GameObject::getAnimation(const char* format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for (int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}
//��һ����ͼ��·��
Sequence* GameObject::MoveWayInMapOne(GameObject * monster)
{
    float v = monster->speed;
    auto fadeIn = FadeIn::create(0.1f);
    float time1 = (Vec2(885, 532) - monster->objectPosition).getLength() / v;
    auto moveTo1 = MoveTo::create(time1, Vec2(885, 532));
    float time2 = (Vec2(885, 532) - Vec2(885, 335)).getLength() / v;
    auto moveTo2 = MoveTo::create(time2, Vec2(885, 335));
    auto scaleXAction = ScaleBy::create(0, -1.0f, 1.0f);
    float time3 = (Vec2(885, 335) - Vec2(210, 335)).getLength() / v;
    auto moveTo3 = MoveTo::create(time3, Vec2(210, 335));
    float time4 = (Vec2(210, 335) - Vec2(210, 153)).getLength() / v;
    auto moveTo4 = MoveTo::create(time4, Vec2(210, 153));
    float time5 = (Vec2(210, 153) - Vec2(702, 153)).getLength() / v;
    auto moveTo5 = MoveTo::create(time5, Vec2(702, 153));
    auto fadeOut = FadeOut::create(0.1f);
    auto arrive = CallFunc::create([=]() {
        carrotLayer->decreaseHealth();
        monster->unscheduleUpdate();
        });
    auto actionRemove = RemoveSelf::create();

    auto seq = Sequence::create(fadeIn, moveTo1, moveTo2, scaleXAction, moveTo3, moveTo4, scaleXAction, moveTo5, fadeOut,arrive ,actionRemove,nullptr);
    return seq;
}
//����ƶ���ʾ����
void GameObject::onMouseMove(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        // ��ȡ�������
        Vec2 mousePosition = Vec2(e->getCursorX(), e->getCursorY());
        //// ���������ת��Ϊ OpenGL ����ϵ�µ�����
        //mousePosition = Director::getInstance()->convertToGL(mousePosition);

        // ��ʾ������Ϣ�����½ǣ�
        auto label = Label::createWithTTF(StringUtils::format("Mouse Position: %.2f, %.2f", mousePosition.x, mousePosition.y), "fonts/arial.ttf", 24);
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2::ZERO);
        this->removeChildByTag(123); // �Ƴ�֮ǰ�� label
        this->addChild(label, 5, 123);
    }
}
//����ֵ
void GameObject::updateHealthBar(ProgressTimer* healthBar, float percentage)
{
    healthBar->setPercentage(percentage);
}
//�Ӵ�
//bool GameObject::onContactBegin(PhysicsContact& contact)
//{
//    auto nodeA = contact.getShapeA()->getBody()->getNode();
//    auto nodeB = contact.getShapeB()->getBody()->getNode();
//
//    if (nodeA && nodeB)
//    {
//        int tagA = nodeA->getTag();
//        int tagB = nodeB->getTag();
//        if (tagA != tagB)
//        {
//            // ������ܲ�������ײ
//            Carrot* carrot;
//            GameObject* monster;
//            if (tagA == CARROT)
//            {
//                carrot = dynamic_cast<Carrot*>(nodeA);
//                monster = dynamic_cast<GameObject*>(nodeB);
//            }
//            else
//            {
//                carrot = dynamic_cast<Carrot*>(nodeB);
//                monster = dynamic_cast<GameObject*>(nodeA);
//            }
//            // �����ܲ�������ֵ
//            carrot->decreaseHealth();
//        }
//    }
//    return true;
//}

//�ܲ���ʼ��
bool Carrot::init()
{
    if (!Node::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //�ܲ��Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    this->addChild(spriteCarrot, 2);
    spriteCarrot->setPosition(702, 156);
    //����ת
    spriteCarrot->setScaleX(-3.8);
    spriteCarrot->setScaleY(3.8);

    //֡����
    auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
    spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));

    carrotLayer = this;
    return true;
}
//�ܲ�����Ѫ��
void Carrot::decreaseHealth()
{
    carrotLayer->objectHealthValue -= 1;
    CCLOG("%.1f", carrotLayer->objectHealthValue);
    if (carrotLayer->objectHealthValue == 9.0f)
    {
        //��������
        spriteNum = Sprite::create("icon_num(9).png");
        this->addChild(spriteNum, 2);
        spriteNum->setScale(2);
        spriteNum->setPosition(702, 255);
        //auto framesCarrot = getAnimation("carrot2%04d.png", 2);
        //auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
        //spriteCarrot->stopAllActions();
        //spriteCarrot->setSpriteFrame(framesCarrot.front());
        //spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));
    }
    else if (carrotLayer->objectHealthValue == 8.0f)
    {
        spriteNum->setTexture("icon_num(8).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->objectHealthValue == 7.0f)
    {
        spriteNum->setTexture("icon_num(7).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        auto remove = RemoveSelf::create();
        spriteCarrot->runAction(remove);
        spriteCarrot = Sprite::create("carrot7.png");
        this->addChild(spriteCarrot, 2);
        spriteCarrot->setPosition(702, 156);
        // ���Ը�����Ҫ�����������
    }
    else if (carrotLayer->objectHealthValue == 6.0f)
    {
        spriteNum->setTexture("icon_num(6).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->objectHealthValue == 5.0f)
    {
        spriteNum->setTexture("icon_num(5).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setTexture("carrot5.png");
    }
    else if (carrotLayer->objectHealthValue == 4.0f)
    {
        spriteNum->setTexture("icon_num(4).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));

        spriteCarrot->stopAllActions();
        spriteCarrot->setTexture("carrot4.png");
        // ���Ը�����Ҫ�����������
        spriteCarrot->setTextureRect(Rect(Vec2::ZERO, spriteCarrot->getContentSize()));
    }
    else if (carrotLayer->objectHealthValue == 3.0f)
    {
        spriteNum->setTexture("icon_num(3).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->objectHealthValue == 2.0f)
    {
        spriteNum->setTexture("icon_num(2).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->stopAllActions();
        spriteCarrot->setTexture("carrot3.png");
        // ���Ը�����Ҫ�����������
        spriteCarrot->setTextureRect(Rect(Vec2::ZERO, spriteCarrot->getContentSize()));
    }
    else if (carrotLayer->objectHealthValue == 1.0f)
    {
        spriteNum->setTexture("icon_num(1).png");
        // ���Ը�����Ҫ�����������
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->stopAllActions();
        spriteCarrot->setTexture("carrot1.png");
        // ���Ը�����Ҫ�����������
        spriteCarrot->setTextureRect(Rect(Vec2::ZERO, spriteCarrot->getContentSize()));
    }
    else
        CCLOG("gameover");
}

Carrot::Carrot() : spriteNum(nullptr)
{
    objectHealthValue = 10.0f;
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    //auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    //spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    //this->addChild(spriteCarrot, 2);
}

//����1��ʼ��
bool MonsterOne::init(Carrot* _carrotLayer)
{
    if (!GameObject::init())
    {
        return false;
    }
    carrotLayer = _carrotLayer;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ����ֵ
    float InitialHealthValue = 100.0f;
    objectHealthValue = InitialHealthValue;
    //����1�Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterOne = getAnimation("monster1/%04d.png", 2);
    objectSprite = Sprite::createWithSpriteFrame(framesMonsterOne.front());
    //�����ٶ�
    this->speed = 500.0f;
    //auto physicsBody = PhysicsBody::createBox(spriteMonsterOne->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    //physicsBody->setDynamic(false);
    //physicsBody->setCategoryBitmask(0x01);    // 0001
    //physicsBody->setContactTestBitmask(0x04); // 0100
    //physicsBody->setCollisionBitmask(0x03);   // 0011
    //spriteMonsterOne->setTag(MONSTER);
    //spriteMonsterOne->setPhysicsBody(physicsBody);

    this->addChild(objectSprite, 2);
    //����
    objectSprite->setScale(1.9, 1.9);
    objectSprite->setOpacity(0);
    objectSprite->setPosition(383, 532);

    //����Ѫ��
    setHealthBar(objectSprite, objectHealthValue, InitialHealthValue);
    //֡����
    auto animationMonsterOne = Animation::createWithSpriteFrames(framesMonsterOne, 1.0f / 3);
    objectSprite->runAction(RepeatForever::create(Animate::create(animationMonsterOne)));
    auto moveAction = MoveWayInMapOne(this); // ���ƶ�������������
    objectSprite->runAction(moveAction);

    // ���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ��
    scheduleUpdate();
    return true;
}
MonsterOne* MonsterOne::create(Carrot* carrotLayer)
{
    MonsterOne* monsterOne = new MonsterOne();
    if (monsterOne && monsterOne->init(carrotLayer))
    {
        monsterOne->autorelease();
        return monsterOne;
    }
    else
    {
        delete monsterOne;
        return nullptr;
    }
}
MonsterTwo* MonsterTwo::create(Carrot* carrotLayer)
{
    MonsterTwo* monsterTwo = new MonsterTwo();
    if (monsterTwo && monsterTwo->init(carrotLayer))
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


bool MonsterTwo::init(Carrot* _carrotLayer)
{
    if (!Node::init())
    {
        return false;
    }
    carrotLayer = _carrotLayer;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ����ֵ
    float InitialHealthValue = 200.0f;
    objectHealthValue = InitialHealthValue;
    //����2�Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterTwo = getAnimation("monster2/%04d.png", 3);
     objectSprite = Sprite::createWithSpriteFrame(framesMonsterTwo.front());
    this->addChild(objectSprite, 2);
    //�����ٶ�
    this->speed = 100.0f;

    //����
    objectSprite->setScale(1.9, 1.9);
    objectSprite->setOpacity(100);
    objectSprite->setPosition(383, 532);
    setHealthBar(objectSprite, objectHealthValue, InitialHealthValue);
    //֡����
    auto animationMonsterTwo = Animation::createWithSpriteFrames(framesMonsterTwo, 1.0f / 3);
    objectSprite->runAction(RepeatForever::create(Animate::create(animationMonsterTwo)));
    auto moveAction = MoveWayInMapOne(this); // ���ƶ�������������
    objectSprite->runAction(moveAction);
    // ���� scheduleUpdate()��ʹ�� update ����������,ÿһ֡����λ��
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::update));
    return true;
}
