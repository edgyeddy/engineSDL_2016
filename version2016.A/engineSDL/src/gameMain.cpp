#include "gameMain.h"
#include "SDL.h"
#include <sstream>
#include "time.h"
#include "UserEventData.h"
#include "sceneManager.h"

namespace vortex {
	GameMain *GameMain::sInstance = nullptr;

	void GameMain::_initialize() {
		vortex::Logger::d(TR("Starting the program..."));

		// The surface contained by the window
		SDL_Surface* screenSurface = nullptr;

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::ostringstream oss;
			oss << TR("SDL could not initialize! SDL_Error: ") << SDL_GetError();
			Logger::e(oss.str());
			return;
		}
		// Create window
		mWindow = SDL_CreateWindow(
			mInitialWindowConfig.screenTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			mInitialWindowConfig.windowWidth,
			mInitialWindowConfig.windowHeight,
			mInitialWindowConfig.screenFlags);

		if (mWindow == nullptr)
		{
			std::ostringstream oss;
			oss << TR("Window could not be created! SDL_Error: ") << SDL_GetError();
			Logger::e(oss.str());
			return;
		}
		// Initialize other
		srand((unsigned int)time(nullptr));

		if (mSceneManager == nullptr) {
			mSceneManager = new SceneManager();
		}
		mSceneManager->initialize();
		if (mAssetsManager == nullptr) {
			mAssetsManager = new AssetsManager();
		}
		mAssetsManager->initialize();
		if (mTextManager == nullptr) {
			mTextManager = new TextManager();
		}
		mTextManager->initialize();
		// @ADD-NEW-MANAGERS-HERE

		mTimerFPS = this->launchUserEventAfterDelay(Constants::DELAY_PRINT_FPS_MS, EventTypeEnum::EVENT_PRINT_FPS, 0, 0, true);
	}
	void GameMain::setSceneManager(SceneManager *sceneManager) {
		if (mSceneManager != nullptr) {
			throw Exception("A sceneManager is already defined.");
		}
		mSceneManager = sceneManager;
		// NOTE: The scene is not initialized yet
	}
	void GameMain::loadScene(int sceneType) {
		mSceneManager->loadScene(sceneType);
	}

	void GameMain::_dispose() {
		vortex::Logger::d(TR("Closing the program..."));

		// Release objects
		mSceneManager = static_cast<SceneManager*>(DELETE_OBJECT(mSceneManager));
		mAssetsManager = static_cast<AssetsManager*>(DELETE_OBJECT(mAssetsManager));
		mTextManager = static_cast<TextManager*>(DELETE_OBJECT(mTextManager));
		// @ADD-NEW-MANAGERS-HERE

		// Delete timer
		SDL_bool ok = SDL_RemoveTimer(mTimerFPS);
		// Wait Xs (debug)
		SDL_Delay(0);
		// Destroy main window
		SDL_DestroyWindow(mWindow);
		// Quit SDL subsystems
		SDL_Quit();
	}

	std::string GameMain::getFpsString() {
		return mFpsString;
	}
	void GameMain::computeFpsString() {
		std::ostringstream oss;
		int timestampMs = SDL_GetTicks();
		float deltaMs = (float)(timestampMs - mTimestampMsLastFPS);
		float fps = (float)(mNumFramesRendered) / ((deltaMs / 1000.0f));
		oss.precision(1);
		oss << std::fixed;
		oss << "FPS=" << fps << " frames=" << mNumFramesRendered << " time(s)=" << (deltaMs / 1000.0f); // << std::endl;
		mNumFramesRendered = 0;
		mTimestampMsLastFPS = timestampMs;
		mFpsString = oss.str();
	}
	GameMain::GameMain() {
		// NOOP
	}
	GameMain *GameMain::getInstance() {
		if (GameMain::sInstance == nullptr) {
			GameMain::sInstance = new GameMain();
		}
		return GameMain::sInstance;
	}
	Rectangle GameMain::getWindowSize() {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(mWindow);
		Rectangle out(screenSurface->w, screenSurface->h, 0, 0);
		return out;
	}
	void GameMain::mainLoop() {
		// Get window surface
		SDL_Surface* screenSurface = SDL_GetWindowSurface(mWindow);

		// Draw initial content from the current scene
		this->onResize(screenSurface->w, screenSurface->h);
		this->onDraw();

		//Main loop flag 
		vortex::Logger::d(TR("Starting event loop."));

		Uint32 windowID = SDL_GetWindowID(mWindow);
		bool quit = false;
		while (!quit) {
			// Event handler 
			SDL_Event ev;
			// Handle events on queue 
			while (SDL_PollEvent(&ev) != 0) {
				switch (ev.type) {
				case SDL_USEREVENT: {
					UserEventData *data = (UserEventData*)ev.user.data1;
					if (ev.user.code == EventTypeEnum::EVENT_PRINT_FPS) {
						computeFpsString();
						Logger::d(getFpsString());
						// NOTE: UserEventData for repeat event SHOULD NOT be released.
					}
					/*
					//void(*p) (void*) = ev.user.data1;
					//p(event.user.data2);
					if (ev.user.code == UserEventData::EVENT_CHANGE_TO_NEXT_SCREEN) {
						UserEventData *data = (UserEventData*)ev.user.data1;
						mSceneManager->loadScene((SceneManager::SceneType)data->data1);
						this->onResize(screenSurface->w, screenSurface->h);
						this->onDraw();
						delete data;
						data = nullptr;
					}
					else  */
					else {
						// Send the unkown user event to the scene for processing
						mSceneManager->getCurrentScene()->onUserEvent(data);
						delete data;
						data = nullptr;
					}
					break;
				}

				case SDL_WINDOWEVENT: {
					if (ev.window.windowID == windowID) {
						switch (ev.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED: {
							int width = ev.window.data1;
							int height = ev.window.data2;
							std::ostringstream oss;
							oss << TR("Resize screen to ") << width << " x " << height;
							vortex::Logger::d(oss.str());
							// Redraw screen
							this->onResize(width, height); // screenSurface->w, screenSurface->h);
							this->onDraw();
							break;
						}
						case SDL_WINDOWEVENT_CLOSE: {
							// Re-send quit event
							ev.type = SDL_QUIT;
							SDL_PushEvent(&ev);
							break;
						}
						} // switch
					} // if
					break;
				} // case
				case SDL_KEYUP: {
					// TODO mGameState->updateKeyState(ev.key.keysym.scancode, false);
					break;
				}

				case SDL_KEYDOWN: {
					if (ev.key.keysym.sym == SDLK_ESCAPE) {
						vortex::Logger::d(TR("Processing <ESC> keydown event."));
						quit = true;
					}
					// TODO mGameState->updateKeyState(ev.key.keysym.scancode, true);
					// TODO mSceneManager->getCurrentScene()->onKeyPressedEvent(ev.key.keysym.scancode);

					break;
				} // case
				case SDL_MOUSEMOTION:
				{
					mSceneManager->getCurrentScene()->onMouseMovementEvent(ev.motion);
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					mSceneManager->getCurrentScene()->onMouseClickUpEvent(ev.button);
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					mSceneManager->getCurrentScene()->onMouseClickDownEvent(ev.button);
					break;
				}
				case SDL_QUIT: {
					vortex::Logger::d(TR("Processing QUIT event."));
					quit = true;
					break;
				} // case
				} // switch
			} // while1
			  // Update scene (animations, ...)
			this->onTimeUpdate();
			// Render scene (always redraw current scene)
			this->onDraw();
		} // while2
	}

	void GameMain::onTimeUpdate() {
		if (mTimestampLastUpdateMs < 0) {
			mTimestampLastUpdateMs = SDL_GetTicks();
			mSceneManager->getCurrentScene()->update(mWindow, 0);
		}
		else {
			int currentMs = SDL_GetTicks();
			int deltaMs = currentMs - mTimestampLastUpdateMs;
			if (deltaMs >= Constants::MINIMUM_UPDATE_INTERVAL_MS) {
				mTimestampLastUpdateMs = currentMs;
				mSceneManager->getCurrentScene()->update(mWindow, deltaMs);
			}
		}
	}
	void GameMain::onDraw() {

		if (mSceneManager->hasScene()) {
			mSceneManager->getCurrentScene()->draw(mWindow, true);
			mNumFramesRendered++;
		}
	}
	void GameMain::onResize(int windowWidth, int windowHeight) {
		if (mSceneManager->hasScene()) {
			mSceneManager->getCurrentScene()->resize(mWindow, windowWidth, windowHeight);
		}
	}

	void PushUserEvent(UserEventData *data) {
		SDL_Event event;
		SDL_UserEvent userevent;
		userevent.type = SDL_USEREVENT;
		userevent.code = data->type;
		userevent.data1 = data;
		userevent.data2 = nullptr;
		event.type = SDL_USEREVENT;
		event.user = userevent;
		SDL_PushEvent(&event);
	}

	Uint32 onTimerCallback(Uint32 interval, void *param) {
		UserEventData *data = (UserEventData*)param;

		PushUserEvent(data);

		if (data->repeat) {
			return(interval); // repeat timer after this delay
		}
		else {
			return 0; // cancel timer
		}
	}
	void GameMain::launchUserEvent(int eventId, int64_t eventData1, int64_t eventData2, bool repeat) {
		UserEventData *data = new UserEventData();
		data->type = eventId;
		data->data1 = eventData1;
		data->data2 = eventData2;
		data->repeat = false;
		PushUserEvent(data);
	}

	SDL_TimerID GameMain::launchUserEventAfterDelay(int delayMs, int eventId, int64_t eventData1, int64_t eventData2, bool repeat) {
		UserEventData *data = new UserEventData();
		data->type = eventId;
		data->data1 = eventData1;
		data->data2 = eventData2;
		data->repeat = repeat;
		SDL_TimerID timerId = SDL_AddTimer(delayMs, onTimerCallback, (void*)data);
		return timerId;
	}
}