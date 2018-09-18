#pragma once

#include "Collider.h"

class SphereCollider : public Collider 
{
public:
	SphereCollider(GameObject* pOwner);
	~SphereCollider();
	
	float _radius;

	bool collidesWith(Collider * other) override;
	bool collidesWith(AABB * other) override;
	bool collidesWith(OBB * other) override;
};

