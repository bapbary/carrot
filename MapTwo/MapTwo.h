#ifndef MAP_TWO_H
#define MAP_TWO_H

#include "cocos2d.h"
#include"MapChoose.h"

class mapTwo : public mapChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* route;//路线图
    cocos2d::MenuItemImage* fireBottle;//火瓶选择图标
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
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; };//点击开始（保证监听正常进行）
    void fireBottleGenerate(cocos2d::Ref* pSender) ;//放置炮塔
    cocos2d::Vec2 passPos() {
        return towerPos;
    }//传递炮塔位置
    void upgradeTower(cocos2d::Ref* pSender);
    void deleteTower(cocos2d::Ref* pSender);//删除炮塔
    bool isTouchTower() { return 1; };
    CREATE_FUNC(mapTwo);

};

#endif // MAP_TWO_H


