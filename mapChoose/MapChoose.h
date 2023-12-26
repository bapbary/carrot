#ifndef  MAP_CHOOSE_H
#define  MAP_CHOOSE_H

#include "cocos2d.h"
static int count;//全局计数器

class mapChoose : public cocos2d::Scene
{
public:
    cocos2d::Size visibleSize;//视图的可见大小
    cocos2d::Vec2 origin;//视图初始化时的可见大小
    cocos2d::Label* label;
    cocos2d::Sprite* route;//路线图
    cocos2d::MenuItemImage* fireBottle;//火瓶选择图标
    cocos2d::MenuItemImage* leafTower;//风扇选择图标
    cocos2d::MenuItemImage* lightingTower;//闪电瓶选择图标
    cocos2d::EventListenerTouchOneByOne* touchListener;//触摸监听
    cocos2d::Sprite* loadingBar;//血条背景
    cocos2d::ProgressTimer* loadingBarBlood;//血条填充
    cocos2d::Sprite* selectedPos;//复选框
    cocos2d::Menu* towerMenu = nullptr;//炮塔升级菜单
    bool fireBottleClicked = false;
    std::string towerName;//若点击位置有炮塔即可接收其名字，若没有则为空串
    cocos2d::Vec2 towerPos;//炮塔位置
    cocos2d::Sprite* obstacleTree;//障碍物
    cocos2d::Label* goldCoinDisplay;
    int goldCoin = 10000;//金币
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图选择场景初始化
    void returnLast(cocos2d::Ref* pSender);//回到上一场景
    void flipToNext(cocos2d::Ref* pSender);//滑动到下一个地图选择场景
    void flipToLast(cocos2d::Ref* pSender);//滑动到上一个地图选择场景
    void enterMapOne(cocos2d::Ref* pSender);//进入第一个地图中
    void enterMapTwo(cocos2d::Ref* pSender);//进入第二个地图中
    void returnChoose(cocos2d::Ref* pSender);//从地图中退出
    virtual bool ifSafe(cocos2d::Vec2 mousePos) { return 1; };//判断点击到的是否为炮塔
    virtual void selectedPosSet(float mouseLocX, float mouseLocY) { return; };//复选框位置设置（不同位置有细小差别）
    virtual void obstacleDispatch() { return; };
    void fireBottleGenerate(cocos2d::Ref* pSender);//放置火焰瓶炮塔
    void leafTowerGenerate(cocos2d::Ref* pSender);//放置风扇炮塔
    void lightingTowerGenerate(cocos2d::Ref* pSender);//放置绿瓶炮塔
    void nullCallBack(cocos2d::Ref* pSender);//空回调函数
    void upgradeFireTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//删除炮塔
    void deleteLightTower(cocos2d::Ref* pSender);//删除炮塔
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//点击结束
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//点击开始（保证监听正常进行）
    cocos2d::Vec2 passPos();//传递炮塔位置

    CREATE_FUNC(mapChoose);

};
#endif // MAP_CHOOSE_H
