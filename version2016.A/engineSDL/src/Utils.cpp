#include "Utils.h"
namespace vortex {
	Json::Value SDLUtils::loadJson(std::string &jsonFile) {
		Json::Reader reader;
		Json::Value root;

		std::string jsonText = SDLUtils::readFileToString(jsonFile);
		bool parseOk = reader.parse(jsonText, root);
		if (!parseOk) {
			std::ostringstream oss;
			oss << TR("Error parsing JSON file=") << jsonFile;
			throw Exception(oss.str());
		}
		return root;
	}

	SDL_Surface *SDLUtils::scaleSurfaceIfNeeded(SDL_Surface *originalSurface, SDL_Surface *scaledSurface, int targetWidth, int targetHeight, const std::string &debugName, bool useAssetsManager) {
		int srcWidth = originalSurface->w;
		int srcHeight = originalSurface->h;
		int curWidth;
		int curHeight;
		bool mustResize = false;
		
		std::string uniqueNameNew = AssetsManager::generateUniqueName(originalSurface, targetWidth, targetHeight);

		if (scaledSurface == nullptr) {
			mustResize = true;
		}
		else {
			curWidth = scaledSurface->w;
			curHeight = scaledSurface->h;
			if (curWidth != targetWidth || curHeight != targetHeight) {
				mustResize = true;
			}
		}

		if (mustResize) {
			std::ostringstream oss;
			oss << "Resizing texture from w=" << srcWidth << " h=" << srcHeight << " to w=" << targetWidth << " h=" << targetHeight;
			Logger::d(oss.str());
			// Delete previous scaled surface
			if (useAssetsManager) {
				if (scaledSurface != nullptr) {
					std::string uniqueNameOld = AssetsManager::generateUniqueName(originalSurface, scaledSurface->w, scaledSurface->h);
					auto deleted = GameMain::getInstance()->getAssetsManager()->forgetBitmapReference(uniqueNameOld);
					if (deleted == AssetsManager::ForgetBitmapResultEnum::ERROR_NOT_FOUND) {
						auto debug = GameMain::getInstance()->getAssetsManager();
						Logger::w("Failed to delete this old scaled texture");
					}
				}
			}
			else {
				SDL_FreeSurface(scaledSurface);
			}
			scaledSurface = nullptr;
			SDL_Surface *output = nullptr;
			if (useAssetsManager) {
				output = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromMemoryOrNull(uniqueNameNew.c_str());
				if (output != nullptr) {
					// NOOP : Cache hit
				}
				else {
					// Scale original to new scale
					double scaleX = ((double)(targetWidth)) / ((double)(srcWidth));
					double scaleY = ((double)(targetHeight)) / ((double)(srcHeight));
					output = zoomSurface(originalSurface, scaleX, scaleY, SMOOTHING_ON);
					// Add to cache
					GameMain::getInstance()->getAssetsManager()->addBitmapReferenceFromMemory(uniqueNameNew, output, debugName);
				}
			}
			else {
				// Scale original to new scale
				double scaleX = ((double)(targetWidth)) / ((double)(srcWidth));
				double scaleY = ((double)(targetHeight)) / ((double)(srcHeight));
				output = zoomSurface(originalSurface, scaleX, scaleY, SMOOTHING_ON);
			}			
			return output;
		}
		else {
			return scaledSurface; // no change
		}
	}
}