#pragma once
#include "boxWidget.h"
#include "Utils.h"

namespace vortex {
	//! UI widget: A vertical widget container.
	class VBoxWidget : public BoxWidget {
	protected:
		virtual Rectangle updateVirtualRectangle(const Rectangle &newItemVirtualRectangle) override {
			int p0 = 0;
			if (getNumChildren() > 1) {
				p0 = mPadding;
			}
			// Compute the position for the new item
			Rectangle out(0, 0, 0, mVirtualRectangle.Rect.h + p0);
			// Adjust self virtual rectangle
			mVirtualRectangle.Rect.h += newItemVirtualRectangle.Rect.h + p0;
			mVirtualRectangle.Rect.w = MAXIMUM(mVirtualRectangle.Rect.w, newItemVirtualRectangle.Rect.w);
			return out;
		}
	public:
		//! Constructor
		VBoxWidget(int virtualTopLeftX, int virtualTopLeftY, int padding) : BoxWidget(virtualTopLeftX, virtualTopLeftY, padding) {
			// NOOP
		}
	};
}