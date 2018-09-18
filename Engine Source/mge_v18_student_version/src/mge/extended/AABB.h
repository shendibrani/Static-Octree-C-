#pragma once

#include "Collider.h"
#include "glm.hpp"
#include <GL/glew.h>

class World;

class AABB : public Collider {
public:
	AABB(glm::vec3 pCenter, glm::vec3 pHalfSize);
	~AABB();

	bool collidesWith(Collider * other) override;
	bool collidesWith(AABB * other) override;
	bool collidesWith(OBB * other) override;

	glm::vec3 _scale;
	glm::vec3 _collisionColor = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 _noCollisionColor = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 GetMin() override;
	glm::vec3 GetMax() override;

	std::vector<glm::vec3> GetCorners();
	std::vector<glm::vec3> GetAxes();

	void render() override;

private:
	
};
