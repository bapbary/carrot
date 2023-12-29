#include "BasicDefensiveTower.h"
#include "MonsterManager.h"
#include"TowerManager.h"

bool BasicDefensiveTower::init()
{
    return true;
}
//��ȡ�������鱾��
cocos2d::Sprite* BasicDefensiveTower::getTowerSprite() {
    return tower;
}

//��ȡ��������
std::string BasicDefensiveTower::getTowerName() {
    return towername;
}

//��ȡ����λ������
cocos2d::Vec2 BasicDefensiveTower::getTowerLocation() {
    return towerlocation;
}

//��ȡ�����ȼ�
int BasicDefensiveTower::getTowerLevel() {
    return tower_level;
}

//ͼ�����ʾ
void BasicDefensiveTower::sprite_show(cocos2d::Sprite* sprite) {
    tower->setVisible(true);
}

//ͼ�������
void BasicDefensiveTower::sprite_hide(cocos2d::Sprite* sprite) {
    tower->setVisible(false);
}

//�����������ж���
void BasicDefensiveTower::tower_targetupdate(float dt) {
    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    for (BasicDefensiveTower* currentTower : TowerManager::getInstance()->towers)
    {
        //�жϵ�ǰ�������ȹ���Ŀ���Ƿ� ��Ϊ�����ڵ�ǰ�����Ĺ�����Χ��
        if (TowerManager::getInstance()->getFirstTarget() != nullptr && (TowerManager::getInstance()->getFirstTarget()->objectPosition - currentTower->getPosition()).length() <= currentTower->tower_attack_range) {
            currentTower->tower_spin(TowerManager::getInstance()->getFirstTarget()->objectPosition);
            currentTower->tower_attack(TowerManager::getInstance()->getFirstTarget()->objectPosition);
        }
        else{
            if (currentTower->currenttarget == nullptr) {
                currentTower->currenttarget = currentTower->findTarget();
            }
            else if ((currentTower->currenttarget->getCurrentPosition() - currentTower->getPosition()).length() > currentTower->tower_attack_range) {
                currentTower->currenttarget = currentTower->findTarget();
            }
            if (currentTower->currenttarget != nullptr) {
                //Ŀ��ѡ�����֮����й�������
                currentTower->tower_spin(currentTower->currenttarget->objectPosition);
                currentTower->tower_attack(currentTower->currenttarget->objectPosition);
            }
        }
    }
}

//���������������
GameObject* BasicDefensiveTower::findTarget() {
    // ��ȡ�����еĹ����б�������������ͨ�� MonsterManager �����
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();

    // ��ʼ����С����Ϊһ���㹻���ֵ
    float minDistance = std::numeric_limits<float>::max();

    // ���ڱ�������Ĺ���
    GameObject* nearestMonster = nullptr;

    // ���������б�
    for (GameObject* monster : monsters) {
        // �������������֮��ľ���
        float distance = towerlocation.distance(monster->getCurrentPosition());

        // �жϹ����Ƿ��������Ĺ�����Χ��
        if (distance <= tower_attack_range && distance < minDistance) {
            // ������С���������Ĺ���
            minDistance = distance;
            nearestMonster = monster;
        }
    }
    return nearestMonster;
}

//��������
void BasicDefensiveTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    //�麯��������
}

//����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
void BasicDefensiveTower::tower_spin(const cocos2d::Vec2& targetlocation) {
    //����Ŀ��������Ŀ��->������㣩
    cocos2d::Vec2 direction = targetlocation - towerlocation;
    // ������ת�ĽǶȣ�ʵ�ʵõ����ǻ��ȣ�
    float angle = atan2(direction.y, direction.x);
    // ������ת��Ϊ�Ƕ�
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    // ������ת����
    //���������һ��-������Ϊ����õ��������Ƕ���Ҫ��ʱ����ת����cocos���ǶȲ�ִ����ʱ����ת��
    auto rotateAction = cocos2d::RotateTo::create(0.3, -angleInDegrees);
    // ִ����ת����
    tower->runAction(rotateAction);
}

//�����������Ӳ�����������Ч
void BasicDefensiveTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //�麯��������
}

//��������
void BasicDefensiveTower::towerUpgrade() {
    //�麯��������
}