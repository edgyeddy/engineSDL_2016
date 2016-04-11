#include "gameMain.h"
#include "SDL.h"

namespace vortex {
	GameMain *GameMain::sInstance = nullptr;

	GameMain::GameMain() {
	}
	GameMain *GameMain::getInstance() {
		if (GameMain::sInstance == nullptr) {
			GameMain::sInstance = new GameMain();
		}
		return GameMain::sInstance;
	}
}