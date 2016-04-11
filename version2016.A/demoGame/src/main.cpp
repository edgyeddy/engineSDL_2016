

// Using SDL and standard IO
#include "gameMain.h"
#include "vortexUtils\exception.h"
#include "logUtils\logger.h"
#include "threadUtils\threadUtils.h"
/*
#include "sceneManager.h"
*/

// SDL2main.dll contains the WinMain() function that will call our main() function.
int main(int argc, char* args[])
{
	try {
		// Get (create) a game master instance
		vortex::GameMain *master = vortex::GameMain::getInstance();

		throw vortex::NotImplementedException();
/*
		// Prepare SDL window
		master->initialize();
		// Load initial scene
		master->loadScene(vortex::SceneManager::SceneType::SCENE_SPLASH);
		// Execute main event loop	
		master->mainLoop();
		// Release SDL resources
		master->dispose();
		// object master has been disposed but it is still alive, as it is a singleton.
		master = nullptr;
*/
	} 
	catch (vortex::Exception &ex) {
		vortex::Logger::e(ex);
		vortex::ThreadUtils::SleepThisThreadSeconds(3);
	}
	catch (std::exception &ex) {
		vortex::Logger::e(ex);
		vortex::ThreadUtils::SleepThisThreadSeconds(3);
	}
	return 0;
}