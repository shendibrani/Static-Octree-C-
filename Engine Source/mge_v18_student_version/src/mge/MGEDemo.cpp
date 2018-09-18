#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/extended/Collider.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

#include "mge/extended/AABB.h"
#include "mge/extended/OBB.h"
#include "mge/extended/SphereCollider.h"

#include "mge/extended/OrbitingBehaviour.h"
#include <numeric>
//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
	//It's important to set same seed, same start for all.
	//displayWindow = true;
	srand(1);

}

void MGEDemo::runTest(int pNumberOfObjects, int pStaticChance, int pTreeHalfSize, int pTreeDepth)
{
	tree = new Octree(glm::vec3(0, 0, 0), glm::vec3(pTreeHalfSize, pTreeHalfSize, pTreeHalfSize), pTreeDepth, 0);
	_world->add(tree);
	_treeDepth = pTreeDepth;
	_treeHalfSize = pTreeHalfSize;
	_totalColliders = pNumberOfObjects;
	_staticChance = pStaticChance;
	std::cout << "\n" << "Starting test with " << pNumberOfObjects << " objects, " << pStaticChance << "% static. " << "T-Size: " << pTreeHalfSize * 2 << ". Depth: " << pTreeDepth << std::endl;
	
	glm::vec3 startVelocity = glm::vec3(0, 0, 0);
	float minSpeed = 0.1f;
	float maxSpeed = 0.3f;
	int staticPercent = pNumberOfObjects * pStaticChance / 100;

	for (int i = 0; i < pNumberOfObjects - staticPercent; i++)
	{
		srand(i);
		glm::vec3 position = glm::vec3((rand() % (int)tree->_halfSize.x * 2) - (int)tree->_halfSize.x, rand() % (int)tree->_halfSize.y * 2 - (int)tree->_halfSize.x, rand() % (int)tree->_halfSize.z * 2 - (int)tree->_halfSize.x);
		float currentSpeed = (maxSpeed - minSpeed) / 200 * i + minSpeed;

		GameObject* object = new GameObject("object1", position);

		if (i % 2 == 0)
		{
			object->setBehaviour(new RotatingBehaviour());
			object->setCollider(new OBB(glm::vec3(0, 0, 0), glm::vec3(rand() % 3 + 0.5f, rand() % 3 + 0.5f, rand() % 3 + 0.5f)));
		}
		else
		{
			object->setCollider(new AABB(glm::vec3(0, 0, 0), glm::vec3(rand() % 3 + 0.5f, rand() % 3 + 0.5f, rand() % 3 + 0.5f)));
		}

		object->isStatic = false;
		object->setVelocity(glm::vec3(currentSpeed, currentSpeed, currentSpeed));
		Colliders.push_back(object->_collider);
		tree->add(object->_collider);
	
		_world->add(object);
	}

	for (int i = 0; i < staticPercent; i++)
	{
		srand(i);
		glm::vec3 position = glm::vec3((rand() % (int)tree->_halfSize.x * 2) - (int)tree->_halfSize.x, (rand() % (int)tree->_halfSize.y * 2) - (int)tree->_halfSize.x, (rand() % (int)tree->_halfSize.z * 2) - (int)tree->_halfSize.x);
		float currentSpeed = (maxSpeed - minSpeed) / 200 * i + minSpeed;
		 
		GameObject* object = new GameObject("object1", position);

		if (i % 2 == 0) 
			object->setCollider(new AABB(glm::vec3(0, 0, 0), glm::vec3(rand() % 3 + 0.5f, rand() % 3 + 0.5f, rand() % 3 + 0.5f)));	
		else
		{
			object->setCollider(new OBB(glm::vec3(0, 0, 0), glm::vec3(rand() % 3 + 0.5f, rand() % 3 + 0.5f, rand() % 3 + 0.5f)));
			object->rotate(rand(), glm::vec3(rand(), rand(), rand()));
		}

		object->isStatic = true;
		Colliders.push_back(object->_collider);
		tree->addStatic(object->_collider);
		_world->add(object);
	}

}

void MGEDemo::finishTest()
{
	//std::cout << "average collision time: " << std::accumulate(Collider::collisionTimes.begin(), Collider::collisionTimes.end(), 0.0f) / Collider::collisionTimes.size() / 1000000.0f << std::endl; // in seconds, read more about std::chrono
	//Collider::collisionTimes.clear();
	Collider::collisionCheckCount = 0;
	_staticCollidedCount = 0;
	_frameCount = 0;
	_collidedCount = 0;
	_sumFPS = 0;

	for each(Collider* col in Colliders) {
		if (col->_owner->isStatic) {
			tree->removeStatic(col);
		}
		else {
		tree->remove(col);
		}
		_world->remove(col->_owner);
		delete col;
	}

	Colliders.clear();
	_world->remove(tree);
	delete tree;
}

void MGEDemo::startNextTest()
{
	_staticChance += 25;
	if (_staticChance > 100){
		_staticChance = 0;
		if (_totalColliders % 9 == 1 )
			_totalColliders *= 2.5f;
		else if (_totalColliders % 3 == 1)
			_totalColliders *= 4.0f;
		_hasFinishedTesting = _totalColliders > 10000 ? true : false;
	}
	
	if (_hasFinishedTesting == false)
	{
		if (_totalColliders > 999) 
		{ 
			_maxFrameCount = 200; 
			_treeHalfSize = 900;
			_treeDepth = 3;
			if (_totalColliders > 1000) {
			//	_treeHalfSize = 1250;
			//	_treeDepth = 4;
			}

		}
		runTest(_totalColliders, _staticChance, _treeHalfSize, _treeDepth);
	}
	else displayWindow = true;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    //MESHES
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load (config::MGE_MODEL_PATH + "sphere_smooth.obj");

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
 
    //SCENE SETUP

   //add camera first (it will be updated last)
	runTest(10, 0, 400, 2);
	camera = new Camera("camera", glm::vec3(0, 15, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	camera->setBehaviour(new OrbitingBehaviour(glm::vec3(0,0,0), 120.0f, 360.0f, 360.0f, 2.0f));
	_world->add(camera);
	_world->setMainCamera(camera);

}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
	
	//tree->renderTree(_world);
	pairs = tree->Collisions(nullptr);
	_collidedCount += pairs->size();

	if (!_hasFinishedTesting) 
	{
		_frameCount++;
		_sumFPS += _fps;
	}

	if (_frameCount >= _maxFrameCount)
	{
		std::cout << "In " << _frameCount << " Frames: Total Collision checks: " << Collider::collisionCheckCount <<
			", Total Collisions: " << _collidedCount  <<" Average FPS: " << _sumFPS / (float)_maxFrameCount << std::endl;

		finishTest();
		startNextTest();
	}

	int size = tree->_halfSize.x;
	
	for each (Collider* col in Colliders)
	{
		//when collider moves too positively.
		if (col->_owner->getLocalPosition().x > size )
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x - (size * 2), col->_owner->getLocalPosition().y, col->_owner->getLocalPosition().z));
		if (col->_owner->getLocalPosition().x < -size)
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x + (size * 2), col->_owner->getLocalPosition().y, col->_owner->getLocalPosition().z));

		if (col->_owner->getLocalPosition().y > size) 
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x, col->_owner->getLocalPosition().y - (size * 2), col->_owner->getLocalPosition().z));
		if( col->_owner->getLocalPosition().y < -size)
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x, col->_owner->getLocalPosition().y + (size * 2), col->_owner->getLocalPosition().z));

		if (col->_owner->getLocalPosition().z > size )
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x, col->_owner->getLocalPosition().y, col->_owner->getLocalPosition().z - (size * 2)));
		if(col->_owner->getLocalPosition().z < -size)
			col->_owner->setLocalPosition(glm::vec3(col->_owner->getLocalPosition().x, col->_owner->getLocalPosition().y, col->_owner->getLocalPosition().z + (size * 2)));
	}
	
	/*if (object1->_collider->collidesWith(object2->_collider)) {
		std::cout << "col";
	}*/
}

void MGEDemo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
