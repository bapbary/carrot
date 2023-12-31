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

//��ȡ�����������鱾��
cocos2d::Sprite* BasicDefensiveTower::getBaseSprite() {
    return base;
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
void BasicDefensiveTower::tower_targetupdate1(float dt){
    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    for (BasicDefensiveTower* currentTower : TowerManager::getInstance()->towers)
    {
        if (currentTower->towername.compare(0, 14, "SunFlowerTower") == 0){
            //�жϵ�ǰ�������ȹ���Ŀ���Ƿ� ��Ϊ�����ڵ�ǰ�����Ĺ�����Χ��
            if (TowerManager::getInstance()->getFirstTarget() != nullptr && (TowerManager::getInstance()->getFirstTarget()->objectPosition - currentTower->getPosition()).length() <= currentTower->tower_attack_range) {
                currentTower->tower_spin(TowerManager::getInstance()->getFirstTarget()->objectPosition);
                currentTower->tower_attack(TowerManager::getInstance()->getFirstTarget()->objectPosition);
            }
            else {
                if (currentTower->currenttarget == nullptr || currentTower->currenttarget->currentHealth <= 0) {
                    currentTower->currenttarget = currentTower->findTarget();
                }
                else if ((currentTower->currenttarget->getCurrentPosition() - currentTower->getPosition()).length() > currentTower->tower_attack_range) {
                    currentTower->currenttarget = currentTower->findTarget();
                }
                if (currentTower->currenttarget != nullptr) {
                    //Ŀ��ѡ�����֮����й���������̫��������ת����
                    //currentTower->tower_spin(currentTower->currenttarget->objectPosition);
                    currentTower->tower_attack(currentTower->currenttarget->objectPosition);
                }
            }
        }
    }
}

//�����������ж���
void BasicDefensiveTower::tower_targetupdate2(float dt) {
    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    for (BasicDefensiveTower* currentTower : TowerManager::getInstance()->towers)
    {
        if(currentTower->towername.compare(0, 13, "LightingTower") == 0){
            //�жϵ�ǰ�������ȹ���Ŀ���Ƿ� ��Ϊ�����ڵ�ǰ�����Ĺ�����Χ��
            if (TowerManager::getInstance()->getFirstTarget() != nullptr && (TowerManager::getInstance()->getFirstTarget()->objectPosition - currentTower->getPosition()).length() <= currentTower->tower_attack_range) {
                currentTower->tower_spin(TowerManager::getInstance()->getFirstTarget()->objectPosition);
                currentTower->tower_attack(TowerManager::getInstance()->getFirstTarget()->objectPosition);
            }
            else {
                if (currentTower->currenttarget == nullptr || currentTower->currenttarget->currentHealth <= 0) {
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
}

//�����������ж���
void BasicDefensiveTower::tower_targetupdate3(float dt) {
    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    for (BasicDefensiveTower* currentTower : TowerManager::getInstance()->towers)
    {
        if (currentTower->towername.compare(0, 9, "LeafTower") == 0){
            //�жϵ�ǰ�������ȹ���Ŀ���Ƿ� ��Ϊ�����ڵ�ǰ�����Ĺ�����Χ��
            if (TowerManager::getInstance()->getFirstTarget() != nullptr && (TowerManager::getInstance()->getFirstTarget()->objectPosition - currentTower->getPosition()).length() <= currentTower->tower_attack_range) {
                currentTower->tower_spin(TowerManager::getInstance()->getFirstTarget()->objectPosition);
                currentTower->tower_attack(TowerManager::getInstance()->getFirstTarget()->objectPosition);
            }
            else {
                if (currentTower->currenttarget == nullptr || currentTower->currenttarget->currentHealth <= 0) {
                    currentTower->currenttarget = currentTower->findTarget();
                }
                else if ((currentTower->currenttarget->getCurrentPosition() - currentTower->getPosition()).length() > currentTower->tower_attack_range) {
                    currentTower->currenttarget = currentTower->findTarget();
                }
                if (currentTower->currenttarget != nullptr) {
                    //Ŀ��ѡ�����֮����й�����������ʵ��Ҳ����ת�ģ�
                    //currentTower->tower_spin(currentTower->currenttarget->objectPosition);
                    currentTower->tower_attack(currentTower->currenttarget->objectPosition);
                }
            }
        }
    }
}

//���������������
GameObject* BasicDefensiveTower::findTarget() {
    // ��ȡ�����еĹ����б�������������ͨ�� MonsterManager �����
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();

    // ���ڱ�������Ĺ���
    GameObject* nearestMonster = nullptr;

    // ���������б�
    for (GameObject* monster : monsters) {
        // �������������֮��ľ���
        float distance = towerlocation.distance(monster->getCurrentPosition());

        // �жϹ����Ƿ��������Ĺ�����Χ�ڡ�ֻҪ�ҵ�һ������Ҫ��Ĺ���ͽ���������
        if (distance <= tower_attack_range) {
            nearestMonster = monster;
            break;
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

void BasicDefensiveTower::setPhysicsBody(cocos2d::Sprite* Bullet, float value)
{
    //��������
    cocos2d::Size smallerSize(Bullet->getContentSize().width * 0.5f, Bullet->getContentSize().height * 0.5f);
    auto physicsBody = cocos2d::PhysicsBody::createBox(smallerSize, cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setPositionOffset(cocos2d::Vec2(smallerSize.width * 0.5f, smallerSize.height * 0.5f));//ƫ����
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x05);    // 0101
    physicsBody->setContactTestBitmask(0x09); // 1001
    Bullet->setTag(value);
    Bullet->setPhysicsBody(physicsBody);

}