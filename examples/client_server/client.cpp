#include "common.h"
#include "stdio.h"
#include <string.h>
#include <iostream>

#define CIPHER_LIST "ALL: !ADH: !LOW: !EXP: !MD5: @STRENGTH"
#define CAFILE "../../certificates/rootcert.pem"
#define CADIR nullptr
#define CERTFILE "../../certificates/client.pem"

const int VERDEPTH = 4;

SSL_CTX *setup_client_ctx()
{

	SSL_CTX *ctx;

	ctx = SSL_CTX_new(SSLv23_method());
	if(SSL_CTX_load_verify_locations(ctx, CAFILE, CADIR) != 1)
		int_error("Errpr laoding CA  file and/or directory");
	if(SSL_CTX_set_default_verify_paths(ctx) != 1)
		int_error("Error loading default CA file and/or directory");
	if(SSL_CTX_use_certificate_chain_file(ctx,CERTFILE) != 1)
		int_error("Error loading certificate from file");
	if(SSL_CTX_use_PrivateKey_file(ctx,CERTFILE,SSL_FILETYPE_PEM) != 1)
		int_error("Error loading key from file");

	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	SSL_CTX_set_verify_depth(ctx, VERDEPTH);
	SSL_CTX_set_options(ctx, SSL_OP_ALL|SSL_OP_NO_SSLv2);
	if(SSL_CTX_set_cipher_list(ctx,CIPHER_LIST) != 1)
		int_error("Error setting cipher list");
	return ctx;
}


int do_client_loop(SSL *ssl)
{
	int err, nwritten;
	char buf[80];

	for(;;)
	{
		if(!fgets(buf,sizeof(buf), stdin))
			break;
		for(nwritten = 0; nwritten < sizeof(buf); nwritten+=err)
		{
			err = SSL_write(ssl, buf + nwritten, strlen(buf) - nwritten);
			if(err <= 0)
				return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	BIO *conn;
	SSL *ssl;
	SSL_CTX *ctx;
	long err;


	init_OpenSSL();
	//seed_prng();
	std::cout << "after init functions" << std::endl;
	ctx = setup_client_ctx();

	conn = BIO_new_connect( SERVER ":" PORT);
	if(!conn)
		int_error("Error creating connection BIO");

	if(BIO_do_connect(conn) <= 0)
		int_error("Error connecting to remote machine");

	if(!(ssl = SSL_new(ctx)))
		int_error("Error creating ssl context");
	SSL_set_bio(ssl,conn,conn);
	if(SSL_connect(ssl) <= 0 )
		int_error("Error connecting SSL object");
	if ((err = post_connection_check(ssl,SERVER "")) != X509_V_OK)
	{
		std::cerr << "-Error: peer certificate: " << X509_verify_cert_error_string(err) <<
		        	std::endl;
		int_error("Error checking SSL object after connection");
	}
	std::cout << "SSL connection opened" << std::endl;

	if(do_client_loop(ssl))
		SSL_shutdown(ssl);
	else
		SSL_clear(ssl);
	std::cout << "SSL connection closed" << std::endl;

	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return 0;
}

