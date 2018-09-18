#include "OBB.h"


OBB::OBB(glm::vec3 pCenter, glm::vec3 pHalfSize) : Collider()
{
	_halfSize = pHalfSize;
	_center = pCenter;
	
}

OBB::~OBB()
{
}

bool OBB::collidesWith(Collider * other)
{
	return other->collidesWith(this);
}

bool OBB::collidesWith(AABB * other)
{
	return isColliding(other, this);
}

bool OBB::collidesWith(OBB * other)
{
	return isColliding(this, other);
}

glm::vec3 OBB::GetMin()
{
	return _center - _halfSize + _owner->getLocalPosition();
}

glm::vec3 OBB::GetMax()
{
	return _center + _halfSize + _owner->getLocalPosition();
}


void OBB::render()
{
	glLineWidth(1.0f);

	if (!collisionFlag)
		glColor3fv(glm::value_ptr(_noCollisionColor));
	else
		glColor3fv(glm::value_ptr(_collisionColor));
	
	glm::mat3 rotMat = _owner->getTransform();

	glm::vec3 localMin = GetMin() - _owner->getLocalPosition();
	glm::vec3 localMax = GetMax() - _owner->getLocalPosition();

	glm::vec3 rotatedCornerA = rotMat * glm::vec3(localMin.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerB = rotMat * glm::vec3(localMax.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerA.x, rotatedCornerA.y, rotatedCornerA.z);
	glVertex3f(rotatedCornerB.x, rotatedCornerB.y, rotatedCornerB.z);
	glEnd();

	glm::vec3 rotatedCornerC = rotMat * glm::vec3(localMin.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerD = rotMat * glm::vec3(localMax.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerC.x, rotatedCornerC.y, rotatedCornerC.z);
	glVertex3f(rotatedCornerD.x, rotatedCornerD.y, rotatedCornerD.z);
	glEnd();

	glm::vec3 rotatedCornerE = rotMat * glm::vec3(localMin.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerF = rotMat * glm::vec3(localMin.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerE.x, rotatedCornerE.y, rotatedCornerE.z);
	glVertex3f(rotatedCornerF.x, rotatedCornerF.y, rotatedCornerF.z);
	glEnd();

	glm::vec3 rotatedCornerG = rotMat * glm::vec3(localMax.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerH = rotMat * glm::vec3(localMax.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerG.x, rotatedCornerG.y, rotatedCornerG.z);
	glVertex3f(rotatedCornerH.x, rotatedCornerH.y, rotatedCornerH.z);
	glEnd();

	glm::vec3 rotatedCornerI = rotMat * glm::vec3(localMin.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerJ = rotMat * glm::vec3(localMax.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerI.x, rotatedCornerI.y, rotatedCornerI.z);
	glVertex3f(rotatedCornerJ.x, rotatedCornerJ.y, rotatedCornerJ.z);
	glEnd();

	glm::vec3 rotatedCornerK = rotMat * glm::vec3(localMin.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerL = rotMat * glm::vec3(localMax.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerK.x, rotatedCornerK.y, rotatedCornerK.z);
	glVertex3f(rotatedCornerL.x, rotatedCornerL.y, rotatedCornerL.z);
	glEnd();

	glm::vec3 rotatedCornerM = rotMat * glm::vec3(localMax.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerN = rotMat * glm::vec3(localMax.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerM.x, rotatedCornerM.y, rotatedCornerM.z);
	glVertex3f(rotatedCornerN.x, rotatedCornerN.y, rotatedCornerN.z);
	glEnd();

	glm::vec3 rotatedCornerO = rotMat * glm::vec3(localMin.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerP = rotMat * glm::vec3(localMin.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerO.x, rotatedCornerO.y, rotatedCornerO.z);
	glVertex3f(rotatedCornerP.x, rotatedCornerP.y, rotatedCornerP.z);
	glEnd();

	glm::vec3 rotatedCornerR = rotMat * glm::vec3(localMin.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerS = rotMat * glm::vec3(localMin.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerR.x, rotatedCornerR.y, rotatedCornerR.z);
	glVertex3f(rotatedCornerS.x, rotatedCornerS.y, rotatedCornerS.z);
	glEnd();

	glm::vec3 rotatedCornerT = rotMat * glm::vec3(localMin.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerU = rotMat * glm::vec3(localMin.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerT.x, rotatedCornerT.y, rotatedCornerT.z);
	glVertex3f(rotatedCornerU.x, rotatedCornerU.y, rotatedCornerU.z);
	glEnd();

	glm::vec3 rotatedCornerV = rotMat * glm::vec3(localMax.x, localMax.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerW = rotMat * glm::vec3(localMax.x, localMax.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerV.x, rotatedCornerV.y, rotatedCornerV.z);
	glVertex3f(rotatedCornerW.x, rotatedCornerW.y, rotatedCornerW.z);
	glEnd();

	glm::vec3 rotatedCornerX = rotMat * glm::vec3(localMax.x, localMin.y, localMax.z) + _owner->getLocalPosition();
	glm::vec3 rotatedCornerY = rotMat * glm::vec3(localMax.x, localMin.y, localMin.z) + _owner->getLocalPosition();
	glBegin(GL_LINES);
	glVertex3f(rotatedCornerX.x, rotatedCornerX.y, rotatedCornerX.z);
	glVertex3f(rotatedCornerY.x, rotatedCornerY.y, rotatedCornerY.z);
	glEnd();
}