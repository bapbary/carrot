#include "LightingTower.h"
#include "SimpleAudioEngine.h"

//���캯�������������ĳ�ʼ������ʾ
LightingTower::LightingTower(const cocos2d::Vec2& touchLocation) {
    tower = cocos2d::Sprite::create("lightingTowerSmall.png");
    towerLocation = touchLocation;
    categoryCode = 2;
    towerLevel = 1;
    //��ʼ��������������ֵ
    towerAttackNumber = 1;
    towerAttackRange = 110;
    towerAttackPower = 50;
    towerAttackSpeed = 0.1;

    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towerName = "LightingTower_" + std::to_string(count);
    count++;

    //������������ʾ
    tower->setPosition(touchLocation);
    //����������С
    tower->setScale(1);
    spriteShow(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���

    //����������������
    base = cocos2d::Sprite::create("lightingTowerBase.png");
    //������������
    base->setPosition(touchLocation);
    //������������
    base->setScale(1);
    spriteShow(base);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//��������
void LightingTower::towerAttack(const cocos2d::Vec2& targetlocation) {
    // ���������ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletSmall.png");
        //��������
        setPhysicsBody(Bullet, LIGHTINGBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletMiddle.png");
        //��������
        setPhysicsBody(Bullet, LIGHTINGBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletBig.png");
        //��������
        setPhysicsBody(Bullet, LIGHTINGBULLET3);
    }

    //�������Ӳ����ô�С
    Bullet->setPosition(towerLocation);
    Bullet->setScale(2);

    //���ӵ����뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // �������Ӳ�����������Ч
    towerBulletShoot(Bullet, targetlocation);
}

//�����������Ӳ�����������Ч
void LightingTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
    //��ʹ�ӵ���׼��������
    // ��������ָ�����ķ�������
    cocos2d::Vec2 direction = targetLocation - towerLocation;
    //�����ӵ���ʼ����ĽǶȣ�ʵ�ʵõ����ǻ��ȣ�
    float angle = atan2(direction.y, direction.x);
    //������ת��Ϊ�Ƕ�
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    //��ת�ӵ�
    bullet->setRotation(-angleInDegrees);

    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("leafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //�����ӵ��ɡ�
    //�������ж���
    auto moveTo = cocos2d::MoveTo::create(0.4, targetLocation);
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
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 130;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("lightingTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 150;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("lightingTowerBig.png");
    }
}