#include "mainScene.h"
#include "gameMain.h"
#include "ui/vBoxWidget.h"
#include "ui/hBoxWidget.h"
#include "ui/textLabelWidget.h"
#include "ui/clickableButtonWidget.h"
#include "ui/checkButtonWidget.h"
#include "ui/radioButtonWidget.h"
//#include "buttonRadioMode.h"
#include "buttonQuit.h"
#include "buttonNewGame.h"
#include "Utils.h"
#include "mySceneManager.h"
#include "gameplayState.h"

namespace vortex {
	bool MainScene::onUserEvent(UserEventData *data) {
		bool captured = Scene::onUserEvent(data);
		if (!captured) {
			if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_CHANGE_BACKGROUND) {
				this->mBackgroundMode = (Rectangle::RectangleAdjustEnum)data->data1;
				// Refresh screen
				GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_REFRESH_SCREEN, 0, 0, false);
				return true;
			}
		}
		return false;
	}
	void MainScene::_initialize() {
		Scene::_initialize();
		// Text
		//mTextSurface = GameMain::getInstance()->getTextManager()->renderTextToSurface("MainScene", Color4::getColor4(255, 255, 0));
		mTextScreenPosition = GameMain::getInstance()->getTextManager()->getTextBoundingBox("MainScene");
		// Wallpaper
		SDL_Surface *unused = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/main_background_640x480.bmp", false, "Game.originalBackground");
		mBackgroundImage = nullptr;
		// Add widgets to UI
		int w = 3000;
		int h = 300;
		VBoxWidget *box = new VBoxWidget(0, 0, 20);
		/*
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
		*/

		// Load game configuration
		Json::Value default;
		Json::Value root = SDLUtils::loadJson(std::string("resources/game.json"));
		GameplayState::DEBUG_STARTING_LEVEL = root.get("debugStartingLevel", default).asInt();
		GameplayState::NUM_COLUMNS = root.get("numColumns", default).asInt();
		GameplayState::NUM_ROWS = root.get("numRows", default).asInt();
		GameplayState::NUM_SYMBOLS = root.get("numSymbols", default).asInt();
		Constants::DEBUG_ENABLE = root.get("enableDebug", default).asBool();
		int nLevels = root.get("numLevels", default).asInt();

		Color4 text = Color4::getColor4(255, 255, 255);
		Color4 back = Color4::getColor4(0, 0, 0, 0);
		Color4 front = Color4::getColor4(36, 92, 147);


		ClickableButtonWidget *widget3 = new NewGameButton("New game <Enter>", 0, "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));

		ClickableButtonWidget *widget6 = nullptr;
		if (Constants::DEBUG_ENABLE) {
			std::ostringstream oss;
			oss << "DEBUG " << GameplayState::DEBUG_STARTING_LEVEL;
			widget6 = new NewGameButton(oss.str(), GameplayState::DEBUG_STARTING_LEVEL, "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		}
		ClickableButtonWidget *widget4 = new QuitButton("Quit <Escape>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		BaseWidget *widget5 = ClickableButtonWidget::createAsImageWidget("resources/vortex_logo_360_alpha.bmp", w, w);


		
		std::vector<std::string> v = { "Ludum Dare 35 : Shapeshift", "To play, use <arrows/space/enter> keys", "There are ?? levels!", "by edgyeddy 2016" };
		for (int ii = 0; ii < (int)v.size(); ii++)
		{
			std::string str = v[ii];
			if (ii == 2) {
				std::ostringstream oss;
				oss << "There are " << nLevels << " levels to play!";
				str = oss.str();
			}
			TextLabelWidget *widget1 = new TextLabelWidget(str, text, back, Rectangle(w, h));
			box->addChild(widget1);
		}
		/*
		box->addChild(hbox);
		box->addChild(widget1);
		box->addChild(widget2);
		*/
		box->addChild(widget5);
		box->addChild(widget3);
		if (Constants::DEBUG_ENABLE) {
			box->addChild(widget6);
		}
		box->addChild(widget4);
		
		box->initialize();

		Rectangle vrect = box->getVirtualRectangle();
		Rectangle vall = Rectangle::getVirtualWorld();
		vrect.centerInParent(vall);
		box->setVirtualRectangle(vrect);
		Rectangle window = GameMain::getInstance()->getWindowSize();
		box->updateLayout(window.Rect.w, window.Rect.h);

		mUiManager->setRootWidget(box);
	}
	void MainScene::_dispose() {
		Scene::_dispose();
		// Dispose text
		/*
		SDL_FreeSurface(mTextSurface);
		mTextSurface = nullptr;
		*/
		// Dispose image (owned by me)
		// SDL_FreeSurface(mBackgroundImage); not owned by me
		mBackgroundImage = nullptr;
	}
	void MainScene::resize(SDL_Window *windowOldSize, int width, int height) {
		Scene::resize(windowOldSize, width, height);
		SDL_Surface *originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/main_background_640x480.bmp", false, "Game.originalBackground");
		Rectangle newScreenSize(width, height);
		Rectangle originalImageSize(640, 480);

		Rectangle newImageSize = Rectangle::adjustRectangle(mBackgroundMode, originalImageSize, newScreenSize);
		
		// Save target image
		mBackgroundImageScreenPosition = newImageSize;
		mBackgroundImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h, "DemoScene.Background.scaled");

		// Move text to the center of the screen
		mTextScreenPosition.centerInParent(newScreenSize);
	}
	void MainScene::draw(SDL_Window *window, bool updateFramebuffer) {
		// NOOP
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		Scene::drawBack(window, false);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, mBackgroundImage, mBackgroundImageScreenPosition);
		// Draw text
		/*
		SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
		*/
		// Draw UI
		Scene::drawFront(window, false);
		//Scene::draw(window, false);
		// Flip framebuffer
		if (updateFramebuffer) {
			SDL_UpdateWindowSurface(window);
		}
	}
	bool MainScene::onKeyPressedEvent(int keyId) {
		bool captured = Scene::onKeyPressedEvent(keyId);
		if (!captured) {
			if (keyId == SDLK_RETURN) {
				GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_CHANGE_SCENE, (int64_t)MySceneManager::SceneTypeEnum::GAME_SCENE, 0, false);
				return true;
			}
		}
		return captured;
	}

}