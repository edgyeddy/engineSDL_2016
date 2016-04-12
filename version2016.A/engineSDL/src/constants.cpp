#include "constants.h"
#include <SDL.h>

namespace vortex {
	const char *Constants::DEFAULT_FONT_PATH = "resources/ARIAL.TTF";
	const int Constants::SCREEN_FLAGS_WINDOWED = SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_RESIZABLE;
	const int Constants::SCREEN_FLAGS_FULLSCREEN = SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_FULLSCREEN;
}