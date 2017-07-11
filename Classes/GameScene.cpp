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
	srand((int)time(0));
	hamsters = 0;
	safe = 0;
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

	hitNum = Label::createWithTTF("hamster: 0", "fonts/arial.TTF", 20);
	hitNum->setColor(Color3B(0, 0, 0));
	hitNum->setPosition(50, 260);
	this->addChild(hitNum, 3);
	findNum = Label::createWithTTF("safe: 0", "fonts/arial.TTF", 20);
	findNum->setColor(Color3B(0, 0, 0));
	findNum->setPosition(50, 230);
	this->addChild(findNum, 3);
	description = Label::createWithTTF("Hit the hamsters and then they will tell you how many mines are around them, and then try to find out safe grids. \nWish you good luck.", "fonts/Marker Felt.TTF", 22);
	description->setColor(Color3B(0, 0, 0));
	description->setAnchorPoint(Vec2(0, 0));
	description->setPosition(10, visibleSize.height / 2 +130);
	this->addChild(description, 3);

	int numofhamster = 5;
	while (numofhamster--) {
		loadAnimation();
		int i = rand() % gridSize;
		int j = rand() % gridSize;
		m_hamsterGrid[i][j]->runAction(Sequence::create(CallFunc::create([=]() {m_hamster[i][j] = true; }),
			m_hamsterAppearAnimate,
			CCDelayTime::create(2.0f),
			m_hamsterDisappearAnimate,
			CallFunc::create([=]() {m_hamster[i][j] = false; }),
			NULL));
	}

    this->addChild(m_backGroundImage, 0);

	addTouchListener();

	schedule(schedule_selector(GameScene::update), 3.0f, kRepeatForever, 0);

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
	sae->preloadEffect(m_hithamsterEffectFile);
	sae->preloadEffect(m_mineExplodeEffectFile);
	sae->preloadEffect(".././Resources/out.wav");
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
	//disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_4.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_3.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_2.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_1.png");
	disappear_animation->addSpriteFrameWithFileName(".././Resources/marmot_6.png");
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
		int k = rand() % gridSize;
		for (int j = 0; j < gridSize; j++) {
			m_solvedGrid[i][j] = Sprite::create(".././Resources/solvedgrid.PNG");
			scaleImage(scaleFactor, m_solvedGrid[i][j], scaledSize);
			gridWidth = scaledSize.x;
			gridHeight = scaledSize.y;
			m_solvedGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			this->addChild(m_solvedGrid[i][j], 2);
			m_solvedGrid[i][j]->setVisible(false);
			
			//一开始没地鼠
			m_hamster[i][j] = false;

			// 是否生成地雷格子
			m_mine[i][j] = false;
			if (j == k) {
				m_mine[i][j] = true;
				m_mineGrid[i][j] = Sprite::create(".././Resources/mine.PNG");
				scaleImage(scaleFactor, m_mineGrid[i][j], scaledSize);
				m_mineGrid[i][j]->setPosition(
					Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
						visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
				this->addChild(m_mineGrid[i][j], 3);
				m_mineGrid[i][j]->setVisible(false);
			}

			//TTFConfig ttfConfig(".././Resources/fonts/arial.ttf", 24);
			//int number = i*gridSize + j;
			//std::string number_str = StringUtils::format("%d", number);
			//m_mineNumberGrid[i][j] = Label::createWithTTF(ttfConfig, number_str);
			//scaleImage(scaleFactor, m_mineNumberGrid[i][j], scaledSize);
			//m_mineNumberGrid[i][j]->setPosition(Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
				//visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));

			// 是否显示周围地雷数的格子
			//m_mineNumberGrid[i][j]->setVisible(false);

			//this->addChild(m_mineNumberGrid[i][j], 3);

			m_normalGrid[i][j] = Sprite::create(".././Resources/grid.PNG");
			scaleImage(scaleFactor, m_normalGrid[i][j],scaledSize);
			m_normalGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight -  gridHeight));
			this->addChild(m_normalGrid[i][j], 1);

			m_hamsterGrid[i][j] = Sprite::create(".././Resources/marmot_5.PNG");
			scaleImage(scaleFactor, m_hamsterGrid[i][j], scaledSize);
			m_hamsterGrid[i][j]->setPosition(
				Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
					visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));
			this->addChild(m_hamsterGrid[i][j], 5);
			
		}
	}
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			TTFConfig ttfConfig(".././Resources/fonts/arial.ttf", 24);
			int number = 0;
			for (int k = i - 1 >= 0 ? i - 1 : 0; k < gridSize && k <= i + 1; k++) {
				for (int l = j - 1 >= 0 ? j - 1 : 0; l < gridSize && l <= j + 1; l++) {
					if (m_mine[k][l] == true)
						number++;
				}
			}
			std::string number_str = StringUtils::format("%d", number);
			m_mineNumberGrid[i][j] = Label::createWithTTF(ttfConfig, number_str);
			scaleImage(scaleFactor, m_mineNumberGrid[i][j], scaledSize);
			m_mineNumberGrid[i][j]->setPosition(Vec2(visibleSize.width / 3 + origin.x + i * gridWidth + 2 * gridWidth,
				visibleSize.height * 2 / 3 + origin.y - j * gridHeight - gridHeight));

			// 是否显示周围地雷数的格子
			m_mineNumberGrid[i][j]->setVisible(false);

			this->addChild(m_mineNumberGrid[i][j], 4);
		}
	}
}

void GameScene::setMineNumberGrid(int x, int y, int value)
{
	std::string number_str = StringUtils::format("%d", value);
	m_mineNumberGrid[x][y]->setString(number_str);
}

void GameScene::update(float dt) {
	int numofhamster = 7;
	while (numofhamster--) {
		loadAnimation();
		int i = rand() % gridSize;
		int j = rand() % gridSize;
		m_hamsterGrid[i][j]->runAction(Sequence::create(CallFunc::create([=]() {m_hamster[i][j] = true; }),
			m_hamsterAppearAnimate,
			CCDelayTime::create(2.0f),
			m_hamsterDisappearAnimate,
			CallFunc::create([=]() {m_hamster[i][j] = false; }),
			NULL));
	}
}

// 添加触摸事件监听器
void GameScene::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

// 鼠标点击发射炮弹
bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (m_normalGrid[i][j]->getBoundingBox().containsPoint(touch->getLocation())) {
				if (m_hamster[i][j] == true) {
					hamsters++;
					char str[15];
					sprintf(str, "hamster: %d", hamsters);
					hitNum->setString(str);
					m_mineNumberGrid[i][j]->setVisible(true);
					loadAnimation();
					m_hamsterGrid[i][j]->stopAllActions();
					m_hamsterGrid[i][j]->runAction(Sequence::create(
						m_hamsterDisappearAnimate,
						CallFunc::create([=]() {m_hamster[i][j] = false; }),
						NULL));
					SimpleAudioEngine::getInstance()->playEffect(m_hithamsterEffectFile, false);
					return true;
				}
				else if (m_mine[i][j] == false) {
					safe++;
					char str[15];
					sprintf(str, "safe: %d", safe);
					findNum->setString(str);
					m_solvedGrid[i][j]->setVisible(true);
					SimpleAudioEngine::getInstance()->playEffect(".././Resources/out.wav", false);
					if (safe == 90) {
						auto win = Sprite::create(".././Resources/win.png");
						win->setAnchorPoint(Vec2(0.5, 0.5));
						win->setPosition(Director::getInstance()->getVisibleSize() / 2);
						this->addChild(win, 6);
						_eventDispatcher->removeAllEventListeners();
						unschedule(schedule_selector(GameScene::update));
					}
					return true;
				}
				else if (m_mine[i][j] == true) {
					m_solvedGrid[i][j]->setVisible(true);
					m_mineGrid[i][j]->setVisible(true);
					SimpleAudioEngine::getInstance()->playEffect(m_mineExplodeEffectFile, false);
					auto gameover = Sprite::create(".././Resources/gameover.png");
					gameover->setAnchorPoint(Vec2(0.5, 0.5));
					gameover->setPosition(Director::getInstance()->getVisibleSize() / 2);
					this->addChild(gameover, 6);
					_eventDispatcher->removeAllEventListeners();
					unschedule(schedule_selector(GameScene::update));
					return true;
				}
			}
		}
	}
	return false;
}


