#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Timer.h"
#include "MathHelper.h"


using namespace SDLFramework;

class Player : public PhysEntity {
private:
	static Player* sInstance;
	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	
	int mScore;
	int mLives;

	GLTexture * mShip;
	AnimatedGLTexture * mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	

private:
	void HandleMovement();
	

public:
	static Player* Instance();
	static void release();
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity * other) override;
	
	bool WasHit();

	void Update() override;
	void Render() override;
};
#endif