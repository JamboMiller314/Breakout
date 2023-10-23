#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "Ball.h"
#include "Blocks.h"
#include "Scoreboard.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;

	Texture * mStartLabel;
	

	Player * mPlayer;

	Ball* mBall;

	
	GameEntity* mTopBar;
	GLTexture* mPlayerOne;
	GLTexture* mPlayerTwo;
	GLTexture* mHiScore;
	GLTexture* mBackground;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;

	std::vector<Blocks*> mBlocks;
private:
	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();
	void handleCollisions();
	void StartNewGame();
	void generateBlocks();
	void Update() override;
	void Render() override;
};
#endif