#define _POSIX_THREADS

#if defined(WIN32)
	#define MUTEX_TYPE HANDLE
	#define MUTEX_SETUP(x)    	(x) = CreateMutex(nullptr, false, nullptr)
	#define MUTEX_CLEANUP(x)  	CloseHandle(x)
	#define MUTEX_LOCK(x)     	WaitForSingleObject((x),INFINITE)
	#define MUTEX_UNLOCK(X)   	ReleaseMutex(x)
	#define MUTEX_SERROR_TYPE	HANDLE
	#define MUTEX_SETUP_ERROR(x)	(x) == nullptr
	#define THREAD_ID	  	GetCurrentThreadId()
#elif defined(_POSIX_THREADS)
	#include "pthread.h"
	#include "sys/types.h"

	#define MUTEX_TYPE	  	pthread_mutex_t
	#define MUTEX_SETUP(x)	  	pthread_mutex_init(&(x),nullptr)
	#define MUTEX_CLEANUP(x)  	pthread_mutex_destroy(&(x))
	#define MUTEX_LOCK(x)	  	pthread_mutex_lock(&(x))
	#define MUTEX_UNLOCK(x)	  	pthread_mutex_unlock(&(x))
	#define MUTEX_SERROR_TYPE	int
	#define MUTEX_SETUP_ERROR(x)	(x) != 0
	#define THREAD_ID	  	pthread_self()
#else
	#error MUTEX OPERATIONS MUST BE DEFINED
#endif




int THREAD_setup();
int THREAD_cleanup();


struct CRYPTO_dynlock_value{
	MUTEX_TYPE mutex;
};


static void locking_function(int mode, int n, const char * file, int line);
static unsigned long id_function();

static CRYPTO_dynlock_value* dyn_create_function(const char* file, int line);
static void dyn_lock_function(int mode, CRYPTO_dynlock_value *l, const char *file, int line);
static void dyn_destroy_function(CRYPTO_dynlock_value *l, const char* file, int line);

static MUTEX_TYPE *mutex_buf = nullptr;
