#include "TowerManager.h"

TowerManager* TowerManager::instance = nullptr;

TowerManager* TowerManager::getInstance() {
    if (!instance) {
        instance = new TowerManager();
    }
    return instance;
}

std::string TowerManager::towerSelected(const cocos2d::Vec2& towerlocation) {
    // �������д洢������
    for (BasicDefensiveTower* currentTower : towers) {
        // ƥ�䵱ǰ��������������Ƿ��뵱ǰ����ʵ���������
        if (towerlocation.x <= currentTower->getTowerSprite()->getPosition().x + 30 && towerlocation.x >= currentTower->getTowerSprite()->getPosition().x - 30 && towerlocation.y <= currentTower->getTowerSprite()->getPosition().y + 30 && towerlocation.y >= currentTower->getTowerSprite()->getPosition().y - 30) {
            // ��ƥ�䵽���ϵ����������ص�ǰ����������
            return currentTower->getTowerName();
            // ע�����������������ȥ�õ���ǰ��ѡ����ʵ����ָ��Ȼ����Զ������в���
        }
    }

    // ����ڵ�����괦û���ҵ�����������һ�����ַ�����ĳ��Ĭ��ֵ
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


