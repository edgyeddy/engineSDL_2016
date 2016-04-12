#include "assetsManager.h"
namespace vortex {
	void AssetsManager::_initialize() {
		// NOOP
	}
	void AssetsManager::_dispose() {
		// Delete all owned surfaces in the cache
		for (std::map<std::string, SDL_Surface *>::const_iterator it = mBitmapCache.cbegin(); it != mBitmapCache.cend(); it++) {
			std::string file = (*it).first;
			Logger::d(std::string("Releasing bitmap named: ") + file);
			SDL_Surface *item = (*it).second;
			SDL_FreeSurface(item);
		}
		mBitmapCache.clear();
	}

	SDL_Surface *AssetsManager::getBitmapReference(const char *filename) {
		SDL_Surface *surface;
		auto it = mBitmapCache.find(filename);
		if (it != mBitmapCache.end()) {
			// Found
			surface = (*it).second;
		}
		else {
			// Not found
			Logger::d(std::string("Loading bitmap named: ") + filename);
			surface = SDL_LoadBMP(filename);
			mBitmapCache.insert(std::pair<std::string, SDL_Surface*>(filename, surface));
		}
		return surface;
	}
}