#include "LightingTower.h"
//构造函数：炮塔参数的初始化并显示
LightingTower::LightingTower(const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create("LightingTower_small.png");
    towerlocation = touchlocation;
    category_code = 1;
    tower_level = 1;
    //初始化炮塔的其他数值
    tower_attack_number = 1;
    tower_attack_range = 2;
    tower_attack_power = 50;
    tower_attack_speed = 0.1;
    tower_sustained_attack_time;

    // 使用全局计数器作为唯一ID 以便后续标识炮塔
    towerName = "LightingTower_" + std::to_string(count);
    count++;

    //放置炮塔并显示
    tower->setPosition(touchlocation);
    //设置炮塔大小
    tower->setScale(10);
    sprite_show(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}

//炮塔产生攻击粒子
cocos2d::Sprite* LightingTower::createBullet() {
    // 根据炮塔类型和等级创建对应大小的子弹
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //将子弹也放入当前场景中
    this->addChild(FireBullet);
    //返回子弹精灵本身，用于后续子弹飞行特效制作
    return FireBullet;
}

//炮塔升级
void LightingTower::tower_upgrade() {
    if (tower_level == 1) {
        tower_level++;
        tower_attack_range = 2.4;
        tower_attack_power = 70;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        tower_attack_range = 2.8;
        tower_attack_power = 100;
        tower_attack_speed = 0.1;

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_big.png");
    }
}