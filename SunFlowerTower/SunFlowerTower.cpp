#include "SunFLowerTower.h"
#include "SimpleAudioEngine.h"

//���캯�������������ĳ�ʼ������ʾ
SunFlowerTower::SunFlowerTower(const cocos2d::Vec2& touchLocation) {
    tower = cocos2d::Sprite::create("sunFlowerTowerSmall.png");
    towerLocation = touchLocation;
    categoryCode = 1;
    towerLevel = 1;
    //��ʼ��������������ֵ
    towerAttackNumber = 1;
    towerAttackRange = 120;
    towerAttackPower = 50;
    towerAttackSpeed = 1;
    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towerName = "SunFlowerTower_" + std::to_string(count);
    count++;
    //������������ʾ
    tower->setPosition(touchLocation);
    //����������С
    tower->setScale(1);
    spriteShow(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���

    //����������������
    base = cocos2d::Sprite::create("sunFlowerTowerBase.png");
    //������������
    base->setPosition(touchLocation);
    //������������
    base->setScale(1);
    spriteShow(base);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//��������
void SunFlowerTower::towerAttack(const cocos2d::Vec2& targetLocation) {
    // ���������ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletSmall.png");
        //��������
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletMiddle.png");
        //��������
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletBig.png");
        //��������
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET3);
    }

    //�������Ӳ����ô�С
    Bullet->setPosition(towerLocation);
    Bullet->setScale(0.01);

    //���ӵ�Ҳ���뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // �������Ӳ�����������Ч
    towerBulletShoot(Bullet, targetLocation);
}

//�����������Ӳ�����������Ч
void SunFlowerTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
    //������Ч
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("leafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //��������
    float targetScaleFactor = 1.05f;
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
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 140;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("sunFlowerTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 160;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("sunFlowerTowerBig.png");
    }
}