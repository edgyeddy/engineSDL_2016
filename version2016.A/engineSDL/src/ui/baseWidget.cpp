#include "ui/baseWidget.h"
#include "gameMain.h"

namespace vortex {
	void BaseWidget::_initialize() {
		// TODO
	}
	void BaseWidget::_dispose() {
		// TODO
	}
	bool BaseWidget::onUserEvent(UserEventData *data) {
		// TODO
		return false;
	}
	bool BaseWidget::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		// TODO
		return false;
	}	
	bool BaseWidget::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		// TODO
		return false;
	}
	bool BaseWidget::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		// TODO
		return false;
	}
	bool BaseWidget::onKeyPressedEvent(int keyId) {
		// TODO
		return false;
	}
	void BaseWidget::computeRealCoordinates(int realOffsetX, int realOffsetY) {
		Rectangle windowRect = GameMain::getInstance()->getWindowSize();
		computeRealCoordinates(windowRect.Rect.w, windowRect.Rect.h, realOffsetX, realOffsetY);
	}
}