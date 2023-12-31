#include"MapTwo.h"
#include"TowerManager.h"
#include"MonsterManager.h"

#define cellHeight 60
#define cellWidth 60

USING_NS_CC;
Scene* mapTwo::createScene()
{
    //Scene* startScene = Scene::create();
    //mapTwo* map = mapTwo::create();
    //startScene->addChild(map);
    //return startScene;
    auto scene = Scene::createWithPhysics();
    auto layer = mapTwo::create();
    scene->addChild(layer);
    return scene;

}
bool mapTwo::init()//第一张地图的初始化
{
    if (!Layer::init())
    {
        return false;
    }
    goldCoin = 10000;

    visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    //炮塔攻击更新调度器启用
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate1), 1.5, CC_REPEAT_FOREVER, 0);
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate2), 0.2, CC_REPEAT_FOREVER, 0);
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::towerTargetUpdate3), 0.8, CC_REPEAT_FOREVER, 0);

    //地图背景图设置
    auto background = Sprite::create("mapBackgroundTwo.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //怪兽路线图设置
    route = Sprite::create("routeTwo.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x , route->getContentSize().height / 2 + origin.y));
    this->addChild(route, 1);
    //怪兽入口设置
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(995, 525));
    this->addChild(monsterEnter, 2);
    //金币放置
    goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);
    //怪物加入
    GameObject* monster = GameObject::create(2,goldCoinDisplay);
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
bool mapTwo::ifSafe(cocos2d::Vec2 mousePos)//判断点击到的是否为炮塔位置是否合法
{
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    if ((mouseLocX <= 710 && mouseLocX >= 185 && mouseLocY <= 455 && mouseLocY >= 395) || (mouseLocX <= 710 && mouseLocX >= 540 && mouseLocY <= 365 && mouseLocY >= 215)||(mouseLocX <= 841 && mouseLocX >= 241 && mouseLocY <= 106 && mouseLocY >= 46) || (mouseLocX <= 75 && mouseLocX >= 15 && mouseLocY <= 570 && mouseLocY >= 90)|| (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 610 && mouseLocY >= 570)|| (mouseLocX <= 1055 && mouseLocX >= 935 && mouseLocY <= 465 && mouseLocY >= 285)|| (mouseLocX <= 1010 && mouseLocX >= 950 && mouseLocY <= 286 && mouseLocY >= 46))
        return true;
    else
        return false;
}
void mapTwo::selectedPosSet(float mouseLocX, float mouseLocY)
{
    if (mouseLocX <= 710 && mouseLocX >= 185 && mouseLocY <= 455 && mouseLocY >= 395)
    {
        mouseLocY += 25;
        int chooseX = static_cast<int>(mouseLocX / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = static_cast<int>((mouseLocX + 10) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 10;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 25;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
        mouseLocY -= 25;
    }
    else if (mouseLocX <= 710 && mouseLocX >= 540 && mouseLocY <= 365 && mouseLocY >= 215)
    {
        mouseLocY += 35;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 - 10;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 35;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
        mouseLocY -= 35;
    }
    else if ((mouseLocX <= 841 && mouseLocX >= 241 && mouseLocY <= 106 && mouseLocY >= 46))
    {
        mouseLocY += 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 - 10;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 15;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
        mouseLocY -= 15;
    }
    else if ((mouseLocX <= 75 && mouseLocX >= 15 && mouseLocY <= 570 && mouseLocY >= 90) || (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 630 && mouseLocY >= 570)|| (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 630 && mouseLocY >= 570))
    {
        mouseLocY -= 15;
        mouseLocX -= 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 + 5;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 + 15;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
        mouseLocY += 15;
        mouseLocX += 15;
    }
    else if(mouseLocX <= 1055 && mouseLocX >= 935 && mouseLocY <= 465 && mouseLocY >= 285)
    {
        mouseLocX += 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 - 25;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + 2 * cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置
        mouseLocX -= 15;
    }
    else if(mouseLocX <= 1021 && mouseLocX >= 950 && mouseLocY <= 286 && mouseLocY >= 46)
    {
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//网格横向坐标
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//网格纵向坐标
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 - 10;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2;
        sunFlower->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2);
        selectedPos->setPosition(towerPos.x, towerPos.y);//设置位置为炮塔所放置位置

    }
}
void mapTwo::tryAgain(Ref* pSender)
{
    TowerManager::getInstance()->clearTowers();//删除上个地图中残留的炮塔管理器
    MonsterManager::getInstance()->clearMonster();//删除上个地图中残留的怪物管理器
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//弹出暂停页面
    Director::getInstance()->popScene();//弹出游戏页面
    enterMapTwo(this);
}

