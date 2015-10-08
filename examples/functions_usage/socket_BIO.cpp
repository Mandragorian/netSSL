/*Create a socket BIO attached to an already existing socket
 * descriptor.  The socket descriptor will not be closed when the BIO is
 * destroyed.
 */
bio = BIO_new(BIO_s_socket());
BIO_set_fd(bio, sd, BIO_NOCLOSE);

/* Create a socket BIO attached to an already existing socket
   descriptor.  The socket descriptor will be closed when the BIO is
   destroyed.
   */
bio = BIO_new_socket(sd, BIO_CLOSE);

/* Create a socket BIO to establish a connection to a remote host. */
bio = BIO_new(BIO_s_connect());
BIO_set_conn_hostname(bio, "www.ora.com");
BIO_set_conn_port(bio, "http");
BIO_do_connect(bio);

/* Create a socket BIO to listen for an incoming connection. */
bio = BIO_new(BIO_s_accept());
BIO_set_accept_port(bio, "https");
BIO_do_accept(bio); /* place the underlying socket into listening
		       mode */
for (;;)
{
    BIO_do_accept(bio); /* wait for a new connection */
    new_bio = BIO_pop(bio);
    /* new_bio now behaves like a BIO_s_socket() BIO */
}

