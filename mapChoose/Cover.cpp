#include"Cover.h"
#include"MapChoose.h"
USING_NS_CC;

void sceneCover::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
Scene* sceneCover::createScene()
{
    Scene* startScene = Scene::create();
    sceneCover* coverLayer = sceneCover::create();
    startScene->addChild(coverLayer);
    return startScene;

}
bool sceneCover::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图的初始化时的可见大小

    auto startItem = MenuItemImage::create(
        "startbutton.png",
        "startSelected.png",
        CC_CALLBACK_1(sceneCover::touchStart, this));//开始游戏

    auto exitItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(sceneCover::menuCloseCallback, this));//退出游戏

    //设置图标位置
    startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 3 * startItem->getContentSize().height / 2));//开始按键位置
    exitItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 2 * exitItem->getContentSize().height / 2));//退出键位置
    auto menu = Menu::create(startItem, exitItem, NULL);//创建菜单，将开始键和退出键加入
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);//将menu加入场景中

    auto label = Label::createWithTTF("Carrot Fantasy", "fonts/Marker Felt.ttf", 54);//字符标签设置
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 4 * label->getContentSize().height));
    this->addChild(label, 1);//将标签加入场景中

    auto sprite = Sprite::create("map.png");//设置背景精灵
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);//加入场景中，并设置为底层
    return true;

}
void sceneCover::touchStart(Ref* pSender)//开始游戏键盘事件
{
    Scene* mapChoose = mapChoose::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, mapChoose));//进入地图选择场景

}
