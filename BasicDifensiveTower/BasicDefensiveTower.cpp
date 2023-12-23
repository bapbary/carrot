#include "BasicDefensiveTower.h"

//获取炮塔精灵本身
cocos2d::Sprite* BasicDefensiveTower::getTowerSprite(){
    return tower;
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
    // 如果当前没有目标或者目标超出索敌范围，重新选择目标
    if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    if (currenttarget != nullptr) {
        //目标选择完成之后进行攻击操作
        tower_spin();
        tower_attack();
    }
}

//炮塔最近距离索敌
cocos2d::Sprite* BasicDefensiveTower::findTarget() {
    // 获取场景中的怪物列表，这里假设怪物是通过 MonsterManager 管理的
    Vector<Monster*> monsters = MonsterManager::getInstance()->getMonsters();

    // 初始化最小距离为一个足够大的值
    float minDistance = std::numeric_limits<float>::max();

    // 用于保存最近的怪物
    Monster* nearestMonster = nullptr;

    // 遍历怪物列表
    for (Monster* monster : monsters) {
        // 计算怪物与炮塔之间的距离
        float distance = towerlocation.distance(monster->getPosition());

        // 判断怪物是否在炮塔的攻击范围内
        if (distance <= tower_attack_range && distance < minDistance) {
            // 更新最小距离和最近的怪物
            minDistance = distance;
            nearestMonster = monster;
        }
    }

    return nullptr;
}

//炮塔攻击
void BasicDefensiveTower::tower_attack() {
    // 检查是否有有效目标
    if (currenttarget != nullptr) {
        // 创建攻击粒子
        cocos2d::Sprite* bullet = createBullet();

        // 发射粒子并产生飞行特效
        tower_bullet_shoot(bullet, currenttarget->getPosition());

        // 检查目标是否死亡
        if (1) {//怪物死亡标志
            // 目标死亡，重置当前目标
            currenttarget = nullptr;
        }
    }
}

//炮塔转动（参数为当前攻击目标的所处的位置）
void BasicDefensiveTower::tower_spin(const cocos2d::Vec2& targetlocation) {
    //计算目标向量（目标->炮塔起点）
    cocos2d::Vec2 direction = towerlocation - targetlocation;
    // 计算旋转的角度（实际得到的是弧度）
    float angle = atan2(direction.y, direction.x);
    // 将弧度转换为角度
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);
    // 创建旋转动作
    auto rotateAction = cocos2d::RotateBy::create(0.2f, angleInDegrees);
    // 执行旋转动作
    tower->runAction(rotateAction);
}

//炮塔产生攻击粒子
cocos2d::Sprite* BasicDefensiveTower::createBullet() {
    //虚函数待覆盖
}

//炮塔发射粒子并产生飞行特效
void BasicDefensiveTower::tower_bullet_shoot(cocos2d::Sprite* bullet, const cocos2d::Vec2& targetlocation) {
    //放置粒子并显示
    bullet->setPosition(towerlocation);
    bullet->setScale(2);
    sprite_show(bullet);
    //然后建立飞行动作
    auto moveTo = cocos2d::MoveTo::create(2.0f, targetlocation);
    //进行速度调整
    auto easeOut = cocos2d::EaseExponentialOut::create(moveTo);
    //执行飞行操作
    bullet->runAction(moveTo);
    //到达目标位置后需产生击中特效
    tower_hit_target(targetlocation);
    //删除子弹（风扇需特判）
    this->removeChild(bullet);
}

//炮塔粒子撞击目标产生短暂打击特效
void BasicDefensiveTower::tower_hit_target(const cocos2d::Vec2& targetlocation) {
    // 根据炮塔类型建立相应打击特效
    cocos2d::Sprite* hit = cocos2d::Sprite::create("Lighting_Hit.png");
    //将打击特效放入场景中
    this->addChild(hit);
    tower->setPosition(targetlocation);
    sprite_show(hit);
    //建立sequence动作序列：先维持半秒后自动销毁
    auto delay = cocos2d::DelayTime::create(1.0f); // 延时1秒
    auto remove = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
    //执行sequence动作序列
    hit->runAction(sequence);
}

//判断炮塔是否可以进行升级并产生
//（？我不知道pzx这个函数可以做这个不）

//炮塔升级
void BasicDefensiveTower::tower_upgrade() {
   //虚函数待覆盖
}