#include "LeafTower.h"
#include "SimpleAudioEngine.h"

//构造函数：炮塔参数的初始化并显示
LeafTower::LeafTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LeafTower_small.png");
    towerLocation = touchlocation;
    categoryCode = 3;
    towerLevel = 1;
    //初始化炮塔的其他数值
    towerAttackNumber = 1;
    towerAttackRange = 115;
    towerAttackPower = 50;
    towerAttackSpeed = 0.1;

    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towerName = "LeafTower_" + std::to_string(count);
    count++;

    //放置炮塔并显示
    tower->setPosition(touchlocation);
    //设置炮塔大小
    tower->setScale(1);
    spriteShow(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入

    //建立炮塔基座精灵
    base = cocos2d::Sprite::create("LeafTower_Base_middle.png");
    base->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    //放置炮塔基座
    base->setPosition(touchlocation);
    //设置炮塔基座
    base->setScale(1);
    spriteShow(base);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔攻击
void LeafTower::towerAttack(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔等级创建对应大小的子弹
    cocos2d::Sprite* Bullet;
    if (towerLevel == 1) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_small.png");
        //物理引擎
        setPhysicsBody(Bullet, LEAFBULLET1);
    }
    else if (towerLevel == 2) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_middle.png");
        //物理引擎
        setPhysicsBody(Bullet, LEAFBULLET2);
    }
    else if (towerLevel == 3) {
        Bullet = cocos2d::Sprite::create("LeafTower_bullet_big.png");
        //物理引擎
        setPhysicsBody(Bullet, LEAFBULLET3);
    }

    //放置粒子并设置大小
    Bullet->setPosition(towerLocation);
    Bullet->setScale(1);

    //将子弹也放入当前场景中
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // 发射粒子并产生飞行特效
    towerBulletShoot(Bullet, targetlocation);
}

//炮塔发射粒子并产生飞行特效
void LeafTower::towerBulletShoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetLocation) {
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
    // 创建飞行动作
    direction.normalize();//（向量归一化）
    auto moveBy = cocos2d::MoveBy::create(5.0, direction * 1000); // 假设速度为每秒1000个像素
    // 创建旋转动作，每秒旋转360度持续五秒
    auto rotateBy = cocos2d::RotateBy::create(5, 1800);
    // 建立Spawn动作序列使子弹同时进行飞行和旋转
    auto spawn = cocos2d::Spawn::create(
        moveBy,
        rotateBy,
        nullptr
    );
    // 创建飞行动画序列
    auto sequence = cocos2d::Sequence::create(
        spawn,
        // 创建一个回调动作，在飞行完成后执行
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
void LeafTower::towerUpgrade() {
    if (towerLevel == 1) {
        towerLevel++;
        towerAttackRange = 125;
        towerAttackPower = 70;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("leafTowerMiddle.png");
    }
    else if (towerLevel == 2) {
        towerLevel++;
        towerAttackRange = 140;
        towerAttackPower = 100;
        towerAttackSpeed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("leafTowerBig.png");
    }
}