
#include "FireTower.h"
//构造函数：炮塔参数的初始化并显示
FireTower::FireTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create(filename);
    towerlocation = touchlocation;
    category_code = code;
    tower_level = level;
    //根据种类代号初始化炮塔的其他数值




    //放置炮塔并显示
    tower->setPosition(touchlocation);
    //设置炮塔大小
    tower->setScale(10);
    sprite_show(tower);
    //加入情景放在建立类操作之后一句，不在类中进行放入
}
