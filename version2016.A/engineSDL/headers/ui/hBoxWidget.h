#pragma once
#include "boxWidget.h"
#include "Utils.h"

namespace vortex {
	//! UI widget: An horizontal widget container.
	class HBoxWidget : public BoxWidget {
	protected:
		virtual Rectangle updateVirtualRectangle(const Rectangle &newItemVirtualRectangle) override {
			int p0 = 0;
			if (getNumChildren() > 1) {
				p0 = mPadding;
			}
			// Compute the position for the new item
			Rectangle out(0, 0, mVirtualRectangle.Rect.w + p0, 0);
			// Adjust self virtual rectangle
			mVirtualRectangle.Rect.w += newItemVirtualRectangle.Rect.w + p0;
			mVirtualRectangle.Rect.h = MAXIMUM(mVirtualRectangle.Rect.h, newItemVirtualRectangle.Rect.h);
			return out;
		}
	public:
		//! Constructor
		HBoxWidget(int virtualTopLeftX, int virtualTopLeftY, int padding) : BoxWidget(virtualTopLeftX, virtualTopLeftY, padding) {
			// NOOP
		}
	};
}