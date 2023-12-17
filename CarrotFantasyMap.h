/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CARROTFANTASYMAP_SCENE_H__
#define __CARROTFANTASYMAP_SCENE_H__

#include "cocos2d.h"


class sceneCover : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void touchStart(cocos2d::Ref* pSender);//进入封面选择
    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序
    CREATE_FUNC(sceneCover);
};

class sceneChoose : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图选择场景初始化
    void returnLast(cocos2d::Ref* pSender);//回到上一场景
    void flipToNext(cocos2d::Ref* pSender);//滑动到下一个地图选择场景
    void flipToLast(cocos2d::Ref* pSender);//滑动到上一个地图选择场景
    void enterMapOne(cocos2d::Ref* pSender);//进入第一个地图中
    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序
    CREATE_FUNC(sceneChoose);

};

class mapOne : public sceneChoose
{
    cocos2d::Label* label;
    cocos2d::Sprite* fireBottle;
    cocos2d::EventListenerMouse* mouseListener;
public:
    mapOne();
    static cocos2d::Scene* createScene();
    virtual bool init();//第一个地图场景初始化
    void onMouseDown(cocos2d::EventMouse* event);
    CREATE_FUNC(mapOne);

};
#endif // __CARROTFANTASYMAP_SCENE_H__

