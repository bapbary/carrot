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
    std::string towerSelected(const cocos2d::Vec2& towerLocation);

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

    //ȷ�����ȹ���Ŀ��
    void setFirstTarget(GameObject* target);

    //ȡ�����ȹ���Ŀ��
    void cancelFirstTarget();

    //��ȡ���ȹ���Ŀ��ָ��
    GameObject* getFirstTarget();
private:
    TowerManager() {}
    //����������������ָ��
    static TowerManager* instance;

    //�������������ȹ�������ָ��
    GameObject* firstTarget = nullptr;
};

#endif // TOWERMANAGER_H