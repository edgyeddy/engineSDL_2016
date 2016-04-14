#include "demoScene.h"
#include "gameMain.h"
#include "ui/vBoxWidget.h"
#include "ui/hBoxWidget.h"
#include "ui/textLabelWidget.h"
#include "ui/clickableButtonWidget.h"
#include "ui/checkButtonWidget.h"
#include "ui/radioButtonWidget.h"
#include "buttonRadioMode.h"
#include "Utils.h"
#include "buttonQuit.h"

namespace vortex {
	bool DemoScene::onUserEvent(UserEventData *data) {
		bool captured = Scene::onUserEvent(data);
		if (!captured) {
			if (data->type == DemoScene::SceneEventsEnum::USER_EVENT_CHANGE_BACKGROUND) {
				this->mBackgroundMode = (Rectangle::RectangleAdjustEnum)data->data1;
				// Refresh screen
				GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_REFRESH_SCREEN, 0, 0, false);
				return true;
			}
		}
		return false;
	}
	void DemoScene::_initialize() {
		Scene::_initialize();
		// Text
		mTextSurface = GameMain::getInstance()->getTextManager()->renderTextToSurface("DemoScene", Color4::getColor4(255, 255, 0));
		mTextScreenPosition = GameMain::getInstance()->getTextManager()->getTextBoundingBox("DemoScene");
		// Wallpaper
		SDL_Surface *unused = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/test_card_640x480.bmp", false, "DemoScene.originalBackground");
		mBackgroundImage = nullptr;
		// Add widgets to UI
		int w = 1000;
		VBoxWidget *box = new VBoxWidget(300, 300, 20);
		HBoxWidget *hbox = new HBoxWidget(300, 300, 20);
		ButtonRadioMode *widget00 = new ButtonRadioMode(Rectangle::RectangleAdjustEnum::STRETCH_TO_FIT, "Stretch", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		ButtonRadioMode *widget01 = new ButtonRadioMode(Rectangle::RectangleAdjustEnum::ADJUST_INSIDE, "Inside", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		ButtonRadioMode *widget02 = new ButtonRadioMode(Rectangle::RectangleAdjustEnum::ADJUST_OUTSIDE, "Outside", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		widget01->setChecked(true);
		hbox->addChild(widget00);
		hbox->addChild(widget01);
		hbox->addChild(widget02);
		TextLabelWidget *widget1 = new TextLabelWidget("UI.Text", Color4::getColor4(255, 0, 0), Color4::getColor4(0, 255, 255), Rectangle(w, 200, 2000 - w/2, 300));
		CheckButtonWidget *widget2 = new CheckButtonWidget("Check", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		ClickableButtonWidget *widget3 = new ClickableButtonWidget("Clickme", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		ClickableButtonWidget *widget4 = new QuitButton("Quit", "resources/button_background.bmp", "resources/button_background2.bmp", Color4::getColor4(255, 0, 0), Rectangle(w, 200, 2000 - w / 2, 300));
		box->addChild(hbox);
		box->addChild(widget1);
		box->addChild(widget2);
		box->addChild(widget3);
		box->addChild(widget4);
		
		
		box->initialize();
		mUiManager->setRootWidget(box);
	}
	void DemoScene::_dispose() {
		Scene::_dispose();
		// Dispose text
		SDL_FreeSurface(mTextSurface);
		mTextSurface = nullptr;
		// Dispose image (owned by me)
		// SDL_FreeSurface(mBackgroundImage); not owned by me
		mBackgroundImage = nullptr;
	}
	void DemoScene::resize(SDL_Window *windowOldSize, int width, int height) {
		Scene::resize(windowOldSize, width, height);
		SDL_Surface *originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/test_card_640x480.bmp", false, "DemoScene.originalBackground");
		Rectangle newScreenSize(width, height);
		Rectangle originalImageSize(640, 480);

		Rectangle newImageSize = Rectangle::adjustRectangle(mBackgroundMode, originalImageSize, newScreenSize);
		
		// Save target image
		mBackgroundImageScreenPosition = newImageSize;
		mBackgroundImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h, "DemoScene.Background.scaled");

		// Move text to the center of the screen
		mTextScreenPosition.centerInParent(newScreenSize);
	}
	void DemoScene::draw(SDL_Window *window, bool updateFramebuffer) {
		// NOOP
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		Scene::drawBack(window, false);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, mBackgroundImage, mBackgroundImageScreenPosition);
		// Draw text
		SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
		// Draw UI
		Scene::drawFront(window, false);
		//Scene::draw(window, false);
		// Flip framebuffer
		if (updateFramebuffer) {
			SDL_UpdateWindowSurface(window);
		}
	}

}