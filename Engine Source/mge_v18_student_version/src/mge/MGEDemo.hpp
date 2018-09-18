#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "mge/core/AbstractGame.hpp"
#include <time.h>
#include <random>
#include "mge/extended/Octree.h"
#include "mge/core/Camera.hpp"
class DebugHud;
class GameObject;
/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS
	public:
		MGEDemo();
		virtual ~MGEDemo();
		GameObject* object1;
		GameObject* object2;
		Octree* tree;
        //override initialize so we can add a DebugHud
        virtual void initialize();
		void runTest(int pNumberOfObjects, int pStaticChance, int pTreeHalfSize, int pTreeDepth);
		void finishTest();
		void startNextTest();
	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();
		std::vector<Collider*> Colliders;
		
	    //override render to render the hud as well.
	    virtual void _render();
		
		std::vector<Pair*>* pairs;
		std::vector<Pair*>* staticPairs;
	private:
		DebugHud* _hud;                   //hud display
		
		Camera* camera;
        void _updateHud();
		int _treeDepth = 2;
		int _treeHalfSize = 400;
		int _collidedCount = 0;
		int _staticCollidedCount = 0;
		int _frameCount = 0;
		float _sumFPS = 0;
		int _maxFrameCount = 500;
		int _staticChance = 0;
		int _totalColliders = 10;
		bool _hasFinishedTesting = false;
        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
