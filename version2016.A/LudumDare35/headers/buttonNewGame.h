#pragma once
#include "ui/clickableButtonWidget.h"
#include <string>
#include "gameMain.h"
#include "mySceneManager.h"
namespace vortex {
	class NewGameButton : public ClickableButtonWidget {
	protected:
		int mStartingLevel = 0;
		virtual void onMouseClickUpEvent() override {
			ClickableButtonWidget::onMouseClickUpEvent();
			GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_CHANGE_SCENE, (int64_t)MySceneManager::SceneTypeEnum::GAME_SCENE, mStartingLevel, false);
		}
	public:
		//! Constructor
		NewGameButton(const std::string &text,
			int startingLevel,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : ClickableButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			mStartingLevel = startingLevel;
			// NOOP
		}
	};

}
