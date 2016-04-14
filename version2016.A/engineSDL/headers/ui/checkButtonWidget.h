#pragma once
#include "clickableButtonWidget.h"

namespace vortex {
	//! UI widget: A check button.
	class CheckButtonWidget : public ClickableButtonWidget {
	protected:
		bool mIsChecked = false; //!< This button is in state "checked"
	public:
		//! Setter
		inline void setChecked(bool value) {
			mIsChecked = value;
		}
		//! Getter
		inline bool isChecked() {
			return mIsChecked;
		}
	protected:
		//! Getter
		virtual SDL_Surface *getCurrentBackgroundTexture() override {
			if (isChecked() || isPressed()) {
				return mPressedBackgroundSurface;
			}
			else {
				return mNormalBackgroundSurface;
			}
		}
	public:
		//! Constructor
		CheckButtonWidget(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : ClickableButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
		}
	public:
		//! Event handler.
		virtual void onMouseClickUpEvent() override {
			setChecked(!isChecked());
		}
	};
}