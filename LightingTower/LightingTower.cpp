#include "LightingTower.h"
//���캯�������������ĳ�ʼ������ʾ
LightingTower::LightingTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LightingTower_small.png");
    towerlocation = touchlocation;
    category_code = 1;
    tower_level = 1;
    //��ʼ��������������ֵ
    tower_attack_number = 1;
    tower_attack_range = 2;
    tower_attack_power = 50;
    tower_attack_speed = 0.1;
    tower_sustained_attack_time;

    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towerName = "LightingTower_" + std::to_string(count);
    count++;

    //������������ʾ
    tower->setPosition(touchlocation);
    //����������С
    tower->setScale(10);
    sprite_show(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//����������������
cocos2d::Sprite* LightingTower::createBullet() {
    // �����������ͺ͵ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //���ӵ�Ҳ���뵱ǰ������
    this->addChild(FireBullet);
    //�����ӵ����鱾�����ں����ӵ�������Ч����
    return FireBullet;
}

//��������
void LightingTower::tower_upgrade() {
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 2.4;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 2.8;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("LightingTower_big.png");
    }
}