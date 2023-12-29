#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "cocos2d.h"
#include "BasicDefensiveTower.h"
#include <vector>

class TowerManager {
public:
    //��ȡ��������ָ�뺯��
    static TowerManager* getInstance();

    //ȷ����ѡ���������󣨷����������֣�
    std::string towerSelected(const cocos2d::Vec2& towerlocation);

    //�ӹ��������������
    void addTower(const std::string& towerName, BasicDefensiveTower* tower);

    //�ӹ��������Ƴ�����
    void removeTower(const std::string& towerName);

    //ͨ���������ֵõ�ָ��
    BasicDefensiveTower* getTower(const std::string& towerName);

    //ɾ������ʱ�ͷ��ڴ�
    void clearTowers();

    //����������������Ϊ��������Ϊ����Ҫ...��
    std::vector<BasicDefensiveTower*> towers;

    //��ȡ���ȹ���Ŀ��ָ��
    GameObject *getFirstTarget();
private:
    TowerManager() {}
    //����������������ָ��
    static TowerManager* instance;

    //�������������ȹ�������ָ��
    GameObject* FirstTarget = nullptr;
};

#endif // TOWERMANAGER_H