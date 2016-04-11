#include "Scene.h"
#include "SDL.h"

namespace vortex {

	void Scene::_initialize() {
		// TODO
		mBackgroundColor.r = 255;
		mBackgroundColor.g = 0;
		mBackgroundColor.b = 255;
		mBackgroundColor.a = 255;

	}
	void Scene::_dispose() {
		// TODO
	}
	void Scene::onUserEvent(UserEventData *data) {
		// TODO
	}
	void Scene::resize(SDL_Window *window, int width, int height) {
		// TODO
	}
	void Scene::draw(SDL_Window *window, bool updateFramebuffer) {
		// TODO
		// begin fake
		
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b));
		SDL_UpdateWindowSurface(window);
		// end fake


	}
	void Scene::update(SDL_Window *window, int deltaMs) {
		// TODO
		mRatio += 0.0005f;
		if (mRatio < 0) { mRatio += 1;  }
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