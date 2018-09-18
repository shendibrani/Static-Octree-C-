#include "AABB.h"
#include <string>;

AABB::AABB(glm::vec3 pCenter, glm::vec3 pHalfSize) : Collider()
{
	_halfSize = pHalfSize ;
	_center = pCenter;
	
}

AABB::~AABB()
{
}

bool AABB::collidesWith(Collider * other) {
	return other->collidesWith(this);
}

bool AABB::collidesWith(AABB * other) {
	return isColliding(this, other);
}

bool AABB::collidesWith(OBB * other) {
	return isColliding(this, other);
}

glm::vec3 AABB::GetMin()
{
	return _center - _halfSize + _owner->getLocalPosition();
}

glm::vec3 AABB::GetMax()
{
	return _center + _halfSize + _owner->getLocalPosition();
}

void AABB::render()
{
	glLineWidth(1.0f);

	if (!collisionFlag)
		glColor3fv(glm::value_ptr(_noCollisionColor));
	else
		glColor3fv(glm::value_ptr(_collisionColor));

	glm::vec3 min = GetMin();
	glm::vec3 max = GetMax();

	glBegin(GL_LINES);
	glVertex3f(min.x, GetMax().y, max.z);
	glVertex3f(max.x, max.y, max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(max.x, min.y, max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, max.y, max.z);
	glVertex3f(min.x, min.y, max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(max.x, min.y, max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(max.x, max.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, min.y, min.z);
	glVertex3f(max.x, min.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(max.x, max.y, min.z);
	glVertex3f(max.x, min.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(min.x, min.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, max.y, max.z);
	glVertex3f(min.x, max.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, min.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(max.x, max.y, min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, min.y, min.z);
	glEnd();
}

