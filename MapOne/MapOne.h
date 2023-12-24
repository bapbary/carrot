#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapOne : public mapChoose
{
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
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图场景初始化(UI设计)
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//点击结束
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//点击开始（保证监听正常进行）
    void obstacleDispatch();//障碍物设置
    void fireBottleGenerate(cocos2d::Ref* pSender);//放置火焰瓶炮塔
    void leafTowerGenerate(cocos2d::Ref* pSender);//放置风扇炮塔
    void lightingTowerGenerate(cocos2d::Ref* pSender);//放置绿瓶炮塔
    void fireBottleCannotGenerate(cocos2d::Ref* pSender);//放置火焰瓶炮塔
    void leafTowerCannotGenerate(cocos2d::Ref* pSender);//放置风扇炮塔
    void lightingTowerCannotGenerate(cocos2d::Ref* pSender);//放置绿瓶炮塔
    cocos2d::Vec2 passPos(){
        return towerPos;
    }//传递炮塔位置
    void upgradeFireTower(cocos2d::Ref* pSender);
    void upgradeLeafTower(cocos2d::Ref* pSender);
    void upgradeLightTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//删除炮塔
    void deleteLightTower(cocos2d::Ref* pSender);//删除炮塔

    bool isTouchTower();
    CREATE_FUNC(mapOne);

};

#endif // MAP_ONE_H

