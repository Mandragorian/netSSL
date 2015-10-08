/*Create read/write BIO */
bio = BIO_new(BIO_s_mem());

/*Create a read only BIO using allocated buffer */
buffer = new char[4096];
//buffer = malloc(4096) for C
bio = BIO_new_mem_buf(buffer,4096);

/*Create read only BIO using C-style string */
bio = BIO_new_mem_buf("This is a read-only buffer",-1);

/*Get a pointer to a memory BIO's memory segment */
BIOS_get_mem_ptr(bio,&buffer);

/*Prevent memory BIO from destroying its memory segment when it
 * is destroyed
 */
BIO_set_close(bio,BIO_noclose);
