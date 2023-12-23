#include "BasicDifensiveTower.h"

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

//判断目标对象消失（攻击致死）



//炮塔更新索敌对象
void BasicDefensiveTower::tower_targetupdate() {
    // 如果当前没有目标或者目标超出索敌范围，重新选择目标
    if (currenttarget == nullptr || (currenttarget->getPosition() - tower->getPosition()).length() > tower_attack_range) {
        currenttarget = findTarget();
    }
    //目标选择完成之后进行攻击操作
    tower_attack();
}

//炮塔最近距离索敌
cocos2d::Sprite* BasicDefensiveTower::findTarget() {
    //在怪物图层中搜索遍历最近的那个
    //需return一个精灵或者return nullptr
    return tower;
}

//炮塔攻击
void BasicDefensiveTower::tower_attack() {
    //本次攻击目标坐标一脉相承至后续三个函数！！！
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
    // 根据炮塔类型和等级创建对应大小的子弹
    cocos2d::Sprite* lightingbullet = cocos2d::Sprite::create("LightingTower_bullet_small.png");
    //将子弹也放入当前场景中
    this->addChild(lightingbullet);
    //返回子弹精灵本身，用于后续子弹飞行特效制作
    return lightingbullet;
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
    if (tower_level == 1) {
        tower_level++;
        //一系列数值增加

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_middle.png");
    }
    else if (tower_level == 2) {
        tower_level++;
        //一系列数值增加

        // 使用新图标替换旧图标
        tower->setTexture("LightingTower_big.png");
    }
}