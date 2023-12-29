#include "LightingTower.h"
//构造函数：炮塔参数的初始化并显示
LightingTower::LightingTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LightingTower_small.png");
    towerlocation = touchlocation;
    category_code = 2;
    tower_level = 1;
    //初始化炮塔的其他数值
    tower_attack_number = 1;
    tower_attack_range = 300;
    tower_attack_power = 50;
    tower_attack_speed = 0.1;
    tower_sustained_attack_time;

    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towername = "LightingTower_" + std::to_string(count);
    count++;

    //放置炮塔并显示
    tower->setPosition(touchlocation);
    //设置炮塔大小
    tower->setScale(1);
    sprite_show(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入

    //建立炮塔基座精灵
    base = cocos2d::Sprite::create("LightingTower_Base.png");
    //放置炮塔基座
    base->setPosition(touchlocation);
    //设置炮塔基座
    base->setScale(1);
    sprite_show(base);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔攻击
void LightingTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔等级创建对应大小的子弹
    cocos2d::Sprite* Bullet;
    if (tower_level == 1) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET1);
    }
    else if (tower_level == 2) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_middle.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET2);
    }
    else if (tower_level == 3) {
        Bullet = cocos2d::Sprite::create("LightingTower_bullet_big.png");
        //物理引擎
        setPhysicsBody(Bullet, LIGHTINGBULLET3);
    }

    //放置粒子并设置大小
    Bullet->setPosition(towerlocation);
    Bullet->setScale(2);

    //将子弹放入当前场景中
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // 发射粒子并产生飞行特效
    tower_bullet_shoot(Bullet, targetlocation);
}

//炮塔发射粒子并产生飞行特效
void LightingTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //【使子弹对准攻击方向】
    // 计算炮塔指向怪物的方向向量
    cocos2d::Vec2 direction = targetlocation - towerlocation;
    //计算子弹初始朝向的角度（实际得到的是弧度）
    float angle = atan2(direction.y, direction.x);
    //将弧度转换为角度
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    //旋转子弹
    bullet->setRotation(-angleInDegrees);
    //【让子弹飞】
    //建立飞行动作
    auto moveTo = cocos2d::MoveTo::create(0.4, targetlocation);
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
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 350;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 400;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_big.png");
    }
}