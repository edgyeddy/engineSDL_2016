#pragma once
#include "SDL.h"
#include "Rectangle.h"
#include "SDL2_rotozoom.h"
#include <string>
#include <fstream>
#include "gameMain.h"

namespace vortex {

#define MINIMUM(x,y) (((x)<(y))?(x):(y))
#define MAXIMUM(x,y) (((x)>(y))?(x):(y))

	//! Provides several SDL-related utility functions.
	class SDLUtils {
	public:
		//! Compute the delta distance from speed and delta time.
		static inline float computeDelta(float speed_units_per_ms, int time_ms) {
			// Speed = distance / time
			// distance = speed * time
			return (speed_units_per_ms * time_ms);
		}
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
		static void renderSurfaceToWindow(SDL_Window *window, SDL_Surface *surfaceSurface, const Rectangle &targetRect) {
			SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
			SDL_Rect rect = targetRect.Rect;
			SDL_BlitSurface(surfaceSurface, nullptr, windowSurface, &rect);
		}
		//! Given an original surface and a (optional) scaled image, generates (or reuses) a scaled image to match the target size.
		static SDL_Surface *scaleSurfaceIfNeeded(SDL_Surface *originalSurface, SDL_Surface *scaledSurface, int targetWidth, int targetHeight, const std::string &debugName, bool useAssetsManager = true);
		
	};
}
