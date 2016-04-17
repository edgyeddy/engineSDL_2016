#pragma once
#include "gameMain.h"
#include "sceneManager.h"

namespace vortex {
	class MySceneManager : public SceneManager {
	public:
		enum SceneEventsEnum {
			USER_EVENT_CHANGE_BACKGROUND = GameMain::EventTypeEnum::USER_EVENTS_BASE_INDEX,
			USER_EVENT_RESTART_LEVEL,
			USER_EVENT_NEXT_LEVEL,
			USER_EVENT_NEXT_FRAGMENT,
			USER_EVENT_NEXT_FRAGMENT_REQUEST,
			USER_EVENT_SHAPESHIFT_REQUEST,
			USER_EVENT_SHOW_END_LEVEL_FX
		};
		enum SceneTypeEnum {
			MAIN_SCENE,
			GAME_SCENE,
			VICTORY_SCENE
		};
	protected:
		virtual Scene *_loadScene(int sceneId, int sceneDataInt1) override;
	};
}
