#include"MapChoose.h"
#include"MapOne.h"
#include"MapTwo.h"
USING_NS_CC;

Scene* mapChoose::createScene()//地图选择场景创建
{
    Scene* startScene = Scene::create();
    mapChoose* background = mapChoose::create();
    startScene->addChild(background);
    return startScene;

}
bool mapChoose::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto background = Sprite::create("map.png");//设置背景精灵
    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图的初始化时的可见大小
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);//加入场景中，并设置为底层

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
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height + 40));
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
void mapChoose::flipToNext(Ref* pSender)
{
    Scene* mapChoose = mapChoose::createScene();
    auto background = Sprite::create("map.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(background, 0);
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
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height + 40));
    auto menu = Menu::create(returnItem, leftItem, enterItem, NULL);//创建菜单，将两个按键加入
    mapChoose->addChild(menu, 1);
    auto label = Label::createWithTTF("Choose Map", "fonts/Marker Felt.ttf", 54);
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
