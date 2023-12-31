#include "MonsterManager.h"

MonsterManager* MonsterManager::getInstance() {
    static MonsterManager instance;
    return &instance;
}

std::vector<GameObject*>& MonsterManager::getMonsters() {
    return monsters;
}
void MonsterManager::addMonster(GameObject* monster)
{
    monsterNum++;
    monsters.push_back(monster);
}
void MonsterManager::removeMonster(GameObject*&monster)
{
    // 在monsters容器中查找并删除指定的怪物
    auto it = std::find(monsters.begin(), monsters.end(), monster);
    if (it != monsters.end())
    {
        monsters.erase(it);
        monster = nullptr;
    }
}

const std::vector<cocos2d::Vec2>& MonsterManager::getMonsterPositions() 
{
    return monsterPositions;
}
void MonsterManager::clearMonster()
{
    monsters.clear();
}
void MonsterManager::updateMonsterPositions() {
    // 更新怪物位置
    monsterPositions.clear();
    for (const auto& monster : monsters) {
        if(auto sprite = dynamic_cast<cocos2d::Sprite*>(monster)) {
            monsterPositions.push_back(sprite->getPosition());
            CCLOG("guQ");
        }
    }
}

bool MonsterManager::IsEmpty()
{
    if (monsters.size() == 0)
        return true;
    else
        return false;
}
