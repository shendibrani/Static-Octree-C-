

SphereCollider::SphereCollider(GameObject* pOwner) : Collider (pOwner)
{

}


SphereCollider::~SphereCollider()
{
}

bool SphereCollider::collidesWith(Collider * other)
{
	return false;
}

bool SphereCollider::collidesWith(AABB * other)
{
	return false;
}

bool SphereCollider::collidesWith(OBB * other)
{
	return false;
}

bool SphereCollider::collidesWith(SphereCollider * other)
{
	glm::vec3 vecDistance = _owner->getWorldPosition() - other->_owner->getWorldPosition();
	float distance = glm::pow(vecDistance.x, 2) + glm::pow(vecDistance.y, 2) + glm::pow(vecDistance.z, 2);

	float radiusLength = other->_radius + this->_radius;

	if (radiusLength < distance)
	{
		return true;
	}

	return false;
}
