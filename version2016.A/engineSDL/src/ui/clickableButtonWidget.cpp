#include "ui/clickableButtonWidget.h"
#include "gameMain.h"
#include "Utils.h"

namespace vortex {
	bool ClickableButtonWidget::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		// Capture this event if: button.isPressed && event.isReleased && event.isLeftButton --> pressed = false && return true
		// Otherwise: return false
		SDL_Rect r;
		r = mScreenRectangle.Rect;
		SDL_Point p;
		p.x = event.x;
		p.y = event.y;

		if (this->isPressed()) {
			if (event.state == SDL_RELEASED) {
				if (event.button == SDL_BUTTON_LEFT) {
					setPressed(false);
					// emit click event
					this->onMouseClickUpEvent();
					return true;
				}
			}
		}
		return false;
	}
	bool ClickableButtonWidget::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		// Capture this event if: event.isInside(button) && event.isPressed && event.isLeftButton --> pressed = true && return true
		// Otherwise: return false
		SDL_Rect r;
		r = mScreenRectangle.Rect;
		SDL_Point p;
		p.x = event.x;
		p.y = event.y;
		/*
		std::ostringstream oss;
		oss << "Point x=" << p.x << " y=" << p.y << " Rect=" << mScreenRectangle.toString();
		Logger::d(oss.str());
		*/

		if (SDL_PointInRect(&p, &r)) {
			if (event.state == SDL_PRESSED) {
				if (event.button == SDL_BUTTON_LEFT) {
					setPressed(true);
					return true;
				}
			}
		}
		return false;
	}
	bool ClickableButtonWidget::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		SDL_Rect r;
		r = mScreenRectangle.Rect;
		SDL_Point p;
		p.x = event.x;
		p.y = event.y;

		if (SDL_PointInRect(&p, &r)) {
			setHover(true);
			return true;
		}
		else {
			setHover(false);
			return false;
		}
	}
	void ClickableButtonWidget::draw(SDL_Window *window) {
		//TextLabelWidget::draw(window, updateFramebuffer);
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		// Draw background
		SDLUtils::renderSurfaceToWindow(window, getCurrentBackgroundTexture(), mWidgetScreenPosition);
		// Draw text 
		SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
	}
	void ClickableButtonWidget::resize(SDL_Window *windowOldSize, int width, int height) {
		TextLabelWidget::resize(windowOldSize, width, height);

		//Rectangle newImageSize(200, 200, 200, 200); // TODO
		Rectangle newImageSize = mWidgetScreenPosition;

		SDL_Surface *originalImage;

		// Recompute textures
		originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReference(mNormalBackgroundPath);
		mNormalBackgroundSurface = SDLUtils::scaleSurfaceIfNeeded(originalImage, mNormalBackgroundSurface, newImageSize.Rect.w, newImageSize.Rect.h);

		originalImage = GameMain::getInstance()->getAssetsManager()->getBitmapReference(mPressedBackgroundPath);
		mPressedBackgroundSurface = SDLUtils::scaleSurfaceIfNeeded(originalImage, mPressedBackgroundSurface, newImageSize.Rect.w, newImageSize.Rect.h);
	}
	void ClickableButtonWidget::_initialize() {
		TextLabelWidget::_initialize();

		SDL_Surface *unused;
		unused = GameMain::getInstance()->getAssetsManager()->getBitmapReference(this->mNormalBackgroundPath);
		unused = GameMain::getInstance()->getAssetsManager()->getBitmapReference(this->mPressedBackgroundPath);
		// Textures
		mNormalBackgroundSurface = nullptr;
		mPressedBackgroundSurface = nullptr;
	}
	void ClickableButtonWidget::_dispose() {
		TextLabelWidget::_dispose();

		SDL_FreeSurface(mNormalBackgroundSurface);
		mNormalBackgroundSurface = nullptr;

		SDL_FreeSurface(mPressedBackgroundSurface);
		mPressedBackgroundSurface = nullptr;
	}
}