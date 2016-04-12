#include "demoScene.h"
#include "gameMain.h"
#include "Utils.h"
namespace vortex {
	void DemoScene::_initialize() {
		Scene::_initialize();

		mTextSurface = GameMain::getInstance()->getTextManager()->renderTextToSurface("DemoScene", Color4::getColor4(255, 255, 0));
		mBackgroundImage = GameMain::getInstance()->getAssetsManager()->getBitmapReference("resources/test_card_640x480.bmp");
	}
	void DemoScene::_dispose() {
		Scene::_dispose();
		// Dispose text
		SDL_FreeSurface(mTextSurface);
		mTextSurface = nullptr;
		// Dispose image (not owned by me)
		mBackgroundImage = nullptr;
	}
	void DemoScene::draw(SDL_Window *window, bool updateFramebuffer) {
		Scene::draw(window, false);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, mBackgroundImage, Rectangle(800, 800, 0, 0));
		// Draw text
		SDLUtils::renderSurfaceToWindow(window, mTextSurface, Rectangle(800, 60, 15, 15));
		// Flip framebuffer
		if (updateFramebuffer) {
			SDL_UpdateWindowSurface(window);
		}
	}

}