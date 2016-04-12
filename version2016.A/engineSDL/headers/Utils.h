#pragma once
#include "SDL.h"
#include "Rectangle.h"
#include <string>
#include <fstream>

namespace vortex {

#define MINIMUM(x,y) (((x)<(y))?(x):(y))
#define MAXIMUM(x,y) (((x)>(y))?(x):(y))

	//! Provides several SDL-related utility functions.
	class SDLUtils {
	public:
		//! Reads the contents of a file to a std::string
		static inline std::string readFileToString(std::string &filename) {
			// http://insanecoding.blogspot.com.es/2011/11/how-to-read-in-file-in-c.html

			std::ifstream in(filename, std::ios::in | std::ios::binary);
			if (in)
			{
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize((unsigned int)(in.tellg()));
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				return(contents);
			}
			throw(errno);
		}

		//! Renders input surface to a window in the giving top-left position.
		static void renderSurfaceToWindow(SDL_Window *window, SDL_Surface *surfaceSurface, Rectangle &targetRect) {
			SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
			SDL_BlitSurface(surfaceSurface, nullptr, windowSurface, &targetRect.Rect);
		}
	};
}
