#ifndef __Ball_H
#define __Ball_H
#include "PhysEntity.h"
#include "Timer.h"
#include "Player.h"
using namespace SDLFramework;

class Ball : public PhysEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;
	Player* mPlayer;
	Timer * mTimer;
	bool mWasHit;
	Texture * mTexture;
	bool mYDirection;
	float mSpeed;
	Vector2 mVelocity;
	Vector2 mVelocityX;
	Vector2 mMoveBounds;
	bool mBallHit;
private:
	//Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	Ball();
	~Ball();

	void Fire(Vector2 pos);
	void Reload();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;
};
#endif