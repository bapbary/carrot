/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CarrotFantasyMap.h"
#include "ui/CocosGUI.h"
using namespace std::chrono;
#define cellHeight 45
#define cellWidth 67.5

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
    Scene* mapChoose = sceneChoose::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, mapChoose));//进入地图选择场景
    
}

Scene* sceneChoose::createScene()//地图选择场景创建
{
    Scene* startScene = Scene::create();
    sceneChoose* background = sceneChoose::create();
    startScene->addChild(background);
    return startScene;

}
bool sceneChoose::init()
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
        CC_CALLBACK_1(sceneChoose::returnLast, this));//回到封面的按键
    auto rightItem = MenuItemImage::create(
        "right.png",
        "rightSelected.png",
        CC_CALLBACK_1(sceneChoose::flipToNext, this));//滑动到下一地图选择的按键
    auto enterItem= MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(sceneChoose::enterMapOne, this));
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
void sceneChoose::returnLast(Ref* pSender)
{
    CCLOG("return last");
    Director::getInstance()->popScene();//从地图选择的场景，并从栈里将封面场景弹出作为当前运行场景
    return;
}
void sceneChoose::flipToNext(Ref* pSender)
{
    Scene* mapChoose = sceneChoose::createScene();
    auto background = Sprite::create("map.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(background, 0);
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(sceneChoose::returnLast, this));//回到封面的按键
    auto leftItem = MenuItemImage::create(
        "left.png",
        "leftSelected.png",
        CC_CALLBACK_1(sceneChoose::flipToLast, this));//滑动到上一地图选择的按键
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    leftItem->setPosition(Vec2(origin.x - visibleSize.width / 2 + 80, origin.y));
    auto menu = Menu::create(returnItem, leftItem, NULL);//创建菜单，将两个按键加入
    mapChoose->addChild(menu, 1);
    auto label = Label::createWithTTF("Choose Map", "fonts/Marker Felt.ttf", 54);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapChoose->addChild(label, 1);
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
}
void sceneChoose::flipToLast(Ref* pSender)
{
    Scene* mapChoose = sceneChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));//回到上个地图选择场景
}
void sceneChoose::enterMapOne(Ref* pSender)
{
    Scene* map = mapOne::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//进入地图选择场景
}

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

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小


    auto background = Sprite::create("mapBackground.png");//地图背景图
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    auto route = Sprite::create("route.png");//怪兽路线
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, route->getContentSize().height / 2));
    this->addChild(route, 1);

    auto monsterEnter = Sprite::create("monsterEnter.png");//怪兽门
    monsterEnter->setPosition(Vec2(5 * cellWidth, 12 * cellHeight));
    this->addChild(monsterEnter, 2);


    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(sceneChoose::returnLast, this));//回到上一场景的按键
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    auto menu = Menu::create(returnItem, NULL);//创建菜单，将按键加入
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+40));
    this->addChild(label,3);

    fireBottle = nullptr;
    //触摸监听创建
    touchListener = EventListenerTouchOneByOne::create();
    // 绑定触摸的的回调函数
    touchListener->onTouchEnded = CC_CALLBACK_2(mapOne::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapOne::onTouchBegan, this);
    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool  mapOne::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onMouseDown - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//视图的可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//视图初始化时的可见大小
    
    cocos2d::Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));

    if (fireBottle == nullptr)
    {
        fireBottle = MenuItemImage::create(
            "fireBottle.png",
            "fireBottle.png",
            CC_CALLBACK_1(mapOne::menuCloseCallback, this));
        fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - cellWidth / 2, static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
        Menu* menu = Menu::create(fireBottle, NULL);
        this->addChild(menu, 3);

    }
    else
    {
        if (fireBottle->getBoundingBox().containsPoint(mousePos))
        {
            // 点击了fireBottle图标，执行回调函数
            CCLOG("Clicked on the sprite!");
            menuCloseCallback(fireBottle);
        }
        else {
            // 点击了非fireBottle图标，移除fireBottle图标
            CCLOG("Removing fireBottle");
            CCLOG("Clicked outside the sprite!");
            this->removeChild(fireBottle->getParent());//移除选择图标所在菜单
            fireBottle = nullptr;  // 将精灵置为空，以便下次点击重新创建
        }
       
    }
    CCLOG("onMouseDown - End");
    event->stopPropagation();
    return true;
}
bool  mapOne::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void mapOne::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();//从地图选择的场景，并从栈里将封面场景弹出作为当前运行场景
    return;

}
