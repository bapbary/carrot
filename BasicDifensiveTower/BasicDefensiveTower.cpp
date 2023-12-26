#include "BasicDefensiveTower.h"
#include "MonsterManager.h"

//获取炮塔精灵本身
cocos2d::Sprite* BasicDefensiveTower::getTowerSprite() {
    return tower;
}

//获取炮塔名字
std::string BasicDefensiveTower::getTowerName() {
    return towername;
}

//获取炮塔位置坐标
cocos2d::Vec2 BasicDefensiveTower::getTowerLocation() {
    return towerlocation;
}

//获取炮塔等级
int BasicDefensiveTower::getTowerLevel() {
    return tower_level;
}

//图标的显示
void BasicDefensiveTower::sprite_show(cocos2d::Sprite* sprite) {
    tower->setVisible(true);
}

//图标的隐藏
void BasicDefensiveTower::sprite_hide(cocos2d::Sprite* sprite) {
    tower->setVisible(false);
}

//炮塔更新索敌对象
void BasicDefensiveTower::tower_targetupdate(float dt) {

    CCLOG("HereInUpdateTarget!!!");

    // 如果当前没有目标或者目标超出索敌范围，重新选择目标
    if (currenttarget == nullptr || (currenttarget->objectPosition - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    if (currenttarget != nullptr) {
        //目标选择完成之后进行攻击操作
        tower_spin(currenttarget->objectPosition);
        tower_attack(currenttarget->objectPosition);
    }
}

//炮塔最近距离索敌
GameObject* BasicDefensiveTower::findTarget() {
    // 获取场景中的怪物管理器（怪物是通过 MonsterManager 管理的）
    std::vector<GameObject*> monsters = MonsterManager::getInstance()->getMonsters();

    // 初始化最小距离为一个足够大的值
    float minDistance = std::numeric_limits<float>::max();

    // 用于保存最近的怪物
    GameObject* nearestMonster = nullptr;

    // 遍历怪物列表
    for (GameObject* monster : monsters) {
        // 计算怪物与炮塔之间的距离
        float distance = towerlocation.distance(monster->objectPosition);

        // 判断怪物是否在炮塔的攻击范围内
        if (distance <= tower_attack_range && distance < minDistance) {
            // 更新最小距离和最近的怪物
            minDistance = distance;
            nearestMonster = monster;
        }
    }
    return nearestMonster;
}

//炮塔攻击
void BasicDefensiveTower::tower_attack(const cocos2d::Vec2& targetlocation) {
    // 检查是否有有效目标
    //if (currenttarget != nullptr) {
    //    // 创建攻击粒子
    //    cocos2d::Sprite* bullet;

    //    // 根据炮塔类型和等级创建对应大小的子弹
    //    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //    //将子弹也放入当前场景中
    //    this->addChild(FireBullet);

    //    bullet = FireBullet;

    //    // 发射粒子并产生飞行特效
    //    tower_bullet_shoot(bullet, targetlocation);

    //    // 检查目标是否死亡
    //    //if (1) {//怪物死亡标志
    //    //    // 目标死亡，重置当前目标
    //    //    currenttarget = nullptr;
    //    //}
    //}

    // 根据炮塔类型和等级创建对应大小的子弹
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    
    //放置粒子
    FireBullet->setPosition(tower->getPosition());
    FireBullet->setScale(1);

    //将粒子也放入当前场景中
    this->addChild(FireBullet, 3);

    // 发射粒子并产生飞行特效
    tower_bullet_shoot(FireBullet, targetlocation);

}

//炮塔转动（参数为当前攻击目标的所处的位置）
void BasicDefensiveTower::tower_spin(const cocos2d::Vec2& targetlocation) {
    //计算目标向量（目标->炮塔起点）
    cocos2d::Vec2 direction = targetlocation - towerlocation;
    //cocos2d::Vec2 direction = cocos2d::Vec2(1,1) - towerlocation;
    // 计算旋转的角度（实际得到的是弧度）
    float angle = atan2(direction.y, direction.x);
    // 将弧度转换为角度
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    // 创建旋转动作
    auto rotateAction = cocos2d::RotateBy::create(0.3, angleInDegrees);
    // 执行旋转动作
    tower->runAction(rotateAction);
}

//炮塔产生攻击粒子
cocos2d::Sprite* BasicDefensiveTower::createBullet() {
    // 根据炮塔类型和等级创建对应大小的子弹
    cocos2d::Sprite* FireBullet = cocos2d::Sprite::create("FireTower_bullet_small.png");
    //将子弹也放入当前场景中
    this->addChild(FireBullet);
    //返回子弹精灵本身，用于后续子弹飞行特效制作
    return FireBullet;
}

//炮塔发射粒子并产生飞行特效
void BasicDefensiveTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //建立飞行动作
    auto moveTo = cocos2d::MoveTo::create(2, targetlocation);
    //进行速度调整
    auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
    // 创建飞行动画序列
    auto sequence = cocos2d::Sequence::create(
        easeOut,
        // 创建一个回调动作，在飞行动作完成后执行
        cocos2d::CallFunc::create([=]() {
            //移除精灵
            bullet->removeFromParent();
            //到达目标位置后需产生击中特效
            tower_hit_target(targetlocation);
            }),
        nullptr
    );
    // 执行飞行动画序列
    bullet->runAction(sequence);
}

//炮塔粒子撞击目标产生短暂打击特效
void BasicDefensiveTower::tower_hit_target(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔类型建立相应打击特效
    cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
    //将打击特效放入场景中
    this->addChild(hit);
    hit->setPosition(targetlocation);
    sprite_show(hit);
    //建立sequence动作序列：先维持半秒后自动销毁
    auto delay = cocos2d::DelayTime::create(1.0f); // 延时1秒
    auto remove = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
    //执行sequence动作序列
    hit->runAction(sequence);
}

//炮塔升级
void BasicDefensiveTower::towerUpgrade() {
    //虚函数待覆盖
}