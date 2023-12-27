#include "TowerManager.h"

TowerManager* TowerManager::instance = nullptr;

TowerManager* TowerManager::getInstance() {
    if (!instance) {
        instance = new TowerManager();
    }
    return instance;
}

std::string TowerManager::towerSelected(const cocos2d::Vec2& towerlocation) {
    // 遍历所有存储的炮塔
    for (BasicDefensiveTower* currentTower : towers) {
        // 匹配当前点击炮塔的坐标是否与当前遍历实例炮塔相等
        if (towerlocation.x <= currentTower->getTowerSprite()->getPosition().x + 30 && towerlocation.x >= currentTower->getTowerSprite()->getPosition().x - 30 && towerlocation.y <= currentTower->getTowerSprite()->getPosition().y + 30 && towerlocation.y >= currentTower->getTowerSprite()->getPosition().y - 30) {
            // 如匹配到符合的炮塔，返回当前炮塔的名称
            return currentTower->getTowerName();
            // 注：这个炮塔名称用于去得到当前所选炮塔实例的指针然后可以对它进行操作
        }
    }

    // 如果在点击坐标处没有找到炮塔，返回一个空字符串或某个默认值
    return "";
}

void TowerManager::addTower(const std::string& towerName, BasicDefensiveTower* tower) {
    towers.push_back(tower);
}

void TowerManager::removeTower(const std::string& towerName) {
    for (auto it = towers.begin(); it != towers.end(); ++it) {
        if ((*it)->getTowerName() == towerName) {
            delete* it;
            towers.erase(it);
            break;
        }
    }
}

BasicDefensiveTower* TowerManager::getTower(const std::string& towerName) {
    for (BasicDefensiveTower* currentTower : towers) {
        if (currentTower->getTowerName() == towerName) {
            return currentTower;
        }
    }
    return nullptr;
}

void TowerManager::clearTowers()
{
    delete instance;
    instance = nullptr;
}


