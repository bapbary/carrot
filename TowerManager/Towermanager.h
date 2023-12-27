#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"
#include <vector>

class TowerManager {
public:
    static TowerManager* getInstance();

    std::string towerSelected(const cocos2d::Vec2& towerlocation);
    void addTower(const std::string& towerName, BasicDefensiveTower* tower);
    void removeTower(const std::string& towerName);
    BasicDefensiveTower* getTower(const std::string& towerName);
    void clearTowers();
    std::vector<BasicDefensiveTower*> towers;
private:
    TowerManager() {}
    static TowerManager* instance;
};

#endif // TOWERMANAGER_H