#include "sceneManager.h"

namespace vortex {
	void SceneManager::_dispose() {
		unloadScene();
	}
	void SceneManager::_initialize() {
		// TODO
	}
	void SceneManager::unloadScene() {
		mCurrentScene = static_cast<Scene*>(DELETE_OBJECT(mCurrentScene));
	}
	bool SceneManager::hasScene() {
		return (mCurrentScene != nullptr);
	}
	Scene *SceneManager::getCurrentScene() {
		if (mCurrentScene == nullptr) { throw Exception("Current scene is NULL"); }
		return mCurrentScene;
	}
	Scene *SceneManager::loadScene(int sceneType, int sceneDataInt1) {
		// Unload previous scene
		unloadScene();
		// Load new scene
		mCurrentScene = _loadScene(sceneType, sceneDataInt1);
		if (mCurrentScene == nullptr) {
			throw Exception("Scene is NULL");
		}
		if (mCurrentScene != nullptr) {
			// TODO: GameMaster::getInstance()->getGameState()->onEnterScene(); // Before init!
			mCurrentScene->initialize();
		}
		return mCurrentScene;
	}
}