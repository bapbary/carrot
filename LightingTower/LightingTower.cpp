#include "LightingTower.h"
#include "SimpleAudioEngine.h"

//构造函数：炮塔参数的初始化并显示
LightingTower::LightingTower(const cocos2d::Vec2& touchLocation) {
    tower = cocos2d::Sprite::create("lightingTowerSmall.png");
    towerLocation = touchLocation;
    categoryCode = 2;
    towerLevel = 1;
    //初始化炮塔的其他数值
    towerAttackNumber = 1;
    towerAttackRange = 110;
    towerAttackPower = 50;
    towerAttackSpeed = 0.1;

    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towerName = "LightingTower_" + std::to_string(count);
    count++;

    //放置炮塔并显示
    tower->setPosition(touchLocation);
    //设置炮塔大小
    tower->setScale(1);
    spriteShow(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入

    //建立炮塔基座精灵
    base = cocos2d::Sprite::create("lightingTowerBase.png");
    //放置炮塔基座
    base->setPosition(touchLocation);
    //设置炮塔基座
    base->setScale(1);
    spriteShow(base);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔攻击
void LightingTower::towerAttack(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔等级创建对应大小的子弹
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletSmall.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletMiddle.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("lightingTowerBulletBig.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET3);
    }

    //放置粒子并设置大小
    Bullet->setPosition(towerLocation);
    Bullet->setScale(2);

    //将子弹放入当前场景中
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // 发射粒子并产生飞行特效
    towerBulletShoot(Bullet, targetlocation);
}

//炮塔发射粒子并产生飞行特效
void LightingTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
    //【使子弹对准攻击方向】
    // 计算炮塔指向怪物的方向向量
    cocos2d::Vec2 direction = targetLocation - towerLocation;
    //计算子弹初始朝向的角度（实际得到的是弧度）
    float angle = atan2(direction.y, direction.x);
    //将弧度转换为角度
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    //旋转子弹
    bullet->setRotation(-angleInDegrees);

    //播放音效
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("leafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //【让子弹飞】
    //建立飞行动作
    auto moveTo = cocos2d::MoveTo::create(0.4, targetLocation);
    //进行速度调整
    auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
    // 创建飞行动画序列
    auto sequence = cocos2d::Sequence::create(
        easeOut,
        // 创建一个回调动作，在飞行动作完成后执行
        cocos2d::CallFunc::create([=]() {
            //移除精灵
            bullet->removeFromParent();
            }),
        nullptr
    );
    // 执行飞行动画序列
    bullet->runAction(sequence);
}

//炮塔升级
void LightingTower::towerUpgrade() {
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 130;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("lightingTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 150;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("lightingTowerBig.png");
    }
}