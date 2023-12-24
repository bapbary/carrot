#include"MapOne.h"
#include"TowerManager.h"
#include"FireTower.h"
#include"LeafTower.h"
#include"LightingTower.h"
#include<string>
#define cellHeight 60
#define cellWidth 60

USING_NS_CC;

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

    //��ͼ����ͼ����
    auto background = Sprite::create("mapBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    //����·��ͼ����
    route = Sprite::create("route.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, route->getContentSize().height / 2));
    this->addChild(route, 1);
    //�����������
    auto monsterEnter = Sprite::create("monsterEnter.png");
    monsterEnter->setPosition(Vec2(6 * cellWidth, 9 * cellHeight));
    this->addChild(monsterEnter, 2);
    //�������
    GameObject* monster = GameObject::create();
    this->addChild(monster, 2);
    //outline������
    auto outline = Sprite::create("outline.png");
    outline->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - outline->getContentSize().height / 2));
    this->addChild(outline, 1);
    //��ҷ���
    goldCoinDisplay = cocos2d::Label::createWithTTF(std::to_string(goldCoin), "fonts/Marker Felt.ttf", 24);
    goldCoinDisplay->setPosition(Vec2(245, 690));
    this->addChild(goldCoinDisplay, 2);

    //�ϰ�������
    obstacleDispatch();

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
    touchListener->onTouchEnded = CC_CALLBACK_2(mapOne::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapOne::onTouchBegan, this);
    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool mapOne::isTouchTower()//�жϵ�������Ƿ�Ϊ����
{
    return true;
}
bool  mapOne::onTouchEnded(Touch* touch, Event* event)
{
    if (fireBottleClicked == true)
    {
        fireBottleClicked = false;
        return true;
    }
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    cocos2d::Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));
    towerName = TowerManager::getInstance()->towerSelected(mousePos);
    if (towerName == "")
    {
        CCLOG("towerName is valid");
    }
    if (fireBottle == nullptr && towerName == "" && towerMenu == nullptr)//����հ״�
    {
        if (mouseLocY < 100 || (mouseLocY > 185 && mouseLocY < 290 && mouseLocX > 245 && mouseLocX < 1010) || (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825) || (mouseLocY > 570 && mouseLocY < 655 && mouseLocX > 425 && mouseLocX < 1010) || (mouseLocY < 570 && mouseLocY>295 && mouseLocX > 915) || (mouseLocY < 360 && mouseLocY>100 && mouseLocX < 160) && mousePos != obstacleTree->getPosition())//���λ�ÿ��԰�װ����
        {
            if (goldCoin >= 160)
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCanBuild.png",
                    "fireBottleCanBuild.png",
                    CC_CALLBACK_1(mapOne::fireBottleGenerate, this));
                leafTower = MenuItemImage::create(
                    "leafTowerCanBuild.png",
                    "leafTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::leafTowerGenerate, this));
                lightingTower = MenuItemImage::create(
                    "lightingTowerCanBuild.png",
                    "lightingTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::lightingTowerGenerate, this));
            }
            else
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCannotBuild.png",
                    "fireBottleCannotBuild.png",
                    CC_CALLBACK_1(mapOne::fireBottleCannotGenerate, this));
                leafTower = MenuItemImage::create(
                    "leafTowerCannotBuild.png",
                    "leafTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::leafTowerCannotGenerate, this));
                lightingTower = MenuItemImage::create(
                    "lightingTowerCannotBuild.png",
                    "lightingTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::lightingTowerCannotGenerate, this));

            }
            Menu* menu = Menu::create(fireBottle, leafTower, lightingTower, NULL);
            this->addChild(menu, 3);
            //��ѡ������
            selectedPos = Sprite::create("Choose.png");
            towerPos.x = static_cast<int>(mouseLocX / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2);
            if (mouseLocY >= 570 && mouseLocY < 610)
            {
                towerPos.y = static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 20;
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
                leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
                lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 20);
                selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
            }
            else
            {
                towerPos.y = static_cast<int>(mouseLocY / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2);
                fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
                leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
                lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>(mouseLocY / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2);
                selectedPos->setPosition(towerPos.x, towerPos.y);//����λ��Ϊ����������λ��
            }
            this->addChild(selectedPos, 2);
        }
        else
            CCLOG("Click invalid");
    }
    else if (fireBottle == nullptr && (towerName != "" || towerMenu != nullptr))
    {
        // �����fireBottle,ѡ��������ɾ��
        CCLOG("Choose upgrade or delete!");
        if (towerMenu == nullptr && towerName != "")
        {
            if (!towerName.compare(0, 9, "FireTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeFireTower, this));//����ͼ�꣨Ǯ�㹻��
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    upgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = Sprite::create("CannotUpgrade.png");//����ͼ�꣨Ǯ������
                    cannotUpgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(deleteItem, NULL);

                }
            }
            if (!towerName.compare(0, 9, "LeafTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLeafTower, this));//����ͼ�꣨Ǯ�㹻��
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    upgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = Sprite::create("CannotUpgrade.png");//����ͼ�꣨Ǯ������
                    cannotUpgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(deleteItem, NULL);

                }
            }
            if (!towerName.compare(0, 13, "LightingTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "LightingTowerDelete.png",
                    "LightingTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "LightingTowerUpgrade.png",
                        "LightingTowerUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLightTower, this));//����ͼ�꣨Ǯ�㹻��
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    upgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    deleteItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y - cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = Sprite::create("LightingTowerCannotUpgrade.png");//����ͼ�꣨Ǯ������
                    cannotUpgradeItem->setPosition(TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().x - visibleSize.width / 2, TowerManager::getInstance()->getTower(towerName)->getTowerSprite()->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(deleteItem, NULL);

                }
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
    CCLOG("onTouchEnded - End");
    event->stopPropagation();
    return true;
}
bool  mapOne::onTouchBegan(Touch* touch, Event* event)//��֤��������������
{
    return true;
}
void mapOne::obstacleDispatch()
{
    //�ϰ���ͼ������
    obstacleTree = Sprite::create("obstacleTree.png");//�ϰ���������ͣ��������������Ǯ����
    obstacleTree->setPosition(Vec2(6 * cellWidth + 15, 10 * cellHeight));
    this->addChild(obstacleTree, 2);
    //�ϰ���Ľ���������
    loadingBar = Sprite::create("loadingBar.png");
    loadingBar->setPosition(Vec2(obstacleTree->getPositionX() - obstacleTree->getContentSize().width / 2, obstacleTree->getPositionY() + obstacleTree->getContentSize().height / 2));
    //�ϰ���Ѫ������
    loadingBarBlood = ProgressTimer::create(Sprite::create("loadingBarBlood.png"));
    loadingBarBlood->setPosition(Vec2(obstacleTree->getPositionX() + loadingBarBlood->getContentSize().width, obstacleTree->getPositionY() + obstacleTree->getContentSize().height / 2));
    loadingBarBlood->setMidpoint(Vec2(0, obstacleTree->getPositionX()));
    loadingBar->addChild(loadingBarBlood);
    loadingBarBlood->setPercentage(66);//���ü�ʱ���ٷֱ�
    this->addChild(loadingBar, 2);
}
void mapOne::fireBottleGenerate(Ref* pSender)//���ɻ���ƿ��������
{
    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(fireBottle->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    FireTower* towerClass = new FireTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapOne::leafTowerGenerate(Ref* pSender)//���ɷ��ȵ�������
{
    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(leafTower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    LeafTower* towerClass = new LeafTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapOne::lightingTowerGenerate(Ref* pSender)//������ƿ��������
{
    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(leafTower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    fireBottle = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    LightingTower* towerClass = new LightingTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    goldCoin -= 100;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapOne::fireBottleCannotGenerate(Ref* pSender)//���û���ƿ����
{

}
void mapOne::leafTowerCannotGenerate(Ref* pSender)//���û���ƿ����
{

}
void mapOne::lightingTowerCannotGenerate(Ref* pSender)//���û���ƿ����
{

}
void mapOne::upgradeFireTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapOne::upgradeLeafTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}

void mapOne::upgradeLightTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 260;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}

void mapOne::deleteTower(Ref* pSender)//���ɻ���ƿ��������
{
    CCLOG("Remove tower");
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    //������Ӧ���
    goldCoin += 80;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ

    towerMenu = nullptr;
}
void mapOne::deleteLightTower(Ref* pSender)//���ɻ���ƿ��������
{
    CCLOG("Remove tower");
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    //������Ӧ���
    goldCoin += 80;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ

    towerMenu = nullptr;
}
