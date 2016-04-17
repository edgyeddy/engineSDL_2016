#include "victoryScene.h"
#include "gameMain.h"
#include "ui/vBoxWidget.h"
#include "ui/hBoxWidget.h"
#include "ui/textLabelWidget.h"
#include "ui/clickableButtonWidget.h"
#include "ui/checkButtonWidget.h"
#include "ui/radioButtonWidget.h"
#include "buttonGotoMainScene.h"
#include "Utils.h"
#include "mySceneManager.h"
#include "gameplayState.h"

namespace vortex {
	void VictoryScene::_initialize() {
		Scene::_initialize();
		// Background
		SDL_Surface *unused = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/game_background_640x480.bmp", false, "Victory.originalBackground");
		mBackgroundImage = nullptr;
		// Add widgets to UI
		int w = 3000;
		int h = 300;
		VBoxWidget *box = new VBoxWidget(0, 0, 20);
		// Load game configuration

		Color4 text = Color4::getColor4(254, 190, 128);
		Color4 back = Color4::getColor4(0, 0, 0, 0);
		Color4 front = Color4::getColor4(36, 92, 147);

		ClickableButtonWidget *widget4 = new GotoMainSceneButton("Close <Enter>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		BaseWidget *widget5 = ClickableButtonWidget::createAsImageWidget("resources/vortex_logo_360_alpha.bmp", w, w);

		std::vector<std::string> v = { "Ludum Dare 35 : Shapeshift", "Congratulations!", "You have completed all levels", "with a score of ??.", "Game by edgyeddy 2016" };
		for (int ii = 0; ii < (int)v.size(); ii++)
		{
			std::string str = v[ii];
			if (ii == 3) {
				std::ostringstream oss;
				oss << "with a score of " << mScore << ".";
				str = oss.str();
			}
			TextLabelWidget *widget1 = new TextLabelWidget(str, text, back, Rectangle(w, h));
			box->addChild(widget1);
		}
		box->addChild(widget5);
		box->addChild(widget4);

		box->initialize();

		Rectangle vrect = box->getVirtualRectangle();
		Rectangle vall = Rectangle::getVirtualWorld();
		vrect.centerInParent(vall);
		box->setVirtualRectangle(vrect);
		Rectangle window = GameMain::getInstance()->getWindowSize();
		box->updateLayout(window.Rect.w, window.Rect.h);

		mUiManager->setRootWidget(box);

		GameMain::getInstance()->lockUI(false);
	}
	void VictoryScene::_dispose() {
		Scene::_dispose();
		// Dispose background image
		// SDL_FreeSurface(mBackgroundImage); not owned by me
		mBackgroundImage = nullptr;
	}
	void VictoryScene::resize(SDL_Window *windowOldSize, int width, int height) {
		Scene::resize(windowOldSize, width, height);
		SDL_Surface *originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/game_background_640x480.bmp", false, "Victory.originalBackground");
		Rectangle newScreenSize(width, height);
		Rectangle originalImageSize(640, 480);

		Rectangle newImageSize = Rectangle::adjustRectangle(mBackgroundMode, originalImageSize, newScreenSize);

		// Save target image
		mBackgroundImageScreenPosition = newImageSize;
		mBackgroundImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h, "Victory.Background.scaled");
	}
	void VictoryScene::draw(SDL_Window *window, bool updateFramebuffer) {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		Scene::drawBack(window, false);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, mBackgroundImage, mBackgroundImageScreenPosition);
		// Draw UI
		Scene::drawFront(window, false);
		// Flip framebuffer
		if (updateFramebuffer) {
			SDL_UpdateWindowSurface(window);
		}
	}
	bool VictoryScene::onKeyPressedEvent(int keyId) {
		bool captured = Scene::onKeyPressedEvent(keyId);
		if (!captured) {
			if (keyId == SDLK_RETURN) {
				GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_CHANGE_SCENE, (int64_t)MySceneManager::SceneTypeEnum::MAIN_SCENE, 0, false);
				return true;
			}
		}
		return captured;
	}
}