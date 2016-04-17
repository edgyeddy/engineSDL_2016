#pragma once
#include "ui/clickableButtonWidget.h"
#include <string>
#include "gameMain.h"
#include "mySceneManager.h"
namespace vortex {
	class GotoMainSceneButton : public ClickableButtonWidget {
	protected:
		virtual void onMouseClickUpEvent() override {
			ClickableButtonWidget::onMouseClickUpEvent();
			GameMain::getInstance()->launchUserEvent(GameMain::EventTypeEnum::EVENT_CHANGE_SCENE, (int64_t)MySceneManager::SceneTypeEnum::MAIN_SCENE, 0, false);
		}
	public:
		//! Constructor
		GotoMainSceneButton(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : ClickableButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
		}
	};

}
