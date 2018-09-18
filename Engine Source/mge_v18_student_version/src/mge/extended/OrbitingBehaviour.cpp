#include "mge/extended/OrbitingBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "SFML\Window.hpp"
// LM15083245
OrbitingBehaviour::OrbitingBehaviour(glm::vec3 target, float radius, float rotationLimitX, float rotationLimitY, float rotationSpeed)
	: AbstractBehaviour(), _target(target), _radius(radius), _rotLimitX(rotationLimitX), _rotLimitY(rotationLimitY), _rotSpeed(rotationSpeed)
{
	prevMousePos = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

void OrbitingBehaviour::update(float step)
{
	glm::vec2 mouseOffset = GetMouseOffset() * _rotSpeed;

	yaw += mouseOffset.x;
	pitch += mouseOffset.y;

	//Check limits
	//x
	if (_rotLimitX != 0) {
		if (yaw > _rotLimitX)
			yaw = _rotLimitX;
		if (yaw < -_rotLimitX)
			yaw = -_rotLimitX;
	}

	//y
	if (_rotLimitY != 0) {
		if (pitch > _rotLimitY)
			pitch = _rotLimitY;
		if (pitch < -_rotLimitY)
			pitch = -_rotLimitY;
	}

	glm::vec3 newPos;

	newPos.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	newPos.y = sin(glm::radians(pitch));
	newPos.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	newPos = glm::normalize(newPos) * _radius;

	_owner->setTransform(glm::translate(_target + newPos));
	_owner->setTransform(glm::inverse(glm::lookAt(_owner->getLocalPosition(), _target, glm::vec3(0, 1, 0))));
}

glm::vec2 OrbitingBehaviour::GetMouseOffset()
{
	glm::vec2 mousePos = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	//Non zero check
	if (mousePos.x - prevMousePos.x == 0 && mousePos.y - prevMousePos.y == 0)
		return glm::vec2(0, 0);

	glm::vec2 offset = glm::normalize(mousePos - prevMousePos);
	prevMousePos = mousePos;

	//std::cout << "X: " + std::to_string(offset.x) + "; " + "Y: " + std::to_string(offset.y) << std::endl;

	return offset;
}

OrbitingBehaviour::~OrbitingBehaviour()
{

}