#include "mySceneManager.h"
#include "mainScene.h"
#include "victoryScene.h"
#include "gameScene.h"

namespace vortex {
	Scene *MySceneManager::_loadScene(int sceneId, int sceneDataInt1) {
		if ((SceneTypeEnum)sceneId == MAIN_SCENE) {
			return new MainScene();
		}
		else if ((SceneTypeEnum)sceneId == GAME_SCENE) {
			return new GameScene(sceneDataInt1);
		}
		else if ((SceneTypeEnum)sceneId == VICTORY_SCENE) {
			return new VictoryScene(sceneDataInt1);
		}
		return nullptr;
	}
}