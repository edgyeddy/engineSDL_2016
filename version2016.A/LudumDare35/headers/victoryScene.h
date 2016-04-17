#pragma once
#include "Scene.h"
#include "SDL.h"
#include "Rectangle.h"
#include "gameMain.h"

namespace vortex {
	class VictoryScene : public Scene {
	public:
	protected:
		int mScore = 0;
		Rectangle::RectangleAdjustEnum mBackgroundMode = Rectangle::RectangleAdjustEnum::ADJUST_OUTSIDE;
		Rectangle mBackgroundImageScreenPosition;
		SDL_Surface *mBackgroundImage; //!< Not owned by this class
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		bool onKeyPressedEvent(int keyId) override;
		VictoryScene(int finalScore) : Scene() {
			// NOOP
			mScore = finalScore;
		}
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override; //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
	};
}
