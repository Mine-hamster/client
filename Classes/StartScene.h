#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartGameCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

//private:
//	Sprite* m_backgroundPicture;
//	MenuItem* m_startGameItem;
//	char* m_startGameItemPicNormal = "startGameNormal.png";
//	char* m_startGameItemPicSelected = "startGameSelected.png";
};

#endif // __HELLOWORLD_SCENE_H__
