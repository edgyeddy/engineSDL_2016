#pragma once
#include "baseWidget.h"
#include "Utils.h"
#include <deque>
namespace vortex {
	//! UI widget: A generic widget container.
	class BoxWidget : public BaseWidget {
	protected:
		//! Padding to apply.
		int mPadding = 0;
		//! Note: Children widgets are placed in relative coordinates
		std::deque<BaseWidget*> mChildren;
	public:
		//! Getter
		inline BaseWidget *getChildAt(int index) {
			return mChildren.at(index);
		}
		//! Getter
		inline int getNumChildren() {
			return mChildren.size();
		}
	protected:
		inline void _initialize() override {
			// Initialize self
			BaseWidget::_initialize();
			// Initialize all children
			int nn = mChildren.size();
			for (int ii = 0; ii < nn; ii++) {
				BaseWidget *child = mChildren.at(ii);
				child->initialize();
			}
		}
		inline void _dispose() override {
			// Dispose self
			BaseWidget::_dispose();
			// Dispose all children
			int nn = mChildren.size();
			for (int ii = 0; ii < nn; ii++) {
				BaseWidget *child = mChildren.at(ii);
				child = static_cast<BaseWidget *>(DELETE_OBJECT(child));
			}
			mChildren.clear();
		}
	protected:
		//! Returns the top-left position for this item
		virtual Rectangle updateVirtualRectangle(const Rectangle &newItemVirtualRectangle) = 0;
		//! Updates the virtual and real position and size of the container and the last-added item.
		void updateAllCoordinatesAfterAdding(BaseWidget *item) {
			Rectangle oldBoxVirtualSize = this->mVirtualRectangle;
			// 1) Updates the virtual coordinates of box.w / box.h
			Rectangle virtualItem = item->getVirtualRectangle();
			Rectangle topLeftNext = updateVirtualRectangle(virtualItem);
			// 2) Updates the real coordinates of box.
			this->computeRealCoordinates(0, 0);
			// 3) Updates the virtual coordinates of item.x / item.y
			virtualItem.Rect.x = topLeftNext.Rect.x + mVirtualRectangle.Rect.x;
			virtualItem.Rect.y = topLeftNext.Rect.y + mVirtualRectangle.Rect.y;
			item->setVirtualRectangle(virtualItem);
			// 4) Updates the real coordinates of item.
			item->computeRealCoordinates(0, 0); // this->mScreenRectangle.Rect.x, this->mScreenRectangle.Rect.y);
			// 5) The previous items do not change their position or size
		}
	public:
		//! Items are stacked Left/Up to Right/Down, with the top-left corner of the BoxWidget kept fixed; items are Left/Up aligned.
		inline void addChild(BaseWidget *item) {
			// Recompute parent size and position
			// Recompute child size and position
			mChildren.push_back(item);
			updateAllCoordinatesAfterAdding(item);
			item->parentWidget = this;
		}
	public:
		/// Constructor
		BoxWidget(int virtualTopLeftX, int virtualTopLeftY, int padding) : BaseWidget(Rectangle(0, 0, virtualTopLeftX, virtualTopLeftY)) {
			// NOOP
			mPadding = padding;
		}
	public:
		// Events

		//! Event handler
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event);
		//! Event handler
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event);
		//! Event handler
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event);
		//! Event handler
		virtual bool onUserEvent(UserEventData *data);
		//! Event handler
		virtual bool onKeyPressedEvent(int keyId);
	public:
		//! Apply resizing to this widget and its contents.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override; //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		//! Draw this widget and its contents.
		virtual void draw(SDL_Window *window) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		//! Update this widget and its contents.
		virtual void update(SDL_Window *window, int deltaMs) override; //!< Inform the scene that a time interval has passed; must be re-implemented in derived class.
	};
}