#pragma once
#include "ui/radioButtonWidget.h"
namespace vortex {
	class ButtonRadioMode : public RadioButtonWidget {
	protected:
		Rectangle::RectangleAdjustEnum mMode;
	public:
		//! Constructor
		ButtonRadioMode(
			Rectangle::RectangleAdjustEnum mode,
			const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : RadioButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
			mMode = mode;
		}
		virtual void onMouseClickUpEvent() override;
	};
}
