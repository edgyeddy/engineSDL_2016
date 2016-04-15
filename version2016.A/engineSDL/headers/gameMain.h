#include "IDisposableObject.h"
#include "constants.h"
#include "sceneManager.h"
#include "assetsManager.h"
#include "textManager.h"
#pragma once
namespace vortex {
	/// Single game main class. It is the entry point for our engine.
	class GameMain : public IDisposableObject {
	public:
		/// Some of the specific user events this engine can parse.
		enum EventTypeEnum {
			EVENT_PRINT_FPS,
			EVENT_REFRESH_SCREEN,
			USER_EVENTS_BASE_INDEX = 1000,
		};
	public:
		/// Contains the initial window configuration.
		class MainWindowConfig {
		public:
			std::string iconPath; //!< Path to 32x32 window icon bitmap file.
			std::string screenTitle; //!< Window title text.
			int windowWidth; //!< Window width
			int windowHeight; //!< Window height
			int fullscreen; //!< Window is fullscreen?
			int screenFlags; //!< Window SDL flags.
		public:
			//! Constructor, sets defaults values
			MainWindowConfig() {
				_init("EngineSDL", "");
			}
			MainWindowConfig(const std::string &screenTitle, const std::string &windowIconPath) {
				_init(screenTitle, windowIconPath);
			}
		protected:
			inline void _init(const std::string &screenTitle, const std::string &windowIconPath) {
				this->iconPath = windowIconPath;
				this->screenTitle = screenTitle;
				fullscreen = Constants::USE_FULLSCREEN;
				if (fullscreen) {
					windowWidth = Constants::FULLSCREEN_WINDOW_WIDTH;
					windowHeight = Constants::FULLSCREEN_WINDOW_HEIGHT;
					screenFlags = Constants::SCREEN_FLAGS_FULLSCREEN;
				}
				else {
					windowWidth = Constants::WINDOWED_WINDOW_WIDTH;
					windowHeight = Constants::WINDOWED_WINDOW_HEIGHT;
					screenFlags = Constants::SCREEN_FLAGS_WINDOWED;
				}
			}
		};
	protected:
		static GameMain *sInstance; //!< Single static instance of the game engine.
	protected:
		MainWindowConfig mInitialWindowConfig; //!< Stores the requested initial window configuration
		int mTimestampLastUpdateMs = -1; //!< Timestamp of the last update event
		int mTimestampMsLastFPS; //!< Timestamp of the last FPS string computation.
		int mNumFramesRendered; //!< Counts the number of frames drawn.
		std::string mFpsString; //!< Cached FPS string text
		SDL_TimerID mTimerFPS; //!< Timer ID to the FPS timer (needed to cancel it).
		SDL_Window* mWindow; //!< Pointer to the single window of this program
		//@ADD-NEW-MANAGERS-HERE
		AssetsManager *mAssetsManager;  //!< Pointer to the owned assets manager.
		SceneManager *mSceneManager; //!< Pointer to the owned scene manager.
		TextManager *mTextManager;  //!< Pointer to the owned text manager.
	public:
		//@ADD-NEW-MANAGERS-HERE
		inline AssetsManager *getAssetsManager() {
			return mAssetsManager;
		} //!< Getter
		inline TextManager *getTextManager() {
			return mTextManager;
		} //!< Getter
		inline SceneManager *getSceneManager() {
			return mSceneManager;
		} //!< Getter
		inline MainWindowConfig &getMainWindowConfigRef() {
			return mInitialWindowConfig;
		}
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		void computeFpsString(); //!< Generates and stores the FPS string
		std::string getFpsString(); //!< Gets the cached FPS string
		///! Launcher a user event to the event queue after a delay.
		SDL_TimerID launchUserEventAfterDelay(int delayMs, int eventId, int64_t eventData1, int64_t eventData2, bool repeat);
		///! Launcher a user event to the event queue right now.
		void launchUserEvent(int eventId, int64_t eventData1, int64_t eventData2, bool repeat);
	protected:
		/// Constructor
		GameMain();
	public:
		static GameMain *getInstance(); //!< Return the single instance of the game (engine) main.
	public:
		void setSceneManager(SceneManager *sceneManager); //!< Transfers ownership of this SceneManager instance to GameMain.
		void mainLoop(); //!< Main event loop (indefinite)
		void loadScene(int sceneId); //!< Loads the given scene
		//! Getter
		Rectangle getWindowSize();
	protected:
		void onTimeUpdate(); //!< Informs the current scene to perform a time update
		void onDraw(); //!< Redraws the main window, according to the current scene
		void onResize(int windowWidth, int windowHeight); //!< Informs the current scene that the window has been resized
	};
}
