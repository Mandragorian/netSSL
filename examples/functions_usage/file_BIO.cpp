/* Create a buffered file BIO with an existing FILE object that will
 * be closed when the BIO is destroyed. */
file = fopen("filename.ext", "r+"); //file must be a FILE object from stdio.h
bio = BIO_new(BIO_s_file());
BIO_set_file(bio, file, BIO_CLOSE);

/* Create an unbuffered file BIO with an existing file descriptor
 * that will not be closed when the BIO is destroyed. */
fd = open("filename.ext", O_RDWR);
bio = BIO_new(BIO_s_fd());
BIO_set_fd(bio, fd, BIO_NOCLOSE);

/* Create a buffered file BIO with a new FILE object owned by the BIO
 * */
bio = BIO_new_file("filename.ext", "w");

/* Create an unbuffered file BIO with an existing file descriptor
 * that will be closed when the BIO is destroyed. */
fd = open("filename.ext", O_RDONLY);
bio = BIO_new_fd(fd, BIO_CLOSE);

