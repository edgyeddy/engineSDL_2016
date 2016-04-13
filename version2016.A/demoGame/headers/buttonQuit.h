#pragma once
#include "ui/clickableButtonWidget.h"
#include <string>
#include "gameMain.h"
namespace vortex {
	class QuitButton : public ClickableButtonWidget {
	protected:
		virtual void onMouseClickUpEvent() override {
			ClickableButtonWidget::onMouseClickUpEvent();
			//GameMain::getInstance()->launchUserEvent()
			SDL_Event ev;
			ev.quit.type = SDL_QUIT;
			int errcode = SDL_PushEvent(&ev);
			if (errcode != 0) {
				Logger::e(TR("Error pushing event to queue"));
			}
		}
	public:
		//! Constructor
		QuitButton(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : ClickableButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
		}
	};

}
