#include "BasicDefensiveTower.h"

//��ȡ�������鱾��
cocos2d::Sprite* BasicDefensiveTower::getTowerSprite(){
    return tower;
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
    if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    if (currenttarget != nullptr) {
        //Ŀ��ѡ�����֮����й�������
        tower_spin();
        tower_attack();
    }
}

//���������������
cocos2d::Sprite* BasicDefensiveTower::findTarget() {
    // ��ȡ�����еĹ����б�������������ͨ�� MonsterManager �����
    Vector<Monster*> monsters = MonsterManager::getInstance()->getMonsters();

    // ��ʼ����С����Ϊһ���㹻���ֵ
    float minDistance = std::numeric_limits<float>::max();

    // ���ڱ�������Ĺ���
    Monster* nearestMonster = nullptr;

    // ���������б�
    for (Monster* monster : monsters) {
        // �������������֮��ľ���
        float distance = towerlocation.distance(monster->getPosition());

        // �жϹ����Ƿ��������Ĺ�����Χ��
        if (distance <= tower_attack_range && distance < minDistance) {
            // ������С���������Ĺ���
            minDistance = distance;
            nearestMonster = monster;
        }
    }

    return nullptr;
}

//��������
void BasicDefensiveTower::tower_attack() {
    // ����Ƿ�����ЧĿ��
    if (currenttarget != nullptr) {
        // ������������
        cocos2d::Sprite* bullet = createBullet();

        // �������Ӳ�����������Ч
        tower_bullet_shoot(bullet, currenttarget->getPosition());

        // ���Ŀ���Ƿ�����
        if (1) {//����������־
            // Ŀ�����������õ�ǰĿ��
            currenttarget = nullptr;
        }
    }
}

//����ת��������Ϊ��ǰ����Ŀ���������λ�ã�
void BasicDefensiveTower::tower_spin(const cocos2d::Vec2& targetlocation) {
    //����Ŀ��������Ŀ��->������㣩
    cocos2d::Vec2 direction = towerlocation - targetlocation;
    // ������ת�ĽǶȣ�ʵ�ʵõ����ǻ��ȣ�
    float angle = atan2(direction.y, direction.x);
    // ������ת��Ϊ�Ƕ�
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    // ������ת����
    auto rotateAction = cocos2d::RotateBy::create(0.2f, angleInDegrees);
    // ִ����ת����
    tower->runAction(rotateAction);
}

//����������������
cocos2d::Sprite* BasicDefensiveTower::createBullet() {
    //�麯��������
}

//�����������Ӳ�����������Ч
void BasicDefensiveTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //�������Ӳ���ʾ
    bullet->setPosition(towerlocation);
    bullet->setScale(2);
    sprite_show(bullet);
    //Ȼ�������ж���
    auto moveTo = cocos2d::MoveTo::create(2.0f, targetlocation);
    //�����ٶȵ���
    auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
    //ִ�з��в���
    bullet->runAction(moveTo);
    //����Ŀ��λ�ú������������Ч
    tower_hit_target(targetlocation);
    //ɾ���ӵ������������У�
    this->removeChild(bullet);
}

//��������ײ��Ŀ��������ݴ����Ч
void BasicDefensiveTower::tower_hit_target(const cocos2d::Vec2& targetlocation) {
    // �����������ͽ�����Ӧ�����Ч
    cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
    //�������Ч���볡����
    this->addChild(hit);
    tower->setPosition(targetlocation);
    sprite_show(hit);
    //����sequence�������У���ά�ְ�����Զ�����
    auto delay = cocos2d::DelayTime::create(1.0f); // ��ʱ1��
    auto remove = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
    //ִ��sequence��������
    hit->runAction(sequence);
}

//�ж������Ƿ���Խ�������������
//�����Ҳ�֪��pzx��������������������

//��������
void BasicDefensiveTower::tower_upgrade() {
   //�麯��������
}