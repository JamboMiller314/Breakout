#ifndef __BLOCKS_H
#define __BLOCKS_H

#include "PhysEntity.h"
#include "Timer.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Blocks : public PhysEntity {
public:

	enum class BlockType{Purple, Red, Yellow, Green};

protected:
	BlockType mBlockType;
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;
	GLTexture* mBlocks;
	bool mWasHit;
	

	

public:
	Blocks(BlockType type);
	~Blocks();

	bool WasHit();
	void WasHit(bool hit);
	Vector2 scaledDimensions();
	void Hit(PhysEntity* other) override;
	BlockType getBlockType();
	void Update() override;
	void Render() override;
};










#endif // !__BLOCKS_H
