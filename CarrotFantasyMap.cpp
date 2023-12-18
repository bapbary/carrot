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

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ�ĳ�ʼ��ʱ�Ŀɼ���С

    auto startItem = MenuItemImage::create(
        "startbutton.png",
        "startSelected.png",
        CC_CALLBACK_1(sceneCover::touchStart, this));//��ʼ��Ϸ

    auto exitItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(sceneCover::menuCloseCallback, this));//�˳���Ϸ
   
    //����ͼ��λ��
    startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 3 * startItem->getContentSize().height / 2));//��ʼ����λ��
    exitItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 2 * exitItem->getContentSize().height / 2));//�˳���λ��
    auto menu = Menu::create(startItem, exitItem, NULL);//�����˵�������ʼ�����˳�������
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);//��menu���볡����

    auto label = Label::createWithTTF("Carrot Fantasy", "fonts/Marker Felt.ttf", 54);//�ַ���ǩ����
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 4 * label->getContentSize().height));
    this->addChild(label, 1);//����ǩ���볡����

    auto sprite = Sprite::create("map.png");//���ñ�������
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);//���볡���У�������Ϊ�ײ�
    return true;

}
void sceneCover::touchStart(Ref* pSender)//��ʼ��Ϸ�����¼�
{
    Scene* mapChoose = sceneChoose::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, mapChoose));//�����ͼѡ�񳡾�
    
}

Scene* sceneChoose::createScene()//��ͼѡ�񳡾�����
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
   
    auto background = Sprite::create("map.png");//���ñ�������
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ�ĳ�ʼ��ʱ�Ŀɼ���С
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);//���볡���У�������Ϊ�ײ�
   
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(sceneChoose::returnLast, this));//�ص�����İ���
    auto rightItem = MenuItemImage::create(
        "right.png",
        "rightSelected.png",
        CC_CALLBACK_1(sceneChoose::flipToNext, this));//��������һ��ͼѡ��İ���
    auto enterItem= MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(sceneChoose::enterMapOne, this));
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    rightItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y));
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height + 40));
    auto menu = Menu::create(returnItem, rightItem, enterItem, NULL);//�����˵�����������������
    this->addChild(menu, 1);//���˵����볡����
   
    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    this->addChild(label, 1);//����ǩ���볡����

    return true;
}
void sceneChoose::returnLast(Ref* pSender)
{
    CCLOG("return last");
    Director::getInstance()->popScene();//�ӵ�ͼѡ��ĳ���������ջ�ｫ���泡��������Ϊ��ǰ���г���
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
        CC_CALLBACK_1(sceneChoose::returnLast, this));//�ص�����İ���
    auto leftItem = MenuItemImage::create(
        "left.png",
        "leftSelected.png",
        CC_CALLBACK_1(sceneChoose::flipToLast, this));//��������һ��ͼѡ��İ���
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    leftItem->setPosition(Vec2(origin.x - visibleSize.width / 2 + 80, origin.y));
    auto menu = Menu::create(returnItem, leftItem, NULL);//�����˵�����������������
    mapChoose->addChild(menu, 1);
    auto label = Label::createWithTTF("Choose Map", "fonts/Marker Felt.ttf", 54);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapChoose->addChild(label, 1);
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
}
void sceneChoose::flipToLast(Ref* pSender)
{
    Scene* mapChoose = sceneChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));//�ص��ϸ���ͼѡ�񳡾�
}
void sceneChoose::enterMapOne(Ref* pSender)
{
    Scene* map = mapOne::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//�����ͼѡ�񳡾�
}

Scene* mapOne::createScene()
{
    Scene* startScene = Scene::create();
    mapOne* map = mapOne::create();
    startScene->addChild(map);
    return startScene;
}
bool mapOne::init()//��һ�ŵ�ͼ�ĳ�ʼ��
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С


    auto background = Sprite::create("mapBackground.png");//��ͼ����ͼ
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    auto route = Sprite::create("route.png");//����·��
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, route->getContentSize().height / 2));
    this->addChild(route, 1);

    auto monsterEnter = Sprite::create("monsterEnter.png");//������
    monsterEnter->setPosition(Vec2(5 * cellWidth, 12 * cellHeight));
    this->addChild(monsterEnter, 2);


    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(sceneChoose::returnLast, this));//�ص���һ�����İ���
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    auto menu = Menu::create(returnItem, NULL);//�����˵�������������
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+40));
    this->addChild(label,3);

    fireBottle = nullptr;
    //������������
    touchListener = EventListenerTouchOneByOne::create();
    // �󶨴����ĵĻص�����
    touchListener->onTouchEnded = CC_CALLBACK_2(mapOne::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapOne::onTouchBegan, this);
    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool  mapOne::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onMouseDown - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С
    
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
            // �����fireBottleͼ�ִ꣬�лص�����
            CCLOG("Clicked on the sprite!");
            menuCloseCallback(fireBottle);
        }
        else {
            // ����˷�fireBottleͼ�꣬�Ƴ�fireBottleͼ��
            CCLOG("Removing fireBottle");
            CCLOG("Clicked outside the sprite!");
            this->removeChild(fireBottle->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
            fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
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
    Director::getInstance()->popScene();//�ӵ�ͼѡ��ĳ���������ջ�ｫ���泡��������Ϊ��ǰ���г���
    return;

}
