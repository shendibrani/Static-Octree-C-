#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

class OrbitingBehaviour : public AbstractBehaviour
{
public:
	OrbitingBehaviour(glm::vec3 target, float radius, float rotationLimitX, float rotationLimitY, float rotationSpeed);
	virtual void update(float step);
	~OrbitingBehaviour();
private:
	glm::vec3 _target;
	float _radius;
	float _rotLimitX;
	float _rotLimitY;
	float _rotSpeed;
	float yaw = 0.0f;
	float pitch = 0.0f;
	glm::vec2 prevMousePos;
	glm::vec2 GetMouseOffset();
};