#include "assetsManager.h"
namespace vortex {
	int AssetsManager::sSerialNextId = 0;

	void AssetsManager::_initialize() {
		// NOOP
	}
	void AssetsManager::_dispose() {
		// Delete all owned surfaces in the cache
		std::ostringstream oss;
		for (std::map<std::string, AssetEntry>::const_iterator it = mBitmapCache.cbegin(); it != mBitmapCache.cend(); it++) {
			std::string file = (*it).first;
			oss.str("");
			oss << TR("Dispose bitmap=") << file << " debugName=" << (*it).second.debugName << " serial=" << (*it).second.serialId << " users=" << (*it).second.numUsers;
			Logger::d(oss.str());
			SDL_Surface *item = (*it).second.surface;
			SDL_FreeSurface(item);
		}
		oss.str("");
		oss << TR("===================> Num bitmaps still active=") << getNumBitmaps();
		Logger::d(oss.str());
		mBitmapCache.clear();
	}
	void AssetsManager::addBitmapReferenceFromMemory(std::string &uniqueName, SDL_Surface *memorySurface, const std::string &debugName) {
		// Assume asset not present
		auto it = mBitmapCache.find(uniqueName);
		if (it != mBitmapCache.end()) {
			// Found
			std::ostringstream oss;
			oss << "addBitmapReferenceFromMemory() : Memory asset named " << uniqueName << " already found!";
			Logger::w(oss.str());
			return;
		}

		// Not found
		Logger::d(std::string("Loading memory bitmap named ") + uniqueName);
		AssetEntry entry;
		entry.serialId = AssetsManager::sSerialNextId++;
		entry.surface = memorySurface;
		entry.numUsers = 1;
		entry.debugName = debugName;
		mBitmapCache.insert(std::pair<std::string, AssetEntry>(uniqueName, entry));
	}
	AssetsManager::ForgetBitmapResultEnum AssetsManager::forgetBitmapReference(std::string &uniqueName) {
		// Decrease num-references.
		// If num-references == 0, dispose bitmap

		// Assume asset present
		auto it = mBitmapCache.find(uniqueName);
		if (it == mBitmapCache.end()) {
			// Not Found
			std::ostringstream oss;
			oss << "forgetBitmapReference() : Memory asset named " << uniqueName << " not found!";
			Logger::w(oss.str());
			//throw Exception("Not found memory bitmap asset with this name!");
			return ForgetBitmapResultEnum::ERROR_NOT_FOUND;
		}
		// Decrease refs
		(*it).second.numUsers--;
		// Release if needed
		if ((*it).second.numUsers <= 0) {
			//Logger::w("DISPOSE " + (*it).second.serialId);
			Logger::d(std::string("Dispose memory bitmap named ") + uniqueName);
			SDL_Surface *item = (*it).second.surface;
			SDL_FreeSurface(item);
			mBitmapCache.erase(uniqueName);
			return ForgetBitmapResultEnum::BITMAP_HAS_BEEN_DISPOSED;
		}
		return ForgetBitmapResultEnum::BITMAP_STILL_IN_USE;
	}
	SDL_Surface *AssetsManager::getBitmapReferenceFromMemoryOrNull(const char *uniqueName) {
		SDL_Surface *surface;
		auto it = mBitmapCache.find(uniqueName);
		if (it != mBitmapCache.end()) {
			// Found
			surface = (*it).second.surface;
			(*it).second.numUsers++;
			//Logger::w("HIT" + (*it).second.serialId);
			return surface;
		}
		else {
			// Not found
			Logger::w(std::string("getBitmapReferenceFromMemory() : Not found memory bitmap named ") + uniqueName);
			return nullptr;
		}
	}
	SDL_Surface *AssetsManager::getBitmapReferenceFromFile(const char *filename, bool updateUsers, const std::string &debugName) {
		SDL_Surface *surface;
		auto it = mBitmapCache.find(filename);
		if (it != mBitmapCache.end()) {
			// Found
			surface = (*it).second.surface;
			if (updateUsers) {
				(*it).second.numUsers++;
			}
			//Logger::w("HIT" + (*it).second.serialId);
		}
		else {
			// Not found
			Logger::d(std::string("Loading file bitmap named ") + filename);
			surface = SDL_LoadBMP(filename);
			AssetEntry entry;
			entry.serialId = AssetsManager::sSerialNextId++;
			entry.surface = surface;
			entry.debugName = debugName;
			entry.numUsers = 1;
			//Logger::w("MISS" + entry.serialId);
			mBitmapCache.insert(std::pair<std::string, AssetEntry>(filename, entry));
		}
		return surface;
	}
}