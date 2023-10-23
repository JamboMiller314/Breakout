#ifndef __PHYSENTITY_H
#define __PHYSENTITY_H
#include <vector>
#include "Collider.h"

class PhysEntity : public GameEntity {
protected:
	unsigned long mId;

	std::vector<Collider *> mColliders;

	Collider * mBroadPhaseCollider;

	void AddCollider(Collider * collider, Vector2 localPos = Vec2_Zero);

	virtual bool IgnoreCollisions();
	std::string mTag;
	bool isActive;
public:
	PhysEntity();
	virtual ~PhysEntity();

	unsigned long GetId();
	void SetTag(std::string tag);
	std::string GetTag();
	bool CheckCollision(PhysEntity * other);
	bool Destroy();
	virtual void Hit(PhysEntity * other) { }
	bool IsActive() const;
	virtual void Render() override;
};
#endif