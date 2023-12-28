#include"MapTwo.h"
#include"TowerManager.h"
#include"FireTower.h"

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
bool mapTwo::init()//��һ�ŵ�ͼ�ĳ�ʼ��
{
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    //��ͼ����ͼ����
    auto background = Sprite::create("mapBackgroundTwo.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //����·��ͼ����
    route = Sprite::create("routeTwo.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x , route->getContentSize().height / 2 + origin.y));
    this->addChild(route, 1);
    //�����������
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(995, 525));
    this->addChild(monsterEnter, 2);
    //�������
    GameObject* monster = GameObject::create(2);
    this->addChild(monster, 2);
    //outline������
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //��ͣ������
    int mapType = 1;
    auto suspend = MenuItemImage::create(
        "suspendItem.png",
        "suspendItem.png",
        CC_CALLBACK_1(mapChoose::suspend, this));

    //��ҷ���
    goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);

    //�ص���ť����
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));//�ص���һ�����İ���
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 4 * returnItem->getContentSize().height));
    auto menu = Menu::create(returnItem, suspend, NULL);//�����˵�������������
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 3);

    fireBottle = nullptr;
    //������������
    touchListener = EventListenerTouchOneByOne::create();
    // �󶨴����ĵĻص�����
    touchListener->onTouchEnded = CC_CALLBACK_2(mapChoose::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapChoose::onTouchBegan, this);
    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool mapTwo::ifSafe(cocos2d::Vec2 mousePos)//�жϵ�������Ƿ�Ϊ����λ���Ƿ�Ϸ�
{
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    if ((mouseLocX <= 725 && mouseLocX >= 185 && mouseLocY <= 455 && mouseLocY >= 395) || (mouseLocX <= 720 && mouseLocX >= 540 && mouseLocY <= 365 && mouseLocY >= 215)||(mouseLocX <= 841 && mouseLocX >= 241 && mouseLocY <= 106 && mouseLocY >= 46) || (mouseLocX <= 75 && mouseLocX >= 15 && mouseLocY <= 570 && mouseLocY >= 90)|| (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 610 && mouseLocY >= 570)|| (mouseLocX <= 1030 && mouseLocX >= 910 && mouseLocY <= 465 && mouseLocY >= 285)|| (mouseLocX <= 1021 && mouseLocX >= 841 && mouseLocY <= 286 && mouseLocY >= 46))
        return true;
    else
        return false;
}
void mapTwo::selectedPosSet(float mouseLocX, float mouseLocY)
{
    if (mouseLocX <= 725 && mouseLocX >= 185 && mouseLocY <= 455 && mouseLocY >= 395)
    {
        mouseLocY += 25;
        int chooseX = static_cast<int>(mouseLocX / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = static_cast<int>((mouseLocX + 10) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2);
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 25;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 25);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
        mouseLocY -= 25;
    }
    else if (mouseLocX <= 720 && mouseLocX >= 540 && mouseLocY <= 365 && mouseLocY >= 215)
    {
        mouseLocY += 35;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 35;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 35);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
        mouseLocY -= 35;
    }
    else if ((mouseLocX <= 841 && mouseLocX >= 241 && mouseLocY <= 106 && mouseLocY >= 46))
    {
        mouseLocY += 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 15;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
        mouseLocY -= 15;
    }
    else if ((mouseLocX <= 75 && mouseLocX >= 15 && mouseLocY <= 570 && mouseLocY >= 90) || (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 630 && mouseLocY >= 570)|| (mouseLocX <= 1035 && mouseLocX >= 15 && mouseLocY <= 630 && mouseLocY >= 570))
    {
        mouseLocY -= 15;
        mouseLocX -= 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2 + 15;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 + 15;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 + 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
        mouseLocY += 15;
        mouseLocX += 15;
    }
    else if(mouseLocX <= 1030 && mouseLocX >= 910 && mouseLocY <= 465 && mouseLocY >= 285)
    {
        mouseLocX += 15;
        int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 15;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
        mouseLocX -= 15;
    }
    else if(mouseLocX <= 1021 && mouseLocX >= 841 && mouseLocY <= 286 && mouseLocY >= 46)
    {
                int chooseX = static_cast<int>((mouseLocX + 10) / cellHeight) * cellHeight;//�����������
        int chooseY = static_cast<int>(mouseLocY / cellHeight) * cellHeight;//������������
        towerPos.x = chooseX + selectedPos->getContentSize().width / 2;
        towerPos.y = chooseY + selectedPos->getContentSize().height / 2 - 15;
        fireBottle->setPosition(chooseX - visibleSize.width / 2 - cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        leafTower->setPosition(chooseX - visibleSize.width / 2 + cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        lightingTower->setPosition(chooseX - visibleSize.width / 2 + 3 * cellWidth / 2, chooseY + cellHeight - visibleSize.height / 2 - 15);
        selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��

    }
}
void mapTwo::tryAgain(Ref* pSender)
{
    Director::getInstance()->popScene();//������ͣҳ��
    Director::getInstance()->popScene();//������Ϸҳ��
    enterMapTwo(this);
}

