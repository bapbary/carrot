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
    //Scene* startScene = Scene::create();
    //mapOne* map = mapOne::create();
    //startScene->addChild(map);
    auto scene = Scene::createWithPhysics();
    auto layer = mapOne::create();
    scene->addChild(layer);
    return scene;
}
bool mapOne::init()//��һ�ŵ�ͼ�ĳ�ʼ��
{
    if (!Layer::init())
    {
        return false;
    }  
    schedule(CC_SCHEDULE_SELECTOR(BasicDefensiveTower::tower_targetupdate), 1.0f, CC_REPEAT_FOREVER, 0);
    visibleSize = Director::getInstance()->getVisibleSize();//��ͼ�Ŀɼ���С
    origin = Director::getInstance()->getVisibleOrigin();//��ͼ��ʼ��ʱ�Ŀɼ���С

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
        CC_CALLBACK_1(mapChoose::returnChoose, this));//�ص���һ�����İ���
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
    touchListener->onTouchEnded = CC_CALLBACK_2(mapChoose::onTouchEnded, this);
    touchListener->onTouchBegan = CC_CALLBACK_2(mapChoose::onTouchBegan, this);
    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
bool mapOne::ifSafe(cocos2d::Vec2 mousePos)//�жϵ�������Ƿ�Ϊ����λ���Ƿ�Ϸ�
{
    float mouseLocX = mousePos.x;
    float mouseLocY = mousePos.y;
    if (mouseLocY < 100 || (mouseLocY > 185 && mouseLocY < 290 && mouseLocX > 245 && mouseLocX < 1010) || (mouseLocY > 360 && mouseLocY < 470 && mouseLocX > 70 && mouseLocX < 825) || (mouseLocY > 570 && mouseLocY < 655 && mouseLocX > 425 && mouseLocX < 1010) || (mouseLocY < 570 && mouseLocY>295 && mouseLocX > 915) || (mouseLocY < 360 && mouseLocY>100 && mouseLocX < 160 && mouseLocX>40))
        return true;
    else
        return false;
}
void mapOne::selectedPosSet(float mouseLocX, float mouseLocY)
{
    towerPos.x = static_cast<int>((mouseLocX + 1) / cellWidth) * cellWidth + static_cast<int>(selectedPos->getContentSize().width / 2) - 1;
    if (mouseLocY >= 570 && mouseLocY < 610)
    {
        towerPos.y = static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + static_cast<int>(selectedPos->getContentSize().height / 2) + 10;
        fireBottle->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 - static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
        leafTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
        lightingTower->setPosition(static_cast<int>(mouseLocX / cellWidth) * cellWidth - visibleSize.width / 2 + 3 * static_cast<int>(cellWidth / 2), static_cast<int>((mouseLocY - 10) / cellHeight) * cellHeight + cellHeight - visibleSize.height / 2 + 10);
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
