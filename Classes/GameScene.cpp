#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	loadSprites();
	initGrid();
    // position the sprite on the center of the screen
	float backGroundImageScaleX = visibleSize.width / m_backGroundImage->getContentSize().width;
	float backGroundImageScaleY = visibleSize.height / m_backGroundImage->getContentSize().height;
	m_backGroundImage->setScaleX(backGroundImageScaleX);
	m_backGroundImage->setScaleY(backGroundImageScaleY);
	m_backGroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
/*	float gridWidth = m_solvedGridImage->getContentSize().width;
	float gridHeight = m_solvedGridImage->getContentSize().height;
	m_solvedGridImage->setPosition(Vec2(visibleSize.width / 2 + origin.x - gridWidth, visibleSize.height / 2 + origin.y));
	m_normalGridImage->setPosition(Vec2(visibleSize.width / 2 + origin.x + gridWidth, visibleSize.height / 2 + origin.y));
   */ 
   // add the sprite as a child to this layer
    this->addChild(m_backGroundImage, 0);
	//this->addChild(m_solvedGridImage, 1);
	//this->addChild(m_normalGridImage, 1);
    return true;
}

void GameScene::preloadMusic()
{
	auto sae = SimpleAudioEngine::getInstance();
	sae->preloadEffect(m_hitMineEffectFile);
	sae->preloadEffect(m_mineExplodeEffectFile);

	sae->preloadBackgroundMusic(m_backGroundMusicFile);
	
	sae->playBackgroundMusic(m_backGroundMusicFile, true);
}

void GameScene::loadSprites()
{
	m_backGroundImage = Sprite::create(".././Resources/gameSceneBackGround.JPG");
	m_normalGridImage = Sprite::create(".././Resources/grid.PNG");
	m_solvedGridImage = Sprite::create(".././Resources/solvedGrid.PNG");
}

void GameScene::initGrid()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float gridWidth = m_normalGridImage->getContentSize().width;
	float gridHeight = m_normalGridImage->getContentSize().height;
	int gridNum = gridSize*gridSize;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			m_solvedGrid[i][j] = Sprite::create(".././Resources/solvedgrid.PNG");
			m_solvedGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			this->addChild(m_solvedGrid[i][j], 1);

			//m_mineGrid[i][j] = Sprite::create(".././Resources/mine.PNG");
			//m_mineGrid[i][j]->setPosition(
			//	Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
			//		visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			//this->addChild(m_mineGrid[i][j], 2);

			TTFConfig ttfConfig(".././Resources/fonts/arial.ttf", 24);
			int number = i*gridSize + j;
			std::string number_str = StringUtils::format("%d", number);
			m_mineNumberGrid[i][j] = Label::createWithTTF(ttfConfig, number_str);
			m_mineNumberGrid[i][j]->setPosition(Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
				visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			//m_mineNumberGrid[i][j]->setString("Reset String");
			this->addChild(m_mineNumberGrid[i][j], 3);

	/*		m_normalGrid[i][j] = Sprite::create(".././Resources/grid.PNG");
			m_normalGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight -  gridHeight));
			this->addChild(m_normalGrid[i][j], 4);*/

			
			
		}
	}
	
}


