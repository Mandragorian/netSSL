a = BIO_new(BIO_s_bio());
BIO_set_write_buf_size(a, 4096);

b = BIO_new(BIO_s_bio());
BIO_set_write_buf_size(b, 4096);
BIO_make_bio_pair(a, b);

BIO_new_bio_pair(&a, 8192, &b, 8192);

c = BIO_new(BIO_s_bio());
BIO_set_write_buf_size(c, 1024);
BIO_destroy_bio_pair(a); /* disconnect a from b */
BIO_make_bio_pair(a, c);

