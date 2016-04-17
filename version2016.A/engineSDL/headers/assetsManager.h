#pragma once
#include "IDisposableObject.h"
#include <SDL.h>
#include <map>
namespace vortex {
	//! Manages the (cached) bitmap assets.
	class AssetsManager : public IDisposableObject {
	public:
		//! Enumarates the results for \ref forgetBitmapReference
		enum ForgetBitmapResultEnum {
			ERROR_NOT_FOUND,
			BITMAP_STILL_IN_USE,
			BITMAP_HAS_BEEN_DISPOSED,
		};
	protected:
		static int sSerialNextId; //!< Serial ID generator
		//! A definition of a cached bitmap texture.
		class AssetEntry {
		public:
			int serialId; //!< Serial ID
			int numUsers; //!< Number of object that are using this texture
			std::string debugName; //!< Debug name for this texture
			SDL_Surface *surface; //!< Pointer to the texture
		};
	protected:

		std::map<std::string, AssetEntry> mBitmapCache; //!< Bitmap cache. The surfaces are owned by this class.
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		//! Getter
		inline int getNumBitmaps() const {
			return mBitmapCache.size();
		}
		//! AssetsManager is the owner of the surface
		SDL_Surface *getBitmapReferenceFromFile(const char *filename, bool updateUsers, const std::string &debugName);
		//! AssetsManager is the owner of the surface
		inline SDL_Surface *getBitmapReferenceFromFile(std::string &filename, bool updateUsers, const std::string &debugName) {
			return getBitmapReferenceFromFile(filename.c_str(), updateUsers, debugName);
		}
		//! Returns the required memory texture or null. AssetsManager is the owner of the surface.
		SDL_Surface *getBitmapReferenceFromMemoryOrNull(const char *uniqueName);
		//! Adds a new freshly-generated memory texture to the AssetsManager cache.
		void addBitmapReferenceFromMemory(std::string &uniqueName, SDL_Surface *memorySurface, const std::string &debugName);
		//! Informs the AssetsManager that the object doesn't need to reference this texture.
		ForgetBitmapResultEnum forgetBitmapReference(std::string &uniqueName);
		//! Informs the AssetsManager that the object doesn't need to reference this texture.
		inline ForgetBitmapResultEnum forgetBitmapReference(SDL_Surface *surface) {
			if (surface == nullptr) {
				return ForgetBitmapResultEnum::ERROR_NOT_FOUND;
			}
			return forgetBitmapReference(surface, surface->w, surface->h);
		}
		inline ForgetBitmapResultEnum forgetBitmapReference(SDL_Surface *surface, int width, int height) {
			if (surface == nullptr) {
				return ForgetBitmapResultEnum::ERROR_NOT_FOUND;
			}
			std::string uniqueName = generateUniqueName(surface, width, height);
			return forgetBitmapReference(uniqueName);
		}
		inline static std::string generateUniqueName(void *surface, int width, int height) {
			std::ostringstream oss;
			oss << surface << "#" << width << "#" << height;
			return oss.str();
		}
	};
}
