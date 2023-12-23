#include"MapTwo.h"
#include"TowerManager.h"
#include"FireTower.h"

#define cellHeight 75
#define cellWidth 75

USING_NS_CC;
Scene* mapTwo::createScene()
{
    Scene* startScene = Scene::create();
    mapTwo* map = mapTwo::create();
    startScene->addChild(map);
    return startScene;
}
bool mapTwo::init()//第一张地图的初始化
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    //地图背景图设置
    auto background = Sprite::create("mapBackgroundTwo.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //怪兽路线图设置
    route = Sprite::create("routeTwo.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x + 25, route->getContentSize().height / 2));
    this->addChild(route, 1);
    //怪兽入口设置
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(monsterEnter->getContentSize().width / 2, 7.5 * cellHeight));
    this->addChild(monsterEnter, 2);

    //outline框设置
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //金币放置
    auto goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);

    //障碍物设置

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
    touchListener->onTouchEnded = CC_CALLBACK_2(mapTwo::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapTwo::onTouchBegan, this);
    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool  mapTwo::onTouchEnded(Touch* touch, Event* event)
{
    if (fireBottleClicked == true)
    {
        CCLOG("Clicked!");
        fireBottleClicked = false;
        return true;
    }
    else
    {
        CCLOG("invaid!");
    }
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    cocos2d::Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));
    std::string towerName;//若点击位置有炮塔即可接收其名字，若没有则为空串
    towerName = TowerManager::getInstance()->towerSelected(mousePos);

    if (fireBottle == nullptr && towerName == "" && towerMenu == nullptr)//点击空白处
    {
        if (1)//点击位置可以安装炮塔
        {
            if (goldCoin >= 160)
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCanBuild.png",
                    "fireBottleCanBuild.png",
                    CC_CALLBACK_1(mapTwo::fireBottleGenerate, this));
            }
            else
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCannotBuild.png",
                    "fireBottleCannotBuild.png",
                    CC_CALLBACK_1(mapTwo::fireBottleGenerate, this));
            }
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
    else if (fireBottle == nullptr && towerName != "")
    {
        // 点击了fireBottle,选择升级或删除
        CCLOG("Choose upgrade or delete!");
        if (towerMenu == nullptr && TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getBoundingBox().containsPoint(mousePos))
        {
            if (goldCoin >= 320)
            {
                auto upgradeItem = MenuItemImage::create(
                    "CanUpgrade.png",
                    "CanUpgrade.png",
                    CC_CALLBACK_1(mapTwo::upgradeTower, this)
                );
                upgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                auto deleteItem = MenuItemImage::create(
                    "TowerDelete.png",
                    "TowerDelete.png",
                    CC_CALLBACK_1(mapTwo::deleteTower, this)
                );
                deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
            }
            else
            {
                auto cannotUpgradeItem = Sprite::create("CannotUpgrade.png");
                cannotUpgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                auto deleteItem = MenuItemImage::create(
                    "TowerDelete.png",
                    "TowerDelete.png",
                    CC_CALLBACK_1(mapTwo::deleteTower, this)
                );
                deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                towerMenu = Menu::create(deleteItem, NULL);

            }
            this->addChild(towerMenu, 2);
            fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
        }
        else
        {
            // 点击了非tower图标
            CCLOG("Clicked outside the sprite!");
            this->removeChild(towerMenu);//移除选择图标所在菜单
            towerMenu = nullptr;
            fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
        }
    }
    else
    {
        CCLOG("Remove LOGO");
        this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
        removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
        fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
        fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数

    }
    CCLOG("onMouseDown - End");
    event->stopPropagation();
    return true;
}
void mapTwo::fireBottleGenerate(Ref* pSender)//生成火焰瓶的炮塔类
{
    this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
    fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
    removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
    selectedPos = nullptr;
    fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数

    FireTower* towerClass = new FireTower(towerPos);
    //将炮塔名字及其指针加入炮塔管理器
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //将炮塔精灵加入场景
    this->addChild(towerClass->getTowerSprite(), 2);
    return;
}
void mapTwo::upgradeTower(Ref* pSender)//生成火焰瓶的炮塔类
{

}
void mapTwo::deleteTower(Ref* pSender)//生成火焰瓶的炮塔类
{
    TowerManager::getInstance()->removeTower(towerName);

}
