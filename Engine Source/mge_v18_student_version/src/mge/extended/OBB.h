#pragma once
#include "Collider.h"
#include "AABB.h"

class OBB : public Collider
{
public:
	OBB(glm::vec3 pCenter, glm::vec3 pHalfSize);
	~OBB();

	bool collidesWith(Collider * other) override;
	bool collidesWith(AABB * other) override;
	bool collidesWith(OBB * other) override;
	
	glm::vec3 GetMin() override;
	glm::vec3 GetMax() override;
	std::vector<glm::vec3> GetCorners();
	std::vector<glm::vec3> GetAxes();

	glm::vec3 _collisionColor = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 _noCollisionColor = glm::vec3(0.0f, 1.0f, 0.0f);

	void render() override;
};

