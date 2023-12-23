#include "TowerManager.h"

TowerManager* TowerManager::instance = nullptr;

TowerManager* TowerManager::getInstance() {
    if (!instance) {
        instance = new TowerManager();
    }
    return instance;
}

std::string TowerManager :: towerselected(const cocos2d::Vec2& towerlocation) {
    // �������д洢������
    for (const auto& tower : towers) {
        //��ʾ��ǰ�������ĸ�����ʵ����ָ��
        BasicDefensiveTower* currentTower = tower.second;

        // ƥ�䵱ǰ��������������Ƿ��뵱ǰ����ʵ���������
        if ((currentTower->getTowerLocation()) == towerlocation) {
            // ��ƥ�䵽���ϵ����������ص�ǰ����������
            return currentTower->getTowerName();
            //ע�����������������ȥ�õ���ǰ��ѡ����ʵ����ָ��Ȼ����Զ������в�����������
            
            /*
            // ���� towerName �������ȡ������������
            std::string towerName = "desiredTowerName";
            BasicDefensiveTower* desiredTower = TowerManager::getInstance()->getTower(towerName);

            // ���������ʹ�� desiredTower �������������ʵ��
            if (desiredTower != nullptr) {
                // ������Ĳ���
            }*/

        }
    }

    // ����ڵ�����괦û���ҵ�����������һ�����ַ�����ĳ��Ĭ��ֵ
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