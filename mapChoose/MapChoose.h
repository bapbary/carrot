#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameObject;
class Obstacles;
USING_NS_CC;
extern int goldCoin;
static int count;//全局计数器

class mapChoose : public cocos2d::Layer
{
public:
    cocos2d::Size visibleSize;//视图的可见大小
    cocos2d::Vec2 origin;//视图初始化时的可见大小
    cocos2d::Label* label;
    cocos2d::Sprite* route;//路线图
    cocos2d::MenuItemImage* sunFlower;//火瓶选择图标
    cocos2d::MenuItemImage* leafTower;//风扇选择图标
    cocos2d::MenuItemImage* lightingTower;//闪电瓶选择图标
    cocos2d::EventListenerTouchOneByOne* touchListener;//触摸监听
    cocos2d::Sprite* selectedPos;//复选框
    cocos2d::Menu* towerMenu = nullptr;//炮塔升级菜单
    bool sunFlowerClicked = false;
    std::string towerName;//若点击位置有炮塔即可接收其名字，若没有则为空串
    cocos2d::Vec2 towerPos;//炮塔位置
    cocos2d::Label* goldCoinDisplay;
    Sprite* priorAttackLogo = nullptr;
    Sprite* lastPrior = nullptr;
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图选择场景初始化
    void returnLast(cocos2d::Ref* pSender);//回到上一场景
    void flipToNext(cocos2d::Ref* pSender);//滑动到下一个地图选择场景
    void flipToLast(cocos2d::Ref* pSender);//滑动到上一个地图选择场景
    void enterMapOne(cocos2d::Ref* pSender);//进入第一个地图中
    void enterMapTwo(cocos2d::Ref* pSender);//进入第二个地图中
    Scene* mapOneChoose();
    void returnChoose(cocos2d::Ref* pSender);//从地图中退出
    void suspend(cocos2d::Ref* pSender);//在游戏中暂停
    virtual void tryAgain(cocos2d::Ref* pSender);//重新开始游戏
    virtual bool ifSafe(cocos2d::Vec2 mousePos) { return 1; };//判断点击到的是否为炮塔
    virtual void selectedPosSet(float mouseLocX, float mouseLocY) { return; };//复选框位置设置（不同位置有细小差别）
    virtual void obstacleDispatch() { return; };
    void sunFlowerGenerate(cocos2d::Ref* pSender);//放置火焰瓶炮塔
    void leafTowerGenerate(cocos2d::Ref* pSender);//放置风扇炮塔
    void lightingTowerGenerate(cocos2d::Ref* pSender);//放置绿瓶炮塔
    void nullCallBack(cocos2d::Ref* pSender);//空回调函数
    void upgradeSunFlowerTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//删除炮塔
    void deleteLightTower(cocos2d::Ref* pSender);//删除炮塔
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//点击结束
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//点击开始（保证监听正常进行）
    GameObject* ifClickedMonster(std::vector<GameObject*> monsters, Vec2 mousePos);
    Obstacles* ifClickedObstacle(std::vector<Obstacles*> obstacles, Vec2 mousePos);
    void tryAgainOne(cocos2d::Ref*);
    void tryAgainTwo(cocos2d::Ref*);
    void gameOverOne();
    void gameOverTwo();
    void gameWinOne();
    void gameWinTwo();
    CREATE_FUNC(mapChoose);
};
#endif // MAP_CHOOSE_H
