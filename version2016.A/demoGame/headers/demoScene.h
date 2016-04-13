#pragma once
#include "Scene.h"
#include "SDL.h"
#include "Rectangle.h"

namespace vortex {
	class DemoScene : public Scene {
	protected:
		Rectangle mTextScreenPosition;
		Rectangle mBackgroundImageScreenPosition;
		
		SDL_Surface *mTextSurface; //!< Owned by this class
		SDL_Surface *mBackgroundImage; //!< Owned by this class
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override; //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
	};
}
