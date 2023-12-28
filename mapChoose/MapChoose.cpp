#include"MapChoose.h"
#include"TowerManager.h"
#include "MonsterManager.h"
#include"FireTower.h"
#include"LeafTower.h"
#include"LightingTower.h"
#include<string>
#include<vector>
#include"MapOne.h"
#include"MapTwo.h"
#include"Obstacles.h"
USING_NS_CC;
#define cellHeight 60
#define cellWidth 60

Scene* mapChoose::createScene()//地图选择场景创建
{
    Scene* startScene = Scene::create();
    mapChoose* background = mapChoose::create();
    startScene->addChild(background);
    return startScene;

}
bool mapChoose::init()
{
    if (!Layer::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    auto background = Sprite::create("map.png");//设置背景精灵
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);//加入场景中，并设置为底层

    auto routeOneChoose = Sprite::create("routeOneChoose.png");
    routeOneChoose->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(routeOneChoose, 1);//加入场景中

    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//回到封面的按键
    auto rightItem = MenuItemImage::create(
        "right.png",
        "rightSelected.png",
        CC_CALLBACK_1(mapChoose::flipToNext, this));//滑动到下一地图选择的按键
    auto enterItem = MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(mapChoose::enterMapOne, this));
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    rightItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y));
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height));
    auto menu = Menu::create(returnItem, rightItem, enterItem, NULL);//创建菜单，将三个按键加入
    this->addChild(menu, 1);//将菜单加入场景中

    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//创建标签
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    this->addChild(label, 1);//将标签加入场景中

    return true;
}
void mapChoose::returnLast(Ref* pSender)
{
    CCLOG("return last");
    Director::getInstance()->popScene();//从地图选择的场景，并从栈里将封面场景弹出作为当前运行场景
    return;
}
void mapChoose::returnChoose(Ref* pSender)
{
    CCLOG("return last");
    TowerManager::getInstance()->clearTowers();//删除上个地图中残留的炮塔管理器
    MonsterManager::getInstance()->clearMonster();//删除上个地图中残留的怪物管理器
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//从地图退出，并从栈里将地图选择的场景弹出作为当前运行场景
    Director::getInstance()->popScene();
    return;
}
void mapChoose::flipToNext(Ref* pSender)
{
    Scene* mapChoose = mapChoose::createScene();
    auto background = Sprite::create("map.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(background, 0);

    auto routeTwoChoose = Sprite::create("routeTwoChoose.png");
    routeTwoChoose->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(routeTwoChoose, 1);//加入场景中

    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//回到封面的按键
    auto leftItem = MenuItemImage::create(
        "left.png",
        "leftSelected.png",
        CC_CALLBACK_1(mapChoose::flipToLast, this));//滑动到上一地图选择的按键
    auto enterItem = MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(mapChoose::enterMapTwo, this));//进入第二张地图的按键
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    leftItem->setPosition(Vec2(origin.x - visibleSize.width / 2 + 80, origin.y));
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height));
    auto menu = Menu::create(returnItem, leftItem, enterItem, NULL);//创建菜单，将两个按键加入
    mapChoose->addChild(menu, 1);
    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//创建标签
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapChoose->addChild(label, 1);
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
}
void mapChoose::flipToLast(Ref* pSender)
{
    Scene* mapChoose = mapChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));//回到上个地图选择场景
}
void mapChoose::enterMapOne(Ref* pSender)//进入第一张地图
{
    Scene* map = mapOne::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//进入地图选择场景
}
void mapChoose::enterMapTwo(Ref* pSender)//进入第二张地图
{
    Scene* map = mapTwo::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//进入地图选择场景
}
void mapChoose::onTouchEnded(Touch* touch, Event* event)
{
   /* if (fireBottleClicked == true)
    {
        fireBottleClicked = false;
        return;
    }*/
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小

    //将网格标准化，不添加数，会使得网格不是从边缘开始分布
    Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));
    //获取当前点击有无炮塔
    towerName = TowerManager::getInstance()->towerSelected(mousePos);
    //获取现存怪物的信息
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();
    //存储障碍物坐标
    std::vector<Obstacles*> obstacles = GameObject::getInstance()->getObstacles();
    //遍历判断是否点击到怪物
    GameObject* attackMonster = ifClickedMonster(monsters, mousePos);
    //遍历判断是否点击到障碍物
    Obstacles* attackObstacle = ifClickedObstacle(obstacles, mousePos);

    //判断
    if (fireBottle == nullptr && towerName == "" && towerMenu == nullptr && attackMonster == nullptr && attackObstacle == nullptr)//点击空白处
    {
        if (ifSafe(mousePos))//点击位置可以安装炮塔
        {
            if (goldCoin >= 100)//金币足够修建绿瓶子
            {
                lightingTower = MenuItemImage::create(
                    "lightingTowerCanBuild.png",
                    "lightingTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::lightingTowerGenerate, this));//绑定绿瓶建造回调函数
            }
            else
            {
                lightingTower = MenuItemImage::create(
                    "lightingTowerCannotBuild.png",
                    "lightingTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
            }
            if (goldCoin >= 160)//金币足够
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCanBuild.png",
                    "fireBottleCanBuild.png",
                    CC_CALLBACK_1(mapOne::fireBottleGenerate, this));//绑定火瓶建造回调函数
                leafTower = MenuItemImage::create(
                    "leafTowerCanBuild.png",
                    "leafTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::leafTowerGenerate, this));//绑定风扇建造回调函数
            }
            else
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCannotBuild.png",
                    "fireBottleCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
                leafTower = MenuItemImage::create(
                    "leafTowerCannotBuild.png",
                    "leafTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
            }
            Menu* menu = Menu::create(fireBottle, leafTower, lightingTower, NULL);
            this->addChild(menu, 3);
            //复选框设置
            selectedPos = Sprite::create("Choose.png");
            selectedPosSet(mouseLocX, mouseLocY);//复选框y坐标的设定
            this->addChild(selectedPos, 2);
        }
        else
            CCLOG("Click invalid");
    }
    else if (fireBottle == nullptr && (towerName != "" || towerMenu != nullptr) && attackMonster == nullptr && attackObstacle == nullptr)
    {
        // 点击了fireBottle,选择升级或删除
        CCLOG("Choose upgrade or delete!");
        if (towerMenu == nullptr && towerName != "")//点击了炮塔
        {
            Sprite* towerInstance = TowerManager::getInstance()->getTower(towerName)->getTowerSprite();
            //满级炮塔无法再升级
             
            if (!towerName.compare(0, 9, "FireTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//删除图标
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeFireTower, this));//升级图标（钱足够）
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "CannotUpgrade.png",
                        "CannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
                }
            }
            if (!towerName.compare(0, 9, "LeafTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//删除图标
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLeafTower, this));//升级图标（钱足够）
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "CannotUpgrade.png",
                        "CannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
                }
            }
            if (!towerName.compare(0, 13, "LightingTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "LightingTowerDelete.png",
                    "LightingTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//删除图标
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "LightingTowerUpgrade.png",
                        "LightingTowerUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLightTower, this));//升级图标（钱足够）
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "LightingTowerCannotUpgrade.png",
                        "LightingTowerCannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//绑定空回调函数
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
                }
            }
            this->addChild(towerMenu, 2);
            fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
        }
        else
        {
            // 点击了非tower图标
            this->removeChild(towerMenu);//移除选择图标所在菜单
            towerMenu = nullptr;
            //fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
        }
    }
    else if (attackMonster != nullptr || attackObstacle != nullptr)
    {
        //优先攻击传递
        if (priorAttackLogo != nullptr)
        {
            if (attackMonster != nullptr && attackMonster->getSprite() != lastPrior)
            {
                lastPrior->removeChild(priorAttackLogo, true); //从 attackObstacle 的子节点中移除
                priorAttackLogo = Sprite::create("priorAttackLogo.png");
                priorAttackLogo->setPosition(Vec2(attackMonster->getSprite()->getContentSize().width / 2, attackMonster->getSprite()->getContentSize().height));
                attackMonster->getSprite()->addChild(priorAttackLogo,1);
                lastPrior = attackMonster->getSprite();
                priorAttackLogo->setScale(0.25);
            }
            else if (attackObstacle != nullptr && attackObstacle->getSprite() != lastPrior)
            {
                lastPrior->removeChild(priorAttackLogo, true);//从 attackMonster 的子节点中移除
                priorAttackLogo = Sprite::create("priorAttackLogo.png");
                priorAttackLogo->setPosition(Vec2(attackObstacle->getSprite()->getContentSize().width / 2, attackObstacle->getSprite()->getContentSize().height));
                attackObstacle->getSprite()->addChild(priorAttackLogo,1);
                lastPrior = attackObstacle->getSprite();
                priorAttackLogo->setScale(0.25);
            }
            else if (attackMonster!= nullptr && priorAttackLogo->getParent()== attackMonster->getSprite())
            {
                attackMonster->getSprite()->removeChild(priorAttackLogo, true);//从 attackMonster 的子节点中移除
                priorAttackLogo = nullptr;
            }
            else if(attackObstacle != nullptr && priorAttackLogo->getParent() == attackObstacle->getSprite())
            {
                attackObstacle->getSprite()->removeChild(priorAttackLogo, true); //从 attackObstacle 的子节点中移除
                priorAttackLogo = nullptr;
            }
        }
        else
        {
            priorAttackLogo = Sprite::create("priorAttackLogo.png");
            if (attackMonster != nullptr)
            {
                lastPrior = attackMonster->getSprite();
                attackMonster->getSprite()->addChild(priorAttackLogo, 1);
                priorAttackLogo->setPosition(Vec2(attackMonster->getSprite()->getContentSize().width / 2, attackMonster->getSprite()->getContentSize().height));
            }
            else
            {
                lastPrior = attackObstacle->getSprite();
                attackObstacle->getSprite()->addChild(priorAttackLogo, 1);
                priorAttackLogo->setPosition(Vec2(attackObstacle->getSprite()->getContentSize().width / 2, attackObstacle->getSprite()->getContentSize().height));
            }
            priorAttackLogo->setScale(0.25);
            //传给炮塔
        }

    }
    else
    {
        this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
        removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
        fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
        //fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
    }
    event->stopPropagation();
    return;
}
bool mapChoose::onTouchBegan(Touch* touch, Event* event)//保证监听器正常运行
{
    return true;
}
void mapChoose::fireBottleGenerate(Ref* pSender)//生成火焰瓶的炮塔类
{
    removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
    this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
    fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
    FireTower* towerClass = new FireTower(towerPos);
    //将炮塔名字及其指针加入炮塔管理器
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //将炮塔精灵加入场景
    this->addChild(towerClass->getTowerSprite(), 2);
    //扣除相应金币
    scheduleUpdate();
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//更改金币标签
    //fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
}
void mapChoose::leafTowerGenerate(Ref* pSender)//生成风扇的炮塔类
{
    removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
    this->removeChild(leafTower->getParent());//移除选择图标所在菜单
    fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
    LeafTower* towerClass = new LeafTower(towerPos);
    //将炮塔名字及其指针加入炮塔管理器
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //将炮塔精灵加入场景
    this->addChild(towerClass->getTowerSprite(), 2);
    //扣除相应金币
    scheduleUpdate();
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//更改金币标签
    //fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
}
void mapChoose::lightingTowerGenerate(Ref* pSender)//生成绿瓶的炮塔类
{
    removeChild(selectedPos);//选择取消或者建造炮塔，复选框均消失
    this->removeChild(leafTower->getParent());//移除选择图标所在菜单
    fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
    LightingTower* towerClass = new LightingTower(towerPos);
    //将炮塔名字及其指针加入炮塔管理器
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //将炮塔精灵加入场景
    this->addChild(towerClass->getTowerSprite(), 2);
    //扣除相应金币
    scheduleUpdate();
    goldCoin -= 100;
    goldCoinDisplay->setString(std::to_string(goldCoin));//更改金币标签
    //fireBottleClicked = true;//防止点击fireBottle图标时进入onMouseEnded函数
}
void mapChoose::nullCallBack(Ref* pSender)//放置火焰瓶炮塔
{

}
void mapChoose::upgradeFireTower(Ref* pSender)//升级火焰瓶的炮塔类
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//移除选择图标所在菜单
    goldCoin -= 320;//金币扣除
    goldCoinDisplay->setString(std::to_string(goldCoin));//金币label待修改
    towerMenu = nullptr;

}
void mapChoose::upgradeLeafTower(Ref* pSender)//升级火焰瓶的炮塔类
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//移除选择图标所在菜单
    goldCoin -= 320;//金币扣除
    goldCoinDisplay->setString(std::to_string(goldCoin));//金币label待修改
    towerMenu = nullptr;

}
void mapChoose::upgradeLightTower(Ref* pSender)//升级火焰瓶的炮塔类
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//移除选择图标所在菜单
    goldCoin -= 260;//金币扣除
    goldCoinDisplay->setString(std::to_string(goldCoin));//金币label待修改
    towerMenu = nullptr;

}
void mapChoose::deleteTower(Ref* pSender)//生成火焰瓶的炮塔类
{
    CCLOG("Remove tower");
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//移除选择图标所在菜单
    //返还相应金币
    goldCoin += 80;
    goldCoinDisplay->setString(std::to_string(goldCoin));//更改金币标签

    towerMenu = nullptr;
}
void mapChoose::deleteLightTower(Ref* pSender)//生成火焰瓶的炮塔类
{
    CCLOG("Remove tower");
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//移除选择图标所在菜单
    //返还相应金币
    goldCoin += 80;
    goldCoinDisplay->setString(std::to_string(goldCoin));//更改金币标签

    towerMenu = nullptr;
}
void mapChoose::suspend(Ref* pSender)//在游戏中暂停
{
    //暂停页面场景创建
    Scene* suspendtScene = Scene::create();
    auto suspendBackground = Sprite::create("suspendBG.png");
    suspendBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
    suspendtScene->addChild(suspendBackground, 1);

    auto background = Sprite::create("map.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    suspendtScene->addChild(background, 0);

    //重新开始游戏
    auto tryAgain = MenuItemImage::create(
        "tryAgain.png",
        "tryAgainSelected.png",
        CC_CALLBACK_1(mapChoose::tryAgain, this));
    tryAgain->setPosition(Vec2(origin.x, origin.y + 110));
    //继续游戏
    auto continueGame = MenuItemImage::create(
        "continue.png",
        "continueSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));
    continueGame->setPosition(Vec2(origin.x, origin.y - 110));
    //回到主页面
    auto home = MenuItemImage::create(
        "home.png",
        "homeSelected.png",
        CC_CALLBACK_1(mapChoose::returnHome, this));
    home->setPosition(Vec2(origin.x, origin.y));
    auto menu = Menu::create(tryAgain, continueGame, home, NULL);
    suspendtScene->addChild(menu, 2);
    Director::getInstance()->pushScene(suspendtScene);//进入暂停界面

}
void mapChoose::tryAgain(Ref* pSender)//子类虚函数覆盖
{
}
void mapChoose::returnHome(Ref* pSender)
{
    Director::getInstance()->popToRootScene();
}
cocos2d::Vec2 mapChoose::passPos()
{
    return towerPos;
}//传递炮塔位置
GameObject* mapChoose::ifClickedMonster(std::vector<GameObject*> monsters, Vec2 mousePos)
{
    for (GameObject* currentMonster : monsters)
    {
        if (currentMonster->getSprite()->getBoundingBox().containsPoint(mousePos))//点击到了某一怪物
            return currentMonster;
    }
    return nullptr;
}
Obstacles* mapChoose::ifClickedObstacle(std::vector<Obstacles*> obstacles, Vec2 mousePos)
{
    for (Obstacles* currentObstacle : obstacles)
    {
        if (currentObstacle->getSprite()->getBoundingBox().containsPoint(mousePos))//点击到了某一怪物
            return currentObstacle;
    }
    return nullptr;
}
void mapChoose::gameOver(Ref* pSender)
{
    Scene* gameOverScene = Scene::create();
    auto gameOverBackground = Sprite::create("gameOverItem.png");
    gameOverBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(gameOverBackground, 1);

    auto background = Sprite::create("map.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(background, 0);
    //重新开始游戏
    auto retry = MenuItemImage::create(
        "retry.png",
        "retrySelected.png",
        CC_CALLBACK_1(mapChoose::tryAgain, this));
    retry->setPosition(Vec2(origin.x, origin.y - 50));
    //返回地图选择
    auto returnChoose = MenuItemImage::create(
        "returnChoose.png",
        "returnChooseSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    returnChoose->setPosition(Vec2(origin.x, origin.y - 100));
    auto menu = Menu::create(retry, returnChoose, NULL);
    gameOverScene->addChild(menu, 1);
    Director::getInstance()->pushScene(gameOverScene);//进入获胜界面

}
void mapChoose::gameWin(Ref* pSender)
{
    Scene* winScene = Scene::create();
    auto gameWinBackground = Sprite::create("winBG.png");
    gameWinBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    winScene->addChild(gameWinBackground, 0);
    //胜利字体
    auto win = Sprite::create("win.png");
    win->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));
    winScene->addChild(win, 1);
    auto winItem = Sprite::create("winItem.png");
    winItem->setPosition(Vec2(winItem->getContentSize().width, winItem->getContentSize().height));
    winScene->addChild(winItem, 1);

    //继续游戏
    auto winContinue = MenuItemImage::create(
        "winContinue.png",
        "winContinueSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose,this));
    auto menu = Menu::create(winContinue, NULL);
    winScene->addChild(menu);
    winContinue->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50));
    winScene->addChild(winContinue, 1);
    Director::getInstance()->pushScene(winScene);//进入获胜界面

}
