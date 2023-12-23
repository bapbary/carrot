#include "Monster.h"

USING_NS_CC;
//背景
Scene* basic::createScene()
{
    return basic::create();
}
bool basic::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(basic::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto background = Sprite::create("mapBackground.png");//地图背景图
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    auto route = Sprite::create("route.png");//怪兽路线
    route->setScale(visibleSize.width / route->getContentSize().width, visibleSize.height / route->getContentSize().height);
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(route, 1);
    Monster* MonsterLayer = Monster::create();
    this->addChild(MonsterLayer,2);
    return true;
}

bool Monster::init()
{
    if (!Node::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Carrot* carrotLayer = Carrot::create();
    this->addChild(carrotLayer, 2);

    srand((unsigned int)time(nullptr));
    // 每隔1.5秒生成一个怪物
    this->schedule(CC_SCHEDULE_SELECTOR(Monster::addMonster), 1.5, 10, 0);
    return true;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
//萝卜初始化
bool Carrot::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //萝卜的动画帧
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    auto spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    this->addChild(spriteCarrot,2);
    spriteCarrot->setPosition(666, 215);
    //镜像翻转

    spriteCarrot->setScaleX(-3.8);
    spriteCarrot->setScaleY(3.8);

    //帧速率
    auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
    spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));
    return true;
}
//怪物1初始化
bool MonsterOne::init()
{
    if (!Node::init())
    {
        return false;
    }
    float currentHealthValue=InitialHealthValue;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //怪物1的动画帧
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterOne = getAnimation("monster1/%04d.png", 2);
    auto spriteMonsterOne = Sprite::createWithSpriteFrame(framesMonsterOne.front());
    this->addChild(spriteMonsterOne, 2);
    //缩放
    spriteMonsterOne->setScale(1.9, 1.9);
    spriteMonsterOne->setOpacity(0);
    spriteMonsterOne->setPosition(383, 701);
    //设置血条
    setHealthBar(spriteMonsterOne, currentHealthValue, InitialHealthValue);
    //帧速率
    auto animationMonsterOne = Animation::createWithSpriteFrames(framesMonsterOne, 1.0f / 3);
    spriteMonsterOne->runAction(RepeatForever::create(Animate::create(animationMonsterOne)));
    auto moveAction = MoveWayInMapOne(); // 将移动动作保存起来
    spriteMonsterOne->runAction(moveAction);
    return true;
}
void Monster::setHealthBar(Node* monster,float currentHealthValue,float InitialHealthValue)
{
    auto healthBarBG = Sprite::create("loadingBar.png");
    healthBarBG->setScale(0.7);
    healthBarBG->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // 设置血条底座的位置
    monster->addChild(healthBarBG, 1);
    auto healthBar = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setScale(0.7);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setPosition(Vec2(monster->getContentSize().width / 2, monster->getContentSize().height));  // 设置血条的位置
    monster->addChild(healthBar, 2);
    float healthPercentage = (currentHealthValue / InitialHealthValue) * 100.0f;
    updateHealthBar(healthBar, healthPercentage);
}
bool MonsterTwo::init()
{
    if (!Node::init())
    {
        return false;
    }
    float currentHealthValue = InitialHealthValue;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //怪物2的动画帧
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesMonsterTwo = getAnimation("monster2/%04d.png", 3);
    auto spriteMonsterTwo = Sprite::createWithSpriteFrame(framesMonsterTwo.front());
    this->addChild(spriteMonsterTwo, 2);
    //缩放
    spriteMonsterTwo->setScale(1.9, 1.9);
    spriteMonsterTwo->setOpacity(100);
    spriteMonsterTwo->setPosition(383, 701);
    setHealthBar(spriteMonsterTwo, currentHealthValue, InitialHealthValue);
    //帧速率
    auto animationMonsterTwo = Animation::createWithSpriteFrames(framesMonsterTwo, 1.0f / 3);
    spriteMonsterTwo->runAction(RepeatForever::create(Animate::create(animationMonsterTwo)));
    auto moveAction = MoveWayInMapOne(); // 将移动动作保存起来
    spriteMonsterTwo->runAction(moveAction);
    return true;
}

void basic::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
//生成帧序列
Vector<SpriteFrame*> Monster::getAnimation(const char* format, int count)
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

Sequence* Monster::MoveWayInMapOne()
{
    auto fadeIn = FadeIn::create(0.5f);
    auto moveTo1 = MoveTo::create(2, Vec2(806, 701));
    auto moveTo2 = MoveTo::create(2, Vec2(806, 455));
    auto scaleXAction = ScaleBy::create(0.5f, -1.0f, 1.0f);
    auto moveTo3 = MoveTo::create(2, Vec2(227, 455));
    auto moveTo4 = MoveTo::create(2, Vec2(227, 207));
    auto moveTo5 = MoveTo::create(2, Vec2(647, 207));
    auto fadeOut = FadeOut::create(0.5f);
    auto actionRemove = RemoveSelf::create();
    auto seq = Sequence::create(fadeIn,moveTo1, moveTo2, scaleXAction, moveTo3,  moveTo4, scaleXAction, moveTo5, fadeOut,actionRemove, nullptr);
    return seq;
}
void basic::onMouseMove(Event* event)
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
void Monster::addMonster(float dt)
{
    MonsterOne* MonsterOneLayer = MonsterOne::create();
    this->addChild(MonsterOneLayer, 2);
    auto delayAction = DelayTime::create(2.0f);
    auto addMonsterTwoAction = CallFunc::create([this]() {
        MonsterTwo* MonsterTwoLayer = MonsterTwo::create();
        this->addChild(MonsterTwoLayer, 2);
        });
    // 将两个动作组合在一起
    auto sequence = Sequence::create(delayAction, addMonsterTwoAction, nullptr);

    // 运行 Sequence
    this->runAction(sequence);
}
void Monster::updateHealthBar(ProgressTimer* healthBar,float percentage) {
    healthBar->setPercentage(percentage);
}