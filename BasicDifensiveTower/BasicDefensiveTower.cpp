#include "BasicDefensiveTower.h"
#include "MonsterManager.h"

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

    CCLOG("HereInUpdateTarget!!!");

    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    if (currenttarget == nullptr || (currenttarget->objectPosition - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    if (currenttarget != nullptr) {
        //Ŀ��ѡ�����֮����й�������
        tower_spin(currenttarget->objectPosition);
        tower_attack(currenttarget->objectPosition);
    }
}

//���������������
GameObject* BasicDefensiveTower::findTarget() {
    // ��ȡ�����еĹ����������������ͨ�� MonsterManager ����ģ�
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();

    // ��ʼ����С����Ϊһ���㹻���ֵ
    float minDistance = std::numeric_limits<float>::max();

    // ���ڱ�������Ĺ���
    GameObject* nearestMonster = nullptr;

    // ���������б�
    for (GameObject* monster : monsters) {
        // �������������֮��ľ���
        float distance = towerlocation.distance(monster->objectPosition);

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
    // ����Ƿ�����ЧĿ��
    //if (currenttarget != nullptr) {
    //    // ������������
    //    cocos2d::Sprite* bullet;

    //    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    //    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //    //���ӵ�Ҳ���뵱ǰ������
    //    this->addChild(FireBullet);

    //    bullet = FireBullet;

    //    // �������Ӳ�����������Ч
    //    tower_bullet_shoot(bullet, targetlocation);

    //    // ���Ŀ���Ƿ�����
    //    //if (1) {//����������־
    //    //    // Ŀ�����������õ�ǰĿ��
    //    //    currenttarget = nullptr;
    //    //}
    //}

    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    
    //��������
    FireBullet->setPosition(tower->getPosition());
    FireBullet->setScale(1);

    //������Ҳ���뵱ǰ������
    this->addChild(FireBullet, 3);

    // �������Ӳ�����������Ч
    tower_bullet_shoot(FireBullet, targetlocation);

}

//����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
void BasicDefensiveTower::tower_spin(const cocos2d::Vec2& targetlocation) {
    //����Ŀ��������Ŀ��->������㣩
    cocos2d::Vec2 direction = targetlocation - towerlocation;
    //cocos2d::Vec2 direction = cocos2d::Vec2(1,1) - towerlocation;
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
    //�������ж���
    auto moveTo = cocos2d::MoveTo::create(2, targetlocation);
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
    this->addChild(hit);
    hit->setPosition(targetlocation);
    sprite_show(hit);
    //����sequence�������У���ά�ְ�����Զ�����
    auto delay = cocos2d::DelayTime::create(1.0f); // ��ʱ1��
    auto remove = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
    //ִ��sequence��������
    hit->runAction(sequence);
}

//��������
void BasicDefensiveTower::towerUpgrade() {
    //�麯��������
}