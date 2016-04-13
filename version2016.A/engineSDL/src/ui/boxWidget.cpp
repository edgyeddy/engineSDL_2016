#include "ui/boxWidget.h"
namespace vortex {
	/// Return true if captures the event, false otherwise
	bool BoxWidget::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		bool captured = false;
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Compute
			captured = child->onMouseClickUpEvent(event);
			// Stop at first
			if (captured) { return true; }
		}
		return false;
	}
	/// Return true if captures the event, false otherwise
	bool BoxWidget::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		bool captured = false;
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Compute
			captured = child->onMouseClickDownEvent(event);
			// Stop at first
			if (captured) { return true; }
		}
		return false;
	}
	bool BoxWidget::onUserEvent(UserEventData *data) {
		bool captured = false;
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Compute
			captured = child->onUserEvent(data);
			// Stop at first
			if (captured) { return true; }
		}
		return false;
	}
	bool BoxWidget::onKeyPressedEvent(int keyId) {
		bool captured = false;
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Compute
			captured = child->onKeyPressedEvent(keyId);
			// Stop at first
			if (captured) { return true; }
		}
		return false;
	}

	/// Return true if captures the event, false otherwise
	bool BoxWidget::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		bool captured = false;
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Compute
			captured = child->onMouseMovementEvent(event);
			// Stop at first
			if (captured) { return true; }
		}
		return false;
	}
	void BoxWidget::draw(SDL_Window *window) {
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Draw
			child->draw(window);
		}
	}
	void BoxWidget::update(SDL_Window *window, int deltaMs) {
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// update
			child->update(window, deltaMs);
		}
	}
	void BoxWidget::resize(SDL_Window *windowOldSize, int width, int height) {
		int nn = mChildren.size();
		for (int ii = 0; ii < nn; ii++) {
			BaseWidget *child = mChildren.at(ii);
			// Resize
			child->resize(windowOldSize, width, height);
		}
	}
}