int RAND_load_file(const char *filename, long bytes);
int RAND_write_file(const char *filename);

/* Read 1024 bytes from /dev/random and seed the PRNG with it */
RAND_load_file("/dev/random", 1024);

/* Write a seed file */
RAND_write_file("prngseed.dat");

/* Read the seed file in its entirety and print the number of bytes
 * obtained */
nb = RAND_load_file("prngseed.dat", -1);
printf("Seeded the PRNG with %d byte(s) of data from prngseed.dat.\n", nb);

