#include "ui\UiManager.h"
namespace vortex {
	void UiManager::_initialize() {
		// TODO
	}
	void UiManager::_dispose() {
		// TODO
		mRoot = static_cast<BaseWidget *>(DELETE_OBJECT(mRoot));
	}
	void UiManager::resize(SDL_Window *windowOldSize, int width, int height) {
		// TODO
		if (mRoot != nullptr) {
			mRoot->resize(windowOldSize, width, height);
		}
	}
	void UiManager::draw(SDL_Window *window) {
		// TODO
		if (mRoot != nullptr) {
			mRoot->draw(window);
		}
	}
	void UiManager::update(SDL_Window *window, int deltaMs) {
		// TODO
		if (mRoot != nullptr) {
			mRoot->update(window, deltaMs);
		}
	}
	bool UiManager::onUserEvent(UserEventData *data) {
		// TODO
		if (mRoot == nullptr) { return false;  }
		return mRoot->onUserEvent(data);
	}
	bool UiManager::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		// TODO
		if (mRoot == nullptr) { return false; }
		return mRoot->onMouseMovementEvent(event);
	}
	bool UiManager::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		// TODO
		if (mRoot == nullptr) { return false; }
		return mRoot->onMouseClickDownEvent(event);
	}
	bool UiManager::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		// TODO
		if (mRoot == nullptr) { return false; }
		return mRoot->onMouseClickUpEvent(event);
	}
	bool UiManager::onKeyPressedEvent(int keyId) {
		// TODO
		if (mRoot == nullptr) { return false; }
		return mRoot->onKeyPressedEvent(keyId);
	}
}