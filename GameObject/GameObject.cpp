#include "GameObject.h"
#include"Carrot.h"
#include"MonsterOne.h"
#include"MonsterTwo.h"
#include"MonsterManager.h"
#include"MonsterThree.h"
#include"Obstacles.h"
#include "mapChoose.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
GameObject* GameObject::create(int mapCatalog,cocos2d::Label* _goldCoinDisplay)
{
    GameObject* gameobject = new GameObject();
    if (gameobject && gameobject->init(mapCatalog,_goldCoinDisplay))
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
int MonsterManager::round = 0;

bool GameObject::init(int mapCatalog,cocos2d::Label* _goldCoinDisplay)
{
    if (!Node::init())
    {
        return false;
    }
    instance = this;
    mapChoose = mapCatalog;
    goldCoinDisplay = _goldCoinDisplay;
    //�����������Ҫɾ
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(GameObject::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //��ʼ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����ܲ�
    carrotLayer = Carrot::create(mapChoose);
    this->addChild(carrotLayer, 2);
    //�Ӵ�����
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameObject::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    //��ӹ���
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
    if (this != nullptr && objectSprite !=nullptr)
    {
        objectPosition = objectSprite->getPosition();
        return objectPosition;
    }
    else
        return nullptr;
}
//ÿ֡����λ�á�Ѫ��
void GameObject::update(float dt)
{
    getCurrentPosition();
    updateHealthBar(healthBar, initialHealth, currentHealth);
}
//���Ѳ���
void GameObject::setLabel(char* str,Vec2 origin,Size visibleSize)
{
    //��ǩ
    auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 36);
    label->setTextColor(Color4B::YELLOW);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    this->addChild(label, 2);
    //�ӳ������ɾ��
    label->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
}
//��ӹ���
//��ͼһ�ִ���
void GameObject::addMonsterInMapOne()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��һ��
    auto sequenceMonster1 = Sequence::create(
        CallFunc::create([=]()
            {
                SimpleAudioEngine::getInstance()->playEffect("start.MP3", false, 1.0f, 1.0f, 1.0f); }),
                DelayTime::create(3.0f),
            CallFunc::create([=](){
            setLabel("The First Wave",origin,visibleSize);
            //�������
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 4, 0);
        }), 
        DelayTime::create(12.5f),
        CallFunc::create([this]()
            {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 5, 1, 0);
            }),
        // �ڶ�ʱ���ص��м��MonsterManager�Ƿ�Ϊ��
        CallFunc::create([=]() 
            {
                this->schedule([=](float dt) 
                    {
                    if (MonsterManager::getInstance()->IsEmpty()&&MonsterManager::getInstance()->monsterNum==7) 
                    {
                        // ���Ϊ�գ�5�뿪ʼ��һ��
                        MonsterManager::getInstance()->monsterNum = 0;
                        //�ڶ���
                        auto sequenceMonster2 = Sequence::create(
                            DelayTime::create(5.0f), 
                            CallFunc::create([=]() 
                                {
                            this->unschedule("sequenceMonster2");
                            // ��ǩ
                            setLabel("The Second Wave",origin,visibleSize);
                            // ���� 5һ+10��+5��
                            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 4, 0);
                            }), 
                            DelayTime::create(12.5f), 
                            CallFunc::create([this]() 
                                {
                                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 5, 3, 0);
                                }), 
                            DelayTime::create(20.0f), 
                            CallFunc::create([this]() 
                                {
                                    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 0, 0);
                                 }), 
                            // �ڶ�ʱ���ص��м��MonsterManager�Ƿ�Ϊ��
                            CallFunc::create([=]() 
                                {
                                        this->schedule([=](float dt) {
                                            if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 10) {
                                                // ���Ϊ�գ���ʼ��һ��
                                                MonsterManager::getInstance()->monsterNum = 0;
                                                auto sequenceMonster3 = Sequence::create(DelayTime::create(5.0f),
                                                    CallFunc::create([=]() {
                                                    this->unschedule("sequenceMonster3");
                                                    setLabel("The Third Wave", origin, visibleSize);
                                                    // ���� 10һ+10��+10��
                                                    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 9, 0);
                                                    }), DelayTime::create(25.0f), CallFunc::create([this]() {
                                                        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 3, 9, 0);
                                                        }), DelayTime::create(20.0f), CallFunc::create([this]() {
                                                            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 3, 4, 0); }),
                                                            CallFunc::create([=]()
                                                                {
                                                                    this->schedule([=](float dt) {
                                                                        if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 25)
                                                                        {
                                                                            MonsterManager::getInstance()->monsterNum = 0;
                                                                            this->unschedule("GameOver");
                                                                            CCLOG("gameover");
                                                                            gameWinOne();
                                                                        }}, 0.5f, "GameOver"); }), nullptr);
                                                this->runAction(sequenceMonster3);
                                            }}, 0.5f, "sequenceMonster3"); }), nullptr);
                        this->runAction(sequenceMonster2);
                    }}, 0.5f, "sequenceMonster2"); }), nullptr);
    this->runAction(sequenceMonster1);
}
//��ͼ���ִ���
void GameObject::addMonsterInMapTwo()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��һ��
    auto sequenceMonster1 = Sequence::create(
        CallFunc::create([=]()
            {
                SimpleAudioEngine::getInstance()->playEffect("start.MP3", false, 1.0f, 1.0f, 1.0f); }),
                DelayTime::create(3.0f),
                CallFunc::create([=]() {
            setLabel("The First Wave", origin, visibleSize);
            //�������
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 4, 0);
                    }),
        DelayTime::create(12.5f),
        CallFunc::create([this]()
            {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 5, 4, 0);
            }),
        // �ڶ�ʱ���ص��м��MonsterManager�Ƿ�Ϊ��
        CallFunc::create([=]()
            {
                this->schedule([=](float dt)
                    {
                        if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 10)
                        {
                            // ���Ϊ�գ�5�뿪ʼ��һ��
                            MonsterManager::getInstance()->monsterNum = 0;
                            //�ڶ���
                            auto sequenceMonster2 = Sequence::create(
                                DelayTime::create(5.0f),
                                CallFunc::create([=]()
                                    {
                                        this->unschedule("sequenceMonster2");
                                        // ��ǩ
                                        setLabel("The Second Wave", origin, visibleSize);
                                        // ���� 5һ+10��+5��
                                        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 9, 0);
                                    }),
                                DelayTime::create(20.0f),
                                CallFunc::create([this]()
                                    {
                                        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 3, 4, 0);
                                    }),
                                // �ڶ�ʱ���ص��м��MonsterManager�Ƿ�Ϊ��
                                CallFunc::create([=]()
                                    {
                                        this->schedule([=](float dt) {
                                            if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 15) {
                                                // ���Ϊ�գ���ʼ��һ��
                                                MonsterManager::getInstance()->monsterNum = 0;
                                                auto sequenceMonster3 = Sequence::create(DelayTime::create(5.0f),
                                                    CallFunc::create([=]() {
                                                        this->unschedule("sequenceMonster3");
                                                        setLabel("The Third Wave", origin, visibleSize);
                                                        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 4, 0);
                                                        }), DelayTime::create(12.5f),
                                                            CallFunc::create([this]() {
                                                            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 3, 4, 0);
                                                            }), DelayTime::create(15.0f), CallFunc::create([this]() {
                                                                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 3, 4, 0); }),
                                                                CallFunc::create([=]()
                                                                    {
                                                                        this->schedule([=](float dt) {
                                                                            if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 15)
                                                                            {
                                                                                MonsterManager::getInstance()->monsterNum = 0;
                                                                                this->unschedule("sequenceMonster4");
                                                                                auto sequenceMonster4 = Sequence::create(DelayTime::create(5.0f),
                                                                                    CallFunc::create([=]() {
                                                                                        this->unschedule("sequenceMonster4");
                                                                                        setLabel("The Third Wave", origin, visibleSize);
                                                                                        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2.5, 4, 0);
                                                                                        }), DelayTime::create(12.5f),
                                                                                            CallFunc::create([this]() {
                                                                                            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 9, 0);
                                                                                                }), DelayTime::create(20.0f), CallFunc::create([this]() {
                                                                                                    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 3, 9, 0); }),
                                                                                                    CallFunc::create([=]()
                                                                                                        {
                                                                                                            this->schedule([=](float dt) {
                                                                                                                if (MonsterManager::getInstance()->IsEmpty() && MonsterManager::getInstance()->monsterNum == 25)
                                                                                                                {
                                                                                                                    MonsterManager::getInstance()->monsterNum = 0;
                                                                                                                    this->unschedule("GameOver");
                                                                                                                    CCLOG("gameover");
                                                                                                                    gameWinTwo();
                                                                                                                }}, 0.5f, "GameOver"); }), nullptr);
                                                                                this->runAction(sequenceMonster4);
                                                                            }}, 0.5f, "sequenceMonster4"); }), nullptr);
                                                this->runAction(sequenceMonster3);
                                            }}, 0.5f, "sequenceMonster3"); }), nullptr);
                            this->runAction(sequenceMonster2);
                        }}, 0.5f, "sequenceMonster2"); }), nullptr);
    this->runAction(sequenceMonster1);
}

void GameObject::addMonsterOne(float dt)
{
    MonsterOne* MonsterOneLayer = MonsterOne::create(carrotLayer, mapChoose);
    this->addChild(MonsterOneLayer, 2);
    SimpleAudioEngine::getInstance()->playEffect("addmonster.MP3", false, 1.0f, 1.0f, 1.0f);
    MonsterManager::getInstance()->addMonster(MonsterOneLayer);
}
void GameObject::addMonsterTwo(float dt)
{
    MonsterTwo* MonsterTwoLayer = MonsterTwo::create(carrotLayer, mapChoose);
    this->addChild(MonsterTwoLayer, 2);
    SimpleAudioEngine::getInstance()->playEffect("addmonster.MP3", false, 1.0f, 1.0f, 1.0f);
    MonsterManager::getInstance()->addMonster(MonsterTwoLayer);
}
void GameObject::addMonsterThree(float dt)
{
    MonsterThree* MonsterThreeLayer = MonsterThree::create(carrotLayer, mapChoose);
    this->addChild(MonsterThreeLayer, 2);
    SimpleAudioEngine::getInstance()->playEffect("addmonster.MP3", false, 1.0f, 1.0f, 1.0f);
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
    int v = monster->speed;
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
//�ڶ�����ͼ·��
Sequence* GameObject::MoveWayInMapTwo(GameObject* monster)
{
    int v = monster->speed;
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
    float time10 = (Vec2(875, 270) - Vec2(875, 437)).getLength() / v;
    auto moveTo10 = MoveTo::create(time10, Vec2(875, 270));
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
void GameObject::updateHealthBar(ProgressTimer* healthBar, int initialHealthValue, int currentHealth)
{
    if (currentHealth < initialHealthValue)
    {
        healthBarBG->setVisible(true);
        healthBar->setVisible(true);
    }
    float healthPercentage = (static_cast<float>(currentHealth) / initialHealthValue) * 100.0f;
    healthBar->setPercentage(healthPercentage);
}
void  GameObject::hitMonster(Node*node, int num, float scale,char* filename)
{
    Sprite* sprite = dynamic_cast<Sprite*>(node);
    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
    monster->currentHealth -= num;
    auto hit = Sprite::create(filename);
    //������Ч
    hit->setScale(scale);
    sprite->addChild(hit, 2);
    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
    hit->runAction(Sequence::create(DelayTime::create(0.1f), RemoveSelf::create(), nullptr));
    if (monster->currentHealth <= 0)
    {
        SimpleAudioEngine::getInstance()->playEffect("monsterdie.MP3", false, 1.0f, 1.0f, 1.0f);
        goldCoin += monster->coinValue;
        goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
        monster->unscheduleUpdate();
        monster->runAction(RemoveSelf::create());
        MonsterManager::getInstance()->removeMonster(monster);
    }
}
void GameObject::hitObstacle(Node* node, int num, float scale, char* filename)
{
    Sprite* sprite = dynamic_cast<Sprite*>(node);
    GameObject* obstacle = dynamic_cast<GameObject*>(sprite->getParent());
    obstacle->currentHealth -= num;
    auto hit = Sprite::create(filename);
    sprite->addChild(hit, 2);
    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
    hit->runAction(Sequence::create(DelayTime::create(0.5f), RemoveSelf::create(), nullptr));
    if (obstacle->currentHealth <= 0)
    {
        SimpleAudioEngine::getInstance()->playEffect("obstacledie.MP3", false, 1.0f, 1.0f, 1.0f);
        goldCoin += obstacle->coinValue;
        goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
        obstacle->unscheduleUpdate();
        removeObstacle(obstacle);
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
            if (tagA == MONSTER && tagB == SUNFLOWERBULLET1 || tagA == SUNFLOWERBULLET1 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, SUNFLOWERBULLET1, 0.5, "SunFlower_Hit.png");
                else
                    hitMonster(nodeB, SUNFLOWERBULLET1, 0.5, "SunFlower_Hit.png");
            }
            if (tagA == MONSTER && tagB == SUNFLOWERBULLET2 || tagA == SUNFLOWERBULLET2 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, SUNFLOWERBULLET2, 1, "SunFlower_Hit.png");
                else
                    hitMonster(nodeB, SUNFLOWERBULLET2, 1, "SunFlower_Hit.png");
            }
            if (tagA == MONSTER && tagB == SUNFLOWERBULLET3 || tagA == SUNFLOWERBULLET3 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, SUNFLOWERBULLET3, 1.5, "SunFlower_Hit.png");
                else
                    hitMonster(nodeB, SUNFLOWERBULLET3, 1.5, "SunFlower_Hit.png");
            }
            //����
            if (tagA == MONSTER && tagB == LEAFBULLET1 || tagA == LEAFBULLET1 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAFBULLET1, 0.5,"Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAFBULLET1, 0.5,"Leaf_Hit.png");
            }
            if (tagA == MONSTER && tagB == LEAFBULLET2 || tagA == LEAFBULLET2 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAFBULLET2, 1, "Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAFBULLET2, 1, "Leaf_Hit.png");
            }
            if (tagA == MONSTER && tagB == LEAFBULLET3 || tagA == LEAFBULLET3 && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                    hitMonster(nodeA, LEAFBULLET3, 1.5, "Leaf_Hit.png");
                else
                    hitMonster(nodeB, LEAFBULLET3, 1.5, "Leaf_Hit.png");
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
            if (tagA == OBSTACLE && tagB == SUNFLOWERBULLET1 || tagA == SUNFLOWERBULLET1 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, SUNFLOWERBULLET1, 0.5, "SunFlower_Hit.png");
                else
                    hitObstacle(nodeB, SUNFLOWERBULLET1, 0.5, "SunFlower_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == SUNFLOWERBULLET2 || tagA == SUNFLOWERBULLET2 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, SUNFLOWERBULLET2, 1, "SunFlower_Hit.png");
                else
                    hitObstacle(nodeB, SUNFLOWERBULLET2, 1, "SunFlower_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == SUNFLOWERBULLET3 || tagA == SUNFLOWERBULLET3 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, SUNFLOWERBULLET3, 1.5, "SunFlower_Hit.png");
                else
                    hitObstacle(nodeB, SUNFLOWERBULLET3, 1.5, "SunFlower_Hit.png");
            }
            //����
            if (tagA == OBSTACLE && tagB == LEAFBULLET1 || tagA == LEAFBULLET1 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAFBULLET1, 0.5, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAFBULLET1, 0.5, "Leaf_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LEAFBULLET2 || tagA == LEAFBULLET2 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAFBULLET2, 1, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAFBULLET2, 1, "Leaf_Hit.png");
            }
            if (tagA == OBSTACLE && tagB == LEAFBULLET3 || tagA == LEAFBULLET3 && tagB == OBSTACLE)
            {
                if (tagA == OBSTACLE)
                    hitObstacle(nodeA, LEAFBULLET3, 1.5, "Leaf_Hit.png");
                else
                    hitObstacle(nodeB, LEAFBULLET3, 1.5, "Leaf_Hit.png");
            }
        }
    }
    return true;
}

void GameObject::addObstaclesInMapOne()
{
    obstacles.clear();
    Obstacles* obstacle1 = Obstacles::create(Vec2(538, 434), 2.0, "obstacle/obstacle1.png", 100.0f, 200.0f);
    obstacle1->setScale(1.05);
    this->addChild(obstacle1, 2);
    obstacles.push_back(obstacle1);
    Obstacles* obstacle2 = Obstacles::create(Vec2(637, 600), 1.5, "obstacle/obstacle2.png", 100.0f, 200.0f);
    obstacle2->setScale(1.05);
    this->addChild(obstacle2, 2);
    obstacles.push_back(obstacle2);
    Obstacles* obstacle3 = Obstacles::create(Vec2(714, 434), 2.0, "obstacle/obstacle3.png", 100.0f, 200.0f);
    this->addChild(obstacle3, 2);
    obstacles.push_back(obstacle3);
    Obstacles* obstacle4 = Obstacles::create(Vec2(233, 419), 2.0, "obstacle/obstacle4.png", 100.0f, 200.0f);
    obstacle4->setScale(1.05);
    this->addChild(obstacle4, 2);
    obstacles.push_back(obstacle4);
    Obstacles* obstacle5 = Obstacles::create(Vec2(530, 69), 2.5, "obstacle/obstacle5.png", 100.0f, 200.0f);
    this->addChild(obstacle5, 2);
    obstacles.push_back(obstacle5);
}

//void GameObject::addObstaclesInMapTwo()
//{
//    obstacles.clear();
//    Obstacles* obstacle1 = Obstacles::create(Vec2(648, 424), 2.0, "obstacle/1.png", 100.0f, 200.0f);
//    this->addChild(obstacle1, 2);
//    obstacles.push_back(obstacle1);
//    Obstacles* obstacle2 = Obstacles::create(Vec2(811, 617), 1.5, "obstacle/2.png", 100.0f, 200.0f);
//    this->addChild(obstacle2, 2);
//    obstacles.push_back(obstacle2);
//    Obstacles* obstacle3 = Obstacles::create(Vec2(215, 433), 2.0, "obstacle/3.png", 100.0f, 200.0f);
//    this->addChild(obstacle3, 2);
//    obstacles.push_back(obstacle3);
//    Obstacles* obstacle4 = Obstacles::create(Vec2(592, 333), 2.0, "obstacle/4.png", 100.0f, 200.0f);
//    this->addChild(obstacle4, 2);
//    obstacles.push_back(obstacle4);
//    Obstacles* obstacle5 = Obstacles::create(Vec2(872, 151), 2.5, "obstacle/5.png", 100.0f, 200.0f);
//    this->addChild(obstacle5, 2);
//    obstacles.push_back(obstacle5);
//    Obstacles* obstacle6 = Obstacles::create(Vec2(142, 613), 3.0, "obstacle/6.png", 100.0f, 200.0f);
//    this->addChild(obstacle6, 2);
//    obstacles.push_back(obstacle6);
//    Obstacles* obstacle7 = Obstacles::create(Vec2(676, 235), 3.0, "obstacle/7.png", 100.0f, 200.0f);
//    this->addChild(obstacle7, 2);
//    obstacles.push_back(obstacle7);
//    Obstacles* obstacle8 = Obstacles::create(Vec2(517, 70), 3.0, "obstacle/8.png", 100.0f, 200.0f);
//    this->addChild(obstacle8, 2);
//    obstacles.push_back(obstacle8);
//}
void GameObject::addObstaclesInMapTwo()
{
    obstacles.clear();
    Obstacles* obstacle1 = Obstacles::create(Vec2(648, 424), 2.0, "obstacle/1.png", 100.0f, 200.0f);
    this->addChild(obstacle1, 2);
    obstacles.push_back(obstacle1);
    Obstacles* obstacle2 = Obstacles::create(Vec2(811, 617), 1.5, "obstacle/2.png", 100.0f, 200.0f);
    this->addChild(obstacle2, 2);
    obstacles.push_back(obstacle2);
    Obstacles* obstacle3 = Obstacles::create(Vec2(232, 433), 2.0, "obstacle/3.png", 100.0f, 200.0f);
    this->addChild(obstacle3, 2);
    obstacles.push_back(obstacle3);
    Obstacles* obstacle4 = Obstacles::create(Vec2(596, 355), 2.0, "obstacle/4.png", 100.0f, 200.0f);
    this->addChild(obstacle4, 2);
    obstacles.push_back(obstacle4);
    Obstacles* obstacle5 = Obstacles::create(Vec2(887, 151), 2.5, "obstacle/5.png", 100.0f, 200.0f);
    this->addChild(obstacle5, 2);
    obstacles.push_back(obstacle5);
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
void GameObject::removeObstacle(GameObject* obstacle)
{
    auto it = std::find(obstacles.begin(), obstacles.end(), obstacle);
    if (it != obstacles.end())
    {
        obstacles.erase(it);
        obstacle = nullptr;
    }
}

void GameObject::setMonsterPhysicsBody()
{
    cocos2d::Size smallerSize(objectSprite->getContentSize().width * 0.1f, objectSprite->getContentSize().height * 0.1f);
    auto physicsBody = PhysicsBody::createBox(objectSprite->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    objectSprite->setTag(MONSTER);
    objectSprite->setPhysicsBody(physicsBody);
}
