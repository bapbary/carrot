#include "GameObject.h"
#include"Carrot.h"
#include"MonsterOne.h"
#include"MonsterTwo.h"
#include"MonsterManager.h"
#include"MonsterThree.h"
USING_NS_CC;
int count = 0;
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
    mapChoose = mapCatalog;
    //鼠标监听，最后要删
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(GameObject::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //初始化
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //添加萝卜
    carrotLayer = Carrot::create(mapChoose);
    this->addChild(carrotLayer, 2);
    //接触监听
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameObject::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    //添加怪物
    if (mapChoose == 1)
        addMonsterInMapOne();
    else
        addMonsterInMapTwo();
    return true;
}
//获取精灵
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
//获取当前位置
cocos2d::Vec2 GameObject::getCurrentPosition()
{
    objectPosition = objectSprite->getPosition();
    return objectPosition;
}
//每帧更新位置、血量
void GameObject::update(float dt)
{
    getCurrentPosition();
    updateHealthBar(healthBar, initialHealthValue, currentHealthValue);
}
//添加怪物
//地图一轮次三
void GameObject::addMonsterInMapOne()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //第一波
    auto sequenceMonster1 = Sequence::create(CallFunc::create([=]() {
    //第一波标签
    auto label1 = Label::createWithTTF("The First Wave", "fonts/Marker Felt.ttf", 36);
    label1->setTextColor(Color4B::YELLOW);
    label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label1->getContentSize().height));
    this->addChild(label1, 2);
    //延迟两秒后删除
    label1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
    //怪物加入
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
    }), DelayTime::create(2.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(1.5f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
            }), DelayTime::create(38.0f), nullptr);
    //第二波
    auto sequenceMonster2 = Sequence::create(CallFunc::create([=]() {
        // 标签
    auto label2 = Label::createWithTTF("The Second Wave", "fonts/Marker Felt.ttf", 36); 
    label2->setTextColor(Color4B::YELLOW);
    label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label2->getContentSize().height));
    this->addChild(label2, 2); 
    // 延迟两秒后删除
    label2->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
    // 怪物 5一+10二+5三
    this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 5, 0);
    }), DelayTime::create(5.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
        }), DelayTime::create(2.0f), CallFunc::create([this]() {
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(25.0f), nullptr);
    //第三波
    auto sequenceMonster3 = Sequence::create( CallFunc::create([=]() {
        // 标签
        auto label3 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label3->setTextColor(Color4B::YELLOW);
        label3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label3->getContentSize().height));
        this->addChild(label3, 2);
        // 延迟两秒后删除
        label3->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // 怪物 10一+10二+10三
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
        }), DelayTime::create(1.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
            }), DelayTime::create(1.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
                }), DelayTime::create(25.0f), nullptr);
    this->runAction(Sequence::create(sequenceMonster1, sequenceMonster2, sequenceMonster3,nullptr));
}
//地图二轮次四
void GameObject::addMonsterInMapTwo()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //第一波
    auto sequenceMonster1 = Sequence::create(CallFunc::create([=]() {
        //第一波标签
        auto label1 = Label::createWithTTF("The First Wave", "fonts/Marker Felt.ttf", 36);
        label1->setTextColor(Color4B::YELLOW);
        label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label1->getContentSize().height));
        this->addChild(label1, 2);
        //延迟两秒后删除
        label1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        //怪物加入
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
        }), DelayTime::create(5.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 10, 0);
            }), DelayTime::create(10.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 5, 0);
                }), DelayTime::create(40.0f), nullptr);
    //第二波
    auto sequenceMonster2 = Sequence::create(CallFunc::create([=]() {
        // 标签
        auto label2 = Label::createWithTTF("The Second Wave", "fonts/Marker Felt.ttf", 36);
        label2->setTextColor(Color4B::YELLOW);
        label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label2->getContentSize().height));
        this->addChild(label2, 2);
        // 延迟两秒后删除
        label2->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // 怪物 5一+10二+10三
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 5, 0);
        }), DelayTime::create(5.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
            }), DelayTime::create(2.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
                }), DelayTime::create(45.0f), nullptr);
    //第三波
    auto sequenceMonster3 = Sequence::create(CallFunc::create([=]() {
        // 标签
        auto label3 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label3->setTextColor(Color4B::YELLOW);
        label3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label3->getContentSize().height));
        this->addChild(label3, 2);
        // 延迟两秒后删除
        label3->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // 怪物 15一+10二+10三
        this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterOne), 2, 15, 0);
        }), DelayTime::create(1.0f), CallFunc::create([this]() {
            this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterThree), 2, 10, 0);
            }), DelayTime::create(1.0f), CallFunc::create([this]() {
                this->schedule(CC_SCHEDULE_SELECTOR(GameObject::addMonsterTwo), 2, 10, 0);
                }), DelayTime::create(45.0f), nullptr);
    //第四波
    auto sequenceMonster4 = Sequence::create(CallFunc::create([=]() {
        // 标签
        auto label4 = Label::createWithTTF("The Third Wave", "fonts/Marker Felt.ttf", 36);
        label4->setTextColor(Color4B::YELLOW);
        label4->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label4->getContentSize().height));
        this->addChild(label4, 2);
        // 延迟两秒后删除
        label4->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
        // 怪物 15一+10二+10三
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
    healthBarBG->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // 设置血条底座的位置
    monster->addChild(healthBarBG, 1);
    healthBarBG->setVisible(false);
    healthBar = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setScale(0.7);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setVisible(false);
    healthBar->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // 设置血条的位置
    monster->addChild(healthBar, 2);
    float healthPercentage = (currentHealthValue / initialHealthValue) * 100.0f;
    updateHealthBar(healthBar, initialHealthValue, currentHealthValue);
}

void GameObject::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
//生成帧序列
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
//第一个地图的路径
Sequence* GameObject::MoveWayInMapOne(GameObject* monster)
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
        monster->unscheduleUpdate();
        });
    auto actionRemove = RemoveSelf::create();
    auto seq = Sequence::create(fadeIn, moveTo1, moveTo2, scaleXAction, moveTo3, moveTo4, scaleXAction, moveTo5, fadeOut, nullptr);
    return seq;
}
Sequence* GameObject::MoveWayInMapTwo(GameObject* monster)
{
    float v = monster->speed;
    auto fadeIn = FadeIn::create(0.1f);
    float time1 = (Vec2(928, 131) - monster->objectPosition).getLength() / v;
    auto moveTo1 = MoveTo::create(time1, Vec2(928, 131));
    float time2 = (Vec2(674, 131) - Vec2(928, 131)).getLength() / v;
    auto moveTo2 = MoveTo::create(time2, Vec2(674, 131));
    auto scaleXAction = ScaleBy::create(0, -1.0f, 1.0f);
    float time3 = (Vec2(674, 307) - Vec2(664, 131)).getLength() / v;
    auto moveTo3 = MoveTo::create(time3, Vec2(674, 307));
    float time4 = (Vec2(414, 307) - Vec2(674, 307)).getLength() / v;
    auto moveTo4 = MoveTo::create(time4, Vec2(414, 307));
    float time5 = (Vec2(414, 307) - Vec2(414,140)).getLength() / v;
    auto moveTo5 = MoveTo::create(time5, Vec2(414, 140));
    float time6 = (Vec2(246, 140) - Vec2(414, 140)).getLength() / v;
    auto moveTo6 = MoveTo::create(time6, Vec2(246, 140));
    float time7 = (Vec2(246, 393) - Vec2(246, 140)).getLength() / v;
    auto moveTo7 = MoveTo::create(time7, Vec2(246, 393));
    float time8 = (Vec2(90, 393) - Vec2(246, 140)).getLength() / v;
    auto moveTo8 = MoveTo::create(time8, Vec2(90, 393));
    auto fadeOut = FadeOut::create(0.1f);
    auto arrive = CallFunc::create([=]() {
        carrotLayer->decreaseHealth();
        monster->unscheduleUpdate();
        });
    auto actionRemove = RemoveSelf::create();
    auto seq = Sequence::create(fadeIn, scaleXAction, moveTo1, moveTo2,  moveTo3, moveTo4, moveTo5, moveTo6,moveTo7,moveTo8,fadeOut, arrive, actionRemove, nullptr);
    return seq;
}

//鼠标移动显示坐标
void GameObject::onMouseMove(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        // 获取鼠标坐标
        Vec2 mousePosition = Vec2(e->getCursorX(), e->getCursorY());
        //// 将鼠标坐标转换为 OpenGL 坐标系下的坐标
        //mousePosition = Director::getInstance()->convertToGL(mousePosition);

        // 显示坐标信息（左下角）
        auto label = Label::createWithTTF(StringUtils::format("Mouse Position: %.2f, %.2f", mousePosition.x, mousePosition.y), "fonts/arial.ttf", 24);
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2::ZERO);
        this->removeChildByTag(123); // 移除之前的 label
        this->addChild(label, 5, 123);
    }
}
//生命值
void GameObject::updateHealthBar(ProgressTimer* healthBar, float initialHealthValue, float currentHealthValue)
{
    if (currentHealthValue < initialHealthValue)
    {
        healthBar->setVisible(true);
        healthBar->setVisible(true);
    }
    float healthPercentage = (currentHealthValue / initialHealthValue) * 100.0f;
    healthBar->setPercentage(healthPercentage);
}
//接触
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
            // 怪物和萝卜接触
            if (tagA == CARROT && tagB == MONSTER || tagA == MONSTER && tagB == CARROT)
            {
                if (tagA == MONSTER)
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeA);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    carrotLayer->decreaseHealth();
                    monster->unscheduleUpdate();
                    MonsterManager::getInstance()->removeMonster(monster);
                    monster->runAction(RemoveSelf::create());
                }
                else
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeB);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    carrotLayer->decreaseHealth();
                    monster->unscheduleUpdate();
                    MonsterManager::getInstance()->removeMonster(monster);
                    monster->runAction(RemoveSelf::create());
                }
            }
            //怪物和子弹接触
            if (tagA == MONSTER && tagB == LIGHTINGBULLET || tagA == LIGHTINGBULLET && tagB == MONSTER)
            {
                if (tagA == MONSTER)
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeA);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    monster->currentHealthValue -= float(LIGHTINGBULLET);
                    auto hit = Sprite::create("Lighting_Hit.png");
                    sprite->addChild(hit, 2);
                    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
                    hit->runAction(Sequence::create(DelayTime::create(0.5f), RemoveSelf::create(),nullptr));
                    if(monster->currentHealthValue<=0)
                    {
                        monster->unscheduleUpdate();
                        monster->runAction(RemoveSelf::create());
                    }
                }
                else
                {
                    Sprite* sprite = dynamic_cast<Sprite*>(nodeB);
                    GameObject* monster = dynamic_cast<GameObject*>(sprite->getParent());
                    monster->currentHealthValue -= float(LIGHTINGBULLET);
                    auto hit = Sprite::create("Lighting_Hit.png");
                    sprite->addChild(hit, 2);
                    hit->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
                    hit->runAction(Sequence::create(DelayTime::create(0.5f), RemoveSelf::create(), nullptr));
                    if (monster->currentHealthValue <= 0)
                    {
                        monster->unscheduleUpdate();
                        monster->runAction(RemoveSelf::create());
                    }
                }
            }
        }
    }
    return true;
}
