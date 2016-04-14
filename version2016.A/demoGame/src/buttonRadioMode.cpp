#include "buttonRadioMode.h"
#include "gameMain.h"
#include "demoScene.h"

namespace vortex {
	void ButtonRadioMode::onMouseClickUpEvent() {
		RadioButtonWidget::onMouseClickUpEvent();
		// Send message to scene
		GameMain::getInstance()->launchUserEvent(DemoScene::USER_EVENT_CHANGE_BACKGROUND, (int64_t)mMode, 0, false);
	}
}
