#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__
#include <vector>
#include "GameObject.h"
#include "cocos2d.h"

class MonsterManager {
public:
    static MonsterManager* getInstance();
    std::vector<GameObject*>& getMonsters();
    void addMonster(GameObject* monster);
    void removeMonster(GameObject*& monster);
    const std::vector<cocos2d::Vec2>& getMonsterPositions();
    void clearMonster();
    bool IsEmpty();
    static int  round;
    std::vector<GameObject*> monsters;
    int monsterNum=0;
private:
    std::vector<cocos2d::Vec2> monsterPositions;
};

#endif // __MONSTER_MANAGER_H__