#include "mySceneManager.h"
#include "mainScene.h"

namespace vortex {
	Scene *MySceneManager::_loadScene(int sceneId) {
		if ((SceneTypeEnum)sceneId == MAIN_SCENE) {
			return new MainScene();
		}
		return nullptr;
	}
}