#include"MapChoose.h"
#include"TowerManager.h"
#include"MonsterManager.h"
#include"SunFLowerTower.h"
#include"LeafTower.h"
#include"LightingTower.h"
#include<string>
#include<vector>
#include"MapOne.h"
#include"MapTwo.h"
#include"Obstacles.h"
#include"GameObject.h"

USING_NS_CC;
#define cellHeight 60
#define cellWidth 60
int goldCoin = 10000;//���
bool ifLocked = 1;//mapTwo����

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

    auto routeOneChoose = Sprite::create("routeOneChoose.png");
    routeOneChoose->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(routeOneChoose, 1);//���볡����

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
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height));
    auto menu = Menu::create(returnItem, rightItem, enterItem, NULL);//�����˵�����������������
    this->addChild(menu, 1);//���˵����볡����

    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    this->addChild(label, 1);//����ǩ���볡����
    return true;
}
Scene* mapChoose::mapOneChoose()
{
    Scene* mapOneScene = Scene::create();

    auto background = Sprite::create("map.png");//���ñ�������
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapOneScene->addChild(background, 0);//���볡���У�������Ϊ�ײ�

    auto routeOneChoose = Sprite::create("routeOneChoose.png");
    routeOneChoose->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapOneScene->addChild(routeOneChoose, 1);//���볡����

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
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height));
    auto menu = Menu::create(returnItem, rightItem, enterItem, NULL);//�����˵�����������������
    mapOneScene->addChild(menu, 1);//���˵����볡����

    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapOneScene->addChild(label, 1);//����ǩ���볡����
    return mapOneScene;

}
void mapChoose::returnLast(Ref* pSender)
{
    CCLOG("return last");
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
    Director::getInstance()->popScene();//�ӵ�ͼѡ��ĳ���������ջ�ｫ���泡��������Ϊ��ǰ���г���
    return;
}
void mapChoose::returnChoose(Ref* pSender)
{
    CCLOG("return last");
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    TowerManager::getInstance()->clearTowers();//ɾ���ϸ���ͼ�в���������������
    MonsterManager::getInstance()->clearMonster();//ɾ���ϸ���ͼ�в����Ĺ��������
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//�ӵ�ͼ�˳�������ջ�ｫ��ͼѡ��ĳ���������Ϊ��ǰ���г���
    Director::getInstance()->popScene();
    return;
}
void mapChoose::flipToNext(Ref* pSender)
{
    Scene* mapChoose = mapChoose::createScene();
    auto background = Sprite::create("map.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(background, 0);

    auto routeTwoChoose = Sprite::create("routeTwoChoose.png");
    routeTwoChoose->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    mapChoose->addChild(routeTwoChoose, 1);//���볡����

    auto returnItem = MenuItemImage::create(
        "return.png",
        "returnSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));//�ص�����İ���
    auto leftItem = MenuItemImage::create(
        "left.png",
        "leftSelected.png",
        CC_CALLBACK_1(mapChoose::flipToLast, this));//��������һ��ͼѡ��İ���
    MenuItemImage* enterItem;
    if (ifLocked == 0)
    {
        enterItem = MenuItemImage::create(
            "enter.png",
            "enterSelected.png",
            CC_CALLBACK_1(mapChoose::enterMapTwo, this));//����ڶ��ŵ�ͼ�İ���
    }
    else
    {
        enterItem = MenuItemImage::create(
            "enter.png",
            "enterSelected.png",
            CC_CALLBACK_1(mapChoose::nullCallBack, this));//����ڶ��ŵ�ͼ�İ���
        Sprite* lock = Sprite::create("mapLock.png");
        lock->setPosition(Vec2(routeTwoChoose->getPosition().x + routeTwoChoose->getContentSize().width / 2 - 50, routeTwoChoose->getPosition().y - routeTwoChoose->getContentSize().height / 2));
        mapChoose->addChild(lock, 2);
    }
    returnItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + 3 * returnItem->getContentSize().height));
    leftItem->setPosition(Vec2(origin.x - visibleSize.width / 2 + 80, origin.y));
    enterItem->setPosition(Vec2(origin.x, origin.y - 3 * enterItem->getContentSize().height));
    auto menu = Menu::create(returnItem, leftItem, enterItem, NULL);//�����˵�����������������
    mapChoose->addChild(menu, 2);

    auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 54);//������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * label->getContentSize().height));
    mapChoose->addChild(label, 1);
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
}
void mapChoose::flipToLast(Ref* pSender)
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    Scene* mapChoose = mapChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, mapChoose));
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
    /* if (sunFlowerClicked == true)
     {
         sunFlowerClicked = false;
         return;
     }*/
    CCLOG("onTouchEnded - Start");

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

    //�������׼���������������ʹ�������Ǵӱ�Ե��ʼ�ֲ�
    Vec2 mousePos = touch->getLocation();
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    label->setString("Mouse Coordinates: " + std::to_string(mouseLocX) + ", " + std::to_string(mouseLocY));
    //��ȡ��ǰ�����������
    towerName = TowerManager::getInstance()->towerSelected(mousePos);
    //��ȡ�ִ�������Ϣ
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();
    //�洢�ϰ�������
    std::vector<Obstacles*> obstacles = GameObject::getInstance()->getObstacles();
    ////�����ж��Ƿ���������
    //GameObject* attackMonster = ifClickedMonster(monsters, mousePos);
    ////�����ж��Ƿ������ϰ���
    //Obstacles* attackObstacle = ifClickedObstacle(obstacles, mousePos);
    GameObject* attackMonster = nullptr;
    Obstacles* attackObstacle = nullptr;
    //�ж�
    if (sunFlower == nullptr && towerName == "" && towerMenu == nullptr && attackMonster == nullptr && attackObstacle == nullptr)//����հ״�
    {
        if (ifSafe(mousePos))//���λ�ÿ��԰�װ����
        {
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("pointEmpty.MP3", false, 1.0f, 1.0f, 1.0f);
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
                leafTower = MenuItemImage::create(
                    "leafTowerCanBuild.png",
                    "leafTowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::leafTowerGenerate, this));//�󶨷��Ƚ���ص�����
            }
            else
            {
                leafTower = MenuItemImage::create(
                    "leafTowerCannotBuild.png",
                    "leafTowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
            }
            if (goldCoin >= 160)//����㹻
            {
                sunFlower = MenuItemImage::create(
                    "sunFlowerCanBuild.png",
                    "sunFlowerCanBuild.png",
                    CC_CALLBACK_1(mapOne::sunFlowerGenerate, this));//�󶨻�ƿ����ص�����
            }
            else
            {
                sunFlower = MenuItemImage::create(
                    "sunFlowerCannotBuild.png",
                    "sunFlowerCannotBuild.png",
                    CC_CALLBACK_1(mapOne::nullCallBack, this));//�󶨿ջص�����
            }
            Menu* menu = Menu::create(sunFlower, leafTower, lightingTower, NULL);
            this->addChild(menu, 3);
            //��ѡ������
            selectedPos = Sprite::create("Choose.png");
            selectedPosSet(mouseLocX, mouseLocY);//��ѡ��y������趨
            this->addChild(selectedPos, 2);
        }
        else
        {
            //������Ч
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("forbidden.MP3", false, 1.0f, 1.0f, 1.0f);
        }
    }
    else if (sunFlower == nullptr && (towerName != "" || towerMenu != nullptr) && attackMonster == nullptr && attackObstacle == nullptr)
    {
        // �����sunFlower,ѡ��������ɾ��
        CCLOG("Choose upgrade or delete!");
        if (towerMenu == nullptr && towerName != "")//���������
        {
            Sprite* towerInstance = TowerManager::getInstance()->getTower(towerName)->getTowerSprite();
            //���������޷�������
            if (TowerManager::getInstance()->getTower(towerName)->getTowerLevel() == 3)
            {
                if (!towerName.compare(0, 14, "SunFlowerTower") || !towerName.compare(0, 9, "LeafTower"))
                {
                    auto deleteItem = MenuItemImage::create(
                        "fullTowerDelete.png",
                        "fullTowerDelete.png",
                        CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                    deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(deleteItem, NULL);
                }
                else
                {
                    auto deleteItem = MenuItemImage::create(
                        "fullTowerDeleteTwo.png",
                        "fullTowerDeleteTwo.png",
                        CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                    deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                    towerMenu = Menu::create(deleteItem, NULL);
                }
            }
            else
            {
                if (!towerName.compare(0, 14, "SunFlowerTower"))
                {
                    auto deleteItem = MenuItemImage::create(
                        "sunFlowerTowerDelete.png",
                        "sunFlowerTowerDelete.png",
                        CC_CALLBACK_1(mapOne::deleteTower, this));//ɾ��ͼ��
                    deleteItem->setPosition(towerInstance->getPosition().x - visibleSize.width / 2, towerInstance->getPosition().y - cellHeight - visibleSize.height / 2);
                    if (goldCoin >= 320)
                    {
                        auto upgradeItem = MenuItemImage::create(
                            "CanUpgrade.png",
                            "CanUpgrade.png",
                            CC_CALLBACK_1(mapOne::upgradeSunFlowerTower, this));//����ͼ�꣨Ǯ�㹻��
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
                        "sunFlowerTowerDelete.png",
                        "sunFlowerTowerDelete.png",
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
            }
            this->addChild(towerMenu, 2);
            //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
        }
        else
        {
            // ����˷�towerͼ��
            this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
            towerMenu = nullptr;
            //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
        }
    }
    //else if (attackMonster != nullptr || attackObstacle != nullptr)
    //{
    //    //���ȹ�������
    //    if (priorAttackLogo != nullptr)
    //    {
    //        //if (priorAttackLogo != nullptr && dynamic_cast<GameObject*>(dynamic_cast<Sprite*>(priorAttackLogo)->getParent())->currentHealth <= 0)
    //        //    priorAttackLogo = nullptr;

    //        if (attackMonster != nullptr && priorAttackLogo->getParent() == attackMonster->getSprite())
    //        {
    //            attackMonster->getSprite()->removeChild(priorAttackLogo, true);//�� attackMonster ���ӽڵ����Ƴ�
    //            priorAttackLogo = nullptr;
    //            //ȡ�����ȹ���
    //            TowerManager::getInstance()->cancelFirstTarget();
    //        }
    //        else if(attackObstacle != nullptr && priorAttackLogo->getParent() == attackObstacle->getSprite())
    //        {
    //            attackObstacle->getSprite()->removeChild(priorAttackLogo, true); //�� attackObstacle ���ӽڵ����Ƴ�
    //            priorAttackLogo = nullptr;
    //            //ȡ�����ȹ���
    //            TowerManager::getInstance()->cancelFirstTarget();
    //        }
    //    }
    //    else
    //    {
    //        priorAttackLogo = Sprite::create("priorAttackLogo.png");
    //        if (attackMonster != nullptr)
    //        {
    //            lastPrior = attackMonster->getSprite();
    //            attackMonster->getSprite()->addChild(priorAttackLogo, 1);
    //            priorAttackLogo->setPosition(Vec2(attackMonster->getSprite()->getContentSize().width / 2, attackMonster->getSprite()->getContentSize().height));
    //            //��������
    //            TowerManager::getInstance()->setFirstTarget(attackMonster);
    //        }
    //        else
    //        {
    //            lastPrior = attackObstacle->getSprite();
    //            attackObstacle->getSprite()->addChild(priorAttackLogo, 1);
    //            priorAttackLogo->setPosition(Vec2(attackObstacle->getSprite()->getContentSize().width / 2, attackObstacle->getSprite()->getContentSize().height));
    //            //��������
    //            TowerManager::getInstance()->setFirstTarget(attackObstacle);
    //        }
    //        //������Ч
    //        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    //        audio->playEffect("pointObstacle.MP3", false, 1.0f, 1.0f, 1.0f);

    //        priorAttackLogo->setScale(0.25);
    //    }
    //}
    else
    {
        this->removeChild(sunFlower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
        removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
        sunFlower = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
        //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
    }
    event->stopPropagation();
    return;
}
bool mapChoose::onTouchBegan(Touch* touch, Event* event)//��֤��������������
{
    return true;
}
void mapChoose::sunFlowerGenerate(Ref* pSender)//����̫����������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(sunFlower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    sunFlower = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    SunFlowerTower* towerClass = new SunFlowerTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getBaseSprite(), 2);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    scheduleUpdate();
    goldCoin -= 180;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
}
void mapChoose::leafTowerGenerate(Ref* pSender)//���ɷ��ȵ�������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(leafTower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    sunFlower = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    LeafTower* towerClass = new LeafTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getBaseSprite(), 2);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    scheduleUpdate();
    goldCoin -= 160;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
}
void mapChoose::lightingTowerGenerate(Ref* pSender)//������ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    removeChild(selectedPos);//ѡ��ȡ�����߽�����������ѡ�����ʧ
    this->removeChild(leafTower->getParent());//�Ƴ�ѡ��ͼ�����ڲ˵�
    sunFlower = nullptr;  // ��������Ϊ�գ��Ա��´ε�����´���
    LightingTower* towerClass = new LightingTower(towerPos);
    //���������ּ���ָ���������������
    TowerManager::getInstance()->addTower(towerClass->getTowerName(), towerClass);
    //������������볡��
    this->addChild(towerClass->getBaseSprite(), 2);
    //������������볡��
    this->addChild(towerClass->getTowerSprite(), 2);
    //�۳���Ӧ���
    scheduleUpdate();
    goldCoin -= 100;
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ
    //sunFlowerClicked = true;//��ֹ���sunFlowerͼ��ʱ����onMouseEnded����
}
void mapChoose::upgradeSunFlowerTower(Ref* pSender)//��������ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;
}
void mapChoose::upgradeLeafTower(Ref* pSender)//��������ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 320;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapChoose::upgradeLightTower(Ref* pSender)//��������ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
    TowerManager::getInstance()->getTower(towerName)->towerUpgrade();
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    goldCoin -= 260;//��ҿ۳�
    goldCoinDisplay->setString(std::to_string(goldCoin));//���label���޸�
    towerMenu = nullptr;

}
void mapChoose::deleteTower(Ref* pSender)//���ɻ���ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
    CCLOG("Remove tower");
    if (TowerManager::getInstance()->getTower(towerName)->getTowerLevel() == 3)
        goldCoin += 480;
    else
        goldCoin += 120;
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    removeChild(TowerManager::getInstance()->getTower(towerName)->getBaseSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    //������Ӧ���
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ

    towerMenu = nullptr;
}
void mapChoose::deleteLightTower(Ref* pSender)//���ɻ���ƿ��������
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
    CCLOG("Remove tower");
    if (TowerManager::getInstance()->getTower(towerName)->getTowerLevel() == 3)
        goldCoin += 352;
    else
        goldCoin += 80;
    removeChild(TowerManager::getInstance()->getTower(towerName)->getTowerSprite());
    removeChild(TowerManager::getInstance()->getTower(towerName)->getBaseSprite());
    TowerManager::getInstance()->removeTower(towerName);
    this->removeChild(towerMenu);//�Ƴ�ѡ��ͼ�����ڲ˵�
    //������Ӧ���
    goldCoinDisplay->setString(std::to_string(goldCoin));//���Ľ�ұ�ǩ

    towerMenu = nullptr;
}
void mapChoose::nullCallBack(cocos2d::Ref* pSender)//�ջص�����
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);
}
void mapChoose::suspend(Ref* pSender)//����Ϸ����ͣ
{
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("button.MP3", false, 1.0f, 1.0f, 1.0f);

    //��ͣҳ�泡������
    Scene* suspendScene = Scene::create();
    auto suspendBackground = Sprite::create("suspendBG.png");
    suspendBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
    suspendScene->addChild(suspendBackground, 1);

    auto background = Sprite::create("map.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    suspendScene->addChild(background, 0);

    //���¿�ʼ��Ϸ
    auto tryAgain = MenuItemImage::create(
        "tryAgain.png",
        "tryAgainSelected.png",
        CC_CALLBACK_1(mapChoose::tryAgain, this));
    tryAgain->setPosition(Vec2(origin.x, origin.y + 110));
    //������Ϸ
    auto continueGame = MenuItemImage::create(
        "continue.png",
        "continueSelected.png",
        CC_CALLBACK_1(mapChoose::returnLast, this));
    continueGame->setPosition(Vec2(origin.x, origin.y - 110));
    //�ص���ҳ��
    auto home = MenuItemImage::create(
        "home.png",
        "homeSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    home->setPosition(Vec2(origin.x, origin.y));
    auto menu = Menu::create(tryAgain, continueGame, home, NULL);
    suspendScene->addChild(menu, 2);
    Director::getInstance()->pushScene(suspendScene);//������ͣ����

}
void mapChoose::tryAgain(Ref* pSender)//�����麯������
{
    CCLOG("virtual");
}
GameObject* mapChoose::ifClickedMonster(std::vector<GameObject*> monsters, Vec2 mousePos)
{
    for (GameObject* currentMonster : monsters)
    {
        if (currentMonster->getSprite()->getBoundingBox().containsPoint(mousePos))//�������ĳһ����
            return currentMonster;
    }
    return nullptr;
}
Obstacles* mapChoose::ifClickedObstacle(std::vector<Obstacles*> obstacles, Vec2 mousePos)
{
    for (Obstacles* currentObstacle : obstacles)
    {
        if (currentObstacle->getSprite()->getBoundingBox().containsPoint(mousePos))//�������ĳһ����
            return currentObstacle;
    }
    return nullptr;
}
void mapChoose::gameWinOne()
{
    ifLocked = 0;
    // ��ȡ�ɼ���С��ԭ��
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Scene* winScene = Scene::create();
    auto gameWinBackground = Sprite::create("winBG.png");
    gameWinBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    winScene->addChild(gameWinBackground, 0);
    //ʤ������
    auto win = Sprite::create("win.png");
    win->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
    winScene->addChild(win, 1);
    auto winItem = Sprite::create("winGameItem.png");
    winItem->setPosition(Vec2(winItem->getContentSize().width / 2, winItem->getContentSize().height / 2));
    winScene->addChild(winItem, 1);

    //������Ϸ
    auto winContinue = MenuItemImage::create(
        "winContinue.png",
        "winContinueSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    auto menu = Menu::create(winContinue, NULL);
    winScene->addChild(menu, 1);
    winContinue->setPosition(Vec2(origin.x, origin.y - 100));
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("success.MP3", false, 1.0f, 1.0f, 1.0f);


    Director::getInstance()->pushScene(winScene);//�����ʤ����

}
void mapChoose::gameWinTwo()
{
    // ��ȡ�ɼ���С��ԭ��
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Scene* winScene = Scene::create();
    auto gameWinBackground = Sprite::create("winBG.png");
    gameWinBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    winScene->addChild(gameWinBackground, 0);
    //ʤ������
    auto win = Sprite::create("win.png");
    win->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
    winScene->addChild(win, 1);
    auto winItem = Sprite::create("winGameItem.png");
    winItem->setPosition(Vec2(winItem->getContentSize().width / 2, winItem->getContentSize().height / 2));
    winScene->addChild(winItem, 1);

    //������Ϸ
    auto winContinue = MenuItemImage::create(
        "winContinue.png",
        "winContinueSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    auto menu = Menu::create(winContinue, NULL);
    winScene->addChild(menu, 1);
    winContinue->setPosition(Vec2(origin.x, origin.y - 100));
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("success.MP3", false, 1.0f, 1.0f, 1.0f);


    Director::getInstance()->pushScene(winScene);//�����ʤ����

}

void mapChoose::tryAgainOne(cocos2d::Ref*)
{
    TowerManager::getInstance()->clearTowers();//ɾ���ϸ���ͼ�в���������������
    MonsterManager::getInstance()->clearMonster();//ɾ���ϸ���ͼ�в����Ĺ��������
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//������ͣҳ��
    Director::getInstance()->popScene();//������Ϸҳ��
    enterMapOne(this);
}
void mapChoose::gameOverOne()
{
    Scene* gameOverScene = Scene::create();
    // ��ȡ�ɼ���С��ԭ��
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // ����ʧ�ܱ���
    auto gameOverBackground = Sprite::create("gameOverItem.png");
    gameOverBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(gameOverBackground, 1);

    // ������������������Ļ����
    auto background = Sprite::create("winBG.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(background, 0);
    //���¿�ʼ��Ϸ
    auto retry = MenuItemImage::create(
        "retry.png",
        "retrySelected.png",
        CC_CALLBACK_1(mapChoose::tryAgainOne, this));
    retry->setPosition(Vec2(origin.x - 10, origin.y - 145));
    //���ص�ͼѡ��
    auto returnChoose = MenuItemImage::create(
        "returnChoose.png",
        "returnChooseSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    returnChoose->setPosition(Vec2(origin.x - 10, origin.y - 210));
    auto menu = Menu::create(retry, returnChoose, NULL);
    gameOverScene->addChild(menu, 1);
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("fail.MP3", false, 1.0f, 1.0f, 1.0f);


    Director::getInstance()->pushScene(gameOverScene);//����ʧ�ܽ���

}
void mapChoose::tryAgainTwo(cocos2d::Ref*)
{
    TowerManager::getInstance()->clearTowers();//ɾ���ϸ���ͼ�в���������������
    MonsterManager::getInstance()->clearMonster();//ɾ���ϸ���ͼ�в����Ĺ��������
    delete GameObject::getInstance();
    Director::getInstance()->popScene();//������ͣҳ��
    Director::getInstance()->popScene();//������Ϸҳ��
    enterMapTwo(this);
}
void mapChoose::gameOverTwo()
{
    Scene* gameOverScene = Scene::create();
    // ��ȡ�ɼ���С��ԭ��
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // ����ʧ�ܱ���
    auto gameOverBackground = Sprite::create("gameOverItem.png");
    gameOverBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(gameOverBackground, 1);

    // ������������������Ļ����
    auto background = Sprite::create("winBG.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gameOverScene->addChild(background, 0);
    //���¿�ʼ��Ϸ
    auto retry = MenuItemImage::create(
        "retry.png",
        "retrySelected.png",
        CC_CALLBACK_1(mapChoose::tryAgainTwo, this));
    retry->setPosition(Vec2(origin.x - 10, origin.y - 145));
    //���ص�ͼѡ��
    auto returnChoose = MenuItemImage::create(
        "returnChoose.png",
        "returnChooseSelected.png",
        CC_CALLBACK_1(mapChoose::returnChoose, this));
    returnChoose->setPosition(Vec2(origin.x - 10, origin.y - 210));
    auto menu = Menu::create(retry, returnChoose, NULL);
    gameOverScene->addChild(menu, 1);
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("fail.MP3", false, 1.0f, 1.0f, 1.0f);


    Director::getInstance()->pushScene(gameOverScene);//����ʧ�ܽ���

}