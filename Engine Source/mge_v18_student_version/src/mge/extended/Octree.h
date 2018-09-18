#pragma once

#include <iostream>
#include <vector>
#include "Collider.h"
#include "AABB.h"
#include "glm.hpp"
#include <GL/glew.h>


class Pair {
public:
	Collider* one;
	Collider* other;

};

class Octree : public AABB, public GameObject
{
public:
	Octree(glm::vec3 pCenter, glm::vec3 pHalfSize, int pLevel, Octree* pRoot);
	~Octree();

	static int removeCount;
	static int collidesCount;
	static int boxCollidesCount;

	static int _count;

	std::vector<Octree*> _children;
	std::vector<Collider *> _objects;
	std::vector<Collider*> _staticObjects;

	std::vector<Pair*>* Collisions(std::vector<Pair*>* pairs = nullptr);
	void renderTree(World* pWorld);
	void update(float pStep) override;

	bool add(Collider* pCollider);
	bool addStatic(Collider* pCollider);
	bool remove(Collider* pCollider);
	bool removeStatic(Collider* pCollider);

private :
	int _level;
	int _id;

	glm::vec3 _center;
	Octree* _root;

	bool Collides(std::vector<Pair*>* pPair, Collider* pCol);
	bool isLeaf = false;
	void print(std::string prefix = "");
	
	void renderTree();

	glm::vec3 GetMin() override;
	glm::vec3 GetMax() override;
	
	glm::vec3 _collisionColorTree = glm::vec3(1, 0, 0);
	glm::vec3 _noCollisionColorTree = glm::vec3(1, 1, 0);
};

