
#include "Collider.h"
#include "AABB.h"
#include "OBB.h"
#include <chrono>


int Collider::collisionCheckCount;
std::vector<long> Collider::collisionTimes;

Collider::Collider()
{
	_owner = nullptr;
}

Collider::~Collider()
{
}

bool Collider::collidesWith(Collider * other)
{
	return false;
}

bool Collider::collidesWith(AABB * other)
{
	return false;
}

bool Collider::collidesWith(OBB * other)
{

	return false;
}

bool Collider::isColliding(AABB * one, AABB * other) {
	collisionCheckCount+=1;
	
	glm::vec3 onePosition = one->_owner->getWorldPosition();
	glm::vec3 otherPosition = other->_owner->getWorldPosition();

	bool doesCollide;

	doesCollide = glm::fastDistance(onePosition.x, otherPosition.x) < (one->_halfSize.x + other->_halfSize.x) &&
		glm::distance(onePosition.y, otherPosition.y) < (one->_halfSize.y + other->_halfSize.y) &&
		glm::distance(onePosition.z, otherPosition.z) < (one->_halfSize.z + other->_halfSize.z);

	one->collisionFlag = doesCollide;
	other->collisionFlag = doesCollide;

	return doesCollide;
}

bool Collider::isColliding(AABB * one, OBB * other)
{
	if (glm::fastDistance(one->_owner->getLocalPosition(), other->_owner->getLocalPosition()) > glm::fastLength(one->_halfSize) + glm::fastLength(other->_halfSize))
	{
		return false;
	}
	
	
	collisionCheckCount += 1;
	glm::vec3 oneCenter = one->_owner->getWorldPosition(); // object's pos = collider center
	glm::mat4 oneTransform = one->_owner->getTransform(); // removed scaling for halfsize to do it for both AABB and OBB in one place
	glm::vec3 otherCenter = other->_owner->getWorldPosition();
	glm::mat4 otherTransform = other->_owner->getTransform();

	for (int a = 0; a<3; a++) {
		glm::vec3 l = glm::vec3(oneTransform[a]); // one axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			one->collisionFlag = false;
			other->collisionFlag = false;
			return false;
		}
	}

	for (int b = 0; b<3; b++) {
		glm::vec3 l = glm::vec3(otherTransform[b]); // other axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			one->collisionFlag = false;
			other->collisionFlag = false;
			return false;
		}
	}

	for (int a = 0; a<3; a++) {
		glm::vec3 aAxis = glm::vec3(oneTransform[a]);
		for (int b = 0; b<3; b++) {
			glm::vec3 bAxis = glm::vec3(otherTransform[b]);
			if (aAxis != bAxis) {
				glm::vec3 l = glm::cross(aAxis, bAxis); // has flaw when axis are same, result in (0,0,0), solved by if
				float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
				float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
				float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
				float penetration = (ra + rb) - tl;
				if (penetration <= 0) { // no overlap
					one->collisionFlag = false;
					other->collisionFlag = false;
					return false;

				}
			}
		}
	}
	one->collisionFlag = true;
	other->collisionFlag = true;

	
	return true;	
}


bool Collider::isColliding(OBB * one, OBB * other) {
	if (glm::fastDistance(one->_owner->getLocalPosition(), other->_owner->getLocalPosition()) > glm::fastLength(one->_halfSize) + glm::fastLength(other->_halfSize))
	{
		return false;
	}

	//std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());

	collisionCheckCount += 1;
	glm::vec3 oneCenter = one->_owner->getWorldPosition(); // object's pos = collider center
	glm::mat4 oneTransform = one->_owner->getTransform(); // removed scaling for halfsize to do it for both AABB and OBB in one place
	glm::vec3 otherCenter = other->_owner->getWorldPosition();
	glm::mat4 otherTransform = other->_owner->getTransform();

	for (int a = 0; a<3; a++) {
		glm::vec3 l = glm::vec3(oneTransform[a]); // one axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			one->collisionFlag = false;
			other->collisionFlag = false;
			return false;
		}
	}

	for (int b = 0; b<3; b++) {
		glm::vec3 l = glm::vec3(otherTransform[b]); // other axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			one->collisionFlag = false;
			other->collisionFlag = false;
			return false;
		}
	}

	for (int a = 0; a<3; a++) {
		glm::vec3 aAxis = glm::vec3(oneTransform[a]);
		for (int b = 0; b<3; b++) {
			glm::vec3 bAxis = glm::vec3(otherTransform[b]);
			if (aAxis != bAxis) {
				glm::vec3 l = glm::cross(aAxis, bAxis); // has flaw when axis are same, result in (0,0,0), solved by if
				float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
				float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
				float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
				float penetration = (ra + rb) - tl;
				if (penetration <= 0) { // no overlap
					one->collisionFlag = false;
					other->collisionFlag = false;
					return false;
				}
			}
		}
	}
	one->collisionFlag = true;
	other->collisionFlag = true;
	

	//std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());

	//collisionTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count());

	return true;

}

glm::vec3 Collider::GetMin()
{
	return glm::vec3();
}

glm::vec3 Collider::GetMax()
{
	return glm::vec3();
}

void Collider::render()
{
}

