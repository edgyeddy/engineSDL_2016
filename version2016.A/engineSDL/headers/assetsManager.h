#pragma once
#include "IDisposableObject.h"
#include <SDL.h>
#include <map>
namespace vortex {
	//! Manages the (cached) bitmap assets.
	class AssetsManager : public IDisposableObject {
	protected:
		std::map<std::string, SDL_Surface *> mBitmapCache; //!< Bitmap cache. The surfaces are owned by this class.
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		//! AssetsManager is the owner of the surface
		SDL_Surface *getBitmapReference(const char *filename);
		//! AssetsManager is the owner of the surface
		inline SDL_Surface *getBitmapReference(std::string &filename) {
			return getBitmapReference(filename.c_str());
		}
	};
}
