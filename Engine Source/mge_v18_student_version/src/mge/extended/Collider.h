#pragma once

#include "glm\glm.hpp"
#include "mge\core\GameObject.hpp"


class GameObject;
class AABB;
class OBB;


class Collider {
public:
	Collider();
	~Collider();

	GameObject * _owner;
	glm::vec3 _halfSize;
	glm::vec3 _center;

	static int collisionCheckCount;
	static std::vector<long> collisionTimes;
	virtual bool collidesWith(Collider * other) = 0;
	virtual bool collidesWith(AABB * other) = 0;
	virtual bool collidesWith(OBB * other) = 0;

	// all specific checks todo, statics
	static bool isColliding(AABB * one, AABB * other);
	static bool isColliding(AABB * one, OBB * other);
	static bool isColliding(OBB * one, OBB * other);

	bool collisionFlag = false;

	virtual glm::vec3 GetMin();
	virtual glm::vec3 GetMax();

	virtual void render();
private:
};
