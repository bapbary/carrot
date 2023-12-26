#include"MapChoose.h"
#include"TowerManager.h"
#include "MonsterManager.h"
#include"FireTower.h"
#include"LeafTower.h"
#include"LightingTower.h"
#include<string>
#include"MapOne.h"
#include"MapTwo.h"
USING_NS_CC;
#define cellHeight 60
#define cellWidth 60

Scene* mapChoose::createScene()//��ͼѡ�񳡾�����
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
    visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    auto background = Sprite::create("map.png");//���ñ�������
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
void mapChoose::returnChoose(Ref* pSender)
{
    CCLOG("return last");
    TowerManager::getInstance()->clearTowers();//ɾ���ϸ���ͼ�в���������������
    MonsterManager::getInstance()->clearMonster();//ɾ���ϸ���ͼ�в����Ĺ��������
    Director::getInstance()->popScene();//�ӵ�ͼ�˳�������ջ�ｫ��ͼѡ��ĳ���������Ϊ��ǰ���г���
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
void mapChoose::onTouchEnded(Touch* touch, Event* event)
{
    if (fireBottleClicked == true)
    {
        fireBottleClicked = false;
        return;
    }
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    //�������׼���������������ʹ�������Ǵӱ�Ե��ʼ�ֲ�
    Vec2 mousePos = touch->getLocation();
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
        if (ifSafe(mousePos) && mousePos != obstacleTree->getPosition())//���λ�ÿ��԰�װ����
        {
            if (goldCoin >= 100)//����㹻�޽���ƿ��
            {
                lightingTower = MenuItemImage::create(
                    "lightingTowerCanBuild.png",
                    "lightingTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::lightingTowerGenerate, this));//����ƿ����ص�����
            }
            else
            {
                lightingTower = MenuItemImage::create(
                    "lightingTowerCannotBuild.png",
                    "lightingTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
            }
            if (goldCoin >= 160)//����㹻
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCanBuild.png",
                    "fireBottleCanBuild.png",
                    CC_CALLBACK_1(mapOne::fireBottleGenerate, this));//�󶨻�ƿ����ص�����
                leafTower = MenuItemImage::create(
                    "leafTowerCanBuild.png",
                    "leafTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::leafTowerGenerate, this));//�󶨷��Ƚ���ص�����
            }
            else
            {
                fireBottle = MenuItemImage::create(
                    "fireBottleCannotBuild.png",
                    "fireBottleCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
                leafTower = MenuItemImage::create(
                    "leafTowerCannotBuild.png",
                    "leafTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
            }
            Menu* menu = Menu::create(fireBottle, leafTower, lightingTower, NULL);
            this->addChild(menu, 3);
            //��ѡ������
            selectedPos = Sprite::create("Choose.png");
            selectedPosSet(mouseLocX, mouseLocY);//��ѡ��y������趨
            this->addChild(selectedPos, 2);
        }
        else
            CCLOG("Click invalid");
    }
    else if (fireBottle == nullptr && (towerName != "" || towerMenu != nullptr))
    {
        // �����fireBottle,ѡ��������ɾ��
        CCLOG("Choose upgrade or delete!");
        if (towerMenu == nullptr && towerName != "")//���������
        {
            Sprite* towerInstance = TowerManager::getInstance()->getTower(towerName)->getTowerSprite();
            //���������޷�������
            
            if (!towerName.compare(0, 9, "FireTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeFireTower, this));//����ͼ�꣨Ǯ�㹻��
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "CannotUpgrade.png",
                        "CannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
                }
            }
            if (!towerName.compare(0, 9, "LeafTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "FireBottleTowerDelete.png",
                    "FireBottleTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "CanUpgrade.png",
                        "CanUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLeafTower, this));//����ͼ�꣨Ǯ�㹻��
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "CannotUpgrade.png",
                        "CannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
                }
            }
            if (!towerName.compare(0, 13, "LightingTower"))
            {
                auto deleteItem = MenuItemImage::create(
                    "LightingTowerDelete.png",
                    "LightingTowerDelete.png",
                    CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                if (goldCoin >= 320)
                {
                    auto upgradeItem = MenuItemImage::create(
                        "LightingTowerUpgrade.png",
                        "LightingTowerUpgrade.png",
                        CC_CALLBACK_1(mapOne::upgradeLightTower, this));//����ͼ�꣨Ǯ�㹻��
                    upgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(upgradeItem, deleteItem, NULL);
                }
                else
                {
                    auto cannotUpgradeItem = MenuItemImage::create(
                        "LightingTowerCannotUpgrade.png",
                        "LightingTowerCannotUpgrade.png",
                        CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
                    cannotUpgradeItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y + cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(cannotUpgradeItem, deleteItem, NULL);
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
    return;
}
bool mapChoose::onTouchBegan(Touch* touch, Event* event)//��֤��������������
{
    return true;
}
void mapChoose::fireBottleGenerate(Ref* pSender)//���ɻ���ƿ��������
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
    scheduleUpdate();
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapChoose::leafTowerGenerate(Ref* pSender)//���ɷ��ȵ�������
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
    scheduleUpdate();
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapChoose::lightingTowerGenerate(Ref* pSender)//������ƿ��������
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
    scheduleUpdate();
    goldCoin -= 100;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    fireBottleClicked = true;//��ֹ���fireBottleͼ��ʱ����onMouseEnded����
}
void mapChoose::nullCallBack(Ref* pSender)//���û���ƿ����
{

}
void mapChoose::upgradeFireTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapChoose::upgradeLeafTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapChoose::upgradeLightTower(Ref* pSender)//��������ƿ��������
{
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 260;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapChoose::deleteTower(Ref* pSender)//���ɻ���ƿ��������
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
void mapChoose::deleteLightTower(Ref* pSender)//���ɻ���ƿ��������
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
cocos2d::Vec2 mapChoose::passPos()
{
    return towerPos;
}//��������λ��

