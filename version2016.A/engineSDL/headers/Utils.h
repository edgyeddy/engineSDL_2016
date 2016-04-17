#pragma once
#include "SDL.h"
#include "Rectangle.h"
#include "SDL2_rotozoom.h"
#include <string>
#include <fstream>
#include "gameMain.h"
#include "json/json.h"

namespace vortex {

#define MINIMUM(x,y) (((x)<(y))?(x):(y))
#define MAXIMUM(x,y) (((x)>(y))?(x):(y))

	//! Provides several SDL-related utility functions.
	class SDLUtils {
	public:
		static inline bool fileExists(const std::string &filename) {
			// URL = http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
			struct stat buffer;
			return (stat(filename.c_str(), &buffer) == 0);
		}
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
		
		//! Loads a JSON from a file and returns its root value (and its tree undernead)
		static Json::Value loadJson(std::string &jsonFile);


		static inline SDL_Surface* createSurface(int width, int height)
		{
			// URL = http://stackoverflow.com/questions/20174467/sdl-draw-a-half-transparent-rectangle
			uint32_t rmask, gmask, bmask, amask;

			/* SDL interprets each pixel as a 32-bit number, so our masks must depend
			on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
#endif

			SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
			if (surface == nullptr)
			{
				std::ostringstream oss;
				oss << TR("CreateRGBSurface failed SDL_Error: ") << SDL_GetError();
				Logger::e(oss.str());
			}

			return surface;
		}
		static inline void renderColorRectangleToSurface(const Color4 &colRGBA, Rectangle &rect, SDL_Surface *targetSurface, bool applyAlphaBlending) {
			if (applyAlphaBlending) {
				SDL_Surface *tmp = SDLUtils::createSurface(rect.Rect.w, rect.Rect.h);
				(void)SDL_FillRect(tmp, nullptr, colRGBA.toInt32());

				SDL_BlitSurface(tmp, nullptr, targetSurface, &rect.Rect);
				SDL_FreeSurface(tmp);
			}
			else {
				SDL_FillRect(targetSurface, &rect.Rect, SDL_MapRGBA(targetSurface->format, colRGBA.Color.r, colRGBA.Color.g, colRGBA.Color.b, colRGBA.Color.a));
			}
		}
	};
}
