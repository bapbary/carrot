#include "TowerManager.h"

TowerManager* TowerManager::instance = nullptr;

TowerManager* TowerManager::getInstance() {
    if (!instance) {
        instance = new TowerManager();
    }
    return instance;
}

std::string TowerManager :: towerselected(const cocos2d::Vec2& towerlocation) {
    // 遍历所有存储的炮塔
    for (const auto& tower : towers) {
        //表示当前遍历到的该炮塔实例的指针
        BasicDefensiveTower* currentTower = tower.second;

        // 匹配当前点击炮塔的坐标是否与当前遍历实例炮塔相等
        if ((currentTower->getTowerLocation()) == towerlocation) {
            // 如匹配到符合的炮塔，返回当前炮塔的名称
            return currentTower->getTowerName();
            //注：这个炮塔名称用于去得到当前所选炮塔实例的指针然后可以对它进行操作，看下面
            
            /*
            // 假设 towerName 是你想获取的炮塔的名字
            std::string towerName = "desiredTowerName";
            BasicDefensiveTower* desiredTower = TowerManager::getInstance()->getTower(towerName);

            // 现在你可以使用 desiredTower 操作相关炮塔的实例
            if (desiredTower != nullptr) {
                // 进行你的操作
            }*/

        }
    }

    // 如果在点击坐标处没有找到炮塔，返回一个空字符串或某个默认值
    return "";
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