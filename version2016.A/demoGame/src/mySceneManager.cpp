#include "mySceneManager.h"
#include "demoScene.h"

namespace vortex {
	Scene *MySceneManager::_loadScene(int sceneId) {
		if ((SceneTypeEnum)sceneId == DEMO_SCENE) {
			return new DemoScene();
		}
		return nullptr;
	}
}