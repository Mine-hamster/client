#include "StartScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	auto m_startGameItem = MenuItemImage::create(
		m_startGameItemPicNormal,
		m_startGameItemPicSelected,
		CC_CALLBACK_1(StartScene::menuStartGameCallback, this));
	float ScaleFactor = 0.1;
	float ScaleX = visibleSize.width * ScaleFactor / m_startGameItem->getContentSize().width;
	float ScaleY = visibleSize.height * ScaleFactor / m_startGameItem->getContentSize().height;
	//log("Content width is %f ,Scale is %f", m_startGameItem->getContentSize().width, ScaleX);
	if (ScaleX > ScaleY) {
		ScaleX = ScaleY;
	}
	else {
		ScaleY = ScaleX;
	}
	m_startGameItem->setScaleX(ScaleX);
	m_startGameItem->setScaleY(ScaleY);
	//log("Content width is %f ,Scale is %f", m_startGameItem->getContentSize().width, ScaleX);
	m_startGameItem->getContentSize().height;
	m_startGameItem->setPosition(Vec2(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height/2 - 2 * visibleSize.height/10));
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(m_startGameItem, closeItem , NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Mine Hamster", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create(".././Resources/Hamster.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void StartScene::menuStartGameCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}
