#include "Carrot.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
    //λ��
    objectPosition = Destination[mapCatalog-1];
    //����ת
    spriteCarrot->setPosition(objectPosition);
    spriteCarrot->setScaleX(-3.8);
    spriteCarrot->setScaleY(3.8);
    //���ýӴ�
    cocos2d::Size smallerSize(spriteCarrot->getContentSize().width * 0.1f, spriteCarrot->getContentSize().height * 0.1f);
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
    SimpleAudioEngine::getInstance()->playEffect("carrotbite.MP3", false, 1.0f, 1.0f, 1.0f);
    carrotLayer->currentHealth -= 1;
    if (carrotLayer->currentHealth == 9)
    {
        //��������
        spriteNum = Sprite::create("icon_num(9).png");
        this->addChild(spriteNum, 2);
        spriteNum->setScale(2);
        spriteNum->setPosition(Destination[mapChoose-1].x,Destination[mapChoose-1].y+80);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
        auto framesCarrot = getAnimation("carrot2/%04d.png", 2);
        auto animationCarrot = Animation::createWithSpriteFrames(framesCarrot, 1.0f / 3);
        spriteCarrot->stopAllActions();
        spriteCarrot->setSpriteFrame(framesCarrot.front());
        spriteCarrot->runAction(RepeatForever::create(Animate::create(animationCarrot)));
    }
    else if (carrotLayer->currentHealth == 8)
    {
        spriteNum->setTexture("icon_num(8).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealth == 7)
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
    else if (carrotLayer->currentHealth == 6)
    {
        spriteNum->setTexture("icon_num(6).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealth == 5)
    {
        spriteNum->setTexture("icon_num(5).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot5.png");
    }
    else if (carrotLayer->currentHealth == 4)
    {
        spriteNum->setTexture("icon_num(4).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot4.png");

    }
    else if (carrotLayer->currentHealth == 3)
    {
        spriteNum->setTexture("icon_num(3).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
    }
    else if (carrotLayer->currentHealth == 2)
    {
        spriteNum->setTexture("icon_num(2).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot2.png");
    }
    else if (carrotLayer->currentHealth == 1)
    {
        spriteNum->setTexture("icon_num(1).png");
        spriteNum->setTextureRect(Rect(Vec2::ZERO, spriteNum->getContentSize()));
        spriteCarrot->setSpriteFrame("carrot3/carrot1.png");
    }
    else
    {
        SimpleAudioEngine::getInstance()->playEffect("fail.MP3", false, 1.0f, 1.0f, 1.0f);
        CCLOG("gameover");
        if (mapChoose == 1)
            gameOverOne();
        else
            gameOverTwo();
    }
}

Carrot::Carrot() : spriteNum(nullptr)
{
    currentHealth = 10;
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
    //auto framesCarrot = getAnimation("carrot/%04d.png", 3);
    //spriteCarrot = Sprite::createWithSpriteFrame(framesCarrot.front());
    //this->addChild(spriteCarrot, 2);
}
