#pragma once
#include "SDL.h"
namespace vortex {
	class IDrawable {
	public:
		//! Apply resizing to this drawable entity. Must be re-implemented in derived class.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) = 0;
		//! Draw to the window this drawable entity. Must be re-implemented in derived class.
		virtual void draw(SDL_Window *window) = 0; 											
		//! Apply a time interval to this drawable entity. Must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs) = 0;
	};
}
