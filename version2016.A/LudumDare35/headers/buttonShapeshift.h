#pragma once
#include "ui/clickableButtonWidget.h"
#include <string>
#include "gameMain.h"
#include "mySceneManager.h"
namespace vortex {
	class ShapeshiftButton : public ClickableButtonWidget {
	protected:
		virtual void onMouseClickUpEvent() override {
			ClickableButtonWidget::onMouseClickUpEvent();
			GameMain::getInstance()->launchUserEvent(MySceneManager::SceneEventsEnum::USER_EVENT_SHAPESHIFT_REQUEST, 0, 0, false);
		}
	public:
		//! Constructor
		ShapeshiftButton(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : ClickableButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
		}
	};

}
