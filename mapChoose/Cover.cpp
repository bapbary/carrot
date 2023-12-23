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
    Scene* mapChoose = mapChoose::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1, mapChoose));//�����ͼѡ�񳡾�

}
