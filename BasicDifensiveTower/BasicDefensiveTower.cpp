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
        if (currentTower->currenttarget == nullptr || (currentTower->currenttarget->getCurrentPosition() - currentTower->getPosition()).length() > currentTower->tower_attack_range) {
            currentTower->currenttarget = currentTower->findTarget();
        }
        if (currentTower->currenttarget != nullptr) {
            //Ŀ��ѡ�����֮����й�������
            currentTower->tower_spin(currentTower->currenttarget->objectPosition);
            currentTower->tower_attack(currentTower->currenttarget->objectPosition);
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

    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //�������Ӳ���ʾ
    FireBullet->setPosition(towerlocation);
    FireBullet->setScale(1);
    //���ӵ�Ҳ���뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();

    currentScene->addChild(FireBullet, 2);

    const cocos2d::Vec2& vec= FireBullet->getPosition();

    // �������Ӳ�����������Ч
    tower_bullet_shoot(FireBullet, targetlocation);
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
    auto rotateAction = cocos2d::RotateBy::create(0.3, angleInDegrees);
    // ִ����ת����
    tower->runAction(rotateAction);
}

//����������������
cocos2d::Sprite* BasicDefensiveTower::createBullet() {
    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("FireTower_bullet_small.png");
    //���ӵ�Ҳ���뵱ǰ������
    this->addChild(FireBullet);
    //�����ӵ����鱾�����ں����ӵ�������Ч����
    return FireBullet;
}

//�����������Ӳ�����������Ч
void BasicDefensiveTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //Ȼ�������ж���
    auto moveTo = cocos2d::MoveTo::create(0.4, targetlocation);
    //�����ٶȵ���
    auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
    // �������ж�������
    auto sequence = cocos2d::Sequence::create(
        easeOut,
        // ����һ���ص��������ڷ��ж�����ɺ�ִ��
        cocos2d::CallFunc::create([=]() {
            //�Ƴ�����
            bullet->removeFromParent();
            //����Ŀ��λ�ú������������Ч
            tower_hit_target(targetlocation);
            }),
        nullptr
    );
    // ִ�з��ж�������
    bullet->runAction(sequence);
}

//��������ײ��Ŀ��������ݴ����Ч
void BasicDefensiveTower::tower_hit_target(const cocos2d::Vec2& targetlocation) {
    // �����������ͽ�����Ӧ�����Ч
    cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
    //�������Ч���볡����
    hit->setPosition(targetlocation);

    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();

    currentScene->addChild(hit,2);
    sprite_show(hit);
    //����sequence�������У���ά�ְ�����Զ�����
    auto delay = cocos2d::DelayTime::create(0.1); // ��ʱ1��
    auto remove = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
    //ִ��sequence��������
    hit->runAction(sequence);
}

//�ж������Ƿ���Խ�������������
//�����Ҳ�֪��pzx��������������������

//��������
void BasicDefensiveTower::towerUpgrade() {
    //�麯��������
}