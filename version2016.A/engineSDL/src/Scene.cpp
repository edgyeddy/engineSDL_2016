#include "Scene.h"
#include "SDL.h"
#include "Utils.h"

namespace vortex {

	void Scene::_initialize() {
		// TODO
		mBackgroundColor.r = 255;
		mBackgroundColor.g = 0;
		mBackgroundColor.b = 255;
		mBackgroundColor.a = 255;

		mUiManager = new UiManager();
		mUiManager->initialize();
	}
	void Scene::_dispose() {
		// TODO
		mUiManager = static_cast<UiManager*>(DELETE_OBJECT(mUiManager));
	}
	void Scene::resize(SDL_Window *windowOldSize, int width, int height) {
		// TODO
		mUiManager->resize(windowOldSize, width, height);
	}
	void Scene::drawFront(SDL_Window *window, bool updateFramebuffer) {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		// Draw UI overlay
		mUiManager->draw(window);
	}
	void Scene::drawBack(SDL_Window *window, bool updateFramebuffer) {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		// Draw background
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b));
	}
	void Scene::draw(SDL_Window *window, bool updateFramebuffer) {
		/*
		// Draw buffer
		if (updateFramebuffer) {
			SDL_UpdateWindowSurface(window);
		}
		*/
	}
	void Scene::update(SDL_Window *window, int deltaMs) {
		
		mUiManager->update(window, deltaMs);
		// TODO : Adjust to framerate
		mRatio += SDLUtils::computeDelta(0.0002f, deltaMs);
		if (mRatio < 0) { mRatio += 1; }
		else if (mRatio > 1) { mRatio -= 1; }

		mBackgroundColor.r = (Uint8)(mRatio * 255.0f);
		if (mRatio < 0.5) {
			mBackgroundColor.g = (Uint8)(mRatio * 2 * 255.0f);
		}
		else {
			mBackgroundColor.g = (Uint8)((1.0f - mRatio) * 2 * 255.0f);
		}
		mBackgroundColor.b = (Uint8)((1.0f - mRatio) * 255.0f);
	}
}