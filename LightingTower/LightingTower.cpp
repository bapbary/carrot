#include "LightingTower.h"
//���캯�������������ĳ�ʼ������ʾ
LightingTower::LightingTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LightingTower_small.png");
    towerlocation = touchlocation;
    category_code = 2;
    tower_level = 1;
    //��ʼ��������������ֵ
    tower_attack_number = 1;
    tower_attack_range = 300;
    tower_attack_power = 50;
    tower_attack_speed = 0.1;
    tower_sustained_attack_time;

    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towername = "LightingTower_" + std::to_string(count);
    count++;

    //������������ʾ
    tower->setPosition(touchlocation);
    //����������С
    tower->setScale(1);
    sprite_show(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//��������
void LightingTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    // ���������ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* Bullet;
    if (tower_level == 1) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    }
    else if (tower_level == 2) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_middle.png");
    }
    else if (tower_level == 3) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_big.png");
    }

    //���ӵ�����������Ա�־
    auto physicsBody = cocos2d::PhysicsBody::createBox(Bullet->getContentSize(), cocos2d::PhysicsMaterial::PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x01);    // 0001
    physicsBody->setContactTestBitmask(0x04); // 0100
    Bullet->setTag(LIGHTINGBULLET);
    Bullet->setPhysicsBody(physicsBody);

    //�������Ӳ����ô�С
    Bullet->setPosition(towerlocation);
    Bullet->setScale(2);

    //���ӵ����뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // �������Ӳ�����������Ч
    tower_bullet_shoot(Bullet, targetlocation);
}

//�����������Ӳ�����������Ч
void LightingTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //��ʹ�ӵ���׼��������
    // ��������ָ�����ķ�������
    cocos2d::Vec2 direction = targetlocation - towerlocation;
    //�����ӵ���ʼ����ĽǶȣ�ʵ�ʵõ����ǻ��ȣ�
    float angle = atan2(direction.y, direction.x);
    //������ת��Ϊ�Ƕ�
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    //��ת�ӵ�
    bullet->setRotation(-angleInDegrees);
    //�����ӵ��ɡ�
    //�������ж���
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
            }),
        nullptr
    );
    // ִ�з��ж�������
    bullet->runAction(sequence);
}

//��������
void LightingTower::towerUpgrade() {
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 350;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 400;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_big.png");
    }
}