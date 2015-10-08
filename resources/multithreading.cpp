#include <multithreading.hpp>
#include "openssl/crypto.h"
#include <new>
#include "stdlib.h"
static void locking_function (int mode, int n, const char* file, int line)
{
	if (mode & CRYPTO_LOCK)
		MUTEX_LOCK(mutex_buf[n]);
	else
		MUTEX_UNLOCK(mutex_buf[n]);
}

static unsigned long id_function()
{
	return ((unsigned long) THREAD_ID);
}


static CRYPTO_dynlock_value* dyn_create_function(const char *file, int line)
{
	CRYPTO_dynlock_value *value;

	value = new CRYPTO_dynlock_value;

	if(!value)
		return nullptr;
	MUTEX_SETUP(value->mutex);
	return value;
}

static void dyn_lock_function(int mode, CRYPTO_dynlock_value *l,
			      const char *file, int line)
{
	if(mode & CRYPTO_LOCK)
		MUTEX_LOCK(l->mutex);
	else
		MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(CRYPTO_dynlock_value *l, const char *file, int line)
{
	MUTEX_CLEANUP(l->mutex);
	delete l;
}


int THREAD_setup()
{

	MUTEX_SERROR_TYPE check;

	mutex_buf = new MUTEX_TYPE[CRYPTO_num_locks()];
	if (!mutex_buf)
		return 0;
	for(int i=0; i<CRYPTO_num_locks(); i++){
		check = MUTEX_SETUP(mutex_buf[i]);
		if(MUTEX_SETUP_ERROR(check))
			exit(1);
	}
	CRYPTO_set_id_callback(id_function);
	CRYPTO_set_locking_callback(locking_function);

	CRYPTO_set_dynlock_create_callback(dyn_create_function);
	CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
	CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);

	return 1;
}

int THREAD_cleanup()
{
	if (!mutex_buf)
		return 0;
	CRYPTO_set_id_callback(nullptr);
	CRYPTO_set_locking_callback(nullptr);
	CRYPTO_set_dynlock_lock_callback(nullptr);
	CRYPTO_set_dynlock_destroy_callback(nullptr);
	CRYPTO_set_dynlock_create_callback(nullptr);
	for(int i = 0; i< CRYPTO_num_locks(); i++)
		MUTEX_CLEANUP(mutex_buf[i]);
	delete[] mutex_buf;
	mutex_buf = nullptr;
	return 1;
}
