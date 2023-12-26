#include"MapOne.h"
#include"TowerManager.h"
#include"FireTower.h"
#include"LeafTower.h"
#include"LightingTower.h"
#include<string>
#define cellHeight 60
#define cellWidth 60

USING_NS_CC;

Scene* mapOne::createScene()
{
    //Scene* startScene = Scene::create();
    //mapOne* map = mapOne::create();
    //startScene->addChild(map);
    auto scene = Scene::createWithPhysics();
    auto layer = mapOne::create();
    scene->addChild(layer);
    return scene;
}
bool mapOne::init()//第一张地图的初始化
{
    if (!Layer::init())
    {
        return false;
    }  
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::tower_targetupdate), 1.0f, CC_REPEAT_FOREVER, 0);
    visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

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
    //怪物加入
    GameObject* monster = GameObject::create();
    this->addChild(monster, 2);
    //outline框设置
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //金币放置
    goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);

    //障碍物设置
    obstacleDispatch();

    //回调按钮设置
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));//回到上一场景的按键
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
    touchListener->onTouchEnded = CC_CALLBACK_2(mapChoose::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapChoose::onTouchBegan, this);
    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool mapOne::ifSafe(cocos2d::Vec2 mousePos)//判断点击到的是否为炮塔位置是否合法
{
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    if (mouseLocY < 100 || (mouseLocY > 185 && mouseLocY < 290 && mouseLocX > 245 && mouseLocX < 1010) || (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825) || (mouseLocY > 570 && mouseLocY < 655 && mouseLocX > 425 && mouseLocX < 1010) || (mouseLocY < 570 && mouseLocY>295 && mouseLocX > 915) || (mouseLocY < 360 && mouseLocY>100 && mouseLocX < 160 && mouseLocX>40))
        return true;
    else
        return false;
}
void mapOne::selectedPosSet(float mouseLocX, float mouseLocY)
{
    towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
    if (mouseLocY >= 570 && mouseLocY < 610)
    {
        towerPos.y = static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 10;
        fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else
    {
        towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
        fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }

}
void mapOne::obstacleDispatch()
{
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
