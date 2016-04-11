#include "IDisposableObject.h"
namespace vortex {
	int IDisposableObject::sObjectsCreated = 0;
	int IDisposableObject::sObjectsInitialized = 0;
	int IDisposableObject::sObjectsDisposed = 0;
	int IDisposableObject::sObjectsDeleted = 0;
}