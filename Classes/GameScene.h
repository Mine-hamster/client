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

	// 以下由UI部分完成
	void preloadMusic();					// 预加载音乐
	void loadAnimation(string filepath);	// 加载动画
	void loadSprites();						// 加载精灵


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	Sprite* m_backGroundImage;
	Sprite* m_hamsterImage;
	Sprite* m_mineImage;
	Sprite* m_normalGridImage;
	Sprite* m_solvedGridImage;
	Sprite* m_gameOverImage;

	Label* m_time;
	Label* m_score;

	SpriteFrame* m_hamsterAppearFrame;
	SpriteFrame* m_hamsterDisappearFrame;
	SpriteFrame* m_hitFrame;

	char* m_hitMineEffectFile = "";
	char* m_mineExplodeEffectFile = "";
	char* m_backGroundMusicFile = "";
};

#endif // __GAME_SCENE_H__
