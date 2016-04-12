#pragma once

#include "logUtils\logger.h"
#include "constants.h"
#include <sstream>

namespace vortex {
	/// Represents an object that can be initialized/disposed outside the constructor/destructor life-cycle.
	class IDisposableObject {
	protected:
		static int sObjectsCreated; //!< Debug: Counts the number of objects created
		static int sObjectsInitialized; //!< Debug: Counts the number of objects initialized
		static int sObjectsDisposed; //!< Debug: Counts the number of objects disposed
		static int sObjectsDeleted; //!< Debug: Counts the number of objects deleted
	public:
		/// Constructor
		IDisposableObject() {
			// NOOP
			sObjectsCreated++;
		}
		/// Destructor
		virtual ~IDisposableObject() {
			// NOOP
			sObjectsDeleted++;
		}
	protected:
		//! Must be implemented in derived class
		virtual void _initialize() = 0;
		//! Must be implemented in derived class
		virtual void _dispose() = 0;
	private:
		bool mInitialized = false; //!< Is this object initialized?
	public:
		//! On program exit, checks if there are zombie objects.
		static void debugCheck() {
			std::ostringstream oss;
			if (Constants::DEBUG_ENABLE && Constants::DEBUG_VERBOSE) {
				oss << TR("IDisposable created  = ") << sObjectsCreated;
				Logger::d(oss.str());
				oss.str("");
				oss.clear();
				oss << TR("IDisposable deleted  = ") << sObjectsDeleted;
				Logger::d(oss.str());
				oss.str("");
				oss.clear();
				oss << TR("IDisposable initial. = ") << sObjectsInitialized;
				Logger::d(oss.str());
				oss.str("");
				oss.clear();
				oss << TR("IDisposable disposed = ") << sObjectsDisposed;
				Logger::d(oss.str());
			}
			// Always check
			if (sObjectsDeleted < (sObjectsCreated - 1)) { // -1 to allow GameMain to be a singleton.
				Logger::w(TR("Some of the IDisposableObject that have been created haven't been destroyed."));
			}
			if (sObjectsDisposed < sObjectsInitialized) {
				Logger::w(TR("Some of the IDisposableObject that have been initialized haven't been disposed."));
			}
		}
		//! Throws exception if the object is not ready
		void throwIfNotDisposed() {
			if (mInitialized) {
				throw DeletedButStillInitializedException();
			}
		}
		//! Initializes the object after construction.
		void initialize() {
			if (mInitialized) {
				Logger::w(TR("This object is already initialized."));
				//throw AlreadyInitializedException();
				return;
			}
			sObjectsInitialized++;
			_initialize();
			mInitialized = true;
		}
		//! Disposes the object before destruction.
		void dispose() {
			if (!mInitialized) {
				Logger::w(TR("This object is not initialized."));
				//throw NotInitializedException();
				return;
			}
			sObjectsDisposed++;
			_dispose();
			mInitialized = false;
		}
	};

	/// Use this function as replacement for "delete mObj;", as mObj = static_cast<ObjClass*>(DELETE_OBJECT(mObj));
	inline IDisposableObject *DELETE_OBJECT(IDisposableObject *obj) {
		if (obj == nullptr) { return nullptr; }
		obj->dispose();
		delete obj;
		return nullptr;
	}
	
	/// Non-abstract test object for the IDisposableObject class.
	class TestDisposableObject : public IDisposableObject {
	protected:
		void _initialize() override { 
			LOG_FUNC();
		}
		void _dispose() override { 
			LOG_FUNC();
		}
		public:
			TestDisposableObject() : IDisposableObject() {
				LOG_FUNC();
			}
			~TestDisposableObject() {
				LOG_FUNC();
			}

	};
}
