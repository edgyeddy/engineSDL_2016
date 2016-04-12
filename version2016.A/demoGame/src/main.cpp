// Using SDL and standard IO
#include "mySceneManager.h"
#include "gameMain.h"
#include "vortexUtils\exception.h"
#include "logUtils\logger.h"
#include "threadUtils\threadUtils.h"
#include "IDisposableObject.h"

// SDL2main.dll contains the WinMain() function that will call our main() function.
int main(int argc, char* args[])
{
	try {
		vortex::Logger::d(TR("Program starts..."));
		// Get (create) a game main instance
		vortex::GameMain *master = vortex::GameMain::getInstance();
		// Create and add a custom scene manager
		master->setSceneManager(new vortex::MySceneManager());
		// Prepare a SDL window and perform other initialization duties.
		master->initialize();
		// Load initial scene
		master->loadScene(vortex::MySceneManager::SceneTypeEnum::DEMO_SCENE);
		// Execute main event loop	
		master->mainLoop();
		// Release SDL resources and all disposable objects.
		master->dispose();
		// game main has been disposed but the object is still alive, as it is a singleton.
		master = nullptr;
		// Check life-cycles
		vortex::IDisposableObject::debugCheck();
	}
	catch (vortex::Exception &ex) {
		vortex::Logger::e(ex);
		vortex::ThreadUtils::sleepThisThreadSeconds(3);
	}
	catch (std::exception &ex) {
		vortex::Logger::e(ex);
		vortex::ThreadUtils::sleepThisThreadSeconds(3);
	}

	if (vortex::Constants::DEBUG_ENABLE) {
		vortex::Logger::d(TR("Quitting after 3 seconds."));
		vortex::ThreadUtils::sleepThisThreadSeconds(3);
	}
	else {
		vortex::Logger::d(TR("Done."));
	}
	return 0;
}