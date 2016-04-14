#pragma once
#include "checkButtonWidget.h"
#include "boxWidget.h"

namespace vortex {
	//! UI widget: A radio check button.
	class RadioButtonWidget : public CheckButtonWidget {
	public:
		//! Constructor
		RadioButtonWidget(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor,
			const Rectangle &virtualRectangle) : CheckButtonWidget(text, normalBackgroundTexture, pressedBackgroundTexture, textColor, virtualRectangle) {
			// NOOP
		}
	public:
		virtual void onMouseClickUpEvent() override {
			CheckButtonWidget::onMouseClickUpEvent();
			if (!isChecked()) { return; }
			BoxWidget *parent = dynamic_cast<BoxWidget*>(this->parentWidget);
			if (parent != nullptr) {
				int nn = parent->getNumChildren();
				for (int ii = 0; ii < nn; ii++) {
					RadioButtonWidget *sibling = dynamic_cast<RadioButtonWidget*>(parent->getChildAt(ii));
					if (sibling != nullptr && sibling != this) {
						sibling->setChecked(false);
					}
				}
			}

		}
	};
}