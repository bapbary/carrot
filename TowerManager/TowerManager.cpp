#include "TowerManager.h"

TowerManager* TowerManager::instance = nullptr;

TowerManager* TowerManager::getInstance() {
    if (!instance) {
        instance = new TowerManager();
    }
    return instance;
}

void TowerManager::addTower(const std::string& towerName, BasicDefensiveTower* tower) {
    towers[towerName] = tower;
}

void TowerManager::removeTower(const std::string& towerName) {
    auto it = towers.find(towerName);
    if (it != towers.end()) {
        delete it->second;
        towers.erase(it);
    }
}

BasicDefensiveTower* TowerManager::getTower(const std::string& towerName) {
    auto it = towers.find(towerName);
    return (it != towers.end()) ? it->second : nullptr;
}