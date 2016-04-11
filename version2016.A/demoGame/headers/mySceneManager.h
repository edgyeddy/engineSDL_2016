#pragma once
#include "sceneManager.h"

namespace vortex {
	class MySceneManager : public SceneManager {
	public:
		enum SceneTypeEnum {
			DEMO_SCENE
		};
	protected:
		virtual Scene *_loadScene(int sceneId);
	};
}
