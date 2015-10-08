#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include <string>
#ifndef WIN32
#include <pthread.h>
#define THREAD_CC		       *
#define THREAD_TYPE                    pthread_t
#define THREAD_CREATE(tid, entry, arg) pthread_create(&(tid), NULL, \
                                                      (entry), (arg))
#else
#include <windows.h>
#define THREAD_CC                      _  _cdecl
#define THREAD_TYPE                    DWORD
#define THREAD_CREATE(tid, entry, arg) do { _beginthread((entry), 0, (arg)); \
					    GetCurrentThreadId(); \
					} while(0)
#endif

#define PORT            "6001"
#define SERVER          "splat.zork.org"
#define CLIENT          "shell.zork.org"

#define int_error(msg)  handle_error(__FILE__, __LINE__ , msg)
void handle_error(const char *file, int lineno, const char *msg);

void init_OpenSSL();
void seed_prng();
long post_connection_check(SSL *ssl, std::string host);
int verify_callback(int ok, X509_STORE_CTX *store);
