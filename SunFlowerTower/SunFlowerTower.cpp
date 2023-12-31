#include "SunFLowerTower.h"
#include "SimpleAudioEngine.h"

//���캯�������������ĳ�ʼ������ʾ
SunFlowerTower::SunFlowerTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("SunFlowerTower_small.png");
    towerlocation = touchlocation;
    category_code = 1;
    tower_level = 1;
    //��ʼ��������������ֵ
    tower_attack_number = 1;
    tower_attack_range = 120;
    tower_attack_power = 50;
    tower_attack_speed = 1;
    tower_sustained_attack_time;
    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towername = "SunFlowerTower_" + std::to_string(count);
    count++;
    //������������ʾ
    tower->setPosition(touchlocation);
    //����������С
    tower->setScale(1);
    sprite_show(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���

    //����������������
    base = cocos2d::Sprite::create("SunFlowerTower_Base.png");
    //������������
    base->setPosition(touchlocation);
    //������������
    base->setScale(1);
    sprite_show(base);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//��������
void SunFlowerTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    // ���������ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* Bullet;
    if (tower_level == 1) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_small.png");
        //��������
        setPhysicsBody(Bullet, SUNFLOWERBULLET1);
    }
    else if (tower_level == 2) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_middle.png");
        //��������
        setPhysicsBody(Bullet, SUNFLOWERBULLET2);
    }
    else if (tower_level == 3) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_big.png");
        //��������
        setPhysicsBody(Bullet, SUNFLOWERBULLET3);
    }

    //�������Ӳ����ô�С
    Bullet->setPosition(towerlocation);
    Bullet->setScale(0.01);

    //���ӵ�Ҳ���뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // �������Ӳ�����������Ч
    tower_bullet_shoot(Bullet, targetlocation);
}

//�����������Ӳ�����������Ч
void SunFlowerTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("LeafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //��������
    float targetScaleFactor = 1.5f;   
    //�����Ŵ���
    auto scaleUp = ScaleTo::create(1.0, targetScaleFactor);
    //����һ�����ж���������˳��ִ����������
    auto sequence = Sequence::create(
        scaleUp, 
        // ����һ���ص��������ڷ��ж�����ɺ�ִ��
        cocos2d::CallFunc::create([=]() {
            //�Ƴ�����
            bullet->removeFromParent();
            }),
        nullptr
    );
    // ִ�ж�������
    bullet->runAction(sequence);
}

//��������
void SunFlowerTower::towerUpgrade() {
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 140;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("SunFlowerTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 160;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("SunFlowerTower_big.png");
    }
}
