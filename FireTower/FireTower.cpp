
#include "FireTower.h"
//���캯�������������ĳ�ʼ������ʾ
FireTower::FireTower(const char* filename, int code, int level, const cocos2d::Vec2& touchlocation) {
    tower = cocos2d::Sprite::create(filename);
    towerlocation = touchlocation;
    category_code = code;
    tower_level = level;
    //����������ų�ʼ��������������ֵ




    //������������ʾ
    tower->setPosition(touchlocation);
    //����������С
    tower->setScale(10);
    sprite_show(tower);
    //�����龰���ڽ��������֮��һ�䣬�������н��з���
}
