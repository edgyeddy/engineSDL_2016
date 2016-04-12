#pragma once
#include "Scene.h"
#include "SDL.h"

namespace vortex {
	class DemoScene : public Scene {
	protected:
		SDL_Surface *mTextSurface;
		SDL_Surface *mBackgroundImage;
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		virtual void draw(SDL_Window *window, bool updateFramebuffer); //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
	};
}
