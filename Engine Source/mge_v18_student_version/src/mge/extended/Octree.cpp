#include "Octree.h"

#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include <algorithm>


int Octree::_count = 0;

Octree::Octree(glm::vec3 pPosition, glm::vec3 pHalfSize, int pLevel, Octree* pRoot) : AABB (pPosition, pHalfSize), GameObject("Octree", pPosition)
{
	pRoot != nullptr ? _root = pRoot : _root = this;  // given root or be root to self
	_level = pLevel;
	_center = pPosition;
	_halfSize = pHalfSize;
	_id = Octree::_count++;
	
	scale(_halfSize);
	if (_level == 0) isLeaf = true;
	if (!isLeaf)
	{
		glm::vec3 childHalfSize = _halfSize / 2;

		_children.push_back(new Octree(_center + childHalfSize / 2, childHalfSize , _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(+childHalfSize.x, +childHalfSize.y, -childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(+childHalfSize.x, -childHalfSize.y, +childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(-childHalfSize.x, +childHalfSize.y, +childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(+childHalfSize.x, -childHalfSize.y, -childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(-childHalfSize.x, -childHalfSize.y, +childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center + glm::vec3(-childHalfSize.x, +childHalfSize.y, -childHalfSize.z) / 2, childHalfSize, _level - 1, this->_root));
		_children.push_back(new Octree(_center - childHalfSize / 2, childHalfSize, _level - 1, this->_root));
		
	}
}

Octree::~Octree()
{
}

bool Octree::add(Collider * collider)
{
	//Add objects to octree's children
	if (!isLeaf)
	{
		glm::vec3 max = collider->GetMax();
		glm::vec3 min = collider->GetMin();

		if (max.x < _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[7]->add(collider); // - - -
				}
				else if (min.z > _center.z) {
					return _children[5]->add(collider); // - - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[6]->add(collider); // - + -
				}
				else if (min.z > _center.z) {
					return _children[3]->add(collider); // - + +
				}
			}
		}
		else if (min.x > _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[4]->add(collider); // + - -
				}
				else if (min.z > _center.z) {
					return _children[2]->add(collider); // + - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[1]->add(collider); // + + -
				}
				else if (min.z > _center.z) {
					return _children[0]->add(collider); // + + +
				}
			}
		}
	}
	
	_objects.push_back(collider);
	return this;
}

bool Octree::addStatic(Collider * collider)
{
	if (!isLeaf)
	{
		glm::vec3 max = collider->GetMax();
		glm::vec3 min = collider->GetMin();

		if (max.x < _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[7]->addStatic(collider); // - - -
				}
				else if (min.z > _center.z) {
					return _children[5]->addStatic(collider); // - - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[6]->addStatic(collider); // - + -
				}
				else if (min.z > _center.z) {
					return _children[3]->addStatic(collider); // - + +
				}
			}
		}
		else if (min.x > _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[4]->addStatic(collider); // + - -
				}
				else if (min.z > _center.z) {
					return _children[2]->addStatic(collider); // + - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[1]->addStatic(collider); // + + -
				}
				else if (min.z > _center.z) {
					return _children[0]->addStatic(collider); // + + +
				}
			}
		}
	}

	_staticObjects.push_back(collider);
	return this;
}


bool Octree::remove(Collider * collider)
{
	//Remove objects from octree's children
	if (!isLeaf)
	{
		glm::vec3 max = collider->GetMax();
		glm::vec3 min = collider->GetMin();
	
		if (max.x < _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[7]->remove(collider); // - - -
				}
				else if (min.z > _center.z) {
					return _children[5]->remove(collider); // - - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[6]->remove(collider); // - + -
				}
				else if (min.z > _center.z) {
					return _children[3]->remove(collider); // - + +
				}
			}
		}

		else if (min.x > _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[4]->remove(collider); // + - -
				}
				else if (min.z > _center.z) {
					return _children[2]->remove(collider); // + - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[1]->remove(collider); // + + -
				}
				else if (min.z > _center.z) {
					return _children[0]->remove(collider); // + + +
				}
			}
		}
	}

	//get index of our obj
	int index;
	int size = _objects.size();
	for (int i = 0; i < size; i++)
	{
		if (collider == _objects[i])
		{
			index = i;
		}
	}
	
	//erase obj
	_objects.erase(_objects.begin() + index);
	return this;
}

bool Octree::removeStatic(Collider * pCollider)
{
	if (!isLeaf)
	{
		glm::vec3 max = pCollider->GetMax();
		glm::vec3 min = pCollider->GetMin();

		if (max.x < _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[7]->removeStatic(pCollider); // - - -
				}
				else if (min.z > _center.z) {
					return _children[5]->removeStatic(pCollider); // - - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[6]->removeStatic(pCollider); // - + -
				}
				else if (min.z > _center.z) {
					return _children[3]->removeStatic(pCollider); // - + +
				}
			}
		}

		else if (min.x > _center.x) {
			if (max.y < _center.y) {
				if (max.z < _center.z) {
					return _children[4]->removeStatic(pCollider); // + - -
				}
				else if (min.z > _center.z) {
					return _children[2]->removeStatic(pCollider); // + - +
				}
			}
			else if (min.y > _center.y) {
				if (max.z < _center.z) {
					return _children[1]->removeStatic(pCollider); // + + -
				}
				else if (min.z > _center.z) {
					return _children[0]->removeStatic(pCollider); // + + +
				}
			}
		}
	}

	//get index of our obj
	int index;
	int size = _staticObjects.size();
	for (int i = 0; i < size; i++)
	{
		if (pCollider == _staticObjects[i])
		{
			index = i;
		}
	}

	//erase obj
	_staticObjects.erase(_staticObjects.begin() + index);
	return this;
}

std::vector<Pair*>* Octree::Collisions(std::vector<Pair*>* pairs)
{
	if (pairs == nullptr) {
		pairs = new std::vector<Pair*>;
	}

	int objSize1 = _objects.size();
	int staticObjSize1 = _staticObjects.size();
	for (int a = 0; a < objSize1; a++) 
	{
		Collider* one = _objects[a];
		
		for (int b = a + 1; b < objSize1; b++)
		{
			Collider* other = _objects[b];
			
			if (one->collidesWith(other)) {
				Pair * newPair = new Pair();
				newPair->one = one;
				newPair->other = other;
				pairs->push_back(newPair);
			}
		}
		
		//check dynamic colliders against static colliders
		for (int b = 0; b < staticObjSize1; b++)
		{
			Collider* other = _staticObjects[b];

			if (one->collidesWith(other)) {

				Pair * newPair = new Pair();
				newPair->one = one;
				newPair->other = other;
				pairs->push_back(newPair);
			}
		}

		if (!isLeaf) {
			/*for each(Octree* child in _children) {
				child->Collides(pairs, one);
			}*/
			for (int i = 0; i < 8; i++) {
				_children[i]->Collides(pairs, one);
			}
		}
	}

	if (!isLeaf)
	{
		//check collisions in all child quads
		/*for each(Octree* child in _children) {
			child->Collisions(pairs);
		}*/
		for (int i = 0; i < 8; i++) {
			_children[i]->Collisions(pairs);
		}
	}

	return pairs;
}

bool Octree::Collides(std::vector<Pair *>* pPair, Collider * one)
{
	int size = _objects.size();
	for (int b = 0; b < size; b++) {
		Collider* other = _objects[b];
		if (one->collidesWith(other)) {
			Pair * newPair = new Pair();
			newPair->one = one;
			newPair->other = other;
			pPair->push_back(newPair);
		}
	}

	if (!isLeaf) { // very unoptimized....
		/*for each(Octree* child in _children) {
			child->Collides(pPair, one);
		}*/
		for (int i = 0; i < 8; i++) {
			_children[i]->Collides(pPair, one);
		}
	}
	return false;
}


void Octree::print(std::string prefix)
{
	std::cout << prefix;
}

glm::vec3 Octree::GetMin()
{
	return _center - _halfSize + getLocalPosition();
}

glm::vec3 Octree::GetMax()
{
	return _center + _halfSize + getLocalPosition();
}

void Octree::update(float pStep)
{
	std::vector<Collider*> objClone(_objects);
	
	_objects.clear();

	for each(Collider * obj in objClone)
	{
		_root->add(obj);
	}


	if (!isLeaf) {
		for (int i = 0; i < 8; i++) {
			_children[i]->update(pStep);
		}
	}
}

void Octree::renderTree(World* pWorld) {
	glUseProgram(0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::inverse(pWorld->getMainCamera()->getWorldTransform())));
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(pWorld->getMainCamera()->getProjection()));
	renderTree();
}

void Octree::renderTree() {
	for each(Collider* col in _objects) {
			col->render();
	}

	for each(Collider* col in _staticObjects) {
			col->render();
	}

	if (_objects.size() == 0 && _staticObjects.size() == 0) {
		glColor3fv(glm::value_ptr(_noCollisionColorTree));
		glLineWidth(1);
	}
	else {
		glColor3fv(glm::value_ptr(_collisionColorTree));
		glLineWidth(3);
	}
	
	glm::vec3 _min = GetMin();
	glm::vec3 _max = GetMax();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _min.y, _min.z);
	glVertex3f(_max.x, _min.y, _min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _min.y, _min.z);
	glVertex3f(_min.x, _max.y, _min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _min.y, _min.z);
	glVertex3f(_min.x, _min.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_max.x, _max.y, _max.z);
	glVertex3f(_min.x, _max.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_max.x, _max.y, _max.z);
	glVertex3f(_max.x, _min.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_max.x, _max.y, _max.z);
	glVertex3f(_max.x, _max.y, _min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_max.x, _min.y, _min.z);
	glVertex3f(_max.x, _max.y, _min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_max.x, _min.y, _min.z);
	glVertex3f(_max.x, _min.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _max.y, _min.z);
	glVertex3f(_max.x, _max.y, _min.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _max.y, _min.z);
	glVertex3f(_min.x, _max.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _min.y, _max.z);
	glVertex3f(_max.x, _min.y, _max.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(_min.x, _min.y, _max.z);
	glVertex3f(_min.x, _max.y, _max.z);
	glEnd();

	int childCount = _children.size();
	for (int i = 0; i < childCount; ++i) {
		_children[i]->renderTree();
	}

}




