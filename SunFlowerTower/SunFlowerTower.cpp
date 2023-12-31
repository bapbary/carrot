#include "SunFLowerTower.h"
#include "SimpleAudioEngine.h"

//构造函数：炮塔参数的初始化并显示
SunFlowerTower::SunFlowerTower(const cocos2d::Vec2& touchLocation) {
    tower = cocos2d::Sprite::create("sunFlowerTowerSmall.png");
    towerLocation = touchLocation;
    categoryCode = 1;
    towerLevel = 1;
    //初始化炮塔的其他数值
    towerAttackNumber = 1;
    towerAttackRange = 120;
    towerAttackPower = 50;
    towerAttackSpeed = 1;
    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towerName = "SunFlowerTower_" + std::to_string(count);
    count++;
    //放置炮塔并显示
    tower->setPosition(touchLocation);
    //设置炮塔大小
    tower->setScale(1);
    spriteShow(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入

    //建立炮塔基座精灵
    base = cocos2d::Sprite::create("sunFlowerTowerBase.png");
    //放置炮塔基座
    base->setPosition(touchLocation);
    //设置炮塔基座
    base->setScale(1);
    spriteShow(base);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔攻击
void SunFlowerTower::towerAttack(const cocos2d::Vec2& targetLocation) {
    // 根据炮塔等级创建对应大小的子弹
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletSmall.png");
        //物理引擎
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletMiddle.png");
        //物理引擎
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("sunFlowerTowerBulletBig.png");
        //物理引擎
        setSunFlowerPhysicsBody(Bullet, SUNFLOWERBULLET3);
    }

    //放置粒子并设置大小
    Bullet->setPosition(towerLocation);
    Bullet->setScale(0.01);

    //将子弹也放入当前场景中
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // 发射粒子并产生飞行特效
    towerBulletShoot(Bullet, targetLocation);
}

//炮塔发射粒子并产生飞行特效
void SunFlowerTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
    //播放音效
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("leafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //缩放因子
    float targetScaleFactor = 1.05f;
    //创建放大动作
    auto scaleUp = ScaleTo::create(1.0, targetScaleFactor);
    //创建一个序列动作，按照顺序执行上述动作
    auto sequence = Sequence::create(
        scaleUp,
        // 创建一个回调动作，在飞行动作完成后执行
        cocos2d::CallFunc::create([=]() {
            //移除精灵
            bullet->removeFromParent();
            }),
        nullptr
    );
    // 执行动作序列
    bullet->runAction(sequence);
}

//炮塔升级
void SunFlowerTower::towerUpgrade() {
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 140;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("sunFlowerTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 160;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("sunFlowerTowerBig.png");
    }
}