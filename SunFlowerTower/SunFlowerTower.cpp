#include "SunFLowerTower.h"
#include "SimpleAudioEngine.h"

//构造函数：炮塔参数的初始化并显示
SunFlowerTower::SunFlowerTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("SunFlowerTower_small.png");
    towerlocation = touchlocation;
    category_code = 1;
    tower_level = 1;
    //初始化炮塔的其他数值
    tower_attack_number = 1;
    tower_attack_range = 120;
    tower_attack_power = 50;
    tower_attack_speed = 1;
    tower_sustained_attack_time;
    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towername = "SunFlowerTower_" + std::to_string(count);
    count++;
    //放置炮塔并显示
    tower->setPosition(touchlocation);
    //设置炮塔大小
    tower->setScale(1);
    sprite_show(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入

    //建立炮塔基座精灵
    base = cocos2d::Sprite::create("SunFlowerTower_Base.png");
    //放置炮塔基座
    base->setPosition(touchlocation);
    //设置炮塔基座
    base->setScale(1);
    sprite_show(base);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔攻击
void SunFlowerTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔等级创建对应大小的子弹
    cocos2d::Sprite* Bullet;
    if (tower_level == 1) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_small.png");
        //物理引擎
        setPhysicsBody(Bullet, SUNFLOWERBULLET1);
    }
    else if (tower_level == 2) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_middle.png");
        //物理引擎
        setPhysicsBody(Bullet, SUNFLOWERBULLET2);
    }
    else if (tower_level == 3) {
        Bullet = cocos2d::Sprite::create("SunFlowerTower_bullet_big.png");
        //物理引擎
        setPhysicsBody(Bullet, SUNFLOWERBULLET3);
    }

    //放置粒子并设置大小
    Bullet->setPosition(towerlocation);
    Bullet->setScale(0.01);

    //将子弹也放入当前场景中
    Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
    currentScene->addChild(Bullet, 2);

    // 发射粒子并产生飞行特效
    tower_bullet_shoot(Bullet, targetlocation);
}

//炮塔发射粒子并产生飞行特效
void SunFlowerTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //播放音效
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("LeafTowerAttackSound.MP3", false, 1.0f, 1.0f, 1.0f);

    //缩放因子
    float targetScaleFactor = 1.5f;   
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
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 140;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("SunFlowerTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 160;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("SunFlowerTower_big.png");
    }
}
