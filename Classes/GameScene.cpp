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
	preloadMusic();
	loadSprites();
	loadAnimation();
	initGrid();
    // position the sprite on the center of the screen
	float backGroundImageScaleX = visibleSize.width / m_backGroundImage->getContentSize().width;
	float backGroundImageScaleY = visibleSize.height / m_backGroundImage->getContentSize().height;
	m_backGroundImage->setScaleX(backGroundImageScaleX);
	m_backGroundImage->setScaleY(backGroundImageScaleY);
	m_backGroundImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


	//
	m_hamsterGrid[3][3]->runAction(Sequence::create(m_hamsterAppearAnimate,
		m_hamsterDisappearAnimate,
		CallFunc::create([=]() {m_hamsterGrid[3][3]->setVisible(false); }),
		NULL));
   // add the sprite as a child to this layer
    this->addChild(m_backGroundImage, 0);

    return true;
}

void GameScene::scaleImage(float scaleFactor,Node* node, Vec2& scaledSize)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float ScaleX = visibleSize.width * scaleFactor / node->getContentSize().width;
	float ScaleY = visibleSize.height * scaleFactor / node->getContentSize().height;
	//log("Content width is %f ,Scale is %f", m_startGameItem->getContentSize().width, ScaleX);
	if (ScaleX > ScaleY) {
		ScaleX = ScaleY;
	}
	else {
		ScaleY = ScaleX;
	}
	node->setScaleX(ScaleX);
	node->setScaleY(ScaleY);
	scaledSize = Vec2(node->getContentSize().width*ScaleX, node->getContentSize().height*ScaleY);
	
}

void GameScene::preloadMusic()
{
	auto sae = SimpleAudioEngine::getInstance();
	//sae->preloadEffect(m_hitMineEffectFile);
	//sae->preloadEffect(m_mineExplodeEffectFile);
	sae->preloadBackgroundMusic(m_backGroundMusicFile);
	sae->playBackgroundMusic(m_backGroundMusicFile, true);
}

void GameScene::loadAnimation()
{
	Animation* appear_animation = Animation::create();
	appear_animation->addSpriteFrameWithFileName(".././Resources/marmot_1.png");
	appear_animation->addSpriteFrameWithFileName(".././Resources/marmot_2.png");
	appear_animation->addSpriteFrameWithFileName(".././Resources/marmot_3.png");
	appear_animation->setDelayPerUnit(0.1f);//设置动画的间隔时间  
	appear_animation->setRestoreOriginalFrame(false);//是否返回第一帧  
	m_hamsterAppearAnimate = Animate::create(appear_animation);

	Animation* disappear_animation = Animation::create();
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_4.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_3.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_2.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_1.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_5.png");
	disappear_animation->setDelayPerUnit(0.1f);//设置动画的间隔时间  
	disappear_animation->setRestoreOriginalFrame(false);//是否返回第一帧  
	m_hamsterDisappearAnimate = Animate::create(disappear_animation);

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
	float gridWidth;
	float gridHeight;
	Vec2 scaledSize;
	float scaleFactor = 0.05;
	int gridNum = gridSize*gridSize;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			m_solvedGrid[i][j] = Sprite::create(".././Resources/solvedgrid.PNG");
			scaleImage(scaleFactor, m_solvedGrid[i][j], scaledSize);
			gridWidth = scaledSize.x;
			gridHeight = scaledSize.y;
			m_solvedGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			this->addChild(m_solvedGrid[i][j], 1);
			
			// 是否生成地雷格子

			//m_mineGrid[i][j] = Sprite::create(".././Resources/mine.PNG");
			//scaleImage(scaleFactor, m_mineGrid[i][j], scaledSize);
			//m_mineGrid[i][j]->setPosition(
			//	Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
			//		visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			//this->addChild(m_mineGrid[i][j], 2);

			TTFConfig ttfConfig(".././Resources/fonts/arial.ttf", 24);
			int number = i*gridSize + j;
			std::string number_str = StringUtils::format("%d", number);
			m_mineNumberGrid[i][j] = Label::createWithTTF(ttfConfig, number_str);
			scaleImage(scaleFactor, m_mineNumberGrid[i][j], scaledSize);
			m_mineNumberGrid[i][j]->setPosition(Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
				visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));

			// 是否显示周围地雷数的格子
			m_mineNumberGrid[i][j]->setVisible(false);

			this->addChild(m_mineNumberGrid[i][j], 3);

			m_normalGrid[i][j] = Sprite::create(".././Resources/grid.PNG");
			scaleImage(scaleFactor, m_normalGrid[i][j],scaledSize);
			m_normalGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight -  gridHeight));
			this->addChild(m_normalGrid[i][j], 4);

			m_hamsterGrid[i][j] = Sprite::create(".././Resources/marmot_5.PNG");
			scaleImage(scaleFactor, m_hamsterGrid[i][j], scaledSize);
			m_hamsterGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			this->addChild(m_hamsterGrid[i][j], 5);
			
		}
	}
	
}

void GameScene::setMineNumberGrid(int x, int y, int value)
{
	std::string number_str = StringUtils::format("%d", value);
	m_mineNumberGrid[x][y]->setString(number_str);
}


