#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"
#include <vector>

class TowerManager {
public:
    //获取炮塔单例指针函数
    static TowerManager* getInstance();

    //确定所选择炮塔对象（返回炮塔名字）
    std::string towerSelected(const cocos2d::Vec2& towerLocation);

    //从管理器中添加炮塔
    void addTower(const std::string& towerName, BasicDefensiveTower* tower);

    //从管理器中移除炮塔
    void removeTower(const std::string& towerName);

    //通过炮塔名字得到指针
    BasicDefensiveTower* getTower(const std::string& towerName);

    //删除炮塔时释放内存
    void clearTowers();

    //炮塔管理器本身（设为公共是因为有需要...）
    std::vector<BasicDefensiveTower*> towers;

    //确定优先攻击目标
    void setFirstTarget(GameObject* target);

    //取消优先攻击目标
    void cancelFirstTarget();

    //获取优先攻击目标指针
    GameObject* getFirstTarget();
private:
    TowerManager() {}
    //炮塔管理器自身单例指针
    static TowerManager* instance;

    //所有炮塔的优先攻击对象指针
    GameObject* firstTarget = nullptr;
};

#endif // TOWERMANAGER_H