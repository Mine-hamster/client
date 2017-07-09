#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();	

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:

	// 以下由UI部分完成
	void preloadMusic();					// 预加载音乐
	void loadAnimation();	// 加载动画
	void loadSprites();						// 加载精灵
	void initGrid();
	const static int gridSize = 9;
	void setMineNumberGrid(int x,int y, int value);
	Sprite* m_backGroundImage;
	Sprite* m_hamsterImage;
	Sprite* m_mineImage;
	Sprite* m_normalGridImage;
	Sprite* m_solvedGridImage;
	Sprite* m_gameOverImage;

	Sprite* m_normalGrid[gridSize][gridSize];
	Sprite* m_solvedGrid[gridSize][gridSize];
	Sprite* m_mineGrid[gridSize][gridSize];
	Sprite* m_hamsterGrid[gridSize][gridSize];
	Label* m_mineNumberGrid[gridSize][gridSize];

	Label* m_time;
	Label* m_score;
	
	Vector<SpriteFrame*> m_hamsterAppearFrame;
	Animate* m_hamsterAppearAnimate;
	Vector<SpriteFrame*> m_hamsterDisappearFrame;
	Animate* m_hamsterDisappearAnimate;

	SpriteFrame* m_hitFrame;

	char* m_hitMineEffectFile = "";
	char* m_mineExplodeEffectFile = "";
	char* m_backGroundMusicFile = "";
};

#endif // __GAME_SCENE_H__
