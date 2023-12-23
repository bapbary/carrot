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
bool mapTwo::init()//��һ�ŵ�ͼ�ĳ�ʼ��
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    //��ͼ����ͼ����
    auto background = Sprite::create("mapBackgroundTwo.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //����·��ͼ����
    route = Sprite::create("routeTwo.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x + 25, route->getContentSize().height / 2));
    this->addChild(route, 1);
    //�����������
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(monsterEnter->getContentSize().width / 2, 7.5 * cellHeight));
    this->addChild(monsterEnter, 2);

    //outline������
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //��ҷ���
    auto goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);

    //�ϰ�������

    //�ص���ť����
    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//�ص���һ�����İ���
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 4 * returnItem->getContentSize().height));
    auto menu = Menu::create(returnItem, NULL);//�����˵�������������
    this->addChild(menu, 2);


    label = cocos2d::Label::createWithTTF("Mouse Coordinates: ", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 3);

    fireBottle = nullptr;
    //������������
    touchListener = EventListenerTouchOneByOne::create();
    // �󶨴����ĵĻص�����
    touchListener->onTouchEnded = CC_CALLBACK_2(mapTwo::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapTwo::onTouchBegan, this);
    // ����������ӵ��¼��ַ�����
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

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    cocos2d::Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));
    std::string towerName;//�����λ�����������ɽ��������֣���û����Ϊ�մ�
    towerName = TowerManager::getInstance()->towerSelected(mousePos);

    if (fireBottle == nullptr && towerName == "" && towerMenu == nullptr)//����հ״�
    {
        if (1)//���λ�ÿ��԰�װ����
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
            //��ѡ������
            selectedPos = Sprite::create("choose.png");
            towerPos.x = static_cast<int>(mouseLocX / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2);
            if (mouseLocY >= 570 && mouseLocY < 610)
            {
                towerPos.y = static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 20;
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
                selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
            }
            else
            {
                towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
                selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
            }
            this->addChild(selectedPos, 2);
        }
        else
            CCLOG("Click invalid");
    }
    else if (fireBottle == nullptr && towerName != "")
    {
        // �����fireBottle,ѡ��������ɾ��
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
            fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
        }
        else
        {
            // ����˷�towerͼ��
            CCLOG("Clicked outside the sprite!");
            this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
            towerMenu = nullptr;
            fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
        }
    }
    else
    {
        CCLOG("Remove LOGO");
        this->removeChild(fireBottle->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
        removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
        fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
        fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����

    }
    CCLOG("onMouseDown - End");
    event->stopPropagation();
    return true;
}
void mapTwo::fireBottleGenerate(Ref* pSender)//���ɻ���ƿ��������
{
    this->removeChild(fireBottle->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    selectedPos = nullptr;
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����

    FireTower* towerClass = new FireTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    return;
}
void mapTwo::upgradeTower(Ref* pSender)//���ɻ���ƿ��������
{

}
void mapTwo::deleteTower(Ref* pSender)//���ɻ���ƿ��������
{
    TowerManager::getInstance()->removeTower(towerName);

}
