#pragma once
#include "sceneManager.h"

namespace vortex {
	class MySceneManager : public SceneManager {
	public:
		enum SceneTypeEnum {
			MAIN_SCENE
		};
	protected:
		virtual Scene *_loadScene(int sceneId);
	};
}
