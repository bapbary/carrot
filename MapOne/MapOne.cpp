#include"MapOne.h"
#include"TowerManager.h"
#include"MonsterManager.h"
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

    goldCoin = 1000;
    visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小
    //炮塔攻击更新调度器启用，三种不同炮塔分开调用
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate1), 1.5, CC_REPEAT_FOREVER, 0);
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate2), 0.2, CC_REPEAT_FOREVER, 0);
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate3), 0.8, CC_REPEAT_FOREVER, 0);

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
    //金币放置
    goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);
    //怪物加入
    GameObject* monster = GameObject::create(1, goldCoinDisplay);
    this->addChild(monster, 2);
    //outline框设置
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //暂停键放置
    auto suspend = MenuItemImage::create(
        "suspendItem.png",
        "suspendItem.png",
        CC_CALLBACK_1(mapChoose::suspend, this));
    suspend->setPosition(Vec2(325, 325));

    auto menu = Menu::create(suspend, NULL);//创建菜单，将按键加入
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 3);

    sunFlower = nullptr;
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
    if ((mouseLocY < 95 && mouseLocY > 40 && mouseLocX > 300 && mouseLocX < 1010) || (mouseLocY > 180 && mouseLocY < 300 && mouseLocX > 245 && mouseLocX < 1010 && !(mouseLocY > 180 && mouseLocY < 240 && mouseLocX > 660 && mouseLocX < 780)) || (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825) || (mouseLocY > 570 && mouseLocY < 655 && mouseLocX > 300 && mouseLocX < 1010) || (mouseLocY < 570 && mouseLocY>295 && mouseLocX > 915 && mouseLocX < 1018) || (mouseLocY < 360 && mouseLocY>100 && mouseLocX < 160 && mouseLocX>50))
        return true;
    else
        return false;
}
void mapOne::selectedPosSet(float mouseLocX, float mouseLocY)
{
    if (mouseLocY >= 570 && mouseLocY < 610)
    {
        towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
        towerPos.y = static_cast<int>((mouseLocY - 15) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 15;
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 15) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 15);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 15) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 15);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 15) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else if (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825)
    {
        towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
        towerPos.y = static_cast<int>((mouseLocY - 20) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 20;
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 20) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 20) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 20) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else if (mouseLocY < 360 && mouseLocY>100 && mouseLocX < 160 && mouseLocX>50)
    {
        towerPos.x = static_cast<int>((mouseLocX + 10) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 10;
        towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else if (mouseLocY < 570 && mouseLocY > 295 && mouseLocX > 915 && mouseLocX < 1018)
    {
        towerPos.x = static_cast<int>((mouseLocX - 10) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) + 10;
        towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else if (mouseLocY < 95 && mouseLocY > 35 && mouseLocX > 300 && mouseLocX < 1010)
    {
        towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
        towerPos.y = static_cast<int>((mouseLocY + 25) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) - 25;
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY + 25) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 - 25);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY + 25) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 - 25);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY + 25) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 - 25);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }
    else
    {
        towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
        towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
        sunFlower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
    }

}
void mapOne::tryAgain(Ref* pSender)
{
    TowerManager::getInstance()->clearTowers();//删除上个地图中残留的炮塔管理器
    MonsterManager::getInstance()->clearMonster();//删除上个地图中残留的怪物管理器
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//弹出暂停页面
    Director::getInstance()->popScene();//弹出游戏页面
    enterMapOne(this);
}