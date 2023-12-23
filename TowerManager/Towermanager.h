#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"
#include <unordered_map>

class TowerManager {
public:
    static TowerManager* getInstance();

    std::string towerselected(const cocos2d::Vec2& towerlocation);
    void addTower(const std::string& towerName, BasicDefensiveTower* tower);
    void removeTower(const std::string& towerName);
    BasicDefensiveTower* getTower(const std::string& towerName);

private:
    TowerManager() {}
    static TowerManager* instance;
    std::unordered_map<std::string, BasicDefensiveTower*> towers;
};

#endif // TOWERMANAGER_H
