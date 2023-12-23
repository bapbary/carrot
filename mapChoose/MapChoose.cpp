#include"MapChoose.h"
#include"MapOne.h"
#include"MapTwo.h"
USING_NS_CC;

Scene* mapChoose::createScene()//��ͼѡ�񳡾�����
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

    auto background = Sprite::create("map.png");//���ñ�������
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ�ĳ�ʼ��ʱ�Ŀɼ���С
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);//���볡���У�������Ϊ�ײ�

    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//�ص�����İ���
    auto rightItem = MenuItemImage::create(
        "right.png",
        "rightSelected.png",
        CC_CALLBACK_1(mapChoose::flipToNext, this));//��������һ��ͼѡ��İ���
    auto enterItem = MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(mapChoose::enterMapOne, this));
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
void mapChoose::returnLast(Ref* pSender)
{
    CCLOG("return last");
    Director::getInstance()->popScene();//�ӵ�ͼѡ��ĳ���������ջ�ｫ���泡��������Ϊ��ǰ���г���
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
        CC_CALLBACK_1(mapChoose::returnLast, this));//�ص�����İ���
    auto leftItem = MenuItemImage::create(
        "left.png",
        "leftSelected.png",
        CC_CALLBACK_1(mapChoose::flipToLast, this));//��������һ��ͼѡ��İ���
    auto enterItem = MenuItemImage::create(
        "enter.png",
        "enterSelected.png",
        CC_CALLBACK_1(mapChoose::enterMapTwo, this));//����ڶ��ŵ�ͼ�İ���
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    leftItem->setPosition(Vec2(origin.x - visibleSize.width / 2 + 80, origin.y));
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height + 40));
    auto menu = Menu::create(returnItem, leftItem, enterItem, NULL);//�����˵�����������������
    mapChoose->addChild(menu, 1);
    auto label = Label::createWithTTF("Choose Map", "fonts/Marker Felt.ttf", 54);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapChoose->addChild(label, 1);
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
}
void mapChoose::flipToLast(Ref* pSender)
{
    Scene* mapChoose = mapChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));//�ص��ϸ���ͼѡ�񳡾�
}
void mapChoose::enterMapOne(Ref* pSender)//�����һ�ŵ�ͼ
{
    Scene* map = mapOne::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//�����ͼѡ�񳡾�
}
void mapChoose::enterMapTwo(Ref* pSender)//����ڶ��ŵ�ͼ
{
    Scene* map = mapTwo::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, map));//�����ͼѡ�񳡾�
}
