#include"MapOne.h"
#include "Monster.h"
#define cellHeight 60
#define cellWidth 60

USING_NS_CC;

Scene* mapOne::createScene()
{
    Scene* startScene = Scene::create();
    mapOne* map = mapOne::create();
    startScene->addChild(map);
    return startScene;
}
bool mapOne::init()//第一张地图的初始化
{
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
       return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    //地图背景图设置
    auto background = Sprite::create("mapBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //怪兽路线图设置
    route = Sprite::create("route.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, route->getContentSize().height / 2));
    this->addChild(route, 1);
    //怪兽入口设置
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(6 * cellWidth, 9 * cellHeight));
    this->addChild(monsterEnter, 2);

    //outline框设置
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //金币放置
    goldCoin = cocos2d::Label::createWithTTF("1000", "fonts/Marker Felt.ttf", 24);
    goldCoin->setPosition(Vec2(245, 690));
    this->addChild(goldCoin, 2);

    //障碍物设置
    obstacleDispatch();

    //回调按钮设置
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//回到上一场景的按键
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 4 * returnItem->getContentSize().height));
    auto menu = Menu::create(returnItem, NULL);//创建菜单，将按键加入
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 3);

    fireBottle = nullptr;
    //触摸监听创建
    touchListener = EventListenerTouchOneByOne::create();
    // 绑定触摸的的回调函数
    touchListener->onTouchEnded = CC_CALLBACK_2(mapOne::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapOne::onTouchBegan, this);
    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    Monster* MonsterLayer = Monster::create();
    route->addChild(MonsterLayer, 1);

    return true;
}
bool  mapOne::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    cocos2d::Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));

    if (fireBottle == nullptr)
    {
        if (mouseLocY < 90 || (mouseLocY > 185 && mouseLocY < 290 && mouseLocX > 245 && mouseLocX < 1010) || (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825) || (mouseLocY > 570 && mouseLocY < 655 && mouseLocX > 425 && mouseLocX < 1010) && mousePos != obstacleTree->getPosition())//点击位置可以安装炮塔
        {
            fireBottle = MenuItemImage::create(
                "fireBottle.png",
                "fireBottle.png",
                CC_CALLBACK_1(mapOne::fireBottleGenerate, this));
            Menu* menu = Menu::create(fireBottle, NULL);
            this->addChild(menu, 3);
            //复选框设置
            selectedPos = Sprite::create("choose.png");
            towerPos.x = static_cast<int>(mouseLocX / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2);
            if (mouseLocY >= 570 && mouseLocY < 610)
            {
                towerPos.y = static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 20;
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
                selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
            }
            else
            {
                towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
                selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
            }
            this->addChild(selectedPos, 2);
        }
        else
            CCLOG("Click invalid");
    }
    else
    {
        if (fireBottle->getBoundingBox().containsPoint(mousePos))
        {
            // 点击了fireBottle图标，执行回调函数
            CCLOG("Clicked on the sprite!");
            fireBottleGenerate(fireBottle);
        }
        else
        {
            // 点击了非fireBottle图标，移除fireBottle图标
            CCLOG("Removing fireBottle");
            CCLOG("Clicked outside the sprite!");
            this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
            fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
        }
        removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
    }
    CCLOG("onTouchEnded - End");
    event->stopPropagation();
    return true;
}
bool  mapOne::onTouchBegan(Touch* touch, Event* event)//保证监听器正常运行
{
    return true;
}
void mapOne::obstacleDispatch()
{
    CCLOG("onTouchEnded - Start");

    //障碍物图标设置
    obstacleTree = Sprite::create("obstacleTree.png");//障碍物，树林类型，击落后有少量金钱奖励
    obstacleTree->setPosition(Vec2(6 * cellWidth + 15, 10 * cellHeight));
    this->addChild(obstacleTree, 2);
    //障碍物的进度条设置
    loadingBar = Sprite::create("loadingBar.png");
    loadingBar->setPosition(Vec2(obstacleTree->getPositionX() - obstacleTree->getContentSize().width / 2, obstacleTree->getPositionY() + obstacleTree->getContentSize().height / 2));
    //障碍物血条设置
    loadingBarBlood = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    loadingBarBlood->setPosition(Vec2(obstacleTree->getPositionX() + loadingBarBlood->getContentSize().width, obstacleTree->getPositionY() + obstacleTree->getContentSize().height / 2));
    loadingBarBlood->setMidpoint(Vec2(0, obstacleTree->getPositionX()));
    loadingBar->addChild(loadingBarBlood);
    loadingBarBlood->setPercentage(66);//设置计时器百分比
    this->addChild(loadingBar, 2);
}
void mapOne::fireBottleGenerate(Ref* pSender)//生成火焰瓶的炮塔类
{
}