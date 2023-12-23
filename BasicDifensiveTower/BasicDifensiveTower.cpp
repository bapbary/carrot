#include "BasicDifensiveTower.h"

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

//�ж�Ŀ�������ʧ������������



//�����������ж���
void BasicDefensiveTower::tower_targetupdate() {
    // �����ǰû��Ŀ�����Ŀ�곬�����з�Χ������ѡ��Ŀ��
    if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    //Ŀ��ѡ�����֮����й�������
    tower_attack();
}

//���������������
cocos2d::Sprite* BasicDefensiveTower::findTarget() {
    //�ڹ���ͼ������������������Ǹ�
    //��returnһ���������return nullptr
    return tower;
}

//��������
void BasicDefensiveTower::tower_attack() {
    //���ι���Ŀ������һ�������������������������
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
    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* lightingbullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //���ӵ�Ҳ���뵱ǰ������
    this->addChild(lightingbullet);
    //�����ӵ����鱾�����ں����ӵ�������Ч����
    return lightingbullet;
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
    if (tower_level == 1) {
        tower_level++;
        //һϵ����ֵ����

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        //һϵ����ֵ����

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_big.png");
    }
}