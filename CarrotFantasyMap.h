/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CARROTFANTASYMAP_SCENE_H__
#define __CARROTFANTASYMAP_SCENE_H__

#include "cocos2d.h"


class sceneCover : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void touchStart(cocos2d::Ref* pSender);//进入封面选择
    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序
    CREATE_FUNC(sceneCover);
};

class sceneChoose : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图选择场景初始化
    void returnLast(cocos2d::Ref* pSender);//回到上一场景
    void flipToNext(cocos2d::Ref* pSender);//滑动到下一个地图选择场景
    void flipToLast(cocos2d::Ref* pSender);//滑动到上一个地图选择场景
    void enterMapOne(cocos2d::Ref* pSender);//进入第一个地图中
    CREATE_FUNC(sceneChoose);

};

class mapOne : public sceneChoose
{
    cocos2d::Label* label;
    cocos2d::MenuItemImage* fireBottle;
    cocos2d::EventListenerTouchOneByOne* touchListener;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图场景初始化
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序

    CREATE_FUNC(mapOne);

};

//定义炮塔基类（本身派生于scene）【后续派生时根据选择覆盖某些参数和函数】
//类成员数据包含每个炮塔的参数和状态，以及一个最重要的精灵本体
//类成员函数是炮塔相关功能的实现
class BasicDifensiveTower : public cocos2d::Scene {
public:

    //构造函数：炮塔参数的初始化并显示
    BasicDifensiveTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation) {
        tower = cocos2d::Sprite::create(filename);
        towerlocation = touchlocation;
        category_code = code;
        tower_level = level;
        //根据种类代号初始化炮塔的其他数值




        //放置炮塔并显示
        tower->setPosition(touchlocation);
        //设置炮塔大小
        tower->setScale(10);
        sprite_show(tower);
        //加入情景放在建立类操作之后一句，不在类中进行放入
    }

    //获取炮塔精灵本身
    cocos2d::Sprite* BasicDifensiveTower::getTowerSprite() const {
        return tower;
    }

    //图标的显示
    void sprite_show(cocos2d::Sprite* sprite) {
        tower->setVisible(true);
    }
    //图标的隐藏
    void sprite_hide(cocos2d::Sprite* sprite) {
        tower->setVisible(false);
    }

    //判断目标对象消失（攻击致死）



    //炮塔更新索敌对象
    void tower_targetupdate() {
        // 如果当前没有目标或者目标超出索敌范围，重新选择目标
        if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
            currenttarget = findTarget();
        }
        //目标选择完成之后进行攻击操作
        tower_attack();
    }

    //炮塔最近距离索敌
    cocos2d::Sprite* findTarget() {
        //在怪物图层中搜索遍历最近的那个
        //需return一个精灵或者return nullptr
    }

    //炮塔攻击
    void tower_attack() {
        //本次攻击目标坐标一脉相承至后续三个函数！！！
    }

    //炮塔转动（参数为当前攻击目标的所处的位置）
    void tower_spin(const cocos2d::Vec2& targetlocation) {
        //计算目标向量（目标->炮塔起点）
        cocos2d::Vec2 direction = towerlocation - targetlocation;
        // 计算旋转的角度（实际得到的是弧度）
        float angle = atan2(direction.y, direction.x);
        // 将弧度转换为角度
        float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
        // 创建旋转动作
        auto rotateAction = cocos2d::RotateBy::create(0.2f, angleInDegrees);
        // 执行旋转动作
        tower->runAction(rotateAction);
    }

    //炮塔产生攻击粒子
    cocos2d::Sprite* createBullet() {
        // 根据炮塔类型和等级创建对应大小的子弹
        cocos2d::Sprite* lightingbullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
        //将子弹也放入当前场景中
        this->addChild(lightingbullet);
        //返回子弹精灵本身，用于后续子弹飞行特效制作
        return lightingbullet;
    }

    //炮塔发射粒子并产生飞行特效
    void tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
        //放置粒子并显示
        bullet->setPosition(towerlocation);
        bullet->setScale(2);
        sprite_show(bullet);
        //然后建立飞行动作
        auto moveTo = cocos2d::MoveTo::create(2.0f, targetlocation);
        //进行速度调整
        auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
        //执行飞行操作
        bullet->runAction(moveTo);
        //到达目标位置后需产生击中特效
        tower_hit_target(targetlocation);
        //删除子弹（风扇需特判）
        this->removeChild(bullet);
    }
    //炮塔粒子撞击目标产生短暂打击特效
    void tower_hit_target(const cocos2d::Vec2& targetlocation) {
        // 根据炮塔类型建立相应打击特效
        cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
        //将打击特效放入场景中
        this->addChild(hit);
        tower->setPosition(targetlocation);
        sprite_show(hit);
        //建立sequence动作序列：先维持半秒后自动销毁
        auto delay = cocos2d::DelayTime::create(1.0f); // 延时1秒
        auto remove = cocos2d::RemoveSelf::create();
        auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
        //执行sequence动作序列
        hit->runAction(sequence);
    }

    //判断炮塔是否可以进行升级并产生
    //（？我不知道pzx这个函数可以做这个不）

    //炮塔升级
    void tower_upgrade() {
        if (tower_level == 1) {
            tower_level++;
            //一系列数值增加

            // 使用新图标替换旧图标
            tower->setTexture("LightingTower_middle.png");
        }
        else if (tower_level == 2) {
            tower_level++;
            //一系列数值增加

            // 使用新图标替换旧图标
            tower->setTexture("LightingTower_big.png");
        }
    }
    //炮塔的删除
    void tower_delete() {
        // 从父节点中移除炮塔
        this->removeChild(tower);
        //在外部调用过这个函数后需手动delete这个炮塔类保证资源释放
        // 在适当的时机，调用删除函数
        /*例如：mytower->tower_delete();
                delete mytower;*/
    }

private:
    //炮塔本身的精灵表示
    cocos2d::Sprite* tower;
    //炮塔目前攻击对象
    cocos2d::Sprite* currenttarget;
    //炮塔位置坐标
    cocos2d::Vec2 towerlocation;
    //当前攻击对象位置坐标
    cocos2d::Vec2 currenttargetlocation;
    //炮塔种类代号
    int category_code;
    //炮塔等级
    int tower_level;
    //炮塔攻击数量  （风扇设定是打1 魔法球会增长）
    int tower_attack_number;
    //炮塔攻击范围
    int tower_attack_range;
    //炮塔攻击伤害
    int tower_attack_power;
    //炮塔攻击速度
    int tower_attack_speed;
    //炮塔持续攻击时间（针对火焰瓶是否加攻）
    int tower_sustained_attack_time;

    //炮塔优先攻击对象
    //个人感觉这个设置成全局会好一些？
    //。。。。。。。。。。。。。。。。
};

//创建攻击粒子类
class Bullet : public cocos2d::Scene {
public:

private:
};

#endif // __CARROTFANTASYMAP_SCENE_H__

