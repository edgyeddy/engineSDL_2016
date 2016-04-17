#include "gameScene.h"
#include "gameMain.h"
#include "ui/vBoxWidget.h"
#include "ui/hBoxWidget.h"
#include "ui/textLabelWidget.h"
#include "ui/clickableButtonWidget.h"
#include "ui/checkButtonWidget.h"
#include "mySceneManager.h"
#include "ui/radioButtonWidget.h"
#include "buttonRestartLevel.h"
#include "buttonShapeshift.h"
#include "buttonNextFragment.h"
//#include "buttonRadioMode.h"
#include "buttonQuit.h"
#include "Utils.h"

namespace vortex {
	
	void GameScene::_initialize() {
		Scene::_initialize();
		// Text
		/*
		mTextSurface = GameMain::getInstance()->getTextManager()->renderTextToSurface("MainScene", Color4::getColor4(255, 255, 0));
		mTextScreenPosition = GameMain::getInstance()->getTextManager()->getTextBoundingBox("MainScene");
		*/
		// Wallpaper
		SDL_Surface *unused = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/game_background_640x480.bmp", false, "DemoScene.originalBackground");
		mBackgroundImage = nullptr;
		unused = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/grid43.bmp", false, "DemoScene.originalGrid");
		mGridImage = nullptr;
		// Add widgets to UI
		int w = (int)(0.375 * Constants::VIRTUAL_WIDTH);
		int h = 300;
		VBoxWidget *box = new VBoxWidget(0, 0, 0);
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
		Color4 front = Color4::getColor4(36, 92, 147);
		Color4 back = Color4::getColor4(255, 255, 255);

		mGameplay = new GameplayState(mCurrentLevel);
		mGameplay->initialize();

		std::ostringstream oss;

		oss.str("");
		oss << "Level " << mCurrentLevel;
		TextLabelWidget *widget00 = mWidgetLevel = new TextLabelWidget(oss.str(), front, back, Rectangle(w, h));
		oss.str("");
		oss << "Fragments " << mGameplay->getNumPendingFragments();
		TextLabelWidget *widget03 = mWidgetFragments = new TextLabelWidget(oss.str(), front, back, Rectangle(w, h));
		oss.str("");
		oss << "Score " << mUserScore;
		TextLabelWidget *widget01 = mWidgetScore = new TextLabelWidget(oss.str(), front, back, Rectangle(w, h));
		TextLabelWidget *widget05 = new TextLabelWidget("Movement <Arrows>", front, back, Rectangle(w, h));
		TextLabelWidget *widget02 = new ShapeshiftButton("Shapeshift <Space>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		TextLabelWidget *widget04 = new NextFragmentButton("Next fragment <Enter>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		ClickableButtonWidget *widget4 = new QuitButton("Quit <Escape>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		ClickableButtonWidget *widget5 = new RestartLevelButton("Restart level <Back>", "resources/button_background.bmp", "resources/button_background2.bmp", front, Rectangle(w, h));
		/*
		box->addChild(hbox);
		box->addChild(widget1);
		box->addChild(widget2);
		box->addChild(widget3);
		*/		
		box->addChild(widget00);
		box->addChild(widget03);
		box->addChild(widget01);
		box->addChild(widget05);
		box->addChild(widget02);
		box->addChild(widget04);
		box->addChild(widget5);
		box->addChild(widget4);
		
		
		box->initialize();
		mUiManager->setRootWidget(box);

		//Color4 xfront = Color4::getColor4(36, 92, 147);
		Color4 xfront = Color4::getColor4(254, 190, 128);
		mTextSurface = GameMain::getInstance()->getTextManager()->renderTextToSurface("Level cleared!", xfront, false);
		mTextScreenPosition = GameMain::getInstance()->getTextManager()->getTextBoundingBox("Level cleared!", false);
		
	}
	void GameScene::_dispose() {
		Scene::_dispose();

		// Dispose text
		SDL_FreeSurface(mTextSurface);
		mTextSurface = nullptr;

		mGameplay = static_cast<GameplayState*>(DELETE_OBJECT(mGameplay));

		// Dispose text
		/*
		SDL_FreeSurface(mTextSurface);
		mTextSurface = nullptr;
		*/
		// Dispose image (owned by me)
		// SDL_FreeSurface(mBackgroundImage); not owned by me
		mBackgroundImage = nullptr;
		mGridImage = nullptr;
	}
	void GameScene::resize(SDL_Window *windowOldSize, int width, int height) {
		Scene::resize(windowOldSize, width, height);
		Rectangle newScreenSize(width, height);
		
		mGameplay->resize(windowOldSize, width, height);
		
		// Save target image
		SDL_Surface *originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/game_background_640x480.bmp", false, "DemoScene.originalBackground");
		Rectangle originalImageSize(640, 480);
		Rectangle newImageSize = Rectangle::adjustRectangle(mBackgroundMode, originalImageSize, newScreenSize);
		mBackgroundImageScreenPosition = newImageSize;
		mBackgroundImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h, "DemoScene.Background.scaled");

		// Save target image
		originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReferenceFromFile("resources/grid43.bmp", false, "MainScene.originalGrid");
		originalImageSize = Rectangle(400, 300);
		newImageSize = Rectangle::adjustRectangle(Rectangle::RectangleAdjustEnum::ADJUST_INSIDE, originalImageSize, newScreenSize);
		mGridImageScreenPosition = newImageSize;
		mGridImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, mGridImage, newImageSize.Rect.w, newImageSize.Rect.h, "GameScene.Grid.scaled");

		// Move text to the center of the screen
		mTextScreenPosition.centerInParent(newScreenSize);

		// Move text to the center of the screen
		//mTextScreenPosition.centerInParent(newScreenSize);
	}
	void GameScene::draw(SDL_Window *window, bool updateFramebuffer) {
		// NOOP
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		Scene::drawBack(window, false);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, mBackgroundImage, mBackgroundImageScreenPosition);
		// Draw grid
		SDLUtils::renderSurfaceToWindow(window, mGridImage, mGridImageScreenPosition);
		// Draw game elements
		mGameplay->draw(window);
		// Draw text
		if (mShowVictoryFX) {
			SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
		}
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
	void GameScene::update(SDL_Window *window, int deltaMs) {
		Scene::update(window, deltaMs);
		// Update gameplay
		mGameplay->update(window, deltaMs);
	}
	void GameScene::onUpdateScoreLabel() {
		// Update button text
		std::ostringstream oss;
		oss.str("");
		oss << "Score " << this->mUserScore;
		// Do it
		onUpdateLabel(mWidgetScore, oss.str());
	}
	void GameScene::onUpdateLevelLabel() {
		// Update button text
		std::ostringstream oss;
		oss.str("");
		oss << "Level " << mCurrentLevel;
		// Do it
		onUpdateLabel(mWidgetLevel, oss.str());
	}
	void GameScene::onUpdateFragmentsLabel() {
		// Update button text
		std::ostringstream oss;
		oss.str("");
		oss << "Fragments " << mGameplay->getNumPendingFragments();
		// Do it
		onUpdateLabel(mWidgetFragments, oss.str());		
	}
	void GameScene::onUpdateLabel(TextLabelWidget *widget, const std::string &text) {
		widget->setText(text);
		// Refresh screen
		GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_REFRESH_SCREEN, 0, 0, false);
	}
	bool GameScene::onUserEvent(UserEventData *data) {
		if (Scene::onUserEvent(data)) { return true; }
		if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_FRAGMENT_REQUEST) {
			bool changed = mGameplay->tryNextFragment();
		}
		else if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_SHAPESHIFT_REQUEST) {
			mGameplay->tryShapeshift();

			// Update user score
			mUserScore += SCORE_DELTA_PER_ACTION;
			// Refresh screen
			onUpdateScoreLabel();
		}
		else if (data->type == GameMain::EventTypeEnum::EVENT_1_SECOND) {
			// Update user score
			mUserScore += SCORE_DELTA_PER_SECOND;
			// Refresh screen
			onUpdateScoreLabel();
			return true;
		}
		else if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_FRAGMENT) {
			onUpdateFragmentsLabel();
			return true;
		}
		else if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_RESTART_LEVEL) {
			// Reload level
			mGameplay = static_cast<GameplayState*>(DELETE_OBJECT(mGameplay));
			mGameplay = new GameplayState(mCurrentLevel);
			mGameplay->initialize();

			// Update user score
			mUserScore += SCORE_DELTA_AFTER_LEVEL_RESTART;
			// Refresh screen
			onUpdateScoreLabel();

			onUpdateFragmentsLabel();

			// Refresh screen
			GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_REFRESH_SCREEN, 0, 0, false);
			return true;
		}
		else if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_SHOW_END_LEVEL_FX) {
			mShowVictoryFX = true;
		}
		else if (data->type == MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_LEVEL) {
			mShowVictoryFX = false;
			// Update user score
			mUserScore += SCORE_DELTA_AFTER_LEVEL_VICTORY * (mCurrentLevel + 1);
			// Refresh screen
			onUpdateScoreLabel();

			// Load next level
			if (SDLUtils::fileExists(GameplayState::getJsonFileForLevel(mCurrentLevel + 1))) {
				mGameplay = static_cast<GameplayState*>(DELETE_OBJECT(mGameplay));
				mCurrentLevel++;
			}
			else {
				Logger::t("Victory!");
				GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_CHANGE_SCENE, MySceneManager::SceneTypeEnum::VICTORY_SCENE, this->mUserScore, false);
				//mCurrentLevel = 0;
				return true;
			}

			
			// Change gameplay to new level
			mGameplay = new GameplayState(mCurrentLevel);
			mGameplay->initialize();

			onUpdateLevelLabel();
			onUpdateFragmentsLabel(); // After initialize!
			// Refresh screen
			GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_REFRESH_SCREEN, 0, 0, false);
			GameMain::getInstance()->lockUI(false);
			return true;
		}
		return mGameplay->onUserEvent(data);
	}
	bool GameScene::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		if (Scene::onMouseMovementEvent(event)) { return true; }
		return mGameplay->onMouseMovementEvent(event);
	}
	bool GameScene::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		if (Scene::onMouseClickDownEvent(event)) { return true; }
		return mGameplay->onMouseClickDownEvent(event);
	}
	bool GameScene::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		if (Scene::onMouseClickUpEvent(event)) { return true; }
		return mGameplay->onMouseClickUpEvent(event);
	}
	bool GameScene::onKeyPressedEvent(int keyId) {
		if (Scene::onKeyPressedEvent(keyId)) { return true; }
		bool captured = mGameplay->onKeyPressedEvent(keyId);
		if (captured) {
			// Update user score
			mUserScore += SCORE_DELTA_PER_ACTION;
			// Refresh screen
			onUpdateScoreLabel();
		}
		return captured;
	}
}