#include "Ball.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Ball::IgnoreCollisions() 
{
	return !Active();
}

Ball::Ball() {
	mTimer = Timer::Instance();

	mTexture = new GLTexture("breakout.png", 275, 358, 21, 21, true);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTag = "Ball";

	mSpeed = 250;
	mVelocity = Vector2(0, -mSpeed);
	
	isActive = true;
	mWasHit = false;
	mMoveBounds = Vector2(0.0f, Graphics::SCREEN_WIDTH);

	mPlayer = Player::Instance();

	

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Ball);
	
	

}

Ball::~Ball() 
{
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	mPlayer = nullptr;
}

void Ball::Fire(Vector2 pos) 
{
	Position(pos);
	mVelocity = Vector2(0, mSpeed);
	
	
}

void Ball::Reload() 
{
	Active(false);
	
}

void Ball::Hit(PhysEntity * other) 
{
	
	mWasHit = true;
	if (other->GetTag() == "Player")
	{
		mSpeed += 10;
		Vector2 collisionPoint = Position() - other->Position();

		
		float reflectionAngle = atan2(collisionPoint.y, collisionPoint.x);

		
		Vector2 newVelocity = Vector2(cos(reflectionAngle), sin(reflectionAngle));

		
		mVelocity = newVelocity * mSpeed;
		mYDirection = false;
		
		
	}
	else if (other->GetTag() == "Hostile" && !mBallHit)
	{
		if((Position().y - (mTexture->ScaledDimensions().y / 2) <= (other->Position().y + 13.0f) 
			|| Position().y + (mTexture->ScaledDimensions().y / 2) >= (other->Position().y - 13.0f)) 
			&& (Position().x - (mTexture->ScaledDimensions().x / 2) >= (other->Position().x - 27.0f)
			&& Position().x + (mTexture->ScaledDimensions().x / 2) <= (other->Position().x + 27.0f)))
		{
			mVelocity = Vector2(mVelocity.x, mVelocity.y * -1);
		}
		else if(Position().x - (mTexture->ScaledDimensions().x / 2) <= (other->Position().x + 27.0f) 
			|| Position().x + (mTexture->ScaledDimensions().x / 2) >= (other->Position().x - 27.0f))
		{
			mVelocity = Vector2(mVelocity.x * -1, mVelocity.y);
		}
		
		mBallHit = true;
		mSpeed += 10;
	}
	
}

void Ball::Update() 
{
	
	if(Active())
	{
		mBallHit = false;

		Vector2 pos = Position(Local);
		if (pos.x < mMoveBounds.x || pos.x > mMoveBounds.y) {
			mVelocity = Vector2(mVelocity.x * -1, mVelocity.y);
		}
		
		if (pos.y < 0)
		{
			mVelocity = Vector2(mVelocity.x, mVelocity.y * -1);
		}
		if (pos.y > Graphics::SCREEN_HEIGHT)
		{
			Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
			mSpeed = 250.0f;
			mVelocity = Vector2(0.0f, -mSpeed);
			mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);
		}
		Vector2 newPos;
		if (mYDirection)
		{
			newPos = Position() - mVelocity * mTimer->DeltaTime();


		}
		else
		{
			newPos = Position() + mVelocity * mTimer->DeltaTime();

		}


		Position(newPos);

		mWasHit = false;
	}
	

	
}

void Ball::Render() 
{
	if (Active()) {
		mTexture->Render();
		PhysEntity::Render();
	}
	
	
}
