#pragma once
#include "Scene.h"
#include "SDL.h"
#include "Rectangle.h"
#include "gameMain.h"
#include "gameplayState.h"
#include "ui/textLabelWidget.h"

namespace vortex {
	class GameScene : public Scene {
	public:
		static const int SCORE_DELTA_AFTER_LEVEL_VICTORY = 100; // xLevel
		static const int SCORE_DELTA_AFTER_LEVEL_RESTART = -10;
		static const int SCORE_DELTA_PER_SECOND = -1;
		static const int SCORE_DELTA_PER_ACTION = -1;
	protected:
		bool mShowVictoryFX = false;
		Rectangle mTextScreenPosition;
		SDL_Surface *mTextSurface; //!< Owned by this class
		int mUserScore = 0;
		TextLabelWidget *mWidgetScore;
		TextLabelWidget *mWidgetFragments;
		TextLabelWidget *mWidgetLevel;
		int mCurrentLevel = 0;
		GameplayState *mGameplay;
		Rectangle::RectangleAdjustEnum mBackgroundMode = Rectangle::RectangleAdjustEnum::ADJUST_OUTSIDE;
		//Rectangle mTextScreenPosition;
		Rectangle mBackgroundImageScreenPosition;
		Rectangle mGridImageScreenPosition;
		
		//SDL_Surface *mTextSurface; //!< Owned by this class
		SDL_Surface *mBackgroundImage; //!< Not owned by this class
		SDL_Surface *mGridImage; //!< Not owned by this class
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		GameScene(int startingLevel) : Scene() {
			mCurrentLevel = startingLevel;
		}
	public:
		virtual void update(SDL_Window *window, int deltaMs);
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override; //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
	public: 
		virtual bool onUserEvent(UserEventData *data) override;
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) override;
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event) override;
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event) override;
		virtual bool onKeyPressedEvent(int keyId) override;
	public:
		void onUpdateLabel(TextLabelWidget *widget, const std::string &text);
		void onUpdateScoreLabel();
		void onUpdateLevelLabel();
		void onUpdateFragmentsLabel();
	};
}
