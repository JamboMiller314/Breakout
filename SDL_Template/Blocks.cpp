#include "Blocks.h"

Blocks::Blocks(BlockType type)
{
	mBlockType = type;
	mTag = "Hostile";
	mWasHit = false;
	isActive = true;
	if (mBlockType == BlockType::Purple)
	{

		mBlocks = new GLTexture("Breakout.png", 53, 142, 59, 29, true);
		mBlocks->Parent(this);
		mBlocks->Position(Vec2_Zero);
		
		
	}
	else if (mBlockType == BlockType::Red)
	{
		mBlocks = new GLTexture("Breakout.png", 53, 83, 59, 29, true);
		mBlocks->Parent(this);
		mBlocks->Position(Vec2_Zero);
		
		
	}
	else if (mBlockType == BlockType::Yellow)
	{
		mBlocks = new GLTexture("Breakout.png", 53, 112, 59, 29, true);
		mBlocks->Parent(this);
		mBlocks->Position(Vec2_Zero);
		
		
	}
	else if (mBlockType == BlockType::Green)
	{
		mBlocks = new GLTexture("Breakout.png", 53, 53, 59, 29, true);
		mBlocks->Parent(this);
		mBlocks->Position(Vec2_Zero);
		
		
	}
	AddCollider(new BoxCollider(Vector2(59.0f, 29.0f)));
	mId = PhysicsManager::Instance()->RegisterEntity(this,
		PhysicsManager::CollisionLayers::Hostile);

	
}

Blocks::~Blocks()
{
	delete mBlocks;
	mBlocks = nullptr;
	
}

Vector2 Blocks::scaledDimensions()
{
	return mBlocks->ScaledDimensions();
}

bool Blocks::WasHit() {
	return mWasHit;
}

void Blocks::WasHit(bool hit)
{
	mWasHit = hit;
}
void Blocks::Hit(PhysEntity* other)
{
	
	mWasHit = true;
	
	
	
}


Blocks::BlockType Blocks::getBlockType()
{
	return mBlockType;
}

void Blocks::Update()
{
	
}

void Blocks::Render()
{
	
	mBlocks->Render();
	

	PhysEntity::Render();
}