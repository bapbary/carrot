#include "GameObject.h"
#include"Carrot.h"
#include"MonsterOne.h"
#include"MonsterTwo.h"
#include"MonsterManager.h"
#include"MonsterThree.h"
#include"Obstacles.h"
#include "mapChoose.h"
USING_NS_CC;
GameObject* GameObject::create(int mapCatalog)
{
    GameObject* gameobject = new GameObject();
    if (gameobject && gameobject->init(mapCatalog))
    {
        gameobject->autorelease();
        return gameobject;
    }
    else
    {
        delete gameobject;
        return nullptr;
    }
}
bool GameObject::init(int mapCatalog)
{
    if (!Node::init())
    {
        return false;
    }
    instance = this;
    mapChoose = mapCatalog;
    //�����������Ҫɾ
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(GameObject::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //��ʼ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //�����ܲ�
    carrotLayer = Carrot::create(mapChoose);
    this->addChild(carrotLayer, 2);
    //�Ӵ�����
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameObject::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    //���ӹ���
    if (mapChoose == 1)
    {
        addMonsterInMapOne();
        addObstaclesInMapOne();
    }
    else
    {
        addMonsterInMapTwo();
        addObstaclesInMapTwo();
    }
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
//ÿ֡����λ�á�Ѫ��
void GameObject::update(float dt)
{
    getCurrentPosition();
    updateHealthBar(healthBar, initialHealth, currentHealth);
}
//���ӹ���
//��ͼһ�ִ���
void GameObject::addMonsterInMapOne()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��һ��
    auto sequenceMonster1 = Sequence::create(CallFunc::create([=]() {
    //��һ����ǩ
    auto label1 = Label::createWithTTF("The First Wave", "fonts/Marker Felt.ttf", 36);
    label1->setTextColor(Color4B::YELLOW);
    label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label1->getContentSize().height));
    this->addChild(label1, 2);
    //�ӳ������ɾ��
    label1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
    //�������
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
    }), DelayTime::create(2.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(1.5f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
            }), DelayTime::create(38.0f), nullptr);
    //�ڶ���
    auto sequenceMonster2 = Sequence::create(CallFunc::create([=]() {
        // ��ǩ
    auto label2 = Label::createWithTTF("The Second Wave", "fonts/Marker Felt.ttf", 36); 
    label2->setTextColor(Color4B::YELLOW);
    label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label2->getContentSize().height));
    this->addChild(label2, 2); 
    // �ӳ������ɾ��
    label2->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
    // ���� 5һ+10��+5��
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 5, 0);
    }), DelayTime::create(5.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
        }), DelayTime::create(2.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(25.0f), nullptr);
    //������
    auto sequenceMonster3 = Sequence::create( CallFunc::create([=]() {
        // ��ǩ
        auto label3 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label3->setTextColor(Color4B::YELLOW);
        label3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label3->getContentSize().height));
        this->addChild(label3, 2);
        // �ӳ������ɾ��
        label3->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // ���� 10һ+10��+10��
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
        }), DelayTime::create(1.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
            }), DelayTime::create(1.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
                }), DelayTime::create(25.0f), nullptr);
    this->runAction(Sequence::create(sequenceMonster1, sequenceMonster2, sequenceMonster3,nullptr));
}
//��ͼ���ִ���
void GameObject::addMonsterInMapTwo()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��һ��
    auto sequenceMonster1 = Sequence::create(CallFunc::create([=]() {
        //��һ����ǩ
        auto label1 = Label::createWithTTF("The First Wave", "fonts/Marker Felt.ttf", 36);
        label1->setTextColor(Color4B::YELLOW);
        label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label1->getContentSize().height));
        this->addChild(label1, 2);
        //�ӳ������ɾ��
        label1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        //�������
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(5.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
            }), DelayTime::create(10.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
                }), DelayTime::create(40.0f), nullptr);
    //�ڶ���
    auto sequenceMonster2 = Sequence::create(CallFunc::create([=]() {
        // ��ǩ
        auto label2 = Label::createWithTTF("The Second Wave", "fonts/Marker Felt.ttf", 36);
        label2->setTextColor(Color4B::YELLOW);
        label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label2->getContentSize().height));
        this->addChild(label2, 2);
        // �ӳ������ɾ��
        label2->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // ���� 5һ+10��+10��
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 5, 0);
        }), DelayTime::create(5.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
            }), DelayTime::create(2.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
                }), DelayTime::create(45.0f), nullptr);
    //������
    auto sequenceMonster3 = Sequence::create(CallFunc::create([=]() {
        // ��ǩ
        auto label3 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label3->setTextColor(Color4B::YELLOW);
        label3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label3->getContentSize().height));
        this->addChild(label3, 2);
        // �ӳ������ɾ��
        label3->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // ���� 15һ+10��+10��
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 15, 0);
        }), DelayTime::create(1.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
            }), DelayTime::create(1.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
                }), DelayTime::create(45.0f), nullptr);
    //���Ĳ�
    auto sequenceMonster4 = Sequence::create(CallFunc::create([=]() {
        // ��ǩ
        auto label4 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label4->setTextColor(Color4B::YELLOW);
        label4->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label4->getContentSize().height));
        this->addChild(label4, 2);
        // �ӳ������ɾ��
        label4->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // ���� 15һ+10��+10��
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
        }), DelayTime::create(2.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
            }), DelayTime::create(1.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 15, 0);
                }), DelayTime::create(45.0f), nullptr);
    this->runAction(Sequence::create(sequenceMonster1, sequenceMonster2, sequenceMonster3, sequenceMonster4,nullptr));
}

void GameObject::addMonsterOne(float dt)
{
    MonsterOne* MonsterOneLayer = MonsterOne::create(carrotLayer, mapChoose);
    this->addChild(MonsterOneLayer, 2);
    MonsterManager::getInstance()->addMonster(MonsterOneLayer);
}
void GameObject::addMonsterTwo(float dt)
{
    MonsterTwo* MonsterTwoLayer = MonsterTwo::create(carrotLayer, mapChoose);
    this->addChild(MonsterTwoLayer, 2);
    MonsterManager::getInstance()->addMonster(MonsterTwoLayer);
}
void GameObject::addMonsterThree(float dt)
{
    MonsterThree* MonsterThreeLayer = MonsterThree::create(carrotLayer, mapChoose);
    this->addChild(MonsterThreeLayer, 2);
    MonsterManager::getInstance()->addMonster(MonsterThreeLayer);
}
void GameObject::setHealthBar(Sprite* monster)
{
    healthBarBG = Sprite::create("loadingBar.png");
    healthBarBG->setScale(0.7);
    healthBarBG->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // ����Ѫ��������λ��
    monster->addChild(healthBarBG, 1);
    healthBarBG->setVisible(false);
    healthBar = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setScale(0.7);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setVisible(false);
    healthBar->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // ����Ѫ����λ��
    monster->addChild(healthBar, 2);
    float healthPercentage = (currentHealth / initialHealth) * 100.0f;
    updateHealthBar(healthBar, initialHealth, currentHealth);
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
Sequence* GameObject::MoveWayInMapOne(GameObject* monster)
{
    float v = monster->speed;
    auto fadeIn = FadeIn::create(0.1f);
    float time1 = (Vec2(885, 532) - monster->objectPosition).getLength() / v;
    auto moveTo1 = MoveTo::create(time1, Vec2(885, 532));
    float time2 = (Vec2(885, 532) - Vec2(885, 335)).getLength() / v;
    auto moveTo2 = MoveTo::create(time2, Vec2(885, 345));
    auto scaleXAction = ScaleBy::create(0, -1.0f, 1.0f);
    float time3 = (Vec2(885, 345) - Vec2(210, 345)).getLength() / v;
    auto moveTo3 = MoveTo::create(time3, Vec2(210, 345));
    float time4 = (Vec2(210, 345) - Vec2(210, 153)).getLength() / v;
    auto moveTo4 = MoveTo::create(time4, Vec2(210, 153));
    float time5 = (Vec2(210, 153) - Vec2(702, 153)).getLength() / v;
    auto moveTo5 = MoveTo::create(time5, Vec2(702, 153));
    auto fadeOut = FadeOut::create(0.1f);
    //auto arrive = CallFunc::create([=]() {
    //    monster->unscheduleUpdate();
    //    });
    //auto actionRemove = RemoveSelf::create();
    auto seq = Sequence::create(fadeIn, moveTo1, moveTo2, scaleXAction, moveTo3, moveTo4, scaleXAction, moveTo5, fadeOut, nullptr);
    return seq;
}
Sequence* GameObject::MoveWayInMapTwo(GameObject* monster)
{
    float v = monster->speed;
    auto fadeIn = FadeIn::create(0.1f);
    float time1 = (Vec2(116,531) - monster->objectPosition).getLength() / v;
    auto moveTo1 = MoveTo::create(time1, Vec2(116, 531));
    auto scaleXAction = ScaleBy::create(0, -1.0f, 1.0f);
    float time2 = (Vec2(116,339) - Vec2(116, 531)).getLength() / v;
    auto moveTo2 = MoveTo::create(time2, Vec2(116,339));
    float time3 = (Vec2(489,339) - Vec2(116,339)).getLength() / v;
    auto moveTo3 = MoveTo::create(time3, Vec2(489,339));
    float time4 = (Vec2(489,339) - Vec2(489,239)).getLength() / v;
    auto moveTo4 = MoveTo::create(time4, Vec2(489,239));
    float time5 = (Vec2(118,239) - Vec2(489,239)).getLength() / v;
    auto moveTo5 = MoveTo::create(time5, Vec2(118,239));
    float time6 = (Vec2(118,148) - Vec2(118,239)).getLength() / v;
    auto moveTo6 = MoveTo::create(time6, Vec2(118,148));
    float time7 = (Vec2(760,148) - Vec2(118,148)).getLength() / v;
    auto moveTo7 = MoveTo::create(time7, Vec2(760,148));
    float time8 = (Vec2(760, 437) - Vec2(778, 148)).getLength() / v;
    auto moveTo8 = MoveTo::create(time8, Vec2(760,437));
    float time9 = (Vec2(875, 437) - Vec2(760, 437)).getLength() / v;
    auto moveTo9 = MoveTo::create(time9, Vec2(875, 437));
    float time10 = (Vec2(875, 325) - Vec2(875, 437)).getLength() / v;
    auto moveTo10 = MoveTo::create(time10, Vec2(875, 325));
    auto fadeOut = FadeOut::create(0.1f);
    //auto arrive = CallFunc::create([=]() {
    //    carrotLayer->decreaseHealth();
    //    monster->unscheduleUpdate();
    //    });
    //auto actionRemove = RemoveSelf::create();
    auto seq = Sequence::create(fadeIn, scaleXAction, moveTo1, scaleXAction, moveTo2,  moveTo3, scaleXAction, moveTo4, moveTo5, scaleXAction, moveTo6,moveTo7,moveTo8, moveTo9, moveTo10, fadeOut, nullptr);
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
void GameObject::updateHealthBar(ProgressTimer* healthBar, float initialHealthValue, float currentHealth)
{
    if (currentHealth < initialHealthValue)
    {
        healthBarBG->setVisible(true);
        healthBar->setVisible(true);
    }
    float healthPercentage = (currentHealth / initialHealthValue) * 100.0f;
    healthBar->setPercentage(healthPercentage);
}
void  GameObject::hitMonster(Node*node, float num, float scale,char* filename)
{
    Sprite* sprite = dynamic_cast<Sprite*>(node);
    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
    monster->currentHealth -= float(num);
    auto hit = Sprite::create(filename);
    //������Ч
    hit->setScale(scale);
    sprite->addChild(hit, 2);
    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
    hit->runAction(Sequence::create(DelayTime::create(0.1f), RemoveSelf::create(), nullptr));
    if (monster->currentHealth <= 0)
    {
        goldCoin += monster->coinValue;
        monster->unscheduleUpdate();
        monster->runAction(RemoveSelf::create());
        MonsterManager::getInstance()->removeMonster(monster);
    }
}
void GameObject::hitObstacle(Node* node, float num, float scale, char* filename)
{
    Sprite* sprite = dynamic_cast<Sprite*>(node);
    GameObject* obstacle = dynamic_cast<GameObject*>(sprite->getParent());
    obstacle->currentHealth -= float(num);
    auto hit = Sprite::create(filename);
    sprite->addChild(hit, 2);
    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
    hit->runAction(Sequence::create(DelayTime::create(0.5f), RemoveSelf::create(), nullptr));
    if (obstacle->currentHealth <= 0)
    {
        goldCoin += obstacle->coinValue;
        obstacle->unscheduleUpdate();
        obstacle->runAction(RemoveSelf::create());
    }

}
//�Ӵ�
bool GameObject::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA && nodeB)
    {
        int tagA = nodeA->getTag();
        int tagB = nodeB->getTag();
        if (tagA != tagB)
        {
            // ������ܲ��Ӵ�
            if (tagA == CARROT && tagB == MONSTER || tagA == MONSTER && tagB == CARROT)
            {
                if (tagA == MONSTER)
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeA);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    carrotLayer->decreaseHealth();
                    monster->unscheduleUpdate();
                    monster->runAction(RemoveSelf::create());
                    MonsterManager::getInstance()->removeMonster(monster);
                }
                else
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeB);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    carrotLayer->decreaseHealth();
                    monster->unscheduleUpdate();
                    monster->runAction(RemoveSelf::create());
                    MonsterManager::getInstance()->removeMonster(monster);
                }
            }
            //������ӵ��Ӵ�
            //����ƿ
            if (tagA == MONSTER && tagB == LIGHTINGBULLET1 || tagA == LIGHTINGBULLET1 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LIGHTINGBULLET1, 1.0,"Lighting_Hit.png");
                else
                    hitMonster(nodeB, LIGHTINGBULLET1, 1.0, "Lighting_Hit.png");
            }
            if (tagA == MONSTER && tagB == LIGHTINGBULLET2 || tagA == LIGHTINGBULLET2 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LIGHTINGBULLET2, 1, "Lighting_Hit.png");
                else
                    hitMonster(nodeB, LIGHTINGBULLET2, 1, "Lighting_Hit.png");
            }
            if (tagA == MONSTER && tagB == LIGHTINGBULLET3 || tagA == LIGHTINGBULLET3 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LIGHTINGBULLET3, 1.5, "Lighting_Hit.png");
                else
                    hitMonster(nodeB, LIGHTINGBULLET3, 1.5, "Lighting_Hit.png");
            }
            //��ƿ
            if (tagA == MONSTER && tagB == FIREBULLET1 || tagA == FIREBULLET1 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, FIREBULLET1, 0.5, "Fire_Hit.png");
                else
                    hitMonster(nodeB, FIREBULLET1, 0.5, "Fire_Hit.png");
            }
            if (tagA == MONSTER && tagB == FIREBULLET2 || tagA == FIREBULLET2 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, FIREBULLET2, 1, "Fire_Hit.png");
                else
                    hitMonster(nodeB, FIREBULLET2, 1, "Fire_Hit.png");
            }
            if (tagA == MONSTER && tagB == FIREBULLET3 || tagA == FIREBULLET3 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, FIREBULLET3, 1.5, "Fire_Hit.png");
                else
                    hitMonster(nodeB, FIREBULLET3, 1.5, "Fire_Hit.png");
            }
            //����
            if (tagA == MONSTER && tagB == LEAF1 || tagA == LEAF1 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAF1, 0.5,"Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAF1, 0.5,"Leaf_Hit.png");
            }
            if (tagA == MONSTER && tagB == LEAF2 || tagA == LEAF2 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAF2, 1, "Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAF2, 1, "Leaf_Hit.png");
            }
            if (tagA == MONSTER && tagB == LEAF3 || tagA == LEAF3 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAF3, 1.5, "Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAF3, 1.5, "Leaf_Hit.png");
            }

            //�ӵ����ϰ���
            if (tagA == OBSTACLE && tagB == LIGHTINGBULLET1 || tagA == LIGHTINGBULLET1 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LIGHTINGBULLET1, 0.5, "Lighting_Hit.png");
                else
                    hitObstacle(nodeB, LIGHTINGBULLET1, 0.5, "Lighting_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LIGHTINGBULLET2 || tagA == LIGHTINGBULLET2 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LIGHTINGBULLET2, 1, "Lighting_Hit.png");
                else
                    hitObstacle(nodeB, LIGHTINGBULLET2, 1, "Lighting_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LIGHTINGBULLET3 || tagA == LIGHTINGBULLET3 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LIGHTINGBULLET3, 1.5, "Lighting_Hit.png");
                else
                    hitObstacle(nodeB, LIGHTINGBULLET3, 1.5, "Lighting_Hit.png");
            }
            //��ƿ
            if (tagA == OBSTACLE && tagB == FIREBULLET1 || tagA == FIREBULLET1 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, FIREBULLET1, 0.5, "Fire_Hit.png");
                else
                    hitObstacle(nodeB, FIREBULLET1, 0.5, "Fire_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == FIREBULLET2 || tagA == FIREBULLET2 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, FIREBULLET2, 1, "Fire_Hit.png");
                else
                    hitObstacle(nodeB, FIREBULLET2, 1, "Fire_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == FIREBULLET3 || tagA == FIREBULLET3 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, FIREBULLET3, 1.5, "Fire_Hit.png");
                else
                    hitObstacle(nodeB, FIREBULLET3, 1.5, "Fire_Hit.png");
            }
            //����
            if (tagA == OBSTACLE && tagB == LEAF1 || tagA == LEAF1 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAF1, 0.5, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAF1, 0.5, "Leaf_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LEAF2 || tagA == LEAF2 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAF2, 1, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAF2, 1, "Leaf_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LEAF3 || tagA == LEAF3 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAF3, 1.5, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAF3, 1.5, "Leaf_Hit.png");
            }

        }
    }
    return true;
}
void GameObject::addObstaclesInMapOne()
{
    obstacles.clear();
    Obstacles* obstacle1 = Obstacles::create(Vec2(560, 434), 2.0, "obstacle/obstacle1.png", 100.0f, 200.0f);
    this->addChild(obstacle1, 2);
    obstacles.push_back(obstacle1);
    Obstacles* obstacle2 = Obstacles::create(Vec2(687, 600), 1.5, "obstacle/obstacle2.png", 100.0f, 200.0f);
    this->addChild(obstacle2, 2);
    obstacles.push_back(obstacle2);
    Obstacles* obstacle3 = Obstacles::create(Vec2(739, 434), 2.0, "obstacle/obstacle3.png", 100.0f, 200.0f);
    this->addChild(obstacle3, 2);
    obstacles.push_back(obstacle3);
    Obstacles* obstacle4 = Obstacles::create(Vec2(228, 434), 2.0, "obstacle/obstacle4.png", 100.0f, 200.0f);
    this->addChild(obstacle4, 2);
    obstacles.push_back(obstacle4);
    Obstacles* obstacle5 = Obstacles::create(Vec2(525, 69), 2.5, "obstacle/obstacle5.png", 100.0f, 200.0f);
    this->addChild(obstacle5, 2);
    obstacles.push_back(obstacle5);
    Obstacles* obstacle6 = Obstacles::create(Vec2(345, 245), 3.0, "obstacle/obstacle6.png", 100.0f, 200.0f);
    this->addChild(obstacle6, 2);
    obstacles.push_back(obstacle6);
    Obstacles* obstacle7 = Obstacles::create(Vec2(840, 236), 3.0, "obstacle/obstacle7.png", 100.0f, 200.0f);
    this->addChild(obstacle7, 2);
    obstacles.push_back(obstacle7);
}
void GameObject::addObstaclesInMapTwo()
{
    obstacles.clear();
    Obstacles* obstacle1 = Obstacles::create(Vec2(648, 424), 2.0, "obstacle/1.png", 100.0f, 200.0f);
    this->addChild(obstacle1, 2);
    obstacles.push_back(obstacle1);
    Obstacles* obstacle2 = Obstacles::create(Vec2(811, 617), 1.5, "obstacle/2.png", 100.0f, 200.0f);
    this->addChild(obstacle2, 2);
    obstacles.push_back(obstacle2);
    Obstacles* obstacle3 = Obstacles::create(Vec2(215, 433), 2.0, "obstacle/3.png", 100.0f, 200.0f);
    this->addChild(obstacle3, 2);
    obstacles.push_back(obstacle3);
    Obstacles* obstacle4 = Obstacles::create(Vec2(592, 333), 2.0, "obstacle/4.png", 100.0f, 200.0f);
    this->addChild(obstacle4, 2);
    obstacles.push_back(obstacle4);
    Obstacles* obstacle5 = Obstacles::create(Vec2(872, 151), 2.5, "obstacle/5.png", 100.0f, 200.0f);
    this->addChild(obstacle5, 2);
    obstacles.push_back(obstacle5);
    Obstacles* obstacle6 = Obstacles::create(Vec2(142, 613), 3.0, "obstacle/6.png", 100.0f, 200.0f);
    this->addChild(obstacle6, 2);
    obstacles.push_back(obstacle6);
    Obstacles* obstacle7 = Obstacles::create(Vec2(676, 235), 3.0, "obstacle/7.png", 100.0f, 200.0f);
    this->addChild(obstacle7, 2);
    obstacles.push_back(obstacle7);
    Obstacles* obstacle8 = Obstacles::create(Vec2(517, 70), 3.0, "obstacle/8.png", 100.0f, 200.0f);
    this->addChild(obstacle8, 2);
    obstacles.push_back(obstacle8);
}

// ���徲̬��Ա����
GameObject* GameObject::instance = nullptr;
// ��ȡ����ʵ���ľ�̬��Ա������ʵ��
GameObject* GameObject::getInstance()
{
    if (!instance) {
        instance = new GameObject();
    }
    return instance;
}
std::vector<Obstacles*> GameObject::getObstacles()
{
    return obstacles;
}
void GameObject::clear()
{
    delete instance;
}