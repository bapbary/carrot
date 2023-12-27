#include "Carrot.h"
USING_NS_CC;
Carrot* Carrot::create(int mapCatalog)
{
    Carrot* carrot = new Carrot();
    if (carrot && carrot->init(mapCatalog))
    {
        carrot->autorelease();
        return carrot;
    }
    else
    {
        delete carrot;
        return nullptr;
    }
}
//�ܲ���ʼ��
bool Carrot::init(int mapCatalog)
{
    if (!Node::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mapChoose = mapCatalog;
    //�ܲ��Ķ���֡
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    this->addChild(spriteCarrot, 2);
    objectPosition = Destination[mapCatalog-1];
    if (mapCatalog == 1)
    {
        spriteCarrot->setScaleX(-3.8);
    }
    else
    {
        spriteCarrot->setScaleX(3.8);
    }
    //����ת
    spriteCarrot->setPosition(objectPosition);
    spriteCarrot->setScaleY(3.8);
    //���ýӴ�
    auto physicsBody = PhysicsBody::createBox(spriteCarrot->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));// �ܶȣ��޸���Ħ��
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0x04);    // 0100
    physicsBody->setContactTestBitmask(0x01); // 0001
    spriteCarrot->setTag(CARROT);
    spriteCarrot->setPhysicsBody(physicsBody);

    //֡����
    auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
    spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));

    carrotLayer = this;
    return true;
}
//�ܲ�����Ѫ��
void Carrot::decreaseHealth()
{
    carrotLayer->currentHealthValue -= 1;
    if (carrotLayer->currentHealthValue == 9.0f)
    {
        //��������
        spriteNum = Sprite::create("icon_num(9).png");
        this->addChild(spriteNum, 2);
        spriteNum->setScale(2);
        spriteNum->setPosition(Destination[mapChoose-1].x,Destination[mapChoose-1].y+100);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
        auto framesCarrot = getAnimation("carrot2/%04d.png", 2);
        auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
        spriteCarrot->stopAllActions();
        spriteCarrot->setSpriteFrame(framesCarrot.front());
        spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));
    }
    else if (carrotLayer->currentHealthValue == 8.0f)
    {
        spriteNum->setTexture("icon_num(8).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealthValue == 7.0f)
    {
        spriteNum->setTexture("icon_num(7).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        //auto remove = RemoveSelf::create();
        //spriteCarrot->runAction(remove);
        //spriteCarrot = Sprite::create("carrot7.png");
        //this->addChild(spriteCarrot, 2);
        //spriteCarrot->setScale(-2,2);
        //spriteCarrot->setPosition(Destination[mapChoose - 1]);
        spriteCarrot->stopAllActions();
        spriteCarrot->setSpriteFrame("carrot3/carrot7.png");
    }
    else if (carrotLayer->currentHealthValue == 6.0f)
    {
        spriteNum->setTexture("icon_num(6).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealthValue == 5.0f)
    {
        spriteNum->setTexture("icon_num(5).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot5.png");
    }
    else if (carrotLayer->currentHealthValue == 4.0f)
    {
        spriteNum->setTexture("icon_num(4).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));

        spriteCarrot->setSpriteFrame("carrot3/carrot4.png");
    }
    else if (carrotLayer->currentHealthValue == 3.0f)
    {
        spriteNum->setTexture("icon_num(3).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealthValue == 2.0f)
    {
        spriteNum->setTexture("icon_num(2).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot2.png");
    }
    else if (carrotLayer->currentHealthValue == 1.0f)
    {
        spriteNum->setTexture("icon_num(1).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot1.png");
    }
    else
        CCLOG("gameover");
}

Carrot::Carrot() : spriteNum(nullptr)
{
    currentHealthValue = 10.0f;
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    //auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    //spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    //this->addChild(spriteCarrot, 2);
}
