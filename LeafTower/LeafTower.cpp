#include "LeafTower.h"
#include "SimpleAudioEngine.h"

//���캯�������������ĳ�ʼ������ʾ
LeafTower::LeafTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LeafTower_small.png");
    towerLocation = touchlocation;
    categoryCode = 3;
    towerLevel = 1;
    //��ʼ��������������ֵ
    towerAttackNumber = 1;
    towerAttackRange = 115;
    towerAttackPower = 50;
    towerAttackSpeed = 0.1;

    // ʹ��ȫ�ּ�������ΪΨһID �Ա������ʶ����
    towerName = "LeafTower_" + std::to_string(count);
    count++;

    //������������ʾ
    tower->setPosition(touchlocation);
    //����������С
    tower->setScale(1);
    spriteShow(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���

    //����������������
    base = cocos2d::Sprite::create("LeafTower_Base_middle.png");
    base->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    //������������
    base->setPosition(touchlocation);
    //������������
    base->setScale(1);
    spriteShow(base);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}

//��������
void LeafTower::towerAttack(const cocos2d::Vec2& targetlocation) {
    // ���������ȼ�������Ӧ��С���ӵ�
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_small.png");
        //��������
        setPhysicsBody(Bullet, LEAFBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_middle.png");
        //��������
        setPhysicsBody(Bullet, LEAFBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_big.png");
        //��������
        setPhysicsBody(Bullet, LEAFBULLET3);
    }

    //�������Ӳ����ô�С
    Bullet->setPosition(towerLocation);
    Bullet->setScale(1);

    //���ӵ�Ҳ���뵱ǰ������
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // �������Ӳ�����������Ч
    towerBulletShoot(Bullet, targetlocation);
}

//�����������Ӳ�����������Ч
void LeafTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
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
    // �������ж���
    direction.normalize();//��������һ����
    auto moveBy = cocos2d::MoveBy::create(5.0, direction * 1000); // �����ٶ�Ϊÿ��1000������
    // ������ת������ÿ����ת360�ȳ�������
    auto rotateBy = cocos2d::RotateBy::create(5, 1800);
    // ����Spawn��������ʹ�ӵ�ͬʱ���з��к���ת
    auto spawn = cocos2d::Spawn::create(
        moveBy,
        rotateBy,
        nullptr
    );
    // �������ж�������
    auto sequence = cocos2d::Sequence::create(
        spawn,
        // ����һ���ص��������ڷ�����ɺ�ִ��
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
void LeafTower::towerUpgrade() {
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 125;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("leafTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 140;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // ʹ����ͼ���滻��ͼ��
        tower->setTexture("leafTowerBig.png");
    }
}